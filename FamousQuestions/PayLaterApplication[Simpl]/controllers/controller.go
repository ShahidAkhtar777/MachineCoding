package controllers

import (
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/repositories"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/services"
)

// InitializeApp initializes the application components.
func InitializeApp() (*services.MerchantService, *services.UserService, *services.TransactionService, *services.ReportService) {
	// Create in-memory repositories.
	merchantRepo := repositories.NewInMemoryMerchantRepository()
	userRepo := repositories.NewInMemoryUserRepository()
	transactionRepo := repositories.NewInMemoryTransactionRepository()

	// Create services with repositories.
	merchantService := services.NewMerchantService(merchantRepo)
	userService := services.NewUserService(userRepo)
	transactionService := services.NewTransactionService(userRepo, merchantRepo, transactionRepo)
	reportService := services.NewReportService(userRepo, merchantRepo, transactionRepo)

	return merchantService, userService, transactionService, reportService
}
