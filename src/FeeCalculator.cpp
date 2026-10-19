#include "FeeCalculator.h"
#include <stdexcept>

double FeeCalculator::calculateFee(double amount, AccountType type) const {
    if (amount < 10.0) {
        throw std::invalid_argument("El monto mínimo de transferencia es 10.00");
    }
    if (type == AccountType::STANDARD) {
        if (amount <= 100.0) {
            return 2.50;
        } else {
            return amount * 0.02;
        }
    } else {
        if (amount <= 500.0) {
            return 0.0;
        } else {
            return 5.0;
        }
    }
}
