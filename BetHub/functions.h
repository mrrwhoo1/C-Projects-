#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream> //used for read/write functions
#include <iostream>
#include <map>
#include <sstream> //required for splitting new lines into variables easily.
#include <string>
#include <utility> //used for 'pair' in the view tickets function

struct UserProfile {
    std::string first_name;
    std::string last_name;
    std::string email;
    int balance;
    std::string password;
};

// NOTE TO self: extern tells the compiler the varibale live in another file.
extern std::map<std::string, UserProfile> Database;
extern std::map<int, std::pair<std::string, double>> AvailableEvents;
extern const std::string DB_FILE;
extern const std::string EVENTS_DB;

// Functions
void save_to_database();
void load_database();
bool endwithGmail(std::string& email);
void sign_up();
void Login();
void ViewEvents();
void CreateTicket(std::string& username);
void MyTickets();
void Banking();
void Logout();

#endif
