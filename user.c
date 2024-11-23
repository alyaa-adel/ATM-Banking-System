
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "Util.h"


/*
 * Function: load_users_from_file
 * -------------------------------
 * This function reads user data from a CSV file and loads it into a linked list of User structures.
 * Each line in the file represents a user, and the function extracts the user ID, username,
 * encrypted password, and current balance.
 *
 */
User* load_users_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open users file.\n");
        return NULL;
    }

    User* head = NULL;
    User* tail = NULL;

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        User* new_user = (User*)malloc(sizeof(User));
        char encrypted_password[50];
        sscanf(line, "%d,%[^,],%[^,],%f", &new_user->user_id, new_user->username, encrypted_password, &new_user->current_balance);

        strcpy(new_user->password, encrypted_password);
        new_user->next = NULL;

        if (!head) {
            head = new_user;
        } else {
            tail->next = new_user;
        }
        tail = new_user;
    }
    fclose(file);
    return head;
}

/*
 * Function: authenticate_user
 * ---------------------------
 * This function authenticates a user by comparing the provided username and password.
 * The entered password is encrypted before being compared with the stored encrypted password.
 *
 */
User* authenticate_user(User* head, const char* username, const char* password) {
    User* current = head;

    /* Encrypt the entered password */
    char encrypted_input[50];
    encrypt_password(password, encrypted_input); /* Encrypt the input password */

    printf("Encrypted entered password: %s\n", encrypted_input);  /* Debugging print */

    while (current) {
        /* Print the stored encrypted password for debugging */
        printf("Stored encrypted password for %s: %s\n", current->username, current->password);

        /* Compare the encrypted entered password with the stored encrypted password */
        if (strcmp(current->username, username) == 0 && strcmp(current->password, encrypted_input) == 0) {
            return current;  /* User found and authenticated */
        }
        current = current->next;
    }
    return NULL;  /* Authentication failed */
}

/*
 * Function: display_balance
 * -------------------------
 * This function displays the balance of the specified user.
 */
void display_balance(User* user) {
    if (user) {
        printf("Current Balance: $%.2f\n", user->current_balance);
    }
}

/*
 * Function: deposit
 * -----------------
 * This function allows the user to deposit a specified amount into their account.
 * The user's balance is updated accordingly.
 *
 */
void deposit(User* user, float amount) {
    if (user && amount > 0) {
        user->current_balance += amount;
        printf("Deposited $%.2f successfully.\n", amount);
    }
}

/*
 * Function: withdraw
 * ------------------
 * This function allows the user to withdraw a specified amount from their account,
 * provided they have enough balance.
 *
 */
void withdraw(User* user, float amount) {
    if (user && amount > 0 && user->current_balance >= amount) {
        user->current_balance -= amount;
        printf("Withdrawn $%.2f successfully.\n", amount);
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }
}

/*
 * Function: free_users
 * --------------------
 * This function frees the memory allocated for the entire linked list of users.
 * It traverses the linked list and frees each user node.
 */
void free_users(User* head) {
    while (head) {
        User* temp = head;
        head = head->next;
        free(temp);
    }
}

/*
 * Function: change_password
 * -------------------------
 * This function allows the user to change their password.
 * The user must first provide their current password, which is then encrypted for verification.
 * After verifying the old password, the user enters a new password, which is encrypted and saved.
 */
void change_password(User* user) {
    char old_password[50], new_password[50], confirm_password[50];

    printf("Enter your current password: ");
    scanf("%s", old_password);

    char encrypted_old[50];
    encrypt_password(old_password, encrypted_old);
    if (strcmp(user->password, encrypted_old) != 0) {
        printf("Incorrect current password.\n");
        return;
    }

    printf("Enter your new password: ");
    scanf("%s", new_password);
    printf("Confirm your new password: ");
    scanf("%s", confirm_password);

    if (strcmp(new_password, confirm_password) != 0) {
        printf("Passwords do not match. Try again.\n");
        return;
    }

    encrypt_password(new_password, user->password);
    printf("Password changed successfully.\n");

    save_users_to_file(user, "users.csv");
}

/*
 * Function: save_users_to_file
 * ---------------------------
 * This function saves the user data (user ID, username, encrypted password, and balance)
 * from the linked list back to the CSV file.
 */
void save_users_to_file(User* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open users file for writing.\n");
        return;
    }

    fprintf(file, "user_id,username,encrypted_password,current_balance\n");

    User* current = head;
    while (current) {
        fprintf(file, "%d,%s,%s,%.2f\n",
                current->user_id,
                current->username,
                current->password,
                current->current_balance);
        current = current->next;
    }

    fclose(file);
    printf("User data updated successfully in %s.\n", filename);
}
