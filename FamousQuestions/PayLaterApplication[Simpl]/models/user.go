package models

type User struct {
	ID          string
	Name        string
	Email       string
	CreditLimit float64
	Dues        float64
}

func NewUser(id string, name string, email string, creditLimit float64) *User {
	return &User{
		ID:          id,
		Name:        name,
		Email:       email,
		CreditLimit: creditLimit,
		Dues:        0.0,
	}
}
