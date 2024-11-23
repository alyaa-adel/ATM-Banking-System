#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "transaction.h"
#include "util.h"


/*the code purpose :The user is authenticated before accessing the ATM.
Once logged in, the user can perform operations like checking balance, making deposits, and withdrawals.
All transactions are recorded both in memory (linked list) and in a CSV file for persistence.
The program allows multiple sessions, and after each session, it frees up memory used for users and transactions to avoid memory leaks.*/




int main() {
    /* Load users from the file and check if it was successful*/

    User* users = load_users_from_file("users.csv");
    if (!users) {
        printf("Error: Users file is missing or corrupted.\n");
        return 1;/* Exit if loading users failed*/
    }
/* Load transactions from the file, or note that the log is empt*/
    Transaction* transactions = load_transactions_from_file("transactions.csv");
    if (!transactions) {
        printf("Note: No transactions found. Starting with an empty transaction log.\n");
    }




    /*start of(ATM )*/
    while (1) {
        char username[50], password[50];
        printf("********************************************************************************** \n");
        printf("*                         Welcome to ALYAA ATM -_-                               * \n");
        printf("********************************************************************************** \n");
        printf("Enter your data to start: \n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        User* user = authenticate_user(users, username, password);
        if (user) {
            printf("Login successful. Welcome, %s!\n", username);
            int choice;
          /* Menu loop for user options after successful login*/
            do {
                printf("\nHow can I help you?\n");
                printf("1. Check Balance\n");
                printf("2. Deposit\n");
                printf("3. Withdraw\n");
                printf("4. View Last 5 Transactions\n");
                printf("5. Change Password\n");
                printf("6. Exit\n");
                printf("Choose an option: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        display_balance(user);
                        break;

                    case 2: {
                        float amount;
                        printf("Enter amount to deposit: ");
                        scanf("%f", &amount);
                        deposit(user, amount);
                        char date[20];
                        get_current_date(date, sizeof(date));
                        record_transaction(&transactions, user->user_id, amount, "Deposit", date);
                        break;
                    }

                    case 3: {
                        float amount;
                        printf("Enter amount to withdraw: ");
                        scanf("%f", &amount);
                        withdraw(user, amount);
                        char date[20];
                        get_current_date(date, sizeof(date));
                        record_transaction(&transactions, user->user_id, amount, "Withdraw", date);
                        break;
                    }

                    case 4:
                        view_last_transactions(transactions, user->user_id, 5);
                        break;

                    case 5:
                        change_password(user);
                        break;

                    case 6:
                        printf("Logging out...\n");
                        break;

                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 6);
        } else {
            printf("Authentication failed. Please try again.\n");
        }


        printf("Would you like to exit the ATM? (y/n): ");
        char exit_choice;
        scanf(" %c", &exit_choice);
        if (exit_choice == 'y' || exit_choice == 'Y') {
            break;
        }
    }

    printf("--------------------Goodbye -___- ----------------------\n");


    free_users(users);
    free_transactions(transactions);

    return 0;
}
