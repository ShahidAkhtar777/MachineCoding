#pragma once
#include "../repos/eventRepo.h"
#include <iostream>
using namespace std;

class EventService {
public:
    EventService(EventRepository* eventRepository) : eventRepository(eventRepository) {}

    Event* createEvent(string title, string location, User owner, EventType type,
                     vector<pair<User,Status>> users, time_t startTime, time_t endTime) {

        if(startTime >= endTime){
            cout<<"startTime should be greater than endTime\n";
            return nullptr;
        }
        return eventRepository->addEvent(title, location, owner, type, users, startTime, endTime);
    }

    Event *getEventById(int eventId) {
        return eventRepository->getEventById(eventId);
    }

    vector<Event> getUserAcceptedEvents(int userId) {
        return eventRepository->getAcceptedEventsForUser(userId);
    }

    vector<pair<Event, Status>> getAllUserEvents(int userId) {
        return eventRepository->getAllEventsByUserId(userId);
    }

    void updateEvent(int eventId, string title, string location, User owner, EventType type,
                     vector<pair<User,Status>> users, time_t startTime, time_t endTime) {
        eventRepository->updateEvent(eventId, title, location, owner, type, users, startTime, endTime);
    }

    void deleteEvent(int eventId) {
        eventRepository->deleteEvent(eventId);
    }

    void acceptEventForUser(int eventId, int userId) {
        eventRepository->acceptEventForUser(eventId, userId);
    }

    void rejectEventForUser(int eventId, int userId) {
        eventRepository->rejectEventForUser(eventId, userId);
    }

private:
    EventRepository* eventRepository;
};
