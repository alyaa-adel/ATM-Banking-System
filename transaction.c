#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"

/*
 * Function: load_transactions_from_file
 * -------------------------------------
 * This function loads transaction data from a file and stores it in a linked list of `Transaction` structs.
 * Each line of the CSV file represents a transaction, and it is parsed into a `Transaction` object.
 *
 */
Transaction* load_transactions_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open transactions file.\n");
        return NULL;
    }

    Transaction* head = NULL;
    Transaction* tail = NULL;

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Transaction* new_transaction = (Transaction*)malloc(sizeof(Transaction));
        sscanf(line, "%d,%d,%f,%[^,],%s", &new_transaction->transaction_id, &new_transaction->user_id,
               &new_transaction->amount, new_transaction->transaction_type, new_transaction->date);
        new_transaction->next = NULL;

        /*Add the new transaction to the linked list*/
        if (!head) {
            head = new_transaction;
        } else {
            tail->next = new_transaction;
        }
        tail = new_transaction;
    }
    fclose(file);
    return head;
}

/*
 * Function: record_transaction
 * -----------------------------
 * This function records a new transaction by adding it to the linked list and appending it to the `transactions.csv` file.
 * It generates a random transaction ID, associates the transaction with the user, and stores details like amount, type, and date.
 *
 */
void record_transaction(Transaction** head, int user_id, float amount, const char* type, const char* date) {
    Transaction* new_transaction = (Transaction*)malloc(sizeof(Transaction));
    new_transaction->transaction_id = rand() % 1000; /*for generating a random transaction */
    new_transaction->user_id = user_id;
    new_transaction->amount = amount;
    strcpy(new_transaction->transaction_type, type);
    strcpy(new_transaction->date, date);
    new_transaction->next = *head;
    *head = new_transaction;

    /* Write the transaction details to the CSV file for persistence*/
    FILE* file = fopen("transactions.csv", "a");
    if (file) {
        fprintf(file, "%d,%d,%.2f,%s,%s\n", new_transaction->transaction_id, user_id, amount, type, date);
        fclose(file);
    }
}

/*
 * Function: view_transactions
 * ---------------------------
 * This function displays all transactions for a specific user, showing transaction ID, amount, type, and date.
 *
 */
void view_transactions(Transaction* head, int user_id) {
    printf("Transaction History:\n");
    Transaction* current = head;

    /*Loop through all transactions and display the ones for the specified user*/
    while (current) {
        if (current->user_id == user_id) {
            printf("ID: %d | Amount: $%.2f | Type: %s | Date: %s\n",
                   current->transaction_id, current->amount, current->transaction_type, current->date);
        }
        current = current->next;
    }
}

/*
 * Function: free_transactions
 * ---------------------------
 * This function frees all memory allocated for the transaction linked list.
 * It helps prevent memory leaks by deallocating each transaction node.
 *
 */
void free_transactions(Transaction* head) {
    while (head) {
        Transaction* temp = head;
        head = head->next;
        free(temp);
    }
}

/*
 * Function: view_last_transactions
 * -------------------------------
 * This function displays the last N transactions for a given user.
 * It helps the user view their most recent transactions.
 */
void view_last_transactions(Transaction* head, int user_id, int n) {
    printf("Last %d Transactions:\n", n);
    Transaction* current = head;
    int count = 0;

    /*Loop through all transactions, but stop once we've displayed the last 'n' transactions*/
    while (current) {
        if (current->user_id == user_id) {
            printf("ID: %d | Amount: $%.2f | Type: %s | Date: %s\n",
                   current->transaction_id, current->amount,
                   current->transaction_type, current->date);
            count++;
        }
        if (count >= n) break; /* Stop after displaying 'n' transactions*/
        current = current->next;
    }

    if (count == 0) {
        printf("No transactions found.\n"); /* display message if no transactions are found for the user0*/
    }
}
