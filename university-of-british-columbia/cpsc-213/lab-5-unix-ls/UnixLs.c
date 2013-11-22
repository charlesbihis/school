//******************************************************************//
// 	Name: Charles Bihis						Class: Cpsc 213			//
// 	Student #: 43180009						Section: 203			//
// 	Login ID: i8a3							Lab Section: L2M		//
//******************************************************************//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>

#define DEFAULT_PATH "."
#define i_FLAG_CHAR 'i'
#define l_FLAG_CHAR 'l'
#define R_FLAG_CHAR 'R'
#define FLAG_FLAG_CHAR '-'
#define SLASH_CHAR '/'
#define NULL_CHAR '\0'
#define HIDDEN_CHAR '.'
#define EXECUTABLE_CHAR 'x'
#define NO_PERMISSION_CHAR '-'
#define SYMBOLIC_PERMISSION_STRING " l"
#define DIRECTORY_PERMISSION_STRING " d"
#define NO_PERMISSION_STRING " -"

const int COLUMN_WIDTH = 80;
const int COLUMN_SPACE = 3;
const int iNODE_WIDTH = 9;
const int NUM_HARD_LINK_WIDTH = 3;
const int SIZE_WIDTH = 7;
const int GROUP_NAME_WIDTH = 8;
const int USER_NAME_WIDTH = 8;
const int WHITE_SPACE = 1;
const int NULL_SPACE = 1;
const int HIDDEN_INDEX = 0;
const int DIRECTORY_LIMIT = 16384;		// 2^14
const int FILE_LIMIT = 32768;			// 2^15
const int SYMBOLIC_LINK_LIMIT = 40960;	// 2^15 + 2^13 
const int MAX_FILE_NAME = 255;
const int NUM_OF_PERMISSIONS = 3;

void List (char *path, int i_flag);
void ListLong (char *path, int i_flag);
void ListRec (char *path, int i_flag, int l_flag);
char *format_time (time_t cal_time);
void GetAndPrintGroup (gid_t grpNum);
void GetAndPrintUserName (uid_t uid);
int GetAndPrintPermission (int permission, int numOfPermissionsLeft, 
                           int *counter);
int GetMaxFilename (struct dirent *dir_struct, struct stat *stat_struct, 
                    DIR *current_dir, char *path, char *filename);


// Purpose: Here is where the function emulates the 'ls' call.  It can take
//          in arguments from the user and identify them as either output
//          flags or paths
// Inputs:  the user can enter any combination of the three flags -i, -l, and
//          -R, as well as path.  No input arguments will output the default
//          list as 'ls' does with no arguments
// Outputs: similar to that of the actual 'ls' command, minus orderings of
//          files
int main (int argc, char *argv[])
{
  char *path = malloc (sizeof (char) * MAX_FILE_NAME);
  int 
    R_flag = 0,
    l_flag = 0,
    i_flag = 0,
    i,
    j;
  
  for (i = 1; i < argc; i++)						// checks for any flags
  	if (argv[i][0] == FLAG_FLAG_CHAR)				// in user input
  	{
  	  for (j = 1; j < strlen (argv[i]); j++)
  	    if (argv[i][j] == R_FLAG_CHAR)
  	      R_flag++;
  	    else if (argv[i][j] == l_FLAG_CHAR)
  	      l_flag++;
  	    else if (argv[i][j] == i_FLAG_CHAR)
  	      i_flag++;
  	}  // outter if statement

  if ((argc - 1 != 0) && (argv[argc - 1][0] != FLAG_FLAG_CHAR))
  {														// ensure that the
  	path = argv[argc - NULL_SPACE];						// input path does not
														// end with a slash
    if (path[strlen(path) - NULL_SPACE] == SLASH_CHAR)	// as it is attached
  	  path[strlen(path) - NULL_SPACE] = NULL_CHAR;		// later
  }  // if statement
  else
    path = DEFAULT_PATH;
  
  if (R_flag)
    ListRec (path, i_flag, l_flag);
  else if (l_flag)
    ListLong (path, i_flag);
  else
    List (path, i_flag);
    
  return EXIT_SUCCESS;
}  // main


