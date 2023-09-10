package repositories

import (
	"errors"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"sync"
)

// TransactionRepository defines the interface for interacting with transactions.
type TransactionRepository interface {
	Create(transaction *models.Transaction) error
	FindByID(id string) (*models.Transaction, error)
	FindAll() ([]*models.Transaction, error)
	Update(transaction *models.Transaction) error
	Delete(id string) error
}

// InMemoryTransactionRepository is an in-memory implementation of TransactionRepository.
type InMemoryTransactionRepository struct {
	mu           sync.RWMutex
	transactions map[string]*models.Transaction
}

func NewInMemoryTransactionRepository() *InMemoryTransactionRepository {
	return &InMemoryTransactionRepository{
		transactions: make(map[string]*models.Transaction),
	}
}

func (r *InMemoryTransactionRepository) Create(transaction *models.Transaction) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, exists := r.transactions[transaction.ID]; exists {
		return errors.New("transaction already exists")
	}

	r.transactions[transaction.ID] = transaction
	return nil
}

func (r *InMemoryTransactionRepository) FindByID(id string) (*models.Transaction, error) {
	r.mu.RLock()
	defer r.mu.RUnlock()

	transaction, exists := r.transactions[id]
	if !exists {
		return nil, errors.New("transaction not found")
	}

	return transaction, nil
}

func (r *InMemoryTransactionRepository) FindAll() ([]*models.Transaction, error) {
	r.mu.RLock()
	defer r.mu.RUnlock()

	var transactions []*models.Transaction
	for _, transaction := range r.transactions {
		transactions = append(transactions, transaction)
	}

	return transactions, nil
}

func (r *InMemoryTransactionRepository) Update(transaction *models.Transaction) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, exists := r.transactions[transaction.ID]; !exists {
		return errors.New("transaction not found")
	}

	r.transactions[transaction.ID] = transaction
	return nil
}

func (r *InMemoryTransactionRepository) Delete(id string) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, exists := r.transactions[id]; !exists {
		return errors.New("transaction not found")
	}

	delete(r.transactions, id)
	return nil
}
