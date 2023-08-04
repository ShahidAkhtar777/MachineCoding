#pragma once
#include "../repos/eventRepo.h"
#include <iostream>
using namespace std;

class EventService {
public:
    EventService(EventRepository* eventRepository) : eventRepository(eventRepository) {}

    void createEvent(string title, string location, User owner, EventType type,
                     vector<User> users, time_t startTime, time_t endTime) {
        eventRepository->addEvent(title, location, owner, type, users, startTime, endTime);
    }

    Event *getEventById(int eventId) {
        return eventRepository->getEventById(eventId);
    }

    void updateEvent(int eventId, string title, string location, User owner, EventType type,
                     vector<User> users, time_t startTime, time_t endTime) {
        eventRepository->updateEvent(eventId, title, location, owner, type, users, startTime, endTime);
    }

    void deleteEvent(Event event) {
        eventRepository->deleteEvent(event);
    }

private:
    EventRepository* eventRepository;
};