// Purpose: This will output the listing of files according to the ls command.
// Inputs:  path - pathname for which to list files
//          i_flag - flag to signify whether or not the i-flag was set
// Outputs: the listing of files in columns with either the i-nodes printed 
//          or not
void List (char *path, int i_flag)
{
  DIR *current_dir = opendir (path);
  struct dirent *dir_struct = malloc (sizeof (struct dirent));
  struct stat *stat_struct = malloc (sizeof (struct stat));
  char *filename = malloc (sizeof (char) * MAX_FILE_NAME);
  char *path_and_filename = malloc (sizeof (char) * MAX_FILE_NAME);
  int 
    files = 0,
    max_filename = 0,
    files_per_line = 0;

  if (current_dir == NULL) 
    exit (-1);

  dir_struct = readdir (current_dir);  //Open the current directory
  max_filename = GetMaxFilename (dir_struct, stat_struct, current_dir, 
                                 path, filename);
  rewinddir (current_dir);
  dir_struct = readdir(current_dir);
  
  if (i_flag)
    files_per_line = (COLUMN_WIDTH / (max_filename + iNODE_WIDTH + 
                                      WHITE_SPACE + COLUMN_SPACE));
  else
    files_per_line = (COLUMN_WIDTH / (max_filename + COLUMN_SPACE));
  if (files_per_line == 0)
    files_per_line = 1;

  while (dir_struct != NULL) 
  { 
    filename = dir_struct->d_name;
    if (filename [HIDDEN_INDEX] == HIDDEN_CHAR)
    {
      dir_struct = readdir (current_dir);
      continue;
    }  // if statement

    sprintf (path_and_filename, "%s/%s", path, filename);
	if ( -1 ==  lstat(path_and_filename, stat_struct)) 
      exit(-2);

    if (i_flag)
	  printf("%*lu ", iNODE_WIDTH, (unsigned long) stat_struct->st_ino);
	  
	printf("%-*s", max_filename + COLUMN_SPACE, filename);
	files++;
  	
	dir_struct = readdir (current_dir);
	if (files % files_per_line == 0 && dir_struct != NULL)
  	  printf ("\n");
  }  // while loop
  
  printf ("\n");
  closedir (current_dir);
  free (dir_struct);
  free (stat_struct);
  free (path_and_filename);
  free (current_dir);
}  // List


