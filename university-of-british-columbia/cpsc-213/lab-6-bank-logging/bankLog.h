#ifndef __BANKLOG_H
#define __BANKLOG_H



#include <unistd.h>

// STUDENTS HAVE TO USE ALL THESE SYMBOLS IN THEIR bankLog.c
// students SHALL NOT alter these symbols in anyway, 
// otherwise marks will be deducted.

// the name of the log file for the transactions
#define LOG_BANK "bankApp.log" 


// the MAX length of a log "statement"
#define SIZE_LOG sizeof(struct txRec)

// a signal indicating that the statement will be a BEGIN statement
#define BEGIN_LOG 0    

// SESSION statement indicator
#define VALUES_LOG 1  

// COMMIT statement indicator
#define COMMIT_LOG 2  

// TRUNCATE statement indicator
#define TRUNCATE_LOG 3



struct txRec {

  unsigned int typ;   // type of statement

  // the transaction ID
  pid_t pid;          // process ID
  unsigned long trc;  // transaction counter

  // task number in a tx
  unsigned long tnm; // task number

  // account data
  unsigned long ID;   // account ID
  
  long nVal;          // new value
};



// lock the file whose file descriptor is flog and write the string 
// (represented by the variable "log") to it, then unlock the file
//
// PRE:  flog - the file descriptor of the log file.
//       recP - valid pointer to a struct txRec
//
// POST: structure pointed by recP is being written to the log file
//       whose file desciptor is flog
// 
//   return: 0 for sucess, -1 for failure.
//
int recordlog (int flog, const struct txRec * const recP);


#endif //BANKLOG_H
