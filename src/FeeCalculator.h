#ifndef FEE_CALCULATOR_H
#define FEE_CALCULATOR_H

enum class AccountType {
    STANDARD,
    PREMIUM
};

class FeeCalculator {
public:
    double calculateFee(double amount, AccountType type) const;
};

#endif
