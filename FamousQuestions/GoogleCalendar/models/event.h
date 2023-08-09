#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "user.h"
using namespace std;

enum class EventType
{
    MEETING,
    HOLIDAY,
    BIRTHDAY,
    REMINDER
};

enum class Status
{
    ACCEPTED,
    REJECTED,
    NEUTRAL,
    INVALID
};

class Event
{
public:
    Event() = default;

    Event(int eventId, string title, string location, User owner, EventType type,
          vector<pair<User,Status>> attendees, time_t startTime, time_t endTime)
        : eventId(eventId), title(title), location(location), owner(owner), type(type), attendees(attendees),
          startTime(startTime), endTime(endTime) {}

    int getEventId() { return eventId; }
    
    string getTitle() { return title; }
    void setTitle(string newTitle) { title = newTitle; }
    
    string getLocation() { return location; }
    void setLocation(string newLocation) { location = newLocation; }
    
    User getOwner() { return owner; }
    User setOwner(User newOwner) { owner = newOwner; }

    EventType getType() { return type; }
    void setEventType(EventType newType) { type = newType; }

    vector<pair<User,Status>> getUsers() { return attendees; }
    void setUsers(vector<pair<User,Status>> newUsers) { attendees = newUsers; }

    time_t getStartTime() { return startTime; }
    void setStartTime(time_t newStTime) { startTime = newStTime; } 

    time_t getEndTime() { return endTime; }
    void setEndTime(time_t newEdTime) { endTime = newEdTime; } 

    bool hasUser(int userId) {
        for (auto attendee : attendees) {
            if (attendee.first.getUserId() == userId) {
                return true;
            }
        }
        return false;
    }

    bool userAcceptedEvent(int userId) {
        for (auto attendee : attendees) {
            if (attendee.first.getUserId() == userId && attendee.second == Status::ACCEPTED) {
                return true;
            }
        }
        return false;
    }

    Status getStatusForUser(int userId){
        for (auto attendee : attendees) {
            if (attendee.first.getUserId() == userId) {
                return attendee.second;
            }
        }
        return Status::INVALID;
    }

    void acceptEvent(int userId) {
        for (auto attendee : attendees) {
            if (attendee.first.getUserId() == userId) {
                attendee.second = Status::ACCEPTED;
            }
        }
    }

    void rejectEvent(int userId) {
        for (auto attendee : attendees) {
            if (attendee.first.getUserId() == userId) {
                attendee.second = Status::REJECTED;
            }
        }
    }

private:
    int eventId;
    string title;
    string location;
    User owner;
    EventType type;
    vector<pair<User, Status>> attendees; // user, attepted_status
    time_t startTime;
    time_t endTime;
};
