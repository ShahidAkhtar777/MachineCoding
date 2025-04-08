package handlers

import (
	"encoding/json"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"net/http"

	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/services"
)

// ReportHandler handles HTTP requests related to reporting.
type ReportHandler struct {
	reportService *services.ReportService
}

// NewReportHandler creates a new instance of ReportHandler.
func NewReportHandler(reportService *services.ReportService) *ReportHandler {
	return &ReportHandler{reportService}
}

// CalculateTotalDiscount handles calculating the total discount received from merchants.
func (h *ReportHandler) CalculateTotalDiscount(w http.ResponseWriter, r *http.Request) {
	var requestBody map[string]interface{}

	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&requestBody); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	merchantID, ok := requestBody["merchant_id"].(string)
	if !ok {
		http.Error(w, "Invalid or missing merchant_id in request body", http.StatusBadRequest)
		return
	}

	totalDiscount, err := h.reportService.CalculateTotalDiscount(merchantID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	// Return the total discount as JSON response.
	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(totalDiscount); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}

// CalculateUserDues handles calculating the dues for a user.
func (h *ReportHandler) CalculateUserDues(w http.ResponseWriter, r *http.Request) {
	var user models.User
	err := json.NewDecoder(r.Body).Decode(&user)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	userID := user.ID

	userDues, err := h.reportService.CalculateUserDues(userID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	// Return the user dues as JSON response.
	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(userDues); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}

// FindUsersAtCreditLimit handles finding users who have reached their credit limit.
func (h *ReportHandler) FindUsersAtCreditLimit(w http.ResponseWriter, r *http.Request) {
	usersAtCreditLimit, err := h.reportService.FindUsersAtCreditLimit()
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	// Return the list of users at credit limit as JSON response.
	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(usersAtCreditLimit); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}

// CalculateTotalDues handles calculating the total dues from all users together.
func (h *ReportHandler) CalculateTotalDues(w http.ResponseWriter, r *http.Request) {
	totalDues, err := h.reportService.CalculateTotalDues()
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	// Return the total dues as JSON response.
	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(totalDues); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}