// Purpose: This will output the listing of files according to the ls command
//          with the l-flag set.
// Inputs:  path - pathname for which to list files
//          i_flag - flag to signify whether or not the i-flag was set
// Outputs: the listing of files line by line with columns containing
//          permissions, number of hard links to file, owner, group, size,
//          date modified, and filename.  Depending on whether or not the
//          i-flag was set, all of this would be after the i-node number.
void ListLong (char *path, int i_flag)
{
  DIR *current_dir = opendir (path);
  struct dirent *dir_struct = malloc (sizeof (struct dirent));
  struct stat *stat_struct = malloc (sizeof (struct stat));
  char *filename = malloc (sizeof (char) * MAX_FILE_NAME);
  char *path_and_filename = malloc (sizeof (char) * MAX_FILE_NAME);
  char *link_contents = malloc (MAX_FILE_NAME);

  if (current_dir == NULL) 
    exit (-1);
  
  dir_struct = readdir (current_dir);  //Open the current directory

  while (dir_struct != NULL) 
  {
    filename = dir_struct->d_name;
    if (filename [HIDDEN_INDEX] == '.')
    {
      dir_struct = readdir (current_dir);
      continue;
    }  // if statement
    
    sprintf (path_and_filename, "%s/%s", path, filename);
    //*counter = 0;
	if (lstat (path_and_filename, stat_struct) == -1)
      exit(-2);

    int *counter = malloc (sizeof (int));
    int permission = stat_struct->st_mode;
    int isExecutable = 0;
    
    *counter = 0;
    if (i_flag)
	  printf(" %*lu", iNODE_WIDTH, (unsigned long) stat_struct->st_ino);
    
    if (permission >= SYMBOLIC_LINK_LIMIT)
      printf (SYMBOLIC_PERMISSION_STRING);
    else if (permission >= FILE_LIMIT)
      printf (NO_PERMISSION_STRING);
    else if (permission >= DIRECTORY_LIMIT)
      printf (DIRECTORY_PERMISSION_STRING);

    isExecutable = GetAndPrintPermission (permission, 9, counter);
 	printf(" %*u", NUM_HARD_LINK_WIDTH, stat_struct->st_nlink);
	GetAndPrintUserName (stat_struct->st_uid);
	GetAndPrintGroup (stat_struct->st_gid);
	printf(" %*lu", SIZE_WIDTH, (unsigned long) stat_struct->st_size);
    printf(" %s", format_time(stat_struct->st_mtime));
	printf(" %s", filename);

    if (permission >= SYMBOLIC_LINK_LIMIT)
    {
      printf ("-> ");
      int successfulRead = readlink (filename, link_contents, MAX_FILE_NAME);
      if (successfulRead > 0)
        printf ("%s", link_contents);
      else
        printf ("NULL");
    }  // if statement
    
    // used for to indicate executables and folders with -F flag
    /*
    else if ((permission >= FILE_LIMIT) && (isExecutable))
      printf ("*");
    else if ((permission >= DIRECTORY_LIMIT) && (permission < FILE_LIMIT))
      printf ("/");*/
	
	printf("\n");
	dir_struct = readdir (current_dir);
	free (counter);
  }  // while loop
  closedir (current_dir);
  free (dir_struct);
  free (stat_struct);
  free (path_and_filename);
  free (link_contents);
}  // ListLong


// Purpose: This will output the listing of files according to the ls command
//          with the R-flag set, meaning it will list all of the files in
//          the given input folder, as well as the files in all of the 
//          subfolders.
// Inputs:  path - pathname for which to list files
//          i_flag - flag to signify whether or not the i-flag was set
//          l_flag - flag to signify whether or not the l-flag was set
// Outputs: the listing of files according to the appropriate flags given.
//          If the l-flag was set, then the function 'ListLong' will be called,
//          and given the appropriate inputs.  Otherwise, 'List' will be
//          called.  The recursive iterations of this function will list
//          the files in the input folder, as well as the files in all
//          subfolders.
void ListRec (char *path, int i_flag, int l_flag)
{
  DIR *current_dir = opendir (path);
  struct dirent *dir_struct = malloc (sizeof (struct dirent));
  struct stat *stat_struct = malloc (sizeof (struct stat));
  char *filename = malloc (sizeof (char) * MAX_FILE_NAME);
  char *path_and_filename = malloc (sizeof (char) * MAX_FILE_NAME);

  if (current_dir == NULL )  //Open the current directory
    exit (-1);

  dir_struct = readdir (current_dir);
	
  if (l_flag)
    ListLong (path, i_flag);
  else
    List (path, i_flag);

  while (dir_struct != NULL)
  {
    filename = dir_struct->d_name;

    sprintf (path_and_filename, "%s/%s", path, filename);
	if ( -1 ==  lstat(path_and_filename, stat_struct))
	  exit(-2);

    int permission = stat_struct->st_mode;
    int recursiveFlag = 0;

    if (permission >= DIRECTORY_LIMIT && 
        permission < SYMBOLIC_LINK_LIMIT && 
        permission < FILE_LIMIT)
      if (!((strcoll(filename, "..")) == 0 || (strcoll (filename, ".")) == 0))
        recursiveFlag = 1;

    dir_struct = readdir (current_dir);
    if (recursiveFlag)								// if you encounter a
    {												// folder, recursively
      printf ("\n%s\n", path_and_filename);			// call ListRec until there
      ListRec (path_and_filename, i_flag, l_flag);	// are no more subfolders
    }  // if statement
  }  // while loop
  closedir (current_dir);
  free (current_dir);
  free (dir_struct);
  free (stat_struct);
  free (path_and_filename);
}  // ListRec


