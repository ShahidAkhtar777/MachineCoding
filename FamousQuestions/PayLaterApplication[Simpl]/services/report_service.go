package services

import (
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/repositories"
)

// ReportService handles reporting-related operations.
type ReportService struct {
	userRepo        repositories.UserRepository
	merchantRepo    repositories.MerchantRepository
	transactionRepo repositories.TransactionRepository
}

// NewReportService creates a new instance of ReportService.
func NewReportService(
	userRepo repositories.UserRepository,
	merchantRepo repositories.MerchantRepository,
	transactionRepo repositories.TransactionRepository,
) *ReportService {
	return &ReportService{
		userRepo:        userRepo,
		merchantRepo:    merchantRepo,
		transactionRepo: transactionRepo,
	}
}

// CalculateTotalDiscount calculates the total discount received from a merchant till date.
func (s *ReportService) CalculateTotalDiscount(merchantID string) (float64, error) {
	transactions, err := s.transactionRepo.FindByMerchantID(merchantID)
	if err != nil {
		return 0, err
	}

	totalDiscount := 0.0
	for _, transaction := range transactions {
		if transaction.Status == "success" {
			totalDiscount += transaction.Amount - transaction.DiscountedAmount
		}
	}

	return totalDiscount, nil
}

// CalculateUserDues calculates the dues for a user so far.
func (s *ReportService) CalculateUserDues(userID string) (float64, error) {
	transactions, err := s.transactionRepo.FindByUserID(userID)
	if err != nil {
		return 0, err
	}

	userDues := 0.0
	for _, transaction := range transactions {
		if transaction.Status == "success" {
			userDues += transaction.Amount - transaction.DiscountedAmount
		}
	}

	return userDues, nil
}

// FindUsersAtCreditLimit finds users who have reached their credit limit.
func (s *ReportService) FindUsersAtCreditLimit() ([]*models.User, error) {
	users, err := s.userRepo.FindAll()
	if err != nil {
		return nil, err
	}

	var usersAtCreditLimit []*models.User
	for _, user := range users {
		if s.isCreditLimitExceeded(user.ID) {
			usersAtCreditLimit = append(usersAtCreditLimit, user)
		}
	}

	return usersAtCreditLimit, nil
}

// isCreditLimitExceeded checks if a user has exceeded their credit limit.
func (s *ReportService) isCreditLimitExceeded(userID string) bool {
	transactions, err := s.transactionRepo.FindByUserID(userID)
	if err != nil {
		return false
	}

	userCreditLimit, err := s.userRepo.GetCreditLimit(userID)
	if err != nil {
		return false
	}

	totalTransactionAmount := 0.0
	for _, transaction := range transactions {
		totalTransactionAmount += transaction.Amount
	}

	return totalTransactionAmount > userCreditLimit
}

// CalculateTotalDues calculates the total dues from all users together.
func (s *ReportService) CalculateTotalDues() (float64, error) {
	users, err := s.userRepo.FindAll()
	if err != nil {
		return 0, err
	}

	totalDues := 0.0
	for _, user := range users {
		dues, err := s.CalculateUserDues(user.ID)
		if err != nil {
			return 0, err
		}
		totalDues += dues
	}

	return totalDues, nil
}
