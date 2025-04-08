**Calendar Application with Functionality Similar to Google Calendar**

Design a calendar application that mimics the features of Google Calendar. Your task is to develop a functional implementation of this application. You can use any programming language of your choice. Below are the requirements, expectations, and constraints for your implementation:

**Requirements:**

1. **Event Management:**
   - Implement functionality to create, update, and delete events.
   - An event should have attributes like start time, end time, location, owner, list of users, and title.
   - Events can be categorized as meetings (with specified location and attendee list), holidays, birthdays, reminders, etc.
   - After creation, events can be accepted or rejected by users. If no action is taken, the event remains in a neutral state.

2. **User Interface:**
   - Develop a user interface to access a user's calendar.
   - Allow users to view their events for a specific day, week, or month.

3. **Retrieve Event Details:**
   - Implement a feature to retrieve detailed information about an event, including its attributes.

4. **Identify Common Free Time Slot:**
   - Given a set of users [U1, U2, ..., Un], find a mutually available time slot for scheduling a meeting.
   - The time slot should not conflict with any of the users' existing events.

**Expectations:**

1. Your implementation should be demonstrable through either a main driver program or test cases.
2. Generate sample data that can be used to showcase your application's functionalities. You can include this data within the codebase or load it from a file.
3. Prioritize readability, modularity, testability, and extensibility in your code.
4. Use appropriate naming conventions to enhance clarity and maintain consistency.
5. Ensure that your code can easily accommodate the addition or removal of functionalities without requiring a complete rewrite.
6. Handle edge cases effectively and provide graceful error handling.

**Bonus: Recurring Events**

Implement the ability to create recurring events in the calendar application. Allow events to be scheduled on a daily, weekly, or monthly basis. Extend the existing functionalities to support recurring events and ensure that they are displayed correctly in the user interface.

**Recurring Event Requirements:**

1. When creating an event, provide an option to specify whether the event should be recurring and the recurrence pattern (daily, weekly, or monthly).

2. Recurring events should generate occurrences based on the recurrence pattern. For example, a weekly recurring event should generate occurrences every week on the same day as the original event.

3. Recurring events should be displayed in the user interface along with their occurrences. Users should be able to view the details of individual occurrences and take actions on them (accept/reject).

4. When deleting a recurring event, provide an option to delete only the specific occurrence or the entire series of recurring events.

**Expectations for Bonus:**

Extend the existing implementation to include the above requirements for recurring events. Make sure that the user interface and data management are updated to handle recurring events effectively. Handle edge cases such as updating or deleting individual occurrences while preserving the recurrence pattern.

Feel free to modify the existing directory structure and code as needed to accommodate the bonus requirement.

**Constraints:**

1. Do not rely on external data stores; load all data within the application.
2. Minimize time spent on input parsing.

Feel free to include additional features or enhancements beyond the specified requirements if you have time. Focus on creating a well-organized, functional, and user-friendly calendar application.

**Guidelines:**

You can structure your application using classes, functions, and modules as needed. Consider using object-oriented principles to organize your code effectively. You can define sample users, events, and calendars within your codebase or load them from a predefined file. Ensure that your implementation provides clear methods for performing each of the specified functionalities.

Remember, the goal is to create a working representation of a calendar application similar to Google Calendar, focusing on code quality and functionality.