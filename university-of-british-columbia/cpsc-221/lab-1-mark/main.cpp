#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Mark.h"
using namespace std;

void processTeacherFile (ifstream & teacherFile, Mark & finalMark,
                         Mark & midtermMark, Mark & labMark,
                         int & numberOfLabs, int & numberOfOmittedLabs);
void processStudentFile (ifstream & studentFile,
                         ofstream & calculatedGradesFile,
                         const int numberOfLabs,
                         const int numberOfOmittedLabs, Mark & finalMark,
                         Mark & midtermMark, Mark & labMark);
void sortLabGrades (double grades [], const int minIndex,
                    const int maxIndex);
void swapValues (double grades [], const int i, const int j);
double calculatePercentGrade (double grades [], const int countedLabs,
                              const int MIDTERM_PLUS_FINAL,
                              Mark & finalMark, Mark & midtermMark,
                              Mark & labMark, double & averageFinalMark,
                              double & averageMidtermMark,
                              double & averageLabMark);
void outputLetterGrade (const double grade, 
                        ofstream & calculatedGradesFile);
void SayHello (ofstream & calculatedGradesFile);
void SayGoodbye (ofstream & calculatedGradesFile);

int main (void)
{
  int
    numberOfLabs,
    numberOfOmittedLabs;
  ifstream 
    teacherFile,
    studentFile;
  ofstream
    calculatedGradesFile;
  Mark
    finalMark,
    midtermMark,
    labMark;
  
  teacherFile.open ("TeacherFile.txt");
  studentFile.open ("StudentFile.txt");
  calculatedGradesFile.open ("CalculatedGrades.txt");

  if (teacherFile.fail ())
  {
    cout << "ERROR: Teacher file not opened!\n";
    calculatedGradesFile << "ERROR: Teacher file not opened!\n";
    return 0;
  }  // if statement
  else if (studentFile.fail ())
  {
    cout << "ERROR: Student file not opened!\n";
    calculatedGradesFile << "ERROR: Student file not opened!\n";
    return 0;
  }  // else if statement
  
  SayHello (calculatedGradesFile);
  processTeacherFile (teacherFile, finalMark, midtermMark, labMark,
                      numberOfLabs, numberOfOmittedLabs);
  processStudentFile (studentFile, calculatedGradesFile, numberOfLabs,
                      numberOfOmittedLabs, finalMark, midtermMark, 
                      labMark);
  SayGoodbye (calculatedGradesFile);
  teacherFile.close ();
  studentFile.close ();
  calculatedGradesFile.close ();
  
  return EXIT_SUCCESS;
}  // main


// Purpose: to read in the values from the teacher file and store
//          them in the appropriate variables for use in calculations
//          later
// Input: ifstream & teacherFile - the teacher file is passed in
//                                 so that the values can be read in
//        Mark & finalMark - the object for a final exam is passed in
//                           so that its private data members may
//                           be set according to the teacher file
//        Mark & midtermMark - the object for a midterm exam is passed
//                             so that its private data members may
//                             be set according to the teacher file
//        Mark & labMark - the object for the labs is passed in so that
//                         its private data members may be set
//                         according to the teacher file
//        int & numberOfLabs - this is passed by reference so that
//                             it may be set according to the teacher
//                             file for use in other functions
//        int & numberOfOmittedLabs - this is passed by reference so
//                                    that it may be set according
//                                    to the teacher file for use in
//                                    other functions
// Output: the appropriate variables and private data members are set
//         according to the teacher file
void processTeacherFile (ifstream & teacherFile, Mark & finalMark,
                         Mark & midtermMark, Mark & labMark,
                         int & numberOfLabs, int & numberOfOmittedLabs)
{
  int
    temp_outOf,
    temp_weight;
  
  teacherFile >> temp_outOf >> temp_weight;
  finalMark.setOutOf (temp_outOf);
  finalMark.setWeight (temp_weight);
  
  teacherFile >> temp_outOf >> temp_weight;
  midtermMark.setOutOf (temp_outOf);
  midtermMark.setWeight (temp_weight);
  
  teacherFile >> temp_outOf >> temp_weight;
  labMark.setOutOf (temp_outOf);
  labMark.setWeight (temp_weight);
  
  teacherFile >> numberOfLabs >> numberOfOmittedLabs;
}  // processTeacherFile

// Purpose: to read in the name and grades of each student and process
//          their marks.  This is done one student at a time
// Input: ifstream & studentFile - the student file is passed in so
//                                 that values may be read from it
//        ofstream & calculatedGradesFile - this is the output file
//                                          where a summary of the 
//                                          marks will be written to
//        const int numberOfLabs - used for calculating lab mark for
//                                 each student
//        const int numberOfOmittedLabs - used for calculating lab
//                                        mark for each student
//        Mark & finalMark - uses member function to calculate final
//                           mark for each student
//        Mark & midtermMark - uses member function to calculate
//                             midterm mark for each student
//        Mark & labMark - uses member function to calculate lab
//                         mark for each student
// Output: a summary of marks for each student is outputted, one
//         student at a time
void processStudentFile (ifstream & studentFile,
                         ofstream & calculatedGradesFile,
                         const int numberOfLabs,
                         const int numberOfOmittedLabs,
                         Mark & finalMark, Mark & midtermMark, 
                         Mark & labMark)
{
  const int
    MAX_STUDENT_NAME = 30,
    MAX_GRADES = 50,
    MIDTERM_PLUS_FINAL =2,
    PERCENT = 100,
    NUMBERS_AFTER_DECIMAL = 1,
    PERCENT_GRADE_WIDTH = 4,
    LETTER_GRADE_WIDTH = 11,
    NUMBER_STUDENTS_WIDTH = 31,
    AVERAGE_FINAL_WIDTH = 30,
    AVERAGE_MIDTERM_WIDTH = 30,
    AVERAGE_COURSE_WIDTH = 30;
  char
    studentName [MAX_STUDENT_NAME];
  int 
    totalStudents = 0;
  double
    grades [MAX_GRADES],
    thisPercentGrade = 0,
    averageFinalMark = 0,
    averageMidtermMark = 0,
    averageLabMark = 0,
    averageCourseMark = 0;
		// printing header for console output and file output
  cout << "Student Name              Percent Grade     "
       << "Letter Grade\n\n";
  calculatedGradesFile << "Student Name              Percent Grade     "
                       << "Letter Grade\n\n";

  for (;;)
  {
    studentFile.getline (studentName, MAX_STUDENT_NAME, ':');
    if (studentFile.eof ()) break;
    totalStudents++;
    for (int i = 0; i < numberOfLabs + MIDTERM_PLUS_FINAL; i++)
      studentFile >> grades [i];

    sortLabGrades (grades, MIDTERM_PLUS_FINAL,
                   numberOfLabs + MIDTERM_PLUS_FINAL);
    
    thisPercentGrade = calculatePercentGrade (grades, numberOfLabs -
                                              numberOfOmittedLabs,
                                              MIDTERM_PLUS_FINAL,
                                              finalMark, midtermMark,
                                              labMark, averageFinalMark,
                                              averageMidtermMark,
                                              averageLabMark);
    averageCourseMark += thisPercentGrade;
    cout << showpoint << fixed << setprecision (NUMBERS_AFTER_DECIMAL)
         << left << studentName 
         << setw (MAX_STUDENT_NAME - strlen (studentName)) << ": " 
         << thisPercentGrade << setw (PERCENT_GRADE_WIDTH) << "%" 
         << setw (LETTER_GRADE_WIDTH);
    calculatedGradesFile << showpoint << fixed 
         << setprecision (NUMBERS_AFTER_DECIMAL)
         << left << studentName 
         << setw (MAX_STUDENT_NAME - strlen (studentName)) << ": " 
         << thisPercentGrade << setw (PERCENT_GRADE_WIDTH) << "%" 
         << setw (LETTER_GRADE_WIDTH);
    outputLetterGrade (thisPercentGrade, calculatedGradesFile);
    studentFile.getline (studentName, MAX_STUDENT_NAME, '\n');
  }  // for loop
  
  averageFinalMark = (averageFinalMark / totalStudents) * PERCENT;
  averageMidtermMark = (averageMidtermMark / totalStudents) * PERCENT;
  averageLabMark = (averageLabMark / (totalStudents * 
                   (MIDTERM_PLUS_FINAL + numberOfLabs - 
                   numberOfOmittedLabs))) * PERCENT;
  averageCourseMark = (averageCourseMark / totalStudents);
  cout << showpoint << fixed << setprecision (NUMBERS_AFTER_DECIMAL)
       << setw (NUMBER_STUDENTS_WIDTH) << "\n\nNumber of Students: " 
       << totalStudents << setw (AVERAGE_FINAL_WIDTH) 
       << "\nAverage Final Exam Grade: " << averageFinalMark << "%" 
       << setw (30) << "\nAverage Midterm Exam Grade: " 
       << averageMidtermMark << "%" << setw (AVERAGE_MIDTERM_WIDTH) 
       << "\nAverage Lab Mark: " << averageLabMark << "%"
       << setw (AVERAGE_COURSE_WIDTH) << "\nAverage Course Mark: " 
       << averageCourseMark << "%";
}  // processStudentFile

