# Password Keeper 🔐

### Description
This program goals is to keep safely passowrds that the user wants to store in it.
for storing passwords by site/address, searches passwords by address and saves passwords to file with simple “encryption”.

### Functions
1. Storing passwords.
2. Searching for passowrd by typing address of a site.
3. Savinf passwords to file.
4. Printing a report of sites and passwords.

### Encryption

* The encryption is based on master key that is asked from the user. 
* The master key is be stored anywhere.
* If the user forgets the master key the passwords can’t be recovered.
* Passwords are decrypted only when displayed and plaintext password must be wiped from memory after display.
* Program encrypts the passwords by performing xor-operation between master key and the password.
* Encryption is performed by _xoring_ each character in the password with a character from the master key.
* Master key is repeated consecutively over the password.
* The encryption may produce zero as a result of encryption so you need to store the length of the password to be able decrypt the password later.
* Running the “encryption” twice using the same master key should returns password to its original state.
