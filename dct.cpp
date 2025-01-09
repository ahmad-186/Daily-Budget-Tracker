#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Constants and Variables
const int maxExpenses = INT8_MAX;
const int maxDays = 30;
string categories[maxExpenses];
double amount[maxExpenses];
int expenseCount = 0;
double dailyIncome = 0.0;
double dailyExpense[maxExpenses] = {0};
int currentDay = 1;
string dailyHistory[maxDays][maxExpenses];
int dailyHistoryCount[maxDays] = {0};

// Function Prototypes
void displayMenu();
void addExpense();
void viewExpense();
void calculateTotalExpensesForToday();
void checkRemainingBudgetForToday();
void resetForNextDay();
void viewMonthlyExpense();
void specificDayHistory();
void viewCompleteHistory();
void saveDataToFile();
void loadDataFromFile();

// Main Function
int main() {
    cout << "Welcome To Daily and Monthly Budget Tracker." << endl;
    loadDataFromFile(); // Load data from file if it exists

    cout << "Enter Your Daily Income: ";
    cin >> dailyIncome;
    int choice;
    do {
        displayMenu();
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpense(); break;
            case 3: calculateTotalExpensesForToday(); break;
            case 4: checkRemainingBudgetForToday(); break;
            case 5: resetForNextDay(); break;
            case 6: viewMonthlyExpense(); break;
            case 7: specificDayHistory(); break;
            case 8: viewCompleteHistory(); break;
            case 0: 
                saveDataToFile(); 
                cout << "Exiting the Program. Have a Great Day!" << endl; 
                break;
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
    } while (choice != 0);

    return 0;
}

// Function Definitions
void displayMenu() {
    cout << "-------------------Menu-----------------------" << endl;
    cout << "1. Add an expense\n";
    cout << "2. View today's expenses\n";
    cout << "3. Calculate total expenses for today\n";
    cout << "4. Check remaining budget for today\n";
    cout << "5. Reset for next day\n";
    cout << "6. View monthly expenses\n";
    cout << "7. Search for a specific day's history\n";
    cout << "8. View complete history of purchases\n";
    cout << "0. Exit" << endl;
}

void addExpense() {
    if (expenseCount >= maxExpenses) {
        cout << "Error! You have reached maximum expenses for today." << endl;
        return;
    }

    cout << "Enter Expense Category: ";
    cin.ignore();
    getline(cin, categories[expenseCount]);

    cout << "Enter expense amount: ";
    cin >> amount[expenseCount];

    // Update daily expense
    dailyExpense[currentDay - 1] += amount[expenseCount];

    // Add to history
    dailyHistory[currentDay - 1][dailyHistoryCount[currentDay - 1]] = 
        "Category: " + categories[expenseCount] + ", Amount: " + to_string(amount[expenseCount]);
    dailyHistoryCount[currentDay - 1]++;
    expenseCount++;

    cout << "Expense Added Successfully!\n" << endl;
}

void viewExpense() {
    if (expenseCount == 0) {
        cout << "No Expenses Recorded yet for Today." << endl;
    } else {
        cout << "Today's Expenses:" << endl;
        for (int i = 0; i < expenseCount; i++) {
            cout << "Category: " << categories[i] << ", Amount: " << amount[i] << endl;
        }
    }
}

void calculateTotalExpensesForToday() {
    double totalExpense = 0.0;
    for (int i = 0; i < expenseCount; i++) {
        totalExpense += amount[i];
    }
    cout << "Total Expense for Today: " << totalExpense << endl;
}

void checkRemainingBudgetForToday() {
    double totalExpense = 0.0;
    for (int i = 0; i < expenseCount; i++) {
        totalExpense += amount[i];
    }
    double remainingBudget = dailyIncome - totalExpense;
    cout << "Remaining Budget for Today: " << remainingBudget << endl;

    if (remainingBudget < 0) {
        cout << "Alert! You have exceeded your budget for today." << endl;
    }
}

void resetForNextDay() {
    if (currentDay >= maxDays) {
        cout << "Error! You have reached the end of the month." << endl;
        return;
    }

    saveDataToFile(); // Save data before resetting

    expenseCount = 0;
    currentDay++;
    cout << "Moved to day " << currentDay << " of the month." << endl;
}

void viewMonthlyExpense() {
    cout << "\nMonthly Expense Summary:" << endl;
    for (int i = 0; i < currentDay; i++) {
        cout << "Day " << (i + 1) << ": " << dailyExpense[i] << endl;
    }
}

void specificDayHistory() {
    int day;
    cout << "Enter day of the month to view history (1-" << currentDay << "): ";
    cin >> day;

    if (day < 1 || day > currentDay) {
        cout << "Invalid day, please try again!" << endl;
        return;
    }

    cout << "Expense History for Day " << day << ":" << endl;
    for (int i = 0; i < dailyHistoryCount[day - 1]; i++) {
        cout << dailyHistory[day - 1][i] << endl;
    }
}

void viewCompleteHistory() {
    cout << "Complete History for the Month:" << endl;
    for (int i = 0; i < currentDay; i++) {
        cout << "Day " << (i + 1) << ":" << endl;
        for (int j = 0; j < dailyHistoryCount[i]; j++) {
            cout << dailyHistory[i][j] << endl;
        }
    }
}

// File Handling Functions
void saveDataToFile() {
    ofstream outFile("budget_data.txt");
    outFile << currentDay << endl;
    outFile << dailyIncome << endl;

    for (int i = 0; i < currentDay; i++) {
        outFile << dailyExpense[i] << endl;
        outFile << dailyHistoryCount[i] << endl;

        for (int j = 0; j < dailyHistoryCount[i]; j++) {
            outFile << dailyHistory[i][j] << endl;
        }
    }

    outFile.close();
    cout << "Data saved successfully." << endl;
}

void loadDataFromFile() {
    ifstream inFile("budget_data.txt");
    if (!inFile) {
        cout << "No previous data found. Starting fresh." << endl;
        return;
    }

    inFile >> currentDay;
    inFile >> dailyIncome;

    for (int i = 0; i < currentDay; i++) {
        inFile >> dailyExpense[i];
        inFile >> dailyHistoryCount[i];

        inFile.ignore();
        for (int j = 0; j < dailyHistoryCount[i]; j++) {
            getline(inFile, dailyHistory[i][j]);
        }
    }

    inFile.close();
    cout << "Data loaded successfully." << endl;
}

