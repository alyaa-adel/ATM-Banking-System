#include <stdio.h>
#include <string.h>
#include "util.h"
#include <time.h>
/*Hill Cipher encryption key*/
const int key[2][2] = {
    {3, 3},
    {2, 5}
};
/* inverse Hill Cipher encryption key*/
const int inverse_key[2][2] = {
    {15, 17},
    {20, 9}
};
const int mod = 26;
/*
 * Function to encrypt the password using Hill Cipher
 * It processes pairs of characters and applies the matrix to encrypt them.
 */
void encrypt_password(const char* input, char* output) {
    const int key[2][2] = {
        {3, 3},
        {2, 5}
    };
    const int mod = 26; /*For English alphabet*/

    int len = strlen(input);
    int i;
    /*loop for each char and change it to number */
    for (i = 0; i < len; i += 2) {
        int a = input[i] - 'a';
        int b = (i + 1 < len) ? input[i + 1] - 'a' : 0;
      /*encrypt first and second character */
        output[i] = ((key[0][0] * a + key[0][1] * b) % mod) + 'a';
        output[i + 1] = ((key[1][0] * a + key[1][1] * b) % mod) + 'a';

        /*Debugging print for each step of encryption i put it to myself to check that function is work */
        printf("Encrypting: (%c, %c) -> (%c, %c)\n", input[i], input[i + 1], output[i], output[i + 1]);
    }
    output[len] = '\0'; /*end of string*/
}

/*
 * Function to decrypt the password using the inverse Hill Cipher
 * It processes pairs of characters and applies the inverse matrix to decrypt them.
 */

void decrypt_password(const char* input, char* output) {
    int len = strlen(input);int i;

    for (i = 0; i < len; i += 2) {
        int a = input[i] - 'a';
        int b = (i + 1 < len) ? input[i + 1] - 'a' : 0;

        output[i] = ((inverse_key[0][0] * a + inverse_key[0][1] * b) % mod) + 'a';
        output[i + 1] = ((inverse_key[1][0] * a + inverse_key[1][1] * b) % mod) + 'a';
    }
    output[len] = '\0';
}
/*
 * Function to get the current date in the format YYYY-MM-DD
 * Uses system time and formats it.
 */
void get_current_date(char* buffer, int buffer_size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(buffer, buffer_size, "%d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}
