package services

import (
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/repositories"
	"github.com/google/uuid"
	"sync"
)

// MerchantService handles merchant-related operations.
type MerchantService struct {
	repo repositories.MerchantRepository
	mu   sync.RWMutex
}

// NewMerchantService creates a new instance of MerchantService.
func NewMerchantService(repo repositories.MerchantRepository) *MerchantService {
	return &MerchantService{
		repo: repo,
	}
}

// OnboardMerchant allows a merchant to be onboarded with the amount of discounts they offer.
func (s *MerchantService) OnboardMerchant(name string, email string, discount float64) (*models.Merchant, error) {
	//s.mu.Lock()
	//defer s.mu.Unlock()

	merchantID := uuid.New().String()
	merchant := models.NewMerchant(merchantID, name, email, discount)

	if err := s.repo.Create(merchant); err != nil {
		return nil, err
	}

	return merchant, nil
}

// ChangeMerchantDiscount allows a merchant to change the discount they offer.
func (s *MerchantService) ChangeMerchantDiscount(merchantID string, newDiscount float64) (*models.Merchant, error) {
	//s.mu.Lock()
	//defer s.mu.Unlock()

	merchant, err := s.repo.FindByID(merchantID)
	if err != nil {
		return nil, err
	}

	merchant.DiscountPercent = newDiscount
	if err := s.repo.Update(merchant); err != nil {
		return nil, err
	}

	return merchant, nil
}
