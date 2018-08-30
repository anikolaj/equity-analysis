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
    cout << "Enter the last quarter filed: " << endl;
    cin >> entityInfo.last_quarter;

    return entityInfo;
}

// the below method will handle input about the company's income statement
void enter_income_statement(EntityInformation entityInfo) {
    cout << "- Income Statement" << endl;
    cout << endl;

    // enter the year for the income statement being filed
    cout << "Year: ";
    double year;
    cin >> year;

    // check if the company filing is quarterly, semi annual, or annual
    cout << "If the company filing is quarterly, please enter the quarter of the last filing: ";
    double current_quarter;
    cin >> current_quarter;
    cout << endl;

    // enter total revenue
    cout << "Total revenue: ";
    double total_revenue;
    cin >> total_revenue;

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

    // enter total expenses
    cout << "Total operating expenses: ";
    double total_expenses;
    cin >> total_expenses;

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
            other_revenues.push_back(make_pair(expense_name, expense_number));
        }
    }
    cout << endl;

    // enter total additional expenses or income
    cout << "Enter total additional income: ";
    double additional_income;
    cin >> additional_income;

    cout << "Enter total additional expense: ";
    double additional_expense;
    cin >> additional_expense;
    cout << endl;

    // calculate income before taxes
    double pretax_income = total_revenue - total_expenses + additional_income - additional_expense;
    cout << "Pretax income is: " << pretax_income << endl;

    cout << "Enter tax amount: ";
    double tax_amount;
    cin >> tax_amount;
    cout << endl;

    double net_income = pretax_income - tax_amount;
    cout << "Net income: " << net_income << endl;

    double earnings_per_share = (net_income * 1000000) / entityInfo.shares_outstanding;
    cout << "Earnings per share: " << setprecision(2) << fixed << earnings_per_share << endl;
}

int main() {
    // call welcome method
    welcome();

    // call method to grab entity information
    EntityInformation entityInfo = enter_entity_information();

    // call method to grab income statement data
    enter_income_statement(entityInfo);
}