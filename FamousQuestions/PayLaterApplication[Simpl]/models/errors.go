package models

import "errors"

// user Errors
var ErrUserNotFound = errors.New("user not found")
var ErrUserAlreadyExists = errors.New("user already exists")

// merchant Errors
var ErrMerchantNotFound = errors.New("merchant not found")
var ErrMerchantAlreadyExists = errors.New("merchant already exists")

// transaction Errors
var ErrTransactionRejected = errors.New("transaction rejected")
