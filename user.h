#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
/*---------------------------- User Structure ----------------------------*/
typedef struct User {
    int user_id;
    char username[50];
    char password[50];
    float current_balance;
    struct User* next;
} User;
/*-----------------------------------------------------------------------*/
/*-------------------------functions prototype---------------------------*/
/*-----------------------------------------------------------------------*/
/* Function: load_users_from_file
 * Purpose: Load users from a CSV file into a linked list.
 */
User* load_users_from_file(const char* filename);
/* Function: authenticate_user
 * Purpose: Authenticate a user based on username and password.
 * Returns: A pointer to the authenticated user, or NULL if authentication fails.
 */
User* authenticate_user(User* head, const char* username, const char* password);
/* Function: display_balance
 * Purpose: Display the balance of a given user.
 */
void display_balance(User* user);
/* Function: deposit
 * Purpose: Deposit a specified amount into the user's account.
 */
void deposit(User* user, float amount);
/* Function: withdraw
 * Purpose: Withdraw a specified amount from the user's account, if sufficient balance exists.
 */
void withdraw(User* user, float amount);

/* Function: free_users
 * Purpose: Free memory allocated for all users in the linked list.
 */
void free_users(User* head);
/* Function: change_password
 * Purpose: Allow a user to change their password.
 */
void change_password(User* user);
/* Function: save_users_to_file
 * Purpose: Save the updated user data back to the CSV file.
 */
void save_users_to_file(User* head, const char* filename);
#endif
