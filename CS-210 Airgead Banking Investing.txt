#include <iostream>
#include <iomanip>
#include <limits>

class Investment {
private:
    double principalAmount;
    double monthlyDeposit;
    double annualInterestRate;
    int numYears;

public:
    void SetInvestmentDetails(double principal, double deposit, double rate, int years) {
        principalAmount = principal;
        monthlyDeposit = deposit;
        annualInterestRate = rate;
        numYears = years;
    }

    void DisplayInputSummary() const {
        std::cout << "\n********************************\n";
        std::cout << "********** Data Input **********\n";
        std::cout << "Initial Investment Amount: $" << principalAmount << "\n";
        std::cout << "Monthly Deposit: $" << monthlyDeposit << "\n";
        std::cout << "Annual Interest: " << annualInterestRate << "%\n";
        std::cout << "Number of Years: " << numYears << "\n";
        std::cout << "********************************\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    void CalculateWithoutMonthlyDeposits() const {
        double total = principalAmount;
        std::cout << "\nBalance and Interest Without Additional Monthly Deposits\n";
        std::cout << "========================================================\n";
        std::cout << "Year\tYear End Balance\tYear End Earned Interest\n";

        for (int year = 1; year <= numYears; ++year) {
            double interest = total * (annualInterestRate / 100);
            total += interest;
            std::cout << year << "\t$" << std::fixed << std::setprecision(2) << total
                << "\t\t$" << interest << "\n";
        }
    }

    void CalculateWithMonthlyDeposits() const {
        double total = principalAmount;
        std::cout << "\nBalance and Interest With Additional Monthly Deposits\n";
        std::cout << "====================================================\n";
        std::cout << "Year\tYear End Balance\tYear End Earned Interest\n";

        for (int year = 1; year <= numYears; ++year) {
            double yearlyInterest = 0.0;

            for (int month = 1; month <= 12; ++month) {
                total += monthlyDeposit;
                double monthlyInterest = total * ((annualInterestRate / 100) / 12);
                total += monthlyInterest;
                yearlyInterest += monthlyInterest;
            }

            std::cout << year << "\t$" << std::fixed << std::setprecision(2) << total
                << "\t\t$" << yearlyInterest << "\n";
        }
    }
};

// Utility function for input validation
double GetValidatedDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number.\n";
        }
        else {
            return value;
        }
    }
}

int GetValidatedInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive integer.\n";
        }
        else {
            return value;
        }
    }
}

int main() {
    Investment myInvestment;
    char tryAgain;

    do {
        double principal = GetValidatedDouble("Enter the initial investment amount: $");
        double deposit = GetValidatedDouble("Enter the monthly deposit: $");
        double rate = GetValidatedDouble("Enter the annual interest rate (in %): ");
        int years = GetValidatedInt("Enter the number of years: ");

        myInvestment.SetInvestmentDetails(principal, deposit, rate, years);
        myInvestment.DisplayInputSummary();
        myInvestment.CalculateWithoutMonthlyDeposits();
        myInvestment.CalculateWithMonthlyDeposits();

        std::cout << "\nWould you like to try different values? (Y/N): ";
        std::cin >> tryAgain;
        std::cin.ignore();

    } while (tryAgain == 'Y' || tryAgain == 'y');

    std::cout << "\nThank you for using Airgead Banking!\n";
    return 0;
}
