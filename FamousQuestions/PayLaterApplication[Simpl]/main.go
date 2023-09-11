package main

import (
	"bufio"
	"fmt"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/services"
	"os"
	"strconv"
	"strings"

	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/controllers"
)

func main() {
	fmt.Println("Welcome to the Pay-Later Service CLI")
	fmt.Println("Type 'help' to see the list of available commands")

	// Initialize the application components using the controller.
	merchantService, userService, transactionService, reportService := controllers.InitializeApp()

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		scanner.Scan()
		input := scanner.Text()

		// Parse the user input and execute the corresponding command.
		commandParts := strings.Fields(input)
		if len(commandParts) == 0 {
			continue
		}

		command := commandParts[0]
		args := commandParts[1:]

		switch command {
		case "new":
			handleNewCommand(merchantService, userService, transactionService, args)
		case "update":
			handleUpdateCommand(merchantService, args)
		case "payback":
			handlePaybackCommand(userService, args)
		case "report":
			handleReportCommand(reportService, args)
		case "exit":
			fmt.Println("Exiting Pay-Later Service CLI.")
			return
		case "help":
			fmt.Println("Available commands:")
			fmt.Println("new user|merchant|txn ...")
			fmt.Println("update merchant ...")
			fmt.Println("payback user ...")
			fmt.Println("report discount|dues|users-at-credit-limit|total-dues ...")
			fmt.Println("exit")
		default:
			fmt.Println("Invalid command. Type 'help' for available commands.")
		}
	}
}

func handleNewCommand(merchantService *services.MerchantService, userService *services.UserService, transactionService *services.TransactionService, args []string) {
	if len(args) < 2 {
		fmt.Println("Invalid 'new' command. Usage: new user|merchant|txn ...")
		return
	}

	subcommand := args[0]
	subargs := args[1:]

	switch subcommand {
	case "user":
		handleNewUserCommand(userService, subargs)
	case "merchant":
		handleNewMerchantCommand(merchantService, subargs)
	case "txn":
		handleNewTransactionCommand(transactionService, subargs)
	default:
		fmt.Println("Invalid 'new' command. Usage: new user|merchant|txn ...")
	}
}

func handleNewUserCommand(userService *services.UserService, args []string) {
	if len(args) != 3 {
		fmt.Println("Invalid 'new user' command. Usage: new user <name> <email> <creditLimit>")
		return
	}

	name, email, creditLimitStr := args[0], args[1], args[2]
	creditLimit, err := strconv.ParseFloat(creditLimitStr, 64)
	if err != nil {
		fmt.Println("Invalid credit limit:", err)
		return
	}

	user, err := userService.OnboardUser(name, email, creditLimit)
	if err != nil {
		fmt.Printf("User creation failed: %v\n", err)
	} else {
		fmt.Printf("User created: %s with ID: %s\n", user.Name, user.ID)
	}
}

func handleNewMerchantCommand(merchantService *services.MerchantService, args []string) {
	if len(args) != 3 {
		fmt.Println("Invalid 'new merchant' command. Usage: new merchant <name> <email> <discountPercent>")
		return
	}

	name, email, discountPercentStr := args[0], args[1], args[2]
	discountPercent, err := strconv.ParseFloat(discountPercentStr, 64)
	if err != nil {
		fmt.Println("Invalid discount percentage:", err)
		return
	}

	merchant, err := merchantService.OnboardMerchant(name, email, discountPercent)
	if err != nil {
		fmt.Printf("Merchant creation failed: %v\n", err)
	} else {
		fmt.Printf("Merchant created: %s with ID: %s\n", merchant.Name, merchant.ID)
	}
}

func handleNewTransactionCommand(transactionService *services.TransactionService, args []string) {
	if len(args) != 3 {
		fmt.Println("Invalid 'new txn' command. Usage: new txn <userID> <merchantID> <amount>")
		return
	}

	userID, merchantID, amountStr := args[0], args[1], args[2]
	amount, err := strconv.ParseFloat(amountStr, 64)
	if err != nil {
		fmt.Println("Invalid amount:", err)
		return
	}

	transaction, err := transactionService.CarryOutTransaction(userID, merchantID, amount)
	if err != nil {
		fmt.Printf("Transaction creation failed: %v\n", err)
	} else {
		fmt.Printf("Transaction created: ID=%s, Amount=%.2f\n", transaction.ID, transaction.Amount)
	}
}

