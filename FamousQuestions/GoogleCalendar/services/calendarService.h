#pragma once
#include "../models/event.h"
#include "../repos/eventRepo.h"
#include <iostream>
#include <algorithm>
using namespace std;

class CalendarService {
public:
    CalendarService(EventRepository* eventRepository) : eventRepository(eventRepository) {}

    vector<Event> getEventsForDay(time_t date) {
        vector<Event> events = eventRepository->getEventsByDate(date);
        // Filter events for the specified day
        vector<Event> eventsForDay;
        for (Event event : events) {
            if (isSameDay(event.getStartTime(), date)) {
                eventsForDay.push_back(event);
            }
        }
        return eventsForDay;
    }

    vector<Event> getEventsForWeek(time_t date) {
        vector<Event> events = eventRepository->getEventsByDate(date);
        // Filter events for the specified week
        vector<Event> eventsForWeek;
        time_t startOfWeek = getStartOfWeek(date); 
        time_t endOfWeek = getEndOfWeek(date);     
        for (Event event : events) {
            if (event.getStartTime() >= startOfWeek && event.getEndTime() <= endOfWeek) {
                eventsForWeek.push_back(event);
            }
        }
        return eventsForWeek;
    }

    vector<Event> getEventsForMonth(time_t date) {
        vector<Event> events = eventRepository->getEventsByDate(date);
        // Filter events for the specified month
        vector<Event> eventsForMonth;
        time_t startOfMonth = getStartOfMonth(date); 
        time_t endOfMonth = getEndOfMonth(date);     
        for (Event event : events) {
            if (event.getStartTime() >= startOfMonth && event.getEndTime() <= endOfMonth) {
                eventsForMonth.push_back(event);
            }
        }
        return eventsForMonth;
    }

    time_t findMutuallyAvailableTimeSlot(const vector<User>& users, time_t meetingDuration, time_t targetTime) {
        vector<time_t> busyTimes;
        struct tm* targetTm = localtime(&targetTime);
        targetTm->tm_hour = 0;
        targetTm->tm_min = 0;
        targetTm->tm_sec = 0;

        time_t targetDayStart = mktime(targetTm);
        time_t targetDayEnd = targetDayStart + 24 * 60 * 60;

        for (const User& user : users) {
            vector<Event> userEvents = eventRepository->getEventsForUser(user);
            for (Event event : userEvents) {
                time_t eventStartTime = event.getStartTime();
                if (eventStartTime >= targetDayStart && eventStartTime <= targetDayEnd) {
                    busyTimes.push_back(eventStartTime);
                    busyTimes.push_back(event.getEndTime());
                }
            }
        }

        struct tm* targetTm = localtime(&targetTime);
        targetTm->tm_hour = 0;
        targetTm->tm_min = 0;
        targetTm->tm_sec = 0;
        time_t targetBeginningOfDay = mktime(targetTm);
        targetTm->tm_hour = 23;
        targetTm->tm_min = 59;
        targetTm->tm_sec = 59;
        time_t targetEndOfDay = mktime(targetTm);

        busyTimes.push_back(targetBeginningOfDay);
        busyTimes.push_back(targetEndOfDay);

        sort(busyTimes.begin(), busyTimes.end());

        for (size_t i = 1; i < busyTimes.size(); ++i) {
            time_t previousEndTime = busyTimes[i - 1];
            time_t currentStartTime = busyTimes[i];
            if (currentStartTime - previousEndTime >= meetingDuration) {
                return previousEndTime;
            }
        }

        return -1;
    }

    

private:
    EventRepository* eventRepository;
    
    bool isSameDay(time_t timestamp1, time_t timestamp2) {
        struct tm tm1 = *localtime(&timestamp1);
        struct tm tm2 = *localtime(&timestamp2);
        return tm1.tm_year == tm2.tm_year && tm1.tm_mon == tm2.tm_mon && tm1.tm_mday == tm2.tm_mday;
    }

    time_t getStartOfWeek(time_t date) {
        struct tm tmDate = *localtime(&date);
        tmDate.tm_hour = 0;
        tmDate.tm_min = 0;
        tmDate.tm_sec = 0;
        tmDate.tm_wday = 0; // Sunday
        return mktime(&tmDate);
    }

    time_t getEndOfWeek(time_t date) {
        struct tm tmDate = *localtime(&date);
        tmDate.tm_hour = 23;
        tmDate.tm_min = 59;
        tmDate.tm_sec = 59;
        tmDate.tm_wday = 6; // Saturday
        return mktime(&tmDate);
    }

    time_t getStartOfMonth(time_t date) {
        struct tm tmDate = *localtime(&date);
        tmDate.tm_hour = 0;
        tmDate.tm_min = 0;
        tmDate.tm_sec = 0;
        tmDate.tm_mday = 1;
        return mktime(&tmDate);
    }

    time_t getEndOfMonth(time_t date) {
        struct tm tmDate = *localtime(&date);
        tmDate.tm_hour = 23;
        tmDate.tm_min = 59;
        tmDate.tm_sec = 59;
        tmDate.tm_mday = getLastDayOfMonth(tmDate.tm_year, tmDate.tm_mon);
        return mktime(&tmDate);
    }

    int getLastDayOfMonth(int year, int month) {
        if (month == 1) { // February
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                return 29; // Leap year
            } else {
                return 28; // Non-leap year
            }
        }
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return daysInMonth[month];
    }

};
