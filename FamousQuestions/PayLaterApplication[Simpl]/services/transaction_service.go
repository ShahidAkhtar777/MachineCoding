package services

import (
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/repositories"
	"github.com/google/uuid"
	"sync"
	"time"
)

// TransactionService handles transaction-related operations.
type TransactionService struct {
	userRepo        repositories.UserRepository
	merchantRepo    repositories.MerchantRepository
	transactionRepo repositories.TransactionRepository
	mu              sync.RWMutex
}

func NewTransactionService(
	userRepo repositories.UserRepository,
	merchantRepo repositories.MerchantRepository,
	transactionRepo repositories.TransactionRepository,
) *TransactionService {
	return &TransactionService{
		userRepo:        userRepo,
		merchantRepo:    merchantRepo,
		transactionRepo: transactionRepo,
	}
}

// CarryOutTransaction allows a user to carry out a transaction with a merchant.
func (s *TransactionService) CarryOutTransaction(userID, merchantID string, amount float64) (*models.Transaction, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	
	userChan := make(chan *models.User)
	merchantChan := make(chan *models.Merchant)
	errChan := make(chan error)

	// Retrieve user and merchant concurrently.
	go func() {
		user, err := s.userRepo.FindByID(userID)
		if err != nil {
			errChan <- err
			return
		}
		userChan <- user
	}()

	go func() {
		merchant, err := s.merchantRepo.FindByID(merchantID)
		if err != nil {
			errChan <- err
			return
		}
		merchantChan <- merchant
	}()

	// Wait for user and merchant data, or an error.
	var user *models.User
	var merchant *models.Merchant
	for i := 0; i < 2; i++ {
		select {
		case u := <-userChan:
			user = u
		case m := <-merchantChan:
			merchant = m
		case err := <-errChan:
			return nil, err
		}
	}

	close(userChan)
	close(merchantChan)
	close(errChan)

	if amount > user.CreditLimit {
		return nil, models.ErrTransactionRejected
	}

	discountedAmount := amount - (amount * merchant.DiscountPercent / 100)

	// Create a new transaction
	transactionID := "T:" + uuid.New().String()
	transaction := models.NewTransaction(transactionID, userID, merchantID, amount, discountedAmount, time.Now())

	if err := s.transactionRepo.Create(transaction); err != nil {
		return nil, err
	}
	user.Dues += amount * merchant.DiscountPercent / 100
	return transaction, nil
}
