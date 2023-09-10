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

func (u *User) GetID() string {
	return u.ID
}

func (u *User) GetName() string {
	return u.Name
}

func (u *User) GetEmail() string {
	return u.Email
}

func (u *User) GetCreditLimit() float64 {
	return u.CreditLimit
}

func (u *User) GetDues() float64 {
	return u.Dues
}

func (u *User) SetDues(dues float64) {
	u.Dues = dues
}
