#include "functions.h"
#include <cstdio> // For printf
#include <cstdlib> // For std::system

// #include <cctype> has stuff like .isdigit to isalpha to check if a char is a digit or character just incase i ever need it.

// GlOBAL DATA
std::map<std::string, UserProfile> Database;
std::map<int, std::pair<std::string, double>> AvailableEvents;
const std::string DB_FILE = "database.txt";
const std::string EVENTS_DB = "events.txt";

//=============================== HELPER FUNCTION TO SAVE DATA
void save_to_database()
{
    std::ofstream file(DB_FILE); // ofstream opens a file for writing
    if (!file.is_open()) {
        std::cout << "Error, could not save/create database file.\n";
        return;
    }
    for (const auto& pair : Database) // i know i will probaly forget this, the code just means 'loop through the map, refrence every value and store it in a variable named pair.
    {
        std::string key_user = pair.first; // in this sense its the current users username
        UserProfile values = pair.second; // holds everyting in the struct

        file << key_user << "|"
             << values.first_name << "|"
             << values.last_name << "|"
             << values.email << "|"
             << values.balance << "|"
             << values.password << "\n";
    }

    file.close();
}

//====================================================== HELPER FUN TO LOAD THE DB
void load_database()
{
    std::ifstream file(DB_FILE); // open for reading.

    if (!file.is_open()) { // obviosly will run the first time this program initiates cause the file does not exist unless otherwise.
        return;
    }

    std::string line;
    // Read the text file line by line
    while (std::getline(file, line)) {
        if (line.empty())
            continue; // Skip blank lines

        std::stringstream ss(line); // stringstream makes the prgram read directly from the variable, it makes it into a input stream
        std::string username, first_name, last_name, email, balance_str, password;

        // username | first_name | last_name | email | balance | password
        if (std::getline(ss, username, '|') && std::getline(ss, first_name, '|') && std::getline(ss, last_name, '|') && std::getline(ss, email, '|') && std::getline(ss, balance_str, '|') && std::getline(ss, password, '\n')) {

            // Convert the balance text from the file into an integer
            int balance = std::stoi(balance_str);

            // Rebuilds the user structure
            Database[username] = { first_name, last_name, email, balance, password };
        }
    }

    file.close();
}

//===================================== VALID EMAIL CHECKER
bool endwithGmail(std::string& email)
{
    std::string Target = "@gmail.com";

    if (email.length() < Target.length()) {
        return false;
    }
    return email.compare(email.length() - Target.length(), Target.length(), Target) == 0;
}

//=========================================== SIGN UP FUNCTION
void sign_up()
{
    std::string first_name, last_name, email, username, password;

#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif

    std::cout << "==========================================\n\tSign Up Page\n==========================================\n";
    std::cout << "First Name: ";
    std::cin >> first_name;

    std::cout << "Last Name: ";
    std::cin >> last_name;

    std::cout << "Email [@gmail Only]: ";
    std::cin >> email;

    while (!endwithGmail(email)) {
        std::cout << "Registration Failed: Invalid email domain. Only @gmail.com is allowed.\n Try again: ";
        std::cin >> email;
    }

    std::cout << "Username: ";
    std::cin >> username;

    if (Database.count(username) > 0) {
        std::cout << "\nRegistration Failed: Username is already taken.\n";
        return;
    }

    std::cout << "Password: ";
    std::cin >> password;

    int balance = 0;
    int confirm = 0;

    // Confirmation and editing loop
    while (confirm != 4) {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::system("clear");
#endif

        printf("==========================================\n\tConfirm Details\n==========================================\n[1]. First Name: %s\n[2]. Last Name: %s\n[3]. Email: %s\n[4]. Confirm & Proceed\n\nTo Edit any info above, enter its corresponding number: ",
            first_name.c_str(), last_name.c_str(), email.c_str());
        std::cin >> confirm;

        if (confirm == 1) {
            std::cout << "Enter new First Name: ";
            std::cin >> first_name;
        } else if (confirm == 2) {
            std::cout << "Enter new Last Name: ";
            std::cin >> last_name;
        } else if (confirm == 3) {
            std::cout << "Enter new Email [@gmail Only]: ";
            std::cin >> email;
            while (!endwithGmail(email)) {
                std::cout << "Invalid email domain. Try again: ";
                std::cin >> email;
            }
        }
    }

    // Save user data into the map matching your struct order
    Database[username] = {
        first_name,
        last_name,
        email,
        balance,
        password
    };

    save_to_database();

    std::cout << "\nAccount successfully created for " << username << "!\nReturning to main menu...\n";
}

