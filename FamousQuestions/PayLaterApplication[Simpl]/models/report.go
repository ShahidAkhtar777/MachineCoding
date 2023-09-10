package models

type Report struct {
	MerchantID string
	UserID     string
	Total      float64
}

func NewReport(merchantID, userID string, total float64) *Report {
	return &Report{
		MerchantID: merchantID,
		UserID:     userID,
		Total:      total,
	}
}

func (r *Report) GetMerchantID() string {
	return r.MerchantID
}

func (r *Report) GetUserID() string {
	return r.UserID
}

func (r *Report) GetTotal() float64 {
	return r.Total
}

func (r *Report) SetTotal(total float64) {
	r.Total = total
}
