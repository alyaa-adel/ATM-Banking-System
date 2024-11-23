#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED




/*-----------------------------------------------------------------------*/
/*-------------------------functions prototype---------------------------*/
/*-----------------------------------------------------------------------*/

/*
 * Function to encrypt the password using Hill Cipher
 * It processes pairs of characters and applies the matrix to encrypt them.
 */

void encrypt_password(const char* input, char* output);


/*
 * Function to decrypt the password using the inverse Hill Cipher
 * It processes pairs of characters and applies the inverse matrix to decrypt them.
 */

void decrypt_password(const char* input, char* output);



/*
 * Function to get the current date in the format YYYY-MM-DD
 * Uses system time and formats it.
 */

void get_current_date(char* buffer, int buffer_size);
#endif // UTIL_H_INCLUDED
