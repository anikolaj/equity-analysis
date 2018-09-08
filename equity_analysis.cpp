#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <iomanip>

using namespace std;

// custom type definitions
struct EntityInformation{
    string company_name;
    string company_ticker;
    double share_price;
    double shares_outstanding;
    int current_year;
    int last_quarter;

    // vectors of revenue and expense metrics being tracked for the entity
    vector<string> other_revenues;
    vector<string> other_expenses;
};

struct IncomeStatement{
    // revenue
    double total_revenue;
    vector<pair<string, double> > other_revenues;

    // expense
    double total_expenses;
    vector<pair<string, double> > other_expenses;

    // other
    double additional_income;
    double additional_expense;

    double pretax_income;
    double tax_amount;
    double net_income;
    double shares_outstanding;
    double earnings_per_share;
};

// the below method simply contains a text output that will be displayed at the start of the application
void welcome() {
    // introduction to the application
    cout << "---------- Equity Analysis Version 1.0.0 ----------" << endl;
    cout << "The following application will walk you through" << endl;
    cout << "how to go about analyzing the financial statements" << endl;
    cout << "filed by publicly traded companies." << endl;
    cout << endl;
    cout << "Features will be added as deemed necessary." << endl;
    cout << "For now, this program will focus on looking" << endl;
    cout << "at individual metrics to better understand" << endl;
    cout << "a company's business performance." << endl;
    cout << endl;

    // discuss where to get financial statements
    cout << "Financial statements should be taken from www.sec.gov," << endl;
    cout << "you can search the company's stock ticker to find a list" << endl;
    cout << "of SEC filings. 10-Q forms refer to quartely or semiannual" << endl;
    cout << "financial reports, while 10-K forms refer to annual" << endl;
    cout << "financial reports." << endl;
    cout << endl;

    // discuss how the application will guide you through developing financial model
    cout << "The application will guide you through inputing financial" << endl;
    cout << "data for each quarter in the past 3 years. This will help" << endl;
    cout << "develop our model and create a basis for understanding" << endl;
    cout << "the business." << endl;
    cout << endl;
}

// the below method will handle taking in user input about the company's basic information
EntityInformation enter_entity_information() {
    cout << "- Entity Information" << endl;
    cout << endl;

    // cout << "The following section will guide you through taking" << endl;
    // cout << "information about the company. This information is"

    EntityInformation entityInfo;

    // enter the company name
    cout << "Enter the name of the company: ";
    getline(cin, entityInfo.company_name);

    // enter the company stock ticker
    cout << "Enter the stock ticker for the company: ";
    cin >> entityInfo.company_ticker;

    // enter the current stock price for the company
    cout << "Enter the share price for the comapny: ";
    cin >> entityInfo.share_price;

    // enter the amount of shares outstanding for the company
    cout << "Enter the amount of shares outstanding: ";
    cin >> entityInfo.shares_outstanding;

    // enter the current year
    cout << "Enter the current year: ";
    cin >> entityInfo.current_year;

    // enter the last quarter filed
    cout << "Enter the last quarter filed: ";
    cin >> entityInfo.last_quarter;

    cout << endl;

    return entityInfo;
}

// the below method will handle input other individual revenue metrics
vector<pair<string, double> > enter_other_revenues() {

    // enter any other revenue metrics that you wish to track
    cout << "If you have any revenue metrics you would like to track, please enter them" << endl;
    cout << "Otherwise, type 'done' when you are finished." << endl;

    vector<pair<string, double> > other_revenues;
    string revenue_name;
    double revenue_number;

    while(revenue_name != "done") {

        cout << "Enter revenue name (or type 'done'): ";
        // clear the input buffer
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, revenue_name);
        
        if(revenue_name == "done") {
            break;
        }
        else {
            cout << "Enter revenue value: ";
            cin >> revenue_number;
            other_revenues.push_back(make_pair(revenue_name, revenue_number));
        }
    }
    cout << endl;

    return other_revenues;
}

// the below method will handle input other individual expense metrics
vector<pair<string, double> > enter_other_expenses() {
    // enter any other expense metrics that you wish to track
    cout << "If you have any expense metrics you would like to track, please enter them" << endl;
    cout << "Otherwise, type 'done' when you are finished." << endl;

    vector<pair<string, double> > other_expenses;
    string expense_name;
    double expense_number;

    while(expense_name != "done") {

        cout << "Enter operating expense name (or type 'done'): ";
        // clear the input buffer
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, expense_name);
        
        if(expense_name == "done") {
            break;
        }
        else {
            cout << "Enter revenue value: ";
            cin >> expense_number;
            other_expenses.push_back(make_pair(expense_name, expense_number));
        }
    }
    cout << endl;

    return other_expenses;
}

