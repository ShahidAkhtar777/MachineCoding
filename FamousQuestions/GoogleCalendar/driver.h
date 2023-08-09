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
#include <string>
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
                case 8: 
                    displayUsersEvents();
                    break;
                case 9: 
                    acceptRejectUserEvent();
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

    time_t convertStringToDay(string timeStr) {
        tm tmStruct = {};
        istringstream ss(timeStr);
        ss >> get_time(&tmStruct, "%Y-%m-%d");
        auto tp = chrono::system_clock::from_time_t(std::mktime(&tmStruct));
        return chrono::system_clock::to_time_t(tp);
    }

    void displayMenu() {
        cout << "Choose an action:" << endl;
        cout << "\t" << "1. Create User" << endl;
        cout << "\t" << "2. Create Event" << endl;
        cout << "\t" << "3. Update Event" << endl;
        cout << "\t" << "4. Get Events for Day" << endl;
        cout << "\t" << "5. Get Events for Week" << endl;
        cout << "\t" << "6. Get Events for Month" << endl;
        cout << "\t" << "7. Find Mutually Available Time Slot" << endl;
        cout << "\t" << "8. Display User's All Events" <<endl;
        cout << "\t" << "9. Accept/Reject an Event for User" << endl;
        cout << "\t" << "0. Exit" << endl;
    }

    void createUser() {
        string username;
        cout << "Enter username: ";
        cin >> username;
        User *u = userService.createUser(username);
        if(u)
            cout << "User created with userId: " << u->getUserId() << endl;
        else
            cout<< "Something went wrong." <<endl;
    }

    void createEvent() {
        string title, location;
        int ownerId, numUsers;
        vector<pair<User, Status>> users;

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
                users.push_back({*userService.getUserById(userId), Status::NEUTRAL});
            else
                cout<<"User not exists\n"<<endl;
        }

        // Collect start time and end time in seconds since the epoch
        cout << "Enter start time (YYYY-MM-DD HH:MM): ";
        string startTimeStr;
        getline(cin, startTimeStr);
        time_t startTime = convertStringToTime(startTimeStr);
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Enter end time (YYYY-MM-DD HH:MM): ";
        string endTimeStr;
        getline(cin, endTimeStr);
        time_t endTime = convertStringToTime(endTimeStr);

        Event *e = eventService.createEvent(title, location, *owner, EventType::MEETING, users, startTime, endTime);
        if(e)
            cout << "Event created with eventId: " << e->getEventId() << endl;
        else    
            cout << "Something went wrong. Please try again." << endl;
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

            cout << "Enter owner's userId: ";
            int userId;
            cin>>userId;
            User *owner = userService.getUserById(userId);

            // Update attendees
            int numAttendees;
            cout << "Enter the number of attendees: ";
            cin >> numAttendees;
            cin.ignore();
            vector<pair<User,Status>> attendees;
            for (int i = 0; i < numAttendees; ++i) {
                cout << "Enter userId of attendee " << i + 1 << ": ";
                int attendeeId;
                cin>>attendeeId;
                User *attendee = userService.getUserById(attendeeId);
                attendees.push_back({*attendee, Status::NEUTRAL});
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

            cout << "Enter start time (YYYY-MM-DD HH:MM): ";
            string startTimeStr;
            getline(cin, startTimeStr);
            time_t startTime = convertStringToTime(startTimeStr);

            // Clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter end time (YYYY-MM-DD HH:MM): ";
            string endTimeStr;
            getline(cin, endTimeStr);
            time_t endTime = convertStringToTime(endTimeStr);

            eventService.updateEvent(eventId, title, location, *owner, eventType, attendees, startTime, endTime);
            cout << "Event updated successfully:" << endl;
        } else {
            cout << "Event with ID " << eventId << " not found." << endl;
        }
    }


    void displayUsersEvents() {
        cout << "Enter UserID: ";
        int userId;
        cin>>userId;

        vector<pair<Event, Status>> allUserEvents = eventService.getAllUserEvents(userId);
        for(auto event: allUserEvents) {
            Status type = event.second;
            string userStatus;
            switch(type){
                case(Status::ACCEPTED):
                    userStatus = "Accepted";
                    break;
                case(Status::REJECTED):
                    userStatus = "Rejected";
                    break;
                case(Status::NEUTRAL):
                    userStatus = "Neutral";
                    break;
            }
            cout<< "Event Id: " << event.first.getEventId() << ", Status: " << userStatus << 
            ", Start: " << event.first.getStartTime() << ", End: " << event.first.getEndTime() <<endl; 
        }
    }

    void acceptRejectUserEvent() {
        cout << "Enter UserID: \n";
        int userId;
        cin>>userId;
        cout << "Enter EventID: \n";
        int eventId;
        cin>>eventId;

        char status; 
        cout << "Enter (A) Accept (R) Reject\n";
        cin>>status;
        if(status == 'A' || status == 'a')
            eventService.acceptEventForUser(eventId, userId);
        else if(status == 'R' || status == 'r') {
            eventService.rejectEventForUser(eventId, userId);
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
            for (auto user : event.getUsers()) {
                Status type = user.second;
                string userStatus;
                switch(type){
                    case(Status::ACCEPTED):
                        userStatus = "Accepted";
                        break;
                    case(Status::REJECTED):
                        userStatus = "Rejected";
                        break;
                    case(Status::NEUTRAL):
                        userStatus = "Neutral";
                        break;
                }
                cout << "\t" << user.first.getUsername() << ": " << userStatus << "\n";
            }
            cout << endl;
            cout << "Start Time: " << event.getStartTime();
            cout << "End Time: " << event.getEndTime();
            cout << "--------------------------" << endl;
        }
    }

    void getEventsForDay() {
        cout << "Enter date (YYYY-MM-DD): ";
        string eventDateStr;
        getline(cin, eventDateStr);
        time_t eventDate = convertStringToDay(eventDateStr);
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<Event> eventsForDay = calendarService.getEventsForDay(eventDate);
        cout << "Events for the day:" << endl;
        displayEvents(eventsForDay);
    }

    void getEventsForWeek() {
        cout << "Enter any date in that week (YYYY-MM-DD): ";
        string eventDateStr;
        getline(cin, eventDateStr);
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        time_t eventDate = convertStringToDay(eventDateStr);
        vector<Event> eventsForWeek = calendarService.getEventsForWeek(eventDate);
        cout << "Events for the week:" << endl;
        displayEvents(eventsForWeek);
    }

    void getEventsForMonth() {
        cout << "Enter any date in that month (YYYY-MM-DD): ";
        string eventDateStr;
        getline(cin, eventDateStr);
        time_t eventDate = convertStringToDay(eventDateStr);
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<Event> eventsForMonth = calendarService.getEventsForMonth(eventDate);
        cout << "Events for the month:" << endl;
        displayEvents(eventsForMonth);
    }

    void findMutuallyAvailableTimeSlot() {
        int numUsers;
        cout << "Enter number of users: ";
        cin >> numUsers;
        vector<int> userIds;
        for (int i = 0; i < numUsers; ++i) {
            int userId;
            cout << "Enter user " << i + 1 << " ID: ";
            cin >> userId;
            User* user = userService.getUserById(userId);
            if (user) {
                userIds.push_back(userId);
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

        time_t mutuallyAvailableTime = calendarService.findMutuallyAvailableTimeSlot(userIds, meetingDuration, targetTime);
        if (mutuallyAvailableTime != -1) {
            cout << "Mutually available time slot found: " << ctime(&mutuallyAvailableTime);
        } else {
            cout << "No mutually available time slot found." << endl;
        }
    }
};
