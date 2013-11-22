//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 213	//
// Student #: 43180009							Class Section: 203	//
// Date: March 15, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#include "bankApp.h" // part I
#include "bankLog.h" // part III

#include <stdio.h> // printf
#include <stdlib.h> // atol
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>

#define INITIAL_BAL 10000

// add Keystrokes each time before you call 
// 1) lockf(), 2) recordlog(), and 3) close()
// The keyStroke function takes as an argument a string that is to be 
// printed. Ideally the string should give some indication of what the 
// the next action the program is to perform is. For example, add
// if (waitForKeystroke) keyStroke("lockf(F_LOCK)"), to lock a file
// if (waitForKeystroke) keyStroke("lockf(F_ULOCK)"), to unlock a file
// if (waitForKeystroke) keyStroke("lockf(BEGIN_LOG)"), to write BEGIN_LOG
// if (waitForKeystroke) keyStroke("close(acctNums[i])"), to close an account
// make sure you handin a sample output

// NOTE: Line 26 comment close() is already included as part of provided source.
//       Not implemented

void keyStroke (char * msg); // do a keystroke

// perform a transaction
int transact (int waitForKeystroke, int createAccounts, unsigned long *acctNums,
              int *FDs, long *acctBals, long trf, unsigned *transaction_counter);


int main (int argc, char * argv[])
{
  unsigned i = 0;					// counter in for-loops
  int r = 0;						// capture return values
  unsigned waitForKeystroke = 0;	// "keyStrokes"?
  unsigned createAccounts = 0; 		// create new accounts?
  unsigned *transaction_counter = malloc (sizeof (unsigned));
  
  // the account numbers
  unsigned long *acctNums = (unsigned long *) calloc(NUM_ACCT, sizeof(long)); 
  unsigned long *acctNumP = acctNums;
  
  // the account balances
  long *acctBals = (long *) calloc(NUM_ACCT, sizeof(long));
  long trf = 500;

  // the file descriptors for the accounts
  int *acctFDs = (int *) calloc(NUM_ACCT, sizeof(int)); 

  // initializes default variables
  for (i = 0; i < NUM_ACCT; i++)
  {
    acctNums[i] = i+1;
    acctFDs[i] = 0;
    acctBals[i] = INITIAL_BAL;
  }  // for loop


  // read arguments from command prompt
  for (i = 1; i < argc; i++)
  {
    char t = argv[i][0];

    // the argument is an account number
    if ((t >= '0') && (t <= '9'))
    {
      *acctNumP = atol(argv[i]);

      if ((acctNumP - acctNums) < (NUM_ACCT - 1))
        acctNumP++; 
    }  // if statement
    else if ((t == 'k') && (argv[i][1] == '=') && (strlen(argv[i]) > 2))
      waitForKeystroke = atoi(argv[i] + 2);
    else if ((t == 'c') && (argv[i][1] == '=') && (strlen(argv[i]) > 2))
      createAccounts = atoi(argv[i] + 2);
    else if ((t == 't') && (argv[i][1] == '=') && (strlen(argv[i]) > 2))
      trf = atoi(argv[i] + 2);
    else
      printf("Unknown command line option: %s\n", argv[i]); 
  } // end of for (i < argc) ... reading arguments from cmd prompt


  // print the states of variables
  printf("waitForKeystroke=%d, createAccounts=%d, t=%ld \n", waitForKeystroke, createAccounts, trf);
  
  for (i = 0; i < NUM_ACCT; i++)
    printf("\tacctNums[%u]=%lu \n", i, acctNums[i]);

  printf("\n");

  // do a transaction
  r = transact(waitForKeystroke, createAccounts, acctNums, acctFDs, acctBals, trf, transaction_counter);

  free(acctNums);
  free(acctFDs);
  free(acctBals);
  free(transaction_counter);

  return r;
}  // main
   
