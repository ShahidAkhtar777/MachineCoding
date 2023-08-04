#pragma once
#include <unordered_map>
#include "../models/event.h"
#include <iostream>
using namespace std;

class EventRepository {
public:
    void addEvent(string title, string location, User owner, EventType type,
          vector<User> users, time_t startTime, time_t endTime) {
        int newEventId = getNextEventId();
        Event *e = new Event(newEventId, title, location, owner, type, users, startTime, endTime);
        events[newEventId] = *e;
    }
    
    void updateEvent(int eventId, string title, string location, User owner, EventType type,
          vector<User> users, time_t startTime, time_t endTime) {
        Event existingEvent = events[eventId];
        existingEvent.setTitle(title);
        existingEvent.setLocation(location);
        existingEvent.setOwner(owner);
        existingEvent.setEventType(type);
        existingEvent.setUsers(users);
        existingEvent.setStartTime(startTime);
        existingEvent.setEndTime(endTime);
    }
    
    void deleteEvent(Event event) {
        events.erase(event.getEventId());
    }
    
    Event* getEventById(int eventId) {
        auto eventIt = events.find(eventId);
        if (eventIt != events.end()) {
            return &eventIt->second;
        }
        return nullptr;
    }

    vector<Event> getEventsByDate(time_t date) {
        vector<Event> eventsForDate;
        for (auto eventPair : events) {
            Event event = eventPair.second;
            if (isEventOnDate(event.getStartTime(), event.getEndTime(), date)) {
                eventsForDate.push_back(event);
            }
        }
        return eventsForDate;
    }

    vector<Event> getEventsForUser(const User& user) {
        vector<Event> userEvents;
        for (auto eventPair : events) {
            Event event = eventPair.second;
            if (event.hasUser(user)) {
                userEvents.push_back(event);
            }
        }
        return userEvents;
    }
    
private:
    int getNextEventId() {
        static int eventIdCounter = 1; 
        return eventIdCounter++;
    }

    bool isEventOnDate(time_t timestamp1, time_t timestamp2,  time_t timestamp3) {
        tm stTime = *localtime(&timestamp1);
        tm edTime = *localtime(&timestamp2);
        tm event = *localtime(&timestamp3);

        bool year = (stTime.tm_year <= event.tm_year && event.tm_year <= edTime.tm_year);
        bool month = (stTime.tm_mon <= event.tm_mon && event.tm_mon <= edTime.tm_mon);
        bool day = (stTime.tm_mday <= event.tm_mday && event.tm_mday <= edTime.tm_mday);
        return year & month & day;
    }
    
    unordered_map<int, Event> events;
};
