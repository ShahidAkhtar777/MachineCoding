package models

type Merchant struct {
	ID              string
	Name            string
	Email           string
	DiscountPercent float64
}

func NewMerchant(id string, name string, email string, discountPercent float64) *Merchant {
	return &Merchant{
		ID:              id,
		Name:            name,
		Email:           email,
		DiscountPercent: discountPercent,
	}
}

func (m *Merchant) GetID() string {
	return m.ID
}

func (m *Merchant) GetName() string {
	return m.Name
}

func (m *Merchant) GetEmail() string {
	return m.Email
}

func (m *Merchant) GetDiscountPercent() float64 {
	return m.DiscountPercent
}

func (m *Merchant) SetDiscountPercent(discountPercent float64) {
	m.DiscountPercent = discountPercent
}
