package services

import (
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/repositories"
	"sync"
)

// ReportService handles reporting-related operations.
type ReportService struct {
	userRepo        repositories.UserRepository
	merchantRepo    repositories.MerchantRepository
	transactionRepo repositories.TransactionRepository
	mu              sync.RWMutex
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
	s.mu.RLock()
	defer s.mu.RUnlock()

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
	s.mu.RLock()
	defer s.mu.RUnlock()

	user, err := s.userRepo.FindByID(userID)
	if err != nil {
		return 0, err
	}

	return user.Dues, nil
}

// FindUsersAtCreditLimit finds users who have reached their credit limit.
func (s *ReportService) FindUsersAtCreditLimit() ([]*models.User, error) {
	s.mu.RLock()
	defer s.mu.RUnlock()

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
	s.mu.RLock()
	defer s.mu.RUnlock()

	type result struct {
		transactionAmount float64
		err               error
	}

	transactionCh := make(chan result)
	creditLimitCh := make(chan result)

	go func() {
		transactions, err := s.transactionRepo.FindByUserID(userID)
		transactionCh <- result{transactionAmount: calculateTotalTransactionAmount(transactions), err: err}
	}()

	go func() {
		userCreditLimit, err := s.userRepo.GetCreditLimit(userID)
		creditLimitCh <- result{transactionAmount: userCreditLimit, err: err}
	}()

	// Wait for both results
	transactionResult := <-transactionCh
	creditLimitResult := <-creditLimitCh

	// Handle errors
	if transactionResult.err != nil || creditLimitResult.err != nil {
		return false
	}

	return transactionResult.transactionAmount >= creditLimitResult.transactionAmount
}

func calculateTotalTransactionAmount(transactions []*models.Transaction) float64 {
	totalTransactionAmount := 0.0
	for _, transaction := range transactions {
		totalTransactionAmount += transaction.Amount
	}
	return totalTransactionAmount
}

// CalculateTotalDues calculates the total dues from all users together.
func (s *ReportService) CalculateTotalDues() (float64, error) {
	s.mu.RLock()
	defer s.mu.RUnlock()

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