//========================================== USER DASHBOARD MENU
void user_dashboard(std::string username)
{
    int operation = 0;

    // this jst keeps the user logged in until they choose [5] Log Out.
    while (operation != 5) {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::system("clear");
#endif

        printf("==========================================\nBETHUB CLI - Main Menu (%s)\nBalance: $%d\n==========================================\n\n[1] View Available Events\n[2] Create Ticket\n[3] My Tickets (view / edit / delete)\n[4] Banking\n[5] Log Out\n\nSelect an option: ",
            Database[username].first_name.c_str(),
            Database[username].balance);

        std::cin >> operation;

        if (operation == 1) {
#if defined(_WIN32) || defined(_WIN64)
            std::system("cls");
#else
            std::system("clear");
#endif
            ViewEvents();

            // Pause so the user can read the events before clearing the screen
            std::cout << "\nPress Enter to return to menu...";
            std::cin.ignore(); // Clear leftover '1'.
            std::cin.get();
        } else if (operation == 5) {
            std::cout << "\nLogging out...\n";
        } else if (operation == 2) {
#if defined(_WIN32) || defined(_WIN64)
            std::system("cls");
#else
            std::system("clear");
#endif
            CreateTicket(username);
        }
    }
}

//==========================================LOGIN FUNCTION
void Login()
{
#if defined(_WIN32) || defined(_WIN64) // checker if its a windows macine
    std::system("cls");
#else
    std::system("clear"); // linux, mac os etc

#endif
    std::cout << "==========================================\n\tLogin Page\n==========================================\n";
    std::string username, pass;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> pass;

    while (!(Database.count(username) > 0 && Database[username].password == pass)) // Little complaint, having >0 for checks is dumb, just add the 'in' like python.
    {
        std::cout << "Invalid UserName or PassWord, Try again.\n";
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter Password: ";
        std::cin >> pass;
    }

    user_dashboard(username);
}

//============================================ VIEW EVENTS

void ViewEvents()
{
    std::ifstream file(EVENTS_DB);

    if (!file.is_open()) {
        return; // File doesn't exist yet, which is fine
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string id_str, teams, odds_str;

        // Parse: ID | Teams | Odds
        if (std::getline(ss, id_str, '|') && std::getline(ss, teams, '|') && std::getline(ss, odds_str, '\n')) {

            int id = std::stoi(id_str);
            double odds = std::stod(odds_str); // std::stod turns string into double

            AvailableEvents[id] = { teams, odds };
        }
    }

    // Print a wider, clean table header
    std::cout << "=================================================================\n";
    std::cout << "ID   Match Name                                      Odds\n";
    std::cout << "=================================================================\n";

    for (const auto& data : AvailableEvents) {
        int MatchID = data.first;
        std::string Team = data.second.first;
        double Odds = data.second.second;

        // %-45s gives a generous 45 spaces for the team names
        printf("[%2d]  %-45s  %.2f\n", MatchID, Team.c_str(), Odds);
    }

    std::cout << "=================================================================\n";
    file.close();
}

//=============================================== CREATE TICKET
void CreateTicket(std::string& username)
{
    int operation;
    if (Database[username].balance <= 0) {

        std::cout << "=== Create a New Ticket ===\n";
        std::cout << "Your available balance: $" << Database[username].balance << "\n";

        std::cout << "Balance too low to create ticket.\n[1]. Top up.\n[2]. Back\n[3]. Close App.\noperation: ";
        std::cin >> operation;
        if (operation == 3) {
            std::cout << "closing....\n";
            std::exit(0);

        } else if (operation == 2) {
            return;
        }
    }
}
