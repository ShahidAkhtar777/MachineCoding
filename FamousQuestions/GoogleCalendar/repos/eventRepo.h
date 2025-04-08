#pragma once
#include <unordered_map>
#include "../models/event.h"
#include <iostream>
using namespace std;

class EventRepository {
public:
    Event* addEvent(string title, string location, User owner, EventType type,
          vector<pair<User,Status>> attendees, time_t startTime, time_t endTime) {
        int newEventId = getNextEventId();
        Event *e = new Event(newEventId, title, location, owner, type, attendees, startTime, endTime);
        events[newEventId] = *e;
        return e;
    }
    
    void updateEvent(int eventId, string title, string location, User owner, EventType type,
          vector<pair<User,Status>> attendees, time_t startTime, time_t endTime) {
        Event existingEvent = events[eventId];
        existingEvent.setTitle(title);
        existingEvent.setLocation(location);
        existingEvent.setOwner(owner);
        existingEvent.setEventType(type);
        existingEvent.setUsers(attendees);
        existingEvent.setStartTime(startTime);
        existingEvent.setEndTime(endTime);
    }
    
    void deleteEvent(int eventId) {
        events.erase(eventId);
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

    vector<Event> getAcceptedEventsForUser(int userId) {
        vector<Event> userEvents;
        for (auto eventPair : events) {
            Event event = eventPair.second;
            if (event.userAcceptedEvent(userId)) {
                userEvents.push_back(event);
            }
        }
        return userEvents;
    }

    vector<pair<Event, Status>> getAllEventsByUserId(int userId) {
        vector<pair<Event, Status>> userEvents;
        for (auto eventPair : events) {
            Event event = eventPair.second;
            Status s = event.getStatusForUser(userId);
            if(s!=Status::INVALID)
                userEvents.push_back({event, s});
        }
        return userEvents;
    }

    vector<Event> getAllEvents() {
        vector<Event> allEvents;
        for (auto eventPair : events) {
            Event event = eventPair.second;
            allEvents.push_back(event);
        }
        return allEvents;
    }

    void acceptEventForUser(int eventId, int userId){
        for (auto eventPair : events) {
            Event event = eventPair.second;
            if(eventId == event.getEventId())
                event.acceptEvent(userId);
        }
    }

    void rejectEventForUser(int eventId, int userId){
        for (auto eventPair : events) {
            Event event = eventPair.second;
            if(eventId == event.getEventId())
                event.rejectEvent(userId);
        }
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

        // Case 1: Same Yr and month
        bool yr = (stTime.tm_year == event.tm_year && event.tm_year == edTime.tm_year);
        bool mth = (stTime.tm_mon == event.tm_mon && event.tm_mon == edTime.tm_mon);
        bool dy = (stTime.tm_mday <= event.tm_mday && event.tm_mday <= edTime.tm_mday);

        if( yr && mth)
            return dy;

        // Case 2: Not same yr || month
        bool year = (stTime.tm_year <= event.tm_year && event.tm_year <= edTime.tm_year);
        bool month = (stTime.tm_mon <= event.tm_mon && event.tm_mon <= edTime.tm_mon);
        bool day = (stTime.tm_mday <= event.tm_mday && event.tm_mday <= edTime.tm_mday);
        return year && month && day;
    }
    
    unordered_map<int, Event> events; // { eventId } -> [Events]
};
