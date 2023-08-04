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

class Event
{
public:
    Event() = default;

    Event(int eventId, string title, string location, User owner, EventType type,
          vector<User> users, time_t startTime, time_t endTime)
        : eventId(eventId), title(title), location(location), owner(owner), type(type), users(users),
          startTime(startTime), endTime(endTime), accepted(false), rejected(false) {}

    int getEventId() { return eventId; }
    string getTitle() { return title; }
    void setTitle(string newTitle) { title = newTitle; }
    string getLocation() { return location; }
    void setLocation(string newLocation) { location = newLocation; }
    User getOwner() { return owner; }
    User setOwner(User newOwner) { owner = newOwner; }
    EventType getType() { return type; }
    void setEventType(EventType newType) { type = newType; }
    vector<User> getUsers() { return users; }
    void setUsers(vector<User> newUsers) { users = newUsers; }
    time_t getStartTime() { return startTime; }
    void setStartTime(time_t newStTime) { startTime = newStTime; } 
    time_t getEndTime() { return endTime; }
    void setEndTime(time_t newEdTime) { endTime = newEdTime; } 
    bool hasUser(User user) {
        for (User eventUser : users) {
            if (eventUser.getUserId() == user.getUserId()) {
                return true;
            }
        }
        return false;
    }

    void acceptEvent() {
        accepted = true;
        rejected = false;
    }

    void rejectEvent() {
        accepted = false;
        rejected = true;
    }

    bool isAccepted() { return accepted; }
    bool isNeutral() { return !accepted && !rejected; }

private:
    int eventId;
    string title;
    string location;
    User owner;
    EventType type;
    vector<User> users;
    time_t startTime;
    time_t endTime;
    bool accepted;
    bool rejected;
};
