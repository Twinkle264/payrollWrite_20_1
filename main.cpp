#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool isCorrectInt(string a) {

    for (int i = 0; i < a.size()-1; i++) {
        if (a[0] == '-' || a[i] < '0' || a[i] > '9') {
            return false;
        }
    }
    return true;
}

bool isValidDate(string date) {
    if (date.size() != 10 || date[2] != '.' || date[5] != '.') return false;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (day < 1 || day > 31 || month < 1 || month > 12) return false;

    int maxDays = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    }
    if (day > maxDays) {
        return false;
    }
    return true;
}

int main() {
    std::ofstream file("./files/pay.txt", std::ios::app);
    if (!file.is_open()) {
        cerr << "ERROR! The file is not open!";
        return 1;
    }

    string str, name, lastName, date, money;


    while (true) {
        cout << "Enter the name, surname, birthday and money: ";
        getline(cin, str);
        if (str == "exit") break;

        stringstream sStream(str);
        sStream >> name >> lastName >> date >> money;

        if (name.empty() || lastName.empty() || date.empty() || money.empty()) {
            cerr << "Error: some data was not entered!" << endl;
            continue;
        }

        if (!isValidDate(date)) {
            cerr << "Error: invalid format date!" << endl;
            continue;
        }

        if (!isCorrectInt(money)) {
            cerr << "Error: payment amount entered incorrectly!";
            continue;
        }

        file.width(10);
        file << name;
        file.width(20);
        file << lastName;
        file.width(20);
        file << date;
        file.width(10);
        file << money << endl;
    }


    file.close();

    return 0;
}
