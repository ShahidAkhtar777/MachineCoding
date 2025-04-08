package handlers

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/services"
)

// MerchantHandler handles HTTP requests related to merchants.
type MerchantHandler struct {
	merchantService *services.MerchantService // Use a pointer to MerchantService
}

// NewMerchantHandler creates a new instance of MerchantHandler.
func NewMerchantHandler(merchantService *services.MerchantService) *MerchantHandler {
	return &MerchantHandler{merchantService}
}

// OnboardMerchant handles merchant onboarding.
func (h *MerchantHandler) OnboardMerchant(w http.ResponseWriter, r *http.Request) {
	var merchant models.Merchant
	err := json.NewDecoder(r.Body).Decode(&merchant)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	newMerchant, err := h.merchantService.OnboardMerchant(merchant.Name, merchant.Email, merchant.DiscountPercent)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	log.Printf("Merchant onboarded successfully: %v", newMerchant)
	w.WriteHeader(http.StatusCreated)
}

func (h *MerchantHandler) ChangeMerchantDiscount(w http.ResponseWriter, r *http.Request) {
	var merchant models.Merchant

	if err := json.NewDecoder(r.Body).Decode(&merchant); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	merchantID := merchant.ID
	newDiscount := merchant.DiscountPercent

	newMerchant, err := h.merchantService.ChangeMerchantDiscount(merchantID, newDiscount)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	log.Printf("Merchant discount changed successfully, New Discount: %v %", newMerchant.DiscountPercent)
	w.WriteHeader(http.StatusOK)
}