// Purpose: takes in the array of grades and sorts only the lab grades,
//          leaving the final grade and midterm grade alone.  This is
//          to make omitting the lowest lab grades easier
// Input: double grades [] - the array of grades is passed in for
//                            sorting
//         const int minIndex - the number of grades recorded in the 
//                              array of grades before the lab grades
//                              begin
//         const int maxIndex - the maximum number of grades stored
//                              in the array of grades
// Output: the array of grades is sorted accordingly
void sortLabGrades (double grades [], const int minIndex,
                    const int maxIndex)
{
  for (int i = minIndex; i < maxIndex; i++)
    for (int j = i + 1; j < maxIndex; j++)
      if (grades [i] < grades [j])
        swapValues (grades, i, j);
}  // sortLabGrades

// Purpose: swaps two values within an array.  This is used in the
//          sorting call sortLabGrades.
// Input: double grades [] - the array of grades is passed in so that
//                           the values may be swapped and restored in 
//                           the array
//        const int i - the index value of one of the numbers to be
//                      swapped
//        const int j - the index value of the other number to be
//                      swapped
// Output: the values of the indices of the array are swapped
void swapValues (double grades [], const int i, const int j)
{
  grades [i] += grades [j];
  grades [j] = grades [i] - grades [j];
  grades [i] -= grades [j];
}  // swapValues

// Purpose: to calculate the overall grade of a student given his full
//          set of marks
// Input: double grades [] - contains a students full set of marks for
//                           calculating his overall grade
//        const int countedLabs - indicates how many labs to count
//                                when calculating a students lab mark
//        const int MIDTERM_PLUS_FINAL - indicates how many midterms
//                                       and finals there are so as to
//                                       know when the lab marks begin
//                                       in the array of grades
//         Mark & finalMark - uses member function to calculate final
//                            mark for each student
//         Mark & midtermMark - uses member function to calculate
//                              midterm mark for each student
//         Mark & labMark - uses member function to calculate lab
//                          mark for each student
//         double & averageFinalMark, double & averageMidtermMark,
//         double & averageLabMark - stores the average values of each
//                                   respective mark.  Since the marks
//                                   are calculated student by student
//                                   these variable must be passed by
//                                   reference so that they can be
//                                   changed with each new student
// Output: the calculated percent grade of the particular student
//         is returned
double calculatePercentGrade (double grades [], const int countedLabs,
                              const int MIDTERM_PLUS_FINAL,
                              Mark & finalMark, Mark & midtermMark,
                              Mark & labMark, double & averageFinalMark,
                              double & averageMidtermMark,
                              double & averageLabMark)
{
  const int
    FINAL_INDEX = 0,
    MIDTERM_INDEX = 1;
  double
    calculatedGrade = 0;
  
  averageFinalMark += finalMark.calculatePercentGrade (grades [FINAL_INDEX]);
  calculatedGrade += finalMark.calculateWeightedGrade (grades [FINAL_INDEX]);
  averageMidtermMark += midtermMark.calculatePercentGrade (grades [MIDTERM_INDEX]);
  calculatedGrade += midtermMark.calculateWeightedGrade (grades [MIDTERM_INDEX]);
  for (int i = MIDTERM_PLUS_FINAL; i < MIDTERM_PLUS_FINAL + countedLabs; i++)
  {
    averageLabMark += labMark.calculatePercentGrade (grades [i]);
    calculatedGrade += (labMark.calculateWeightedGrade (grades [i])) /
                        countedLabs;
  }  // for loop
  
  return calculatedGrade;
}  // calculateGrade