int transact (int waitForKeystroke, int createAccounts, unsigned long *acctNums,
              int *acctFDs, long *acctBals, long trf, unsigned *transaction_counter)
{
  unsigned i = 0; 				// counter in for-loops
  int 
    r = 0, 						// return value
    flog = open("./bankPro/logfile", O_RDWR | O_CREAT, 0600);
  struct txRec *recP = malloc(sizeof(struct txRec));
  
  recP->typ = BEGIN_LOG;				// records the START of the transaction in the log
  recP->pid = getpid();					// sets the process ID in the log
  recP->trc = *transaction_counter++;	// sets the transaction counter
  
  // All your lockf()'s and logging statements
  // go BELOW this line (inside this function), NOT ABOVE

  // 1st, open the accounts and then
  // getbalance() or set their original balances
  for (i = 0; i < NUM_ACCT; i++)
  {
    if (waitForKeystroke) {printf("acctNum=%lu\n", acctNums[i]); keyStroke ("openOrCreateAcct()");}
    
    // *** BEGIN_LOG ***
    if (waitForKeystroke)
    {
      keyStroke("record log");
      printf ("*account%lu opened...\n", acctNums[i]);
    }
	
	recordlog(flog, recP);

    // open accounts
    r = openOrCreateAcct(acctFDs+i, acctNums[i]);    
    if (r < 0)
    {
      printf("   ... main: openOrCreateAcct[%u]\n", i);
      return r;
    }
   
    // createAccounts=1:create accounts => need to set initial balances => setBalance()    
    if (createAccounts)
    {
      // set the original balance of accounts before transaction
      if (waitForKeystroke) keyStroke("lock account");
      
      lseek (acctFDs[i], 0L, 0);
      lockf(acctFDs[i], F_LOCK, 0);
      r = setBalance(acctFDs[i], acctBals[i]);    
            
      if (waitForKeystroke) keyStroke("unlock account");
      lseek (acctFDs[i], 0, SEEK_SET);
      lockf (acctFDs[i], F_ULOCK, 0);
      
      if (r < 0)
      {
        printf("   ... main: setBalance[%u] (initial)\n", i);
        return r;
      }  // if statement
    }  // if statement

    // createAccounts=0: use existing accounts, just getBalance() of accounts
    else
    {
      if (waitForKeystroke) 
      {
        printf("acctNum=%lu\n", acctNums[i]); 
        keyStroke ("get balance");
      }  // if statement
      
      if (waitForKeystroke) keyStroke("lock account");
      lseek (acctFDs[i], 0, SEEK_SET);
      lockf(acctFDs[i], F_LOCK, 0);
      
      r = getBalance(acctFDs[i], acctBals+i);

      if (r < 0) 
      {
        printf("   ... main: getBalance[%u]\n", i);
        return r;
      }  // if statement
    }  // else statement
        
    long obal = acctBals[i]; // save old balance

    if (waitForKeystroke)
    {
      printf("acctNum=%lu\n", acctNums[i]);
      keyStroke ("calculate new balance");
    }  // if statement

    // calculate new balance
    acctBals[i] += (i)?(0 - trf):trf;
    
    printf("\tacctNums[%u]=%lu (fd=%d, obal=%ld, nbal=%ld)\n", 
           i, acctNums[i], acctFDs[i], obal, acctBals[i]); 


    // *** VALUES_LOG ***
    recP->typ = VALUES_LOG;
    recP->tnm = acctNums[i];
    recP->ID = i + 1;
    if (waitForKeystroke)
    {
      keyStroke("record log with new balance sent");
      printf ("\ttransaction %d: account%lu is sent a new balance of %ld\n", 
              i + 1, acctNums[i], acctBals[i]);
    }

    recordlog(flog, recP);
  } // for loop

  printf("\n");  

  // set the new balances of accounts.
  for (i = 0; i < NUM_ACCT; i++)
  {
    if (waitForKeystroke)
    {
      printf("acctNum=%lu\n", acctNums[i]);
      keyStroke ("setBalance()");
    }  // if statement

    // set the original balance of accounts before transaction
    r = setBalance(acctFDs[i], acctBals[i]);

    // *** COMMIT_LOG ***
    recP->typ = COMMIT_LOG;
    recP->tnm = acctNums[i];
    recP->ID = i + 1;
    if (waitForKeystroke) 
    {
      keyStroke("record log with new balance SET");
      printf ("\ttransaction %d: account%lu is SET a new balance of %ld\n",
               i + 1, acctNums[i], acctBals[i]);
    }  // if statement

    recordlog(flog, recP);

    if (r < 0)
    {
      printf("   ... main: setBalance[%u]\n", i);
      return r;
    }  // if statement
    
    if (waitForKeystroke) {printf("acctNum=%lu\n", acctNums[i]); keyStroke ("getBalance(), after setBalance()");}

    acctBals[i] = -1;			 // to test getBalance()

    r = getBalance(acctFDs[i], acctBals+i);
        
    if (waitForKeystroke) keyStroke("lockf(F_ULOCK)");
    lseek (acctFDs[i], 0, SEEK_SET);
    lockf (acctFDs[i], F_ULOCK, 0);
    
    if (r < 0)
    {
      printf("   ... main: getBalance[%u]\n", i);
      return r;
    }  // if statement

    printf("\tacctNums[%u]=%lu (fd=%d): actual balance in file = %ld)\n",
           i, acctNums[i], acctFDs[i], acctBals[i]);

    if (waitForKeystroke) {printf("acctNum=%lu\n", acctNums[i]); keyStroke ("close()");}
    // close the account files
    close(acctFDs[i]); // close() an account file
    
    // *** TRUNCATE_LOG ***
    if (waitForKeystroke) keyStroke("record log\n");
    recordlog(flog, recP);
  }

  // END of Transaction.        
  printf("\n*** End of transaction ***\n\n");

  return 0; // end of transact()
}  // transact



void keyStroke (char *msg)
{
  if (msg == NULL)
  {
    msg = "";
  }  // if statement

  printf("\tENTER to %s", msg);
  getchar();

  return; // end of keyStroke()
}  // keyStroke

// end of bankKey.c
