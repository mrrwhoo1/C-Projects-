#include "functions.h"

int main()
{
    load_database();
    int action = 0;

    while (action != 3) {

#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::system("clear");
#endif

        std::cout << "==========================================\n\tWELCOME TO BETSLIP CLI\n==========================================\n[1]. Sign Up\n[2]. Login\n[3]. Exit\nSelect an Option[1-3]: ";
        std::cin >> action;

        while (action != 1 && action != 2 && action != 3) {
            std::cout << "\nInvalid Operation, Pick between 1-3.\nTry again: ";
            std::cin >> action;
        }

        if (action == 1) {
            sign_up();

            // Pauses so the user can read the "Account successfully created" mssage before the screen clears.
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get(); // Waits for user to press Enter

        } else if (action == 2) {
            Login();
        } else if (action == 3) {
            std::cout << "Goodbye!\n";
        }
    }

    return 0;
}
