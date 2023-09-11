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
