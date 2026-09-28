#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream> //used for read/write functions
#include <iostream>
#include <map>
#include <sstream> //required for splitting new lines into variables easily.
#include <string>

struct UserProfile {
    std::string first_name;
    std::string last_name;
    std::string email;
    int balance;
    std::string password;
};

// NOTE TO self: extern tells the compiler the varibale live in another file.
extern std::map<std::string, UserProfile> Database;
extern const std::string DB_FILE;

// Functions
void save_to_database();
void load_database();
bool endwithGmail(std::string& email);
void sign_up();
void Login();
void ViewEvents();
void CreateTicket();
void MyTickets();
void Banking();
void Logout();

#endif
