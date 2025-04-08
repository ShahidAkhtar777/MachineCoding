package handlers

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/models"
	"github.com/ShahidAkhtar777/SystemDesign/FamousQuestions/PayLaterApplication/services"
)

// TransactionHandler handles HTTP requests related to transactions.
type TransactionHandler struct {
	transactionService *services.TransactionService
}

// NewTransactionHandler creates a new instance of TransactionHandler.
func NewTransactionHandler(transactionService *services.TransactionService) *TransactionHandler {
	return &TransactionHandler{transactionService}
}

// CarryOutTransaction handles carrying out a new transaction.
func (h *TransactionHandler) CarryOutTransaction(w http.ResponseWriter, r *http.Request) {
	var transaction models.Transaction
	err := json.NewDecoder(r.Body).Decode(&transaction)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	newTransaction, err := h.transactionService.CarryOutTransaction(transaction.UserID, transaction.MerchantID, transaction.Amount)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	log.Printf("Transaction carried successfully: %v", newTransaction)
	w.WriteHeader(http.StatusCreated)
}
