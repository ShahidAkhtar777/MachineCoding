#pragma once
#include <iostream>
#include "./repos/userRepo.h"
#include "./services/userService.h"
#include "./services/eventService.h"
#include "./services/calendarService.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
using namespace std;

class CalendarAppDriver {
public:
    CalendarAppDriver() : userRepository(), userService(&userRepository),
                          eventRepository(), eventService(&eventRepository),
                          calendarService(&eventRepository) {}

    void run() {
        while (true) {
            displayMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    createUser();
                    break;
                case 2:
                    createEvent();
                    break;
                case 3: 
                    updateEvent();
                    break;
                case 4:
                    getEventsForDay();
                    break;
                case 5:
                    getEventsForWeek();
                    break;
                case 6:
                    getEventsForMonth();
                    break;
                case 7:
                    findMutuallyAvailableTimeSlot();
                    break;
                case 0:
                    cout << "Exiting the Calendar App. Goodbye!" << endl;
                    return;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    break;
            }
        }
    }

private:
    UserRepository userRepository;
    UserService userService;
    EventRepository eventRepository;
    EventService eventService;
    CalendarService calendarService;

    time_t convertStringToTime(string timeStr) {
        tm tmStruct = {};
        istringstream ss(timeStr);
        ss >> get_time(&tmStruct, "%Y-%m-%d %H:%M");
        auto tp = chrono::system_clock::from_time_t(std::mktime(&tmStruct));
        return chrono::system_clock::to_time_t(tp);
    }

    void displayMenu() {
        cout << "Choose an action:" << endl;
        cout << "1. Create User" << endl;
        cout << "2. Create Event" << endl;
        cout << "3. Update Event" << endl;
        cout << "4. Get Events for Day" << endl;
        cout << "5. Get Events for Week" << endl;
        cout << "6. Get Events for Month" << endl;
        cout << "7. Find Mutually Available Time Slot" << endl;
        cout << "0. Exit" << endl;
    }

    void createUser() {
        string username;
        cout << "Enter username: ";
        cin >> username;
        userService.createUser(username);
        cout << "User created." << endl;
    }

    void createEvent() {
        string title, location;
        time_t startTime, endTime;
        int ownerId, numUsers;
        vector<User> users;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter event title: ";
        getline(cin, title);

        cout << "Enter event location: ";
        getline(cin, location);

        cout << "Enter owner user ID: ";
        cin >> ownerId;
        User *owner = userService.getUserById(ownerId);

        cout << "Enter number of users for the event: ";
        cin >> numUsers;
        for (int i = 0; i < numUsers; ++i) {
            int userId;
            cout << "Enter user " << i + 1 << " ID: ";
            cin >> userId;
            if(userService.getUserById(userId))
                users.push_back(*userService.getUserById(userId));
            else
                cout<<"User not exists\n"<<endl;
        }

        // Collect start time and end time in seconds since the epoch
        cout << "Enter start time (in seconds since epoch): ";
        cin >> startTime;
        cout << "Enter end time (in seconds since epoch): ";
        cin >> endTime;

        eventService.createEvent(title, location, *owner, EventType::MEETING, users, startTime, endTime);
        cout << "Event created." << endl;
    }

    void updateEvent() {
        int eventId;
        cout << "Enter the ID of the event you want to update: ";
        cin >> eventId;

        Event *existingEvent = eventService.getEventById(eventId);

        if (existingEvent->getEventId() != -1) {
            cout << "Enter updated event details:" << endl;

            cout << "Enter title: ";
            cin.ignore();
            string title;
            getline(cin, title);

            cout << "Enter location: ";
            string location;
            getline(cin, location);

            cout << "Enter start time (YYYY-MM-DD HH:MM): ";
            string startTimeStr;
            getline(cin, startTimeStr);
            time_t startTime = convertStringToTime(startTimeStr);

            cout << "Enter end time (YYYY-MM-DD HH:MM): ";
            string endTimeStr;
            getline(cin, endTimeStr);
            time_t endTime = convertStringToTime(endTimeStr);

            cout << "Enter owner's userId: ";
            int userId;
            cin>>userId;
            User *owner = userService.getUserById(userId);

            // Update attendees
            int numAttendees;
            cout << "Enter the number of attendees: ";
            cin >> numAttendees;
            cin.ignore();
            vector<User> attendees;
            for (int i = 0; i < numAttendees; ++i) {
                cout << "Enter userId of attendee " << i + 1 << ": ";
                int attendeeId;
                cin>>attendeeId;
                User *attendee = userService.getUserById(attendeeId);
                attendees.push_back(*attendee);
            }

            // Update event type
            int eventTypeInt;
            cout << "Select event type:" << endl;
            cout << "1. Meeting" << endl;
            cout << "2. Appointment" << endl;
            cout << "3. Reminder" << endl;
            cout << "Enter the number corresponding to the event type: ";
            cin >> eventTypeInt;
            EventType eventType;
            switch (eventTypeInt) {
                case 1:
                    eventType = EventType::MEETING;
                    break;
                case 2:
                    eventType = EventType::BIRTHDAY;
                    break;
                case 3:
                    eventType = EventType::REMINDER;
                    break;
                case 4: 
                    eventType = EventType::HOLIDAY;
                    break;
                default:
                    cout << "Invalid event type. Setting to Meeting by default." << endl;
                    eventType = EventType::MEETING;
                    break;
            }

            eventService.updateEvent(eventId, title, location, *owner, eventType, attendees, startTime, endTime);
            cout << "Event updated successfully:" << endl;
        } else {
            cout << "Event with ID " << eventId << " not found." << endl;
        }
    }


    void displayEvents(vector<Event> events) {
        for (Event event : events) {
            cout << "Event ID: " << event.getEventId() << endl;
            cout << "Title: " << event.getTitle() << endl;
            cout << "Location: " << event.getLocation() << endl;
            cout << "Owner: " << event.getOwner().getUsername() << endl;
            cout << "Type: ";
            switch (event.getType()) {
                case EventType::MEETING:
                    cout << "Meeting";
                    break;
                case EventType::HOLIDAY:
                    cout << "Holiday";
                    break;
                case EventType::BIRTHDAY:
                    cout << "Birthday";
                    break;
                case EventType::REMINDER:
                    cout << "Reminder";
                    break;
            }
            cout << endl;
            
            cout << "Users: ";
            for (User user : event.getUsers()) {
                cout << user.getUsername() << ", ";
            }
            cout << endl;
            
            cout << "Start Time: " << event.getStartTime();
            cout << "End Time: " << event.getEndTime();
            cout << "Accepted: " << (event.isNeutral() ? "Neutral" : (event.isAccepted() ? "Accepted" : "Rejected")) << endl;
            
            cout << "--------------------------" << endl;
        }
    }

    void getEventsForDay() {
        time_t currentDate = time(0);
        vector<Event> eventsForDay = calendarService.getEventsForDay(currentDate);
        cout << "Events for the day:" << endl;
        displayEvents(eventsForDay);
    }

    void getEventsForWeek() {
        time_t currentDate = time(0);
        vector<Event> eventsForWeek = calendarService.getEventsForWeek(currentDate);
        cout << "Events for the week:" << endl;
        displayEvents(eventsForWeek);
    }

    void getEventsForMonth() {
        time_t currentDate = time(0);
        vector<Event> eventsForMonth = calendarService.getEventsForMonth(currentDate);
        cout << "Events for the month:" << endl;
        displayEvents(eventsForMonth);
    }

    void findMutuallyAvailableTimeSlot() {
        int numUsers;
        cout << "Enter number of users: ";
        cin >> numUsers;
        vector<User> users;
        for (int i = 0; i < numUsers; ++i) {
            int userId;
            cout << "Enter user " << i + 1 << " ID: ";
            cin >> userId;
            User* user = userService.getUserById(userId);
            if (user) {
                users.push_back(*user);
            } else {
                cout << "User not exists\n" << endl;
            }
        }

        time_t meetingDuration;
        cout << "Enter meeting duration (in seconds): ";
        cin >> meetingDuration;

        // Input the desired day for the meeting
        int year, month, day;
        cout << "Enter the year for the desired day: ";
        cin >> year;
        cout << "Enter the month for the desired day (1-12): ";
        cin >> month;
        cout << "Enter the day for the desired day: ";
        cin >> day;

        // Construct the target date for the meeting
        tm targetDate = {0, 0, 0, day, month - 1, year - 1900};
        time_t targetTime = mktime(&targetDate);

        time_t mutuallyAvailableTime = calendarService.findMutuallyAvailableTimeSlot(users, meetingDuration, targetTime);
        if (mutuallyAvailableTime != -1) {
            cout << "Mutually available time slot found: " << ctime(&mutuallyAvailableTime);
        } else {
            cout << "No mutually available time slot found." << endl;
        }
    }
};
