#include <gtest/gtest.h>
#include "FeeCalculator.h"

class FeeCalculatorTest : public ::testing::Test {
protected:
    FeeCalculator calculator;
};

TEST_F(FeeCalculatorTest, ThrowsExceptionWhenAmountIsBelowMinimum) {
    EXPECT_THROW(calculator.calculateFee(9.99, AccountType::STANDARD), std::invalid_argument);
}

TEST_F(FeeCalculatorTest, StandardAccountFlatFeeAtMinimumLimit) {
    double fee = calculator.calculateFee(10.00, AccountType::STANDARD);
    EXPECT_NEAR(fee, 2.50, 0.001);
}

TEST_F(FeeCalculatorTest, PremiumAccountZeroFeeUnderLimit) {
    double fee = calculator.calculateFee(500.00, AccountType::PREMIUM);
    EXPECT_DOUBLE_EQ(fee, 0.0);
}

struct FeeTestCase {
    double amount;
    AccountType type;
    double expectedFee;
};

class FeeCalculatorParamTest : public ::testing::TestWithParam<FeeTestCase> {
protected:
    FeeCalculator calculator;
};

TEST_P(FeeCalculatorParamTest, ValidatesBoundaryValues) {
    const auto& testCase = GetParam();
    double actualFee = calculator.calculateFee(testCase.amount, testCase.type);
    EXPECT_NEAR(actualFee, testCase.expectedFee, 0.0001);
}

INSTANTIATE_TEST_SUITE_P(
    BoundaryAndEquivalenceTests,
    FeeCalculatorParamTest,
    ::testing::Values(
        FeeTestCase{100.00, AccountType::STANDARD, 2.50},
        FeeTestCase{100.01, AccountType::STANDARD, 2.0002},
        FeeTestCase{1000.00, AccountType::STANDARD, 20.00},
        FeeTestCase{500.01, AccountType::PREMIUM, 5.00}
    )
);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