// Purpose: to take in a grade and output the appropriate letter grade
//          both to the console and to the output file given
// Input: const double grade - a percent grade is passed in for which
//                             a letter grade will be assigned
//        ofstream & calculatedGradesFile - the output file to which
//                                          the letter grade will be
//                                          outputted in addition
//                                          to the console output
// Output: the appropriate letter grade will be outputted to both the
//         console and the given output file
void outputLetterGrade (const double grade, 
                        ofstream & calculatedGradesFile)
{
  const int
    MAX_LETTER_GRADE = 2,
    LETTER_INDEX = 0,
    PLUS_MINUS_INDEX = 1,
    F_LOWER_LIMIT = 0,
    F_UPPER_LIMIT = 49,
    D_LOWER_LIMIT = 50,
    D_UPPER_LIMIT = 54,
    C_MINUS_LOWER_LIMIT = 55,
    C_MINUS_UPPER_LIMIT = 59,
    C_LOWER_LIMIT = 60,
    C_UPPER_LIMIT = 63,
    C_PLUS_LOWER_LIMIT = 64,
    C_PLUS_UPPER_LIMIT = 67,
    B_MINUS_LOWER_LIMIT = 68,
    B_MINUS_UPPER_LIMIT= 71,
    B_LOWER_LIMIT = 72,
    B_UPPER_LIMIT = 75,
    B_PLUS_LOWER_LIMIT = 76,
    B_PLUS_UPPER_LIMIT = 79,
    A_MINUS_LOWER_LIMIT = 80,
    A_MINUS_UPPER_LIMIT = 84,
    A_LOWER_LIMIT = 85,
    A_UPPER_LIMIT = 89,
    A_PLUS_LOWER_LIMIT = 90,
    A_PLUS_UPPER_LIMIT = 100;
    
  int roundedGrade = grade + 0.5;
  char
    letterGrade [MAX_LETTER_GRADE];

  if (roundedGrade >= F_LOWER_LIMIT && roundedGrade <= F_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'F';
    letterGrade [PLUS_MINUS_INDEX] = ' ';
  }  // if statement
  else if (roundedGrade >= D_LOWER_LIMIT && roundedGrade <= 
           D_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'D';
    letterGrade [PLUS_MINUS_INDEX] = ' ';
  }  // else if statement
  else if (roundedGrade >= C_MINUS_LOWER_LIMIT && roundedGrade <= 
           C_MINUS_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'C';
    letterGrade [PLUS_MINUS_INDEX] = '-';
  }  // else if statement
  else if (roundedGrade >= C_LOWER_LIMIT && roundedGrade <= 
           C_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'C';
    letterGrade [PLUS_MINUS_INDEX] = ' ';
  }  // else if statement
  else if (roundedGrade >= C_PLUS_LOWER_LIMIT && roundedGrade <= 
           C_PLUS_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'C';
    letterGrade [PLUS_MINUS_INDEX] = '+';
  }  // else if statement
  else if (roundedGrade >= B_MINUS_LOWER_LIMIT && roundedGrade <= 
         B_MINUS_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'B';
    letterGrade [PLUS_MINUS_INDEX] = '-';
  }  // else if statement
  else if (roundedGrade >= B_LOWER_LIMIT && roundedGrade <= 
         B_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'B';
    letterGrade [PLUS_MINUS_INDEX] = ' ';
  }  // else if statement
  else if (roundedGrade >= B_PLUS_LOWER_LIMIT && roundedGrade <= 
         B_PLUS_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'B';
    letterGrade [PLUS_MINUS_INDEX] = '+';
  }  // else if statement
  else if (roundedGrade >= A_MINUS_LOWER_LIMIT && roundedGrade <= 
         A_MINUS_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'A';
    letterGrade [PLUS_MINUS_INDEX] = '-';
  }  // else if statement
  else if (roundedGrade >= A_LOWER_LIMIT && roundedGrade <= 
         A_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'A';
    letterGrade [PLUS_MINUS_INDEX] = ' ';
  }  // else if statement
  else if (roundedGrade >= A_PLUS_LOWER_LIMIT && roundedGrade <= 
         A_PLUS_UPPER_LIMIT)
  {
    letterGrade [LETTER_INDEX] = 'A';
    letterGrade [PLUS_MINUS_INDEX] = '+';
  }  // else if statement
  else
    cout << "ERROR: " << roundedGrade << " is an invalid grade.";
  
  calculatedGradesFile << " " << letterGrade [0] << letterGrade [1] << endl;
  cout << " " << letterGrade [0] << letterGrade [1] << endl;
}  // outputLetterGrade

// Purpose: to introduce the author of the program
// Input: none
// Output: outputs the details of the author to both the console and
//         the given output file
void SayHello (ofstream & calculatedGradesFile)
{
  cout << "Name: Charles Bihis					Course: Cpsc 221\n"
       << "Student #: 43180009					Class Section: 201\n"
       << "Date: January 26, 2005				Lab Section: L2M\n\n\n";
  calculatedGradesFile << "Name: Charles Bihis					"
                       << "Course: Cpsc 221\n"
                       << "Student #: 43180009					"
                       << "Class Section: 201\n"
                       << "Date: January 26, 2005					"
                       << "Lab Section: L2M\n\n\n";
}  // SayHello

// Purpose: to signify the end of the program
// Input: none
// Output: displays a statement showing the end of the program on both
//         the console and the given output file
void SayGoodbye (ofstream & calculatedGradesFile)
{
  cout << "\n\n***** End of program *****\n";
  calculatedGradesFile << "\n\n***** End of program *****\n";
}  // SayGoodbye
