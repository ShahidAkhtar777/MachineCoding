#pragma once

#include <string>
#include <ctime>
#include "User.h"

class Card
{
public:
    Card(int id, string name)
        : id(id), name(name), assignedUserId(-1), priority(0), description(""),
          createdTime(0), finishedTime(0), eta(0), status("") {}

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    int getAssignedUserId()
    {
        return assignedUserId;
    }

    void assignUser(User &user)
    {
        assignedUserId = user.getUserId();
    }

    void unassignUser()
    {
        assignedUserId = -1;
    }

    int getPriority()
    {
        return priority;
    }

    void setPriority(int newPriority)
    {
        priority = newPriority;
    }

    string getDescription()
    {
        return description;
    }

    void setDescription(string newDescription)
    {
        description = newDescription;
    }

    time_t getCreatedTime()
    {
        return createdTime;
    }

    time_t getFinishedTime()
    {
        return finishedTime;
    }

    void setFinishedTime(time_t time)
    {
        finishedTime = time;
    }

    time_t getETA()
    {
        return eta;
    }

    void setETA(time_t newETA)
    {
        eta = newETA;
    }

    string getStatus()
    {
        return status;
    }

    void setStatus(string newStatus)
    {
        status = newStatus;
    }

private:
    int id;
    string name;
    int assignedUserId;
    int priority;
    string description;
    time_t createdTime;
    time_t finishedTime;
    time_t eta;
    string status;
};

