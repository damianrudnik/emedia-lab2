# emedia-lab2
The Vigenère cipher is a method of encrypting alphabetic text by using a series of interwoven Caesar ciphers based on the letters of a keyword. It is a form of polyalphabetic substitution.

This implementation is an ASCII based cipher.
First I generate table of size 95x95 (ASCII 32-127 characters).
 ## Encypting
 1. Take first letter of the message (its the row of the table) and first letter of the key (its the column of the table)
 2. Crypted letter is value of Table[message[i]][key[i]]
 3. After we use all key letters, we go to the begin of the key.
 
 ## Decrypting
 We know the key (column of the table) and the value of Table[message[i]][key[i]], so we just need to find number of the row in the table and convert it to ASCII.
 
