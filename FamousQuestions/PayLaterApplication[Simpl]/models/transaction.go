package models

import (
	"time"
)

type Transaction struct {
	ID               string
	UserID           string
	MerchantID       string
	Amount           float64
	DiscountedAmount float64
	Timestamp        time.Time
	Status           string // Status of the transaction (e.g., "success" or "rejected")
}

func NewTransaction(id, userID, merchantID string, amount float64, discountedAmount float64, timestamp time.Time) *Transaction {
	return &Transaction{
		ID:               id,
		UserID:           userID,
		MerchantID:       merchantID,
		Amount:           amount,
		DiscountedAmount: discountedAmount,
		Timestamp:        timestamp,
		Status:           "success",
	}
}
