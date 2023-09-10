package repositories

import (
	"errors"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"sync"
)

// MerchantRepository defines the interface for interacting with merchants.
type MerchantRepository interface {
	Create(merchant *models.Merchant) error
	FindByID(id string) (*models.Merchant, error)
	FindAll() ([]*models.Merchant, error)
	Update(merchant *models.Merchant) error
	Delete(id string) error
}

// InMemoryMerchantRepository is an in-memory implementation of MerchantRepository.
type InMemoryMerchantRepository struct {
	mu        sync.RWMutex
	merchants map[string]*models.Merchant
}

func NewInMemoryMerchantRepository() *InMemoryMerchantRepository {
	return &InMemoryMerchantRepository{
		merchants: make(map[string]*models.Merchant),
	}
}

func (r *InMemoryMerchantRepository) Create(merchant *models.Merchant) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, exists := r.merchants[merchant.ID]; exists {
		return errors.New("merchant already exists")
	}

	r.merchants[merchant.ID] = merchant
	return nil
}

func (r *InMemoryMerchantRepository) FindByID(id string) (*models.Merchant, error) {
	r.mu.RLock()
	defer r.mu.RUnlock()

	merchant, exists := r.merchants[id]
	if !exists {
		return nil, errors.New("merchant not found")
	}

	return merchant, nil
}

func (r *InMemoryMerchantRepository) FindAll() ([]*models.Merchant, error) {
	r.mu.RLock()
	defer r.mu.RUnlock()

	var merchants []*models.Merchant
	for _, merchant := range r.merchants {
		merchants = append(merchants, merchant)
	}

	return merchants, nil
}

func (r *InMemoryMerchantRepository) Update(merchant *models.Merchant) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, exists := r.merchants[merchant.ID]; !exists {
		return errors.New("merchant not found")
	}

	r.merchants[merchant.ID] = merchant
	return nil
}

func (r *InMemoryMerchantRepository) Delete(id string) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, exists := r.merchants[id]; !exists {
		return errors.New("merchant not found")
	}

	delete(r.merchants, id)
	return nil
}
