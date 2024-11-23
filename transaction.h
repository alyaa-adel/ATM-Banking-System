#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED
/*
 * Transaction Structure
 * ----------------------
 * This structure holds the details of a single transaction in the system.
 * Each transaction has a unique ID, associated user ID, amount, type (deposit or withdrawal),
 * date, and a pointer to the next transaction in the linked list.
 */
typedef struct Transaction {
    int transaction_id;
    int user_id;
    float amount;
    char transaction_type[10];
    char date[20];
    struct Transaction* next;
} Transaction;
/*----------------------------------------------------------------------------------------*/
/*------------------------- Functions Prototypes ------------------------------------*/
/*-----------------------------------------------------------------------------------------*/
/*
 * Function: load_transactions_from_file
 * --------------------------------------
 * This function reads transactions from a CSV file and loads them into a linked list.
 * It parses each line of the file and creates a new `Transaction` object with the data.
 *
 */
Transaction* load_transactions_from_file(const char* filename);
/*
 * Function: record_transaction
 * ------------------------------
 * This function creates a new transaction and adds it to the transaction linked list.
 * The new transaction is then saved to the file to ensure persistence.
 */
void record_transaction(Transaction** head, int user_id, float amount, const char* type, const char* date);
/*
 * Function: view_transactions
 * -----------------------------
 * This function displays all transactions for a given user.
 * It prints each transaction's ID, amount, type, and date.
 */
void view_transactions(Transaction* head, int user_id);

/*
 * Function: free_transactions
 * -----------------------------
 * This function frees all the memory allocated for the transaction linked list.
 * It is important for cleaning up memory and avoiding leaks.
 *
 */
void free_transactions(Transaction* head);
/*
 * Function: view_last_transactions
 * ---------------------------------
 * This function displays the last N transactions for a specific user.
 * It is useful to get a quick summary of recent activities.
 *
 */
void view_last_transactions(Transaction* head, int user_id, int n);
#endif