// the below method will handle input about the company's income statement
IncomeStatement enter_income_statement_values(EntityInformation & entityInfo, bool first_statement) {

    IncomeStatement incomeStatement;

    // enter total revenue
    cout << "Total revenue: ";
    cin >> incomeStatement.total_revenue;

    // check if we need to ask for individual metrics to track
    if(first_statement == true) {
        incomeStatement.other_revenues = enter_other_revenues();
        // probably want to update how we extract revenue names
        for(int i = 0; i < incomeStatement.other_revenues.size(); ++i) {
            entityInfo.other_revenues.push_back(incomeStatement.other_revenues[i].first);
        }
    }
    else {
        cout << "Please enter values for the following metrics" << endl;
        for(int i = 0; i < entityInfo.other_revenues.size(); ++i) {
            cout << entityInfo.other_revenues[i] << ": ";
            double revenue_number;
            cin >> revenue_number;

            // create pair to add to income statement
            incomeStatement.other_revenues.push_back(make_pair(entityInfo.other_revenues[i], revenue_number));
        }
    }

    // enter total expenses
    cout << "Total operating expenses: ";
    cin >> incomeStatement.total_expenses;

    // check if we need to ask for individual metrics to track
    if(first_statement == true) {
        incomeStatement.other_expenses = enter_other_expenses();
        // probably want to update how we extract revenue names
        for(int i = 0; i < incomeStatement.other_expenses.size(); ++i) {
            entityInfo.other_expenses.push_back(incomeStatement.other_expenses[i].first);
        }
    }
    else {
        cout << "Please enter values for the following metrics" << endl;
        for(int i = 0; i < entityInfo.other_expenses.size(); ++i) {
            cout << entityInfo.other_expenses[i] << ": ";
            double expense_number;
            cin >> expense_number;

            // create pair to add to income statement
            incomeStatement.other_expenses.push_back(make_pair(entityInfo.other_expenses[i], expense_number));
        }
    }

    // enter total additional expenses or income
    cout << "Enter total additional income: ";
    cin >> incomeStatement.additional_income;

    cout << "Enter total additional expense: ";
    cin >> incomeStatement.additional_expense;
    cout << endl;

    // calculate income before taxes
    incomeStatement.pretax_income = incomeStatement.total_revenue - incomeStatement.total_expenses + incomeStatement.additional_income - incomeStatement.additional_expense;
    cout << "Pretax income is: " << incomeStatement.pretax_income << endl;

    cout << "Enter tax amount: ";
    cin >> incomeStatement.tax_amount;
    cout << endl;

    incomeStatement.net_income = incomeStatement.pretax_income - incomeStatement.tax_amount;
    cout << "Net income: " << incomeStatement.net_income << endl;

    cout << "Enter the amount of shares outstanding for this quarter: ";
    cin >> incomeStatement.shares_outstanding;

    incomeStatement.earnings_per_share = (incomeStatement.net_income ) / incomeStatement.shares_outstanding;
    cout << "Earnings per share: " << setprecision(2) << fixed << incomeStatement.earnings_per_share << endl;
    cout << endl;

    return incomeStatement;
}

// this method will handle initial call for inputing the income statement
void enter_income_statement(EntityInformation entityInfo) {
    cout << "- Income Statement" << endl;
    cout << endl;

    // add introduction to give context to how statements will be collected
    cout << "To begin aggregating financial data, start by inputting metrics" << endl;
    cout << "for the last quarter filed. We will take data on the current year" << endl;
    cout << "and the previous year. Then, optionally you can continue" << endl;
    cout << "inputting previous income statements." << endl;
    cout << endl;

    // get the current year and latest income statement quarter
    int year = entityInfo.current_year;
    int period = entityInfo.last_quarter;

    bool additional_statements = true;

    bool first_statement = true;

    while(additional_statements == true) {
        cout << "Year: " << year << endl;
        cout << "Quarter: " << period << endl;
        cout << endl;

        // get data from income statement current year
        IncomeStatement current = enter_income_statement_values(entityInfo, first_statement);
        first_statement = false;
 
        // get data from income statement previous year
        cout << "Year: " << year - 1 << endl;
        cout << "Quarter: " << period << endl;
        cout << endl;
        IncomeStatement previous = enter_income_statement_values(entityInfo, first_statement);

        // check if the user would like to input more data
        cout << "Would you like to enter another statement (y/n)? ";
        string yes_no;
        cin >> yes_no;

        if(yes_no == "y") {
            additional_statements = true;

            // check how we are going to update the period
            // if the we are inputtig for the current year, go back a period
            // otherwise, go forward a period
            if(year == entityInfo.current_year) {
                period = period - 1;
            }
            else {
                period = period + 1;
            }

            // if the period is 0 or 4, set the period to 1 and update the year
            if(period == 0 || period == 4) {
                period = 1;
                year = year - 1;
            }
        }
        else {
            additional_statements = false;
        }
    }
}

int main() {
    // call welcome method
    welcome();

    // call method to grab entity information
    EntityInformation entityInfo = enter_entity_information();

    // call method to grab income statement data
    enter_income_statement(entityInfo);
}