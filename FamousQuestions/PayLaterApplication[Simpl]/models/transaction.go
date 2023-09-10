package models

import (
	"time"
)

type Transaction struct {
	ID              string
	UserID          string
	MerchantID      string
	Amount          float64
	Timestamp       time.Time
	Status          string // Status of the transaction (e.g., "success" or "rejected")
	RejectionReason string
}

func NewTransaction(id, userID, merchantID string, amount float64, timestamp time.Time) *Transaction {
	return &Transaction{
		ID:              id,
		UserID:          userID,
		MerchantID:      merchantID,
		Amount:          amount,
		Timestamp:       timestamp,
		Status:          "success",
		RejectionReason: "",
	}
}

func (t *Transaction) GetID() string {
	return t.ID
}

func (t *Transaction) GetUserID() string {
	return t.UserID
}

func (t *Transaction) GetMerchantID() string {
	return t.MerchantID
}

func (t *Transaction) GetAmount() float64 {
	return t.Amount
}

func (t *Transaction) GetTimestamp() time.Time {
	return t.Timestamp
}

func (t *Transaction) GetStatus() string {
	return t.Status
}

func (t *Transaction) SetStatus(status string) {
	t.Status = status
}

func (t *Transaction) GetRejectionReason() string {
	return t.RejectionReason
}

func (t *Transaction) SetRejectionReason(reason string) {
	t.RejectionReason = reason
}
