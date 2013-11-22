function validateUpdateCourseForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  var objCourseName = xgene360_cu.Element( 'CourseName' );
  var objCourseDescription = xgene360_cu.Element( 'CourseDescription' );
  
  var strCourseName = objCourseName.value.trim().escape();
  var strCourseDescription = objCourseDescription.value.trim().escape();
  
  if ( strCourseName.length == 0 )
  {
    alert( 'Please enter the course name' );
    objCourseName.focus();    
    return false;
  }
  
  if ( strCourseDescription.length == 0 )
  {
    alert( 'Please enter the course description' );
    objCourseDescription.focus();
    return false;
  }
  
  objCourseName.value = strCourseName;
  objCourseDescription.value = strCourseDescription;
  
  return true;
}

function resetUpdateCourseForm()
{
  return confirm( 'Reset the form?' );
}

