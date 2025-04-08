package handlers

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/services"
)

// UserHandler handles HTTP requests related to users.
type UserHandler struct {
	userService *services.UserService
}

// NewUserHandler creates a new instance of UserHandler.
func NewUserHandler(userService *services.UserService) *UserHandler {
	return &UserHandler{userService}
}

// OnboardUser handles user onboarding.
func (h *UserHandler) OnboardUser(w http.ResponseWriter, r *http.Request) {
	var user models.User
	err := json.NewDecoder(r.Body).Decode(&user)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	newUser, err := h.userService.OnboardUser(user.Name, user.Email, user.CreditLimit)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	log.Printf("User onboarded successfully: %v", newUser)
	w.WriteHeader(http.StatusCreated)
}

// GetUserByID handles retrieving user information by ID.
func (h *UserHandler) GetUserByID(w http.ResponseWriter, r *http.Request) {
	var user models.User
	if err := json.NewDecoder(r.Body).Decode(&user); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	userID := user.ID

	newUser, err := h.userService.GetUserByID(userID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusNotFound)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(newUser); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}
