## Project Management Application (Trello-like) - Problem Statement

### Basic Features and Workings:

Create an application similar to Trello, a project management tool that helps users manage projects by tracking smaller tasks. The application should have the following components:

- **Boards**: Represent different projects.
- **Lists**: Subdivide boards into stages or sub-projects.
- **Cards**: Represent smaller tasks within lists.

Each card can be assigned to a user or remain unassigned.

### Definitions:

- **User**: Each user has a `userId`, `name`, and `email`.
- **Board**: Each board has an `id`, `name`, `privacy` (PUBLIC/PRIVATE), `url`, members, and lists.
- **List**: Each list has an `id`, `name`, and cards.
- **Card**: Each card has an `id`, `name`, `description`, assigned user, `priority`, `created time`, `finished time`, `ETA`, and `status`.

### Requirements:

1. Implement functionality to create and delete boards. Deleting a board should remove all associated lists.
2. Implement functionality to add and remove members from a board's members list, and modify board attributes.
3. Implement functionality to create and delete lists. Deleting a list should remove all associated cards.
4. Implement functionality to create and delete cards, assign/unassign members to cards, and modify card attributes.
5. Allow movement of cards across lists within the same board.
6. Implement the ability to display all boards, a single board, a single list, and a single card.
7. The default privacy of boards should be public.
8. Cards should be unassigned by default.
9. Automatically generate IDs for boards, lists, and cards.

### Bonus Feature for SDE1:

Implement a **Bookmark** feature, allowing users to add cards, lists, and boards to their favorites. Users should be able to view their bookmarked items.

### Additional Complexity for SDE2:

1. Implement **Search by Filter/Sort**: Users can search, filter, and sort cards based on attributes such as assigned user, created date range, ETA, and priority.
2. Implement a **Watch** feature: Users can subscribe to changes on cards and boards and receive notifications for updates.

### Bonus for SDE2:

Handle **concurrency** when multiple users edit the same card.

### Evaluation Criteria:

- The code should be demoable and functionally correct.
- Code readability, proper entity modeling, modularity, and extensibility are important.
- Use design patterns where applicable.
- Demonstrate separation of concerns and abstractions.
- The project should use in-memory data structures without external databases.
- The main class or driver program should be able to test the code with multiple test cases.
