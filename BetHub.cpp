#include <cstdlib> //primarily used this just to clear the terminal text.
#include <fstream> //used for read/write functions
#include <iostream>
#include <map>
#include <sstream> //required for splitting new lines into variables easily.
#include <string>

// #include <cctype> has stuff like .isdigit to isalpha to check if a char is a digit or character just incase i ever need it.

// GlOBAL DATA
struct UserProfile {
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string password;
};

std::map<std::string, UserProfile> Database;
const std::string DB_FILE = "database.txt";

// Helper function to save data
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
             << values.password << "\n";
    }

    file.close();
}

// Helper fun to Load the DB
void load_database()
{
    std::ifstream file(DB_FILE);

    if (!file.is_open()) { // obviosly will run the first time this program initiates cause the file does not exist unless otherwise.
        return;
    }

    std::string line;
    // Read the text file line by line
    while (std::getline(file, line)) {
        if (line.empty())
            continue; // Skip blank lines

        std::stringstream ss(line); // stringstream makes the prgram read directly from the variable, it makes it into a input stream
        std::string username, first_name, last_name, email, password;

        // Extract each piece of string up until the '|' delimiter symbol
        if (std::getline(ss, username, '|') && std::getline(ss, first_name, '|') && std::getline(ss, last_name, '|') && std::getline(ss, email, '|') && std::getline(ss, password, '\n')) { // Last item reads until newline

            // Rebuilds the user structure and packs it back into the live dictionary
            Database[username] = { first_name, last_name, email, password };
        }
    }

    file.close();
}
// simple function that just checks if emails are valid, or atleast what i regard as valid in this program.
bool endwithGmail(std::string& email)
{
    std::string Target = "@gmail.com";

    if (email.length() < Target.length()) {
        return false;
    }
    return email.compare(email.length() - Target.length(), Target.length(), Target) == 0;
}

void sign_up()
{
    std::string first_name, last_name, email, username, password; // removed phone numbers to avoid the hustle of checking for valid country codes and lenths lol.
    UserProfile user = Database[username];

#if defined(_WIN32) || defined(_WIN64) // checker if its a windows macine
    std::system("cls");
#else
    std::system("clear"); // linux, mac os etc

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

    if (Database.count(username) > 0) { // yeah pythons 'if username in database' will forever be easier to understand.
        std::cout << "\nRegistration Failed: Username is already taken.\n";
        return;
    }

    std::cout << "Password: ";
    std::cin >> password;

    Database[username] = {
        first_name,
        last_name,
        email,
        password
    };

    save_to_database(); // same as git add . & git push

    std::cout << "\nAccount successfully created for " << username << "!\n";
}

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
    std::cout << "Login successful.\nRedirecting to Main Dashboard....." << std::endl;
}

int main()
{
    int action;
    load_database();

    std::cout << "==========================================\n\tWELCOME TO BETSLIP CLI\n==========================================\n[1]. Sign Up\n[2]. Login\n[3]. Exit\nSelect an Option[1-3]: ";
    std::cin >> action;

    while (action != 1 && action != 2 && action != 3) {

        std::cout << "\nInvalid Operation, Pick between 1-3.\nTry again: ";
        std::cin >> action;
    }

    if (action == 1) {
        sign_up();
    } else if (action == 2) {
        Login();
    }

    return 0;
}
