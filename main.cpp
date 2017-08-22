#include <iostream>
#include <iomanip>

using namespace std;
const int TRIP = 101;
const double BASE_PER_KM = 40;
const double ADMIN_FEE = 300;
const double FULL_TANK_PRICE = 1200;
const double FULL_TANK_TRIP = 750;
const double INSU_PREMIUM = 2700;
const double INSU_EXCESS = 5000;
const double DEP_LOAN = 2400;
const double BALOON_SERV = 2000;
const double MONTHLY_MILLEAGE = 5000;
const double PROFIT = 8000;
const double TOTAL_EXPENSES = 0;

double trip_distance = 0;
int head_count = 1;
bool day_trip = true;

double calc_tank_use( double trip){
    double tank = (((trip)/(FULL_TANK_TRIP)) * FULL_TANK_PRICE);
    return tank;
}

double premium_cut( double trip){
    double premium = (((trip)/(MONTHLY_MILLEAGE)) * (INSU_PREMIUM));
    return premium;
}

double dep_loan_cut( double trip){
    double dep = (((trip)/(MONTHLY_MILLEAGE)) * (DEP_LOAN));
    return dep;
}

double baloon_cut( double trip){
    double baloon = (((trip)/(MONTHLY_MILLEAGE)) * (BALOON_SERV));
    return baloon;
}

double trip_rate( double trip_distance){
    double cost = trip_distance * 40;
    return cost;
}

double profit_share ( double trip){
    double profit = (((trip)/(MONTHLY_MILLEAGE)) * (PROFIT));
    return profit;
}

double total_trip_cost( double trip=50, bool one_day=true, int head=1, bool discount=false){
    double sub_total = ADMIN_FEE;
    if (discount){
        sub_total -= (0.75 * ADMIN_FEE);
    }

    cout << "sub: R" << sub_total << endl;
    double risk = premium_cut(trip) + calc_tank_use(trip) + baloon_cut(trip);
    cout << "risk: R" << risk << endl;
    if (one_day){
        sub_total += risk + profit_share(trip);
    }
    cout << "Out Sub : R" << sub_total << endl;
    cout << "Per head: R" << (sub_total/head) << endl;
    // else calc risk for the given length of trip, > one day
    return sub_total;
}


int main()
{
    double totalPrice = 0;
    char confirm;
    char checkoutConfirm;
    char reply;
    bool checkout = false;

    while (checkout == false)
    {
        cout << "Enter trip in KM: ";
        cin >> trip_distance;

        cout << "Enter HeadCount: ";
        cin >> head_count;
        while(!cin)
        {
            cin.clear();
            cin.ignore(9, '\n');
            cout << "Overload, please count < 9 passengers: \n\n";
            cin >> head_count;
        }
        cout << "Your Trip is:" << endl;
        cout << trip_distance << " KM - for " << head_count << " people\n";
        cout << "Correct?(y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y')
        {
            totalPrice += total_trip_cost( trip_distance, true, head_count, true);
            cout << "Your trip cost is: R" << totalPrice;
            cout << "Would you like to check out?(y/n): ";
            cin >> checkoutConfirm;
            if (checkoutConfirm == 'y' || checkoutConfirm == 'Y')
            checkout = true;
            else if (checkoutConfirm == 'n' || checkoutConfirm == 'N')
            checkout = false;
            else
            {
                cout << "Invalid Input. Enter y to checkout or n to change trip details: ";
                cin >> checkoutConfirm;
            }
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            cout << "Entry deleted -- Enter new information: \n";
        }
        else
        {
            cout << "Invalid Input. Enter y to checkout or n to change trip details: ";
            cin >> confirm;
        }
    }
    return 0;
}
