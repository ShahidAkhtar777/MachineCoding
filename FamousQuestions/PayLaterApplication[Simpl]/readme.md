
# Pay-Later Service CLI

Welcome to the Pay-Later Service CLI, a simple command-line interface for a pay-later service. This application allows users to make transactions with merchants, manage credit limits, and perform various reporting functions.

## Getting Started

### Prerequisites

Before you begin, ensure you have the following installed:

- Go (Golang)
- Git (optional)

### Installation

Clone the repository to your local machine (if you haven't already):

```bash
git clone <repository_url>
```

Build the application:

```bash
go build
```

### Usage

Run the application:

```bash
./PayLaterApplication
```

Once the application is running, you can enter various commands to interact with the Pay-Later Service.

#### Available Commands

- `new user <name> <email> <creditLimit>`: Create a new user with a name, email, and credit limit.
- `new merchant <name> <discountPercent>`: Create a new merchant with a name and discount percentage.
- `new txn <userID> <merchantID> <amount>`: Perform a transaction between a user and a merchant.
- `update merchant <merchantID> <newDiscountPercent>`: Update the discount percentage for a merchant.
- `payback user <userID> <paybackAmount>`: Allow a user to pay back their dues (full or partial).
- `report discount <merchantID>`: Generate a report of the total discount received from a specific merchant.
- `report dues <userID>`: Generate a report of dues for a specific user.
- `report users-at-credit-limit`: Generate a report of users who have reached their credit limit.
- `report total-dues`: Generate a report of the total dues from all users together.
- `exit`: Exit the Pay-Later Service CLI.
- `help`: Display a list of available commands.

## Contributing

If you'd like to contribute to this project, please follow the standard GitHub Fork and Pull Request workflow.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

