# Creating a Simple Deferred Payment System

# Table of Contents
- [Introduction](#introduction)
- [Constraints](#constraints)
- [Usage Scenarios](#usage-scenarios)
- [Additional Features](#additional-features)
- [Focus Areas](#focus-areas)
- [Sample Input/Output](#sample-inputoutput)
- [Example Workflow](#example-workflow)

## Introduction

Our system serves as a deferred payment service, enabling users to make immediate purchases from merchants and settle the payments at a later date. This document outlines the core functionalities, constraints, and usage scenarios of our service.

## Constraints

Our service operates within these fundamental constraints:

- **Merchant Discounts**: In each transaction processed through our platform, merchants offer us a discount. This discount varies from merchant to merchant and can change over time.

- **User Credit Limits**: All users are assigned a predefined credit limit. Transactions exceeding this limit are automatically rejected.

## Usage Scenarios

Our service is designed to cater to various usage scenarios:

1. **Merchant Onboarding**: Allow merchants to register with the discounts they are willing to offer.

2. **Discount Modification**: Permit merchants to adjust the discounts they provide at any time.

3. **User Enrollment**: Enroll users with their personal information (name, email-id) and credit limit.

4. **Transaction Processing**: Authorize users to conduct transactions with merchants.

## Additional Features

Once the basic code framework is established, consider implementing these additional features:

- **User Payment**: Enable users to settle their outstanding dues, either partially or in full.

- **Reporting**: Generate various reports, including:
    - Total accumulated discount from a specific merchant up to the current date.
    - Outstanding dues for a particular user.
    - Identify users who have reached their credit limit.
    - Calculate the total dues owed by all users combined.

## Focus Areas

In the development of our system, we emphasize the following areas:

- **Application Design**: Prioritize a well-structured and scalable application design, utilizing appropriate design patterns.

- **Database Schema**: Create a robust and efficient database schema that supports our system's requirements.

- **Core Transaction Logic**: Concentrate on implementing the core transaction logic rather than trivial details like getters and setters.

- **Code Quality**: Ensure code extensibility, modularity, and maintainability.

## Sample Input/Output

Below are sample commands that can be used to interact with our system:

```plaintext
new user u1 u1@email.in 1000
new merchant m1 2%
new txn u1 m2 400
update merchant m1 1%
payback u1 300
report discount m1
report dues u1
report users-at-credit-limit
report total-dues
```

## Example Workflow

Here's an example workflow demonstrating the usage of our system:

```plaintext
> new user user1 u1@users.com 300
user1(300)

> new user user2 u2@users.com 400
user2(400)

> new user user3 u3@users.com 500
user3(500)

> new merchant m1 m1@merchants.com 0.5%
m1(0.5%)

> new merchant m2 m2@merchants.com 1.5%
m2(1.5%)

> new merchant m3 m3@merchants.com 1.25%
m3(1.25%)

> new txn user2 m1 500
rejected! (reason: credit limit)

> new txn user1 m2 300
success!

> new txn user1 m3 10
rejected! (reason: credit limit)

> report users-at-credit-limit
user1

> new txn user3 m3 200
success!

> new txn user3 m3 300
success!

> report users-at-credit-limit
user1
user3

> report discount m3
6.25

> payback user3 400
user3(dues: 100)

> report total-dues
user1: 300
user3: 100
total: 400
```