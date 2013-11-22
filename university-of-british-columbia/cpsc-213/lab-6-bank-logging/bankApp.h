// bankApp.h
// header file for cs213 lab 6 (bankApp.c - bank DBMS)


#ifndef __BANKAPP_H
#define __BANKAPP_H



// Use the following symbols:

#define DIR_BANK "bankPro/" // define the directory where the account files are stored
#define SUF_BANK ".cct" // the SUFFIX for account files

#define LEN_ACCT 16 // Standard length on an account's filename
#define NUM_ACCT 2  // Number of accounts used during testing (bankKey.c)


// Note: all these functions return 0 upon successful completion,
// and -1 for failure. Returned "working" values are accomplished through 
// a pointer.

//------------------ openOrCreateAcct

// openOrCreateAcct - create a new account or just open it
//  PRE:  acctFd - is a constant pointer (not a pointer to constant) and the 
//                 int being pointed to will be set to the file descriptor
//                 resulting from a successful open. If the open fails, 
//                 the value being point to is to be set to -1
// 
//  POST: the file corresponding to acctNum is opened and the int pointed to by
//        acctFd is set.
//
int openOrCreateAcct (int * const acctFd, const unsigned long acctNum); 



//------------------ getBalance

// getBalance - read / get the balance of a bank account
//  PRE:  acctFd = a valid file descriptor
//        balance = a valid pointer to a long
//  POST: the balance of the account file whose file descriptor is acctFd
//        is read and the value being pointed by the pointer "balance" is
//        set to this value
//
int getBalance (const int acctFd, long* balance); 



//----------------- setBalance

// setBalance - set the balance of an account
//  PRE:  acctFd = a valid file descriptor
//  POST: balance of the account represented by acctFd is set to "balance"
//      
int setBalance (const int acctFd, const long balance); 


#endif // __BANKAPP_H


