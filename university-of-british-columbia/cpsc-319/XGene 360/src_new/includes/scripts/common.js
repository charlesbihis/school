function openCourseDetail( strCourseId )
{
  xgene360_cu.setLocation( './viewcourse.php?CourseId=' + strCourseId );
}

function openProblemDetail( strProblemId )
{
  xgene360_cu.setLocation( './viewproblem.php?ProblemId=' + strProblemId );
}

function openProfessorDetail( strProfessorId )
{
  xgene360_cu.setLocation( './viewprofessor.php?ProfessorId=' + strProfessorId );
}

function openTADetail( strTAId )
{
  xgene360_cu.setLocation( './viewta.php?TAId=' + strTAId );
}

function openStudentDetail( strStudentId )
{
  xgene360_cu.setLocation( './viewstudent.php?StudentId=' + strStudentId );
}

function hightlightSelectedRow( objElement, bHightlight )
{
  if ( bHightlight )
  {
    objElement.className = 'highlight';
    xgene360_cu.useHandCursor( objElement );
  }
  
  else
  {
    objElement.className = '';
    xgene360_cu.useRegularCursor( objElement );
  }
}