func handleUpdateCommand(merchantService *services.MerchantService, args []string) {
	if len(args) != 3 || args[0] != "merchant" {
		fmt.Println("Invalid 'update merchant' command. Usage: update merchant <merchantID> <newDiscountPercent>")
		return
	}

	merchantID, newDiscountPercentStr := args[1], args[2]
	newDiscountPercent, err := strconv.ParseFloat(newDiscountPercentStr, 64)
	if err != nil {
		fmt.Println("Invalid discount percentage:", err)
		return
	}

	_, err = merchantService.ChangeMerchantDiscount(merchantID, newDiscountPercent)
	if err != nil {
		fmt.Printf("Merchant update failed: %v\n", err)
	} else {
		fmt.Printf("Merchant %s updated with new discount: %.2f%%\n", merchantID, newDiscountPercent)
	}
}

func handlePaybackCommand(userService *services.UserService, args []string) {
	if len(args) != 3 || args[0] != "user" {
		fmt.Println("Invalid 'payback' command. Usage: payback user <userID> <paybackAmount>")
		return
	}

	userID, paybackAmountStr := args[1], args[2]
	paybackAmount, err := strconv.ParseFloat(paybackAmountStr, 64)
	if err != nil {
		fmt.Println("Invalid payback amount:", err)
		return
	}

	user, err := userService.Payback(userID, paybackAmount)
	if err != nil {
		fmt.Printf("Payback failed: %v\n", err)
	} else {
		fmt.Printf("Payback of %.2f successfully applied to user %s. Remaining dues: %.2f\n", paybackAmount, user.Name, user.Dues)
	}
}

func handleReportCommand(reportService *services.ReportService, args []string) {
	if len(args) < 1 {
		fmt.Println("Invalid 'report' command. Usage: report discount|dues|users-at-credit-limit|total-dues ...")
		return
	}

	reportType := args[0]
	subargs := args[1:]

	switch reportType {
	case "discount":
		handleDiscountReport(reportService, subargs)
	case "dues":
		handleDuesReport(reportService, subargs)
	case "users-at-credit-limit":
		handleUsersAtCreditLimitReport(reportService)
	case "total-dues":
		handleTotalDuesReport(reportService)
	default:
		fmt.Println("Invalid 'report' command. Usage: report discount|dues|users-at-credit-limit|total-dues ...")
	}
}

func handleDiscountReport(reportService *services.ReportService, args []string) {
	if len(args) != 1 {
		fmt.Println("Invalid 'report discount' command. Usage: report discount <merchantID>")
		return
	}

	merchantID := args[0]
	totalDiscount, err := reportService.CalculateTotalDiscount(merchantID)
	if err != nil {
		fmt.Printf("Error calculating merchant discount: %v\n", err)
		return
	}
	fmt.Printf("Total discount received from merchant %s: %.2f\n", merchantID, totalDiscount)
}

func handleDuesReport(reportService *services.ReportService, args []string) {
	if len(args) != 1 {
		fmt.Println("Invalid 'report dues' command. Usage: report dues <userID>")
		return
	}

	userID := args[0]
	userDues, err := reportService.CalculateUserDues(userID)
	if err != nil {
		fmt.Printf("Error calculating user dues: %v\n", err)
		return
	}
	fmt.Printf("Dues for user %s: %.2f\n", userID, userDues)
}

func handleUsersAtCreditLimitReport(reportService *services.ReportService) {
	usersAtCreditLimit, err := reportService.FindUsersAtCreditLimit()
	if err != nil {
		fmt.Printf("Error finding users at credit limit: %v\n", err)
		return
	}
	fmt.Println("Users at credit limit:")
	for _, user := range usersAtCreditLimit {
		fmt.Printf("%s\n", user.Name)
	}
}

func handleTotalDuesReport(reportService *services.ReportService) {
	totalDues, err := reportService.CalculateTotalDues()
	if err != nil {
		fmt.Printf("Error calculating total dues: %v\n", err)
		return
	}
	fmt.Printf("Total dues from all users together: %.2f\n", totalDues)
}