// Purpose: This function will format the time for appropriate output.  Then
//          it will output the time.
// Inputs:  cal_time - the time for which to format and output
// Outputs: the time will be outputted appropriately.
char *format_time (time_t cal_time)
{
  struct tm *time_struct;
  static char string [30];

  time_struct = localtime (&cal_time);
  strftime (string, sizeof string, "%h %e %Y %H:%M", time_struct);

  return (string);
}  // format_time


// Purpose: This function will get and print the group ID of a given user.
// Inputs:  grpNum - the group number of the user will be input
// Outputs: the group name of the user will be printed
// *Given on 'infodemo.c' in lab specifications
void GetAndPrintGroup (gid_t grpNum)
{
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp)
    printf(" %-*s", GROUP_NAME_WIDTH, grp->gr_name);
  else
    printf("No group name for %u found\n", (unsigned int) grpNum);
}  // GetAndPrintGroup


// Purpose: This function will get and print the username of a given user.
// Inputs:  uid - the user number of the user will be input
// Outputs: the user name of the user will be printed
// *Given on 'infodemo.c' in lab specifications
void GetAndPrintUserName (uid_t uid)
{
  struct passwd *pw = NULL;
  pw = getpwuid(uid);

  if (pw)
    printf(" %-*s", USER_NAME_WIDTH, pw->pw_name);
  else
    printf("No name found for %u\n", (unsigned int) uid);
}  // GetAndPrintUserName


// Purpose: This function will output the permissions that a user has to a
//          specified file.  The function does this using recursion.
// Inputs:  permission - the permission set that the user has to the file
//          permissions_left - the count of permissions left to output
//          counter - the count of permissions already outputted.
// Outputs: The appropriate permission set of the user to the file will be
//          outputted.
int GetAndPrintPermission (int permission, int permissions_left, int *counter)
{
  char permissionSet [] = "rwx";

  if ((1 == (permission % 2)) && (permissions_left > 0))
  {
    GetAndPrintPermission (permission >> 1, --permissions_left, counter);
    printf ("%c", permissionSet [permissions_left % NUM_OF_PERMISSIONS]);

    if (permissionSet [permissions_left % NUM_OF_PERMISSIONS] == EXECUTABLE_CHAR)
      (*counter)++;
  }  // if statement
  else if ((permission % 2) == 0 && (permissions_left > 0))
  {
 	GetAndPrintPermission (permission >> 1, --permissions_left, counter);
    printf ("%c", NO_PERMISSION_CHAR);
  }  // else statement
  
  return *counter;
}  // GetAndPrintPermission


// Purpose: This function will run through the filenames of the files in a 
//          given directory and return the length of the longest name.  This is
//          used for the column formatting of the 'List' function.
// Inputs:  dir_struct - the directory for which to look
//          stat_struct - the struct containing the filename, among other
//                        things
//          current_dir - the current directory
//          path - the input path
//          filename - the filename of the current file being looked at
// Outputs: the length of the longest filename will be returned
int GetMaxFilename (struct dirent *dir_struct, 
                    struct stat *stat_struct, 
                    DIR *current_dir, 
                    char *path, 
                    char *filename)
{
  char *pathAndFilename = malloc (sizeof (char) *255);
  int max_filename = 0;

  while (dir_struct != NULL) 
  {
    filename = dir_struct->d_name;
    if (filename [HIDDEN_INDEX] == HIDDEN_CHAR)
    {
      dir_struct = readdir (current_dir);
      continue;
    }  // if statement
    
    if (max_filename < strlen (filename))
      max_filename = strlen(filename);

    sprintf (pathAndFilename, "%s/%s", path, filename);
	if (lstat(pathAndFilename, stat_struct) == -1)
      exit(-2);

	dir_struct = readdir(current_dir);
  }  // while loop
  return max_filename;
}  // GetMaxFilename
