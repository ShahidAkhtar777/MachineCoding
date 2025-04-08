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
        vector<Event> eventsForDay = eventRepository->getEventsByDate(date);
        return eventsForDay;
    }

    vector<Event> getEventsForWeek(time_t date) {
        vector<Event> events = eventRepository->getAllEvents();
        
        vector<Event> eventsForWeek;
        time_t startOfWeek = getStartOfWeek(date); 
        time_t endOfWeek = getEndOfWeek(date);     
        for (Event event : events) {
            if (event.getStartTime() > endOfWeek || event.getEndTime() < startOfWeek) {
                continue;
            } else {
                eventsForWeek.push_back(event);
            }
        }
        return eventsForWeek;
    }

    vector<Event> getEventsForMonth(time_t date) {
        vector<Event> events = eventRepository->getEventsByDate(date);

        vector<Event> eventsForMonth;
        time_t startOfMonth = getStartOfMonth(date); 
        time_t endOfMonth = getEndOfMonth(date);     
        for (Event event : events) {
            if (event.getStartTime() > endOfMonth || event.getEndTime() < startOfMonth) {
                continue;
            } else {
                eventsForMonth.push_back(event);
            }
        }
        return eventsForMonth;
    }

    time_t findMutuallyAvailableTimeSlot(vector<int> userIds, time_t meetingDuration, time_t targetTime) {
        vector<pair<time_t, time_t>> busyTimes;
        vector<pair<time_t, time_t>> freeTimes;
        tm* targetTm = localtime(&targetTime);
        targetTm->tm_hour = 0;
        targetTm->tm_min = 0;
        targetTm->tm_sec = 0;

        time_t targetDayStart = mktime(targetTm);
        time_t targetDayEnd = targetDayStart + 24 * 60 * 60;

        for (auto userId : userIds) {
            vector<Event> userEvents = eventRepository->getAcceptedEventsForUser(userId);
            for (Event event : userEvents) {
                time_t eventStartTime = event.getStartTime();
                time_t eventEndTime = event.getEndTime();
                if (eventStartTime >= targetDayStart && eventEndTime <= targetDayEnd) {
                    busyTimes.push_back({eventStartTime, eventEndTime});
                }
            }
        }

        sort(busyTimes.begin(), busyTimes.end());

        time_t lastEndTime = targetDayStart;
        time_t maxEventEndTime = targetDayStart;

        for (size_t i = 0; i < busyTimes.size(); ++i) {
            time_t previousEndTime = lastEndTime;
            time_t currentStartTime = busyTimes[i].first;
            maxEventEndTime = max(maxEventEndTime, busyTimes[i].second);
            if (currentStartTime > previousEndTime) {
                freeTimes.push_back({previousEndTime, currentStartTime});
            }
            lastEndTime = busyTimes[i].second;
        }

        if(maxEventEndTime!=targetDayEnd)
            freeTimes.push_back({maxEventEndTime, targetDayEnd});

        for(auto freeSlot: freeTimes){
            if(freeSlot.second - freeSlot.first >= meetingDuration)
                return freeSlot.first;
        }

        return -1;
    }
    
private:
    EventRepository* eventRepository;

    time_t getStartOfWeek(time_t date) {
        tm tmDate = *localtime(&date);
        tmDate.tm_hour = 0;
        tmDate.tm_min = 0;
        tmDate.tm_sec = 0;
        tmDate.tm_wday = 0; // Sunday
        return mktime(&tmDate);
    }

    time_t getEndOfWeek(time_t date) {
        tm tmDate = *localtime(&date);
        tmDate.tm_hour = 23;
        tmDate.tm_min = 59;
        tmDate.tm_sec = 59;
        tmDate.tm_wday = 6; // Saturday
        return mktime(&tmDate);
    }

    time_t getStartOfMonth(time_t date) {
        tm tmDate = *localtime(&date);
        tmDate.tm_hour = 0;
        tmDate.tm_min = 0;
        tmDate.tm_sec = 0;
        tmDate.tm_mday = 1;
        return mktime(&tmDate);
    }

    time_t getEndOfMonth(time_t date) {
        tm tmDate = *localtime(&date);
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
