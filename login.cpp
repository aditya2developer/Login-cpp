#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class temp {
    string userName, Email, password;
    string searchName, searchPass, searchEmail;
    fstream file;

public:
    void login();
    void signUp();
    void forgot();
    void showHeader(const string &title);
    void showLoginPage();
    void showMessage(const string &message, int color);
    void clearScreen();
    void pauseAndContinue();
} obj;

void temp::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void temp::showHeader(const string &title) {
    cout << "\n====================================================\n";
    cout << "                    " << title << "\n";
    cout << "====================================================\n";
}

void temp::showMessage(const string &message, int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << message << endl;
    SetConsoleTextAttribute(hConsole, 7);
#else
    cout << message << endl;
#endif
}

void temp::pauseAndContinue() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void temp::showLoginPage() {
    clearScreen();
    cout << "\n====================================================\n";
    cout << "|                 WELCOME BACK                     |\n";
    cout << "|            Secure Login Portal                  |\n";
    cout << "====================================================\n";
    cout << "| Username :                                      |\n";
    cout << "| Password :                                      |\n";
    cout << "====================================================\n";
    cout << "| [1] Login      [2] Sign Up      [3] Forgot      |\n";
    cout << "| [4] Exit                                        |\n";
    cout << "====================================================\n";
    cout << "\nChoose an option: ";
}

int main() {
    char choice;

    while (true) {
        obj.showLoginPage();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case '1':
            obj.login();
            break;

        case '2':
            obj.signUp();
            break;

        case '3':
            obj.forgot();
            break;

        case '4':
            obj.showMessage("\nThank you for using the system. Goodbye!", 10);
            return 0;

        default:
            obj.showMessage("\nInvalid selection. Please try again.", 12);
            obj.pauseAndContinue();
        }
    }
}

void temp::signUp() {
    clearScreen();
    showHeader("SIGN UP");
    cout << "\nEnter your username: ";
    getline(cin, userName);
    cout << "Enter your email address: ";
    getline(cin, Email);
    cout << "Enter password: ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    file << userName << "*" << Email << "*" << password << endl;
    file.close();

    showMessage("\nAccount created successfully!", 10);
    pauseAndContinue();
}

void temp::login() {
    clearScreen();
    showHeader("LOGIN");
    cout << "\nEnter your username: ";
    getline(cin, searchName);
    cout << "Enter your password: ";
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    getline(file, userName, '*');
    getline(file, Email, '*');
    getline(file, password, '\n');

    bool found = false;
    while (!file.eof()) {
        if (userName == searchName) {
            found = true;
            if (password == searchPass) {
                showMessage("\nAccount login successful!", 10);
                cout << "Username : " << userName << endl;
                cout << "Email    : " << Email << endl;
            } else {
                showMessage("\nPassword is incorrect!", 12);
            }
            break;
        }
        getline(file, userName, '*');
        getline(file, Email, '*');
        getline(file, password, '\n');
    }

    if (!found) {
        showMessage("\nUser not found!", 12);
    }

    file.close();
    pauseAndContinue();
}

void temp::forgot() {
    clearScreen();
    showHeader("FORGOT PASSWORD");
    cout << "\nEnter your username: ";
    getline(cin, searchName);
    cout << "Enter your email address: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);

    bool found = false;
    while (getline(file, userName, '*')) {
        getline(file, Email, '*');
        getline(file, password);
        if (userName == searchName && Email == searchEmail) {
            found = true;
            cout << "\nAccount found!" << endl;
            cout << "Your password: " << password << endl;
            break;
        }
    }

    if (!found) {
        showMessage("\nAccount not found!", 12);
    }

    file.close();
    pauseAndContinue();
}