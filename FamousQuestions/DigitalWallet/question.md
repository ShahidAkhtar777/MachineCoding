# Digital Wallet System Requirements

## Problem Statement

The goal of this project is to create a digital wallet system that facilitates the transfer of amounts between user wallets. The system operates using its own currency called FkRupee (F₹). The following requirements must be met:

### Mandatory Requirements:

1. **Wallet Creation:** Users should be able to create their wallets within the system.

2. **Amount Transfer:** The system should allow users to transfer funds from one wallet to another.

3. **Account Statement:** Users should be able to view their account statements, which display transaction details and balances.

4. **Overview:** The system should provide an overview of all existing account numbers and their corresponding balances.

5. **Exit:** The system should offer an option to exit.

### Optional Requirements:

These requirements are not mandatory but are desirable to have:

1. **Offer 1:** If the balance of both the sender and receiver wallets is the same when an amount is transferred from one user to another, an additional F₹ 10 should be added to their respective wallets.

2. **Offer 2:** When Offer 2 is selected, the top three customers with the highest number of transactions should receive rewards in the amounts of F₹ 10, F₹ 5, and F₹ 2. In case of a tie in the number of transactions, priority should be given to the customer with a higher account balance. If the tie persists, the customer whose account was created first should be given preference.

3. **Fixed Deposit:** Introduce an option called `FixedDeposit <fd_amount>`. When selected, an amount equal to `<fd_amount>` will be reserved. If the account balance remains above `<fd_amount>` for the next five transactions, the user will receive F₹ 10 as interest. If the balance falls below `<fd_amount>`, the fixed deposit will be dissolved, and the user will need to initiate a new `FixedDeposit` command to start a new fixed deposit.

4. **Bonus Feature:** Display the `<fd_amount>` and the remaining number of transactions in the Overview and Account Statement commands.

By implementing these requirements, the digital wallet system will provide users with a seamless experience for transferring funds, managing their accounts, and potentially earning rewards and interest through special offers and features.