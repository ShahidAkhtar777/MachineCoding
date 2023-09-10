package services

import (
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/repositories"
	"github.com/google/uuid"
	"sync"
)

type UserService struct {
	repo repositories.UserRepository
	mu   sync.RWMutex
}

func NewUserService(repo repositories.UserRepository) *UserService {
	return &UserService{
		repo: repo,
	}
}

func (s *UserService) OnboardUser(name string, email string, creditLimit float64) (*models.User, error) {
	s.mu.Lock()
	s.mu.Unlock()

	uID := "U" + uuid.New().String()
	user := models.NewUser(uID, name, email, creditLimit)

	if err := s.repo.Create(user); err != nil {
		return nil, err
	}

	return user, nil
}

func (s *UserService) GetUserByID(id string) (*models.User, error) {
	s.mu.Lock()
	defer s.mu.RUnlock()

	user, err := s.repo.FindByID(id)
	if err != nil {
		return nil, err
	}

	return user, nil
}
