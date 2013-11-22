function checkDate()
{

    var monthLength = new Array(31,28,31,30,31,30,31,31,30,31,30,31);
	
	var objstartDateDay = xgene360_cu.Element( 'StartDateDay' );
	var sday = parseInt(objstartDateDay.value);

	var objstartDateMonth = xgene360_cu.Element( 'StartDateMonth' );
	var smonth = parseInt(objstartDateMonth.value);

	var objstartDateYear = xgene360_cu.Element( 'StartDateYear' );
	var syear = parseInt(objstartDateYear.value);

	var objstartDateMinute = xgene360_cu.Element( 'StartDateMinute' );
	var smin = parseInt(objstartDateMinute.value);

	var objstartDateHour = xgene360_cu.Element( 'StartDateHour' );
	var shour = parseInt(objstartDateHour.value);

	var objstartDateAPM = xgene360_cu.Element( 'StartDateAPM' );
	var sapm = objstartDateAPM.value;

	var objendDateDay = xgene360_cu.Element( 'EndDateDay' );
	var eday = parseInt(objendDateDay.value);

	var objendDateMonth = xgene360_cu.Element( 'EndDateMonth' );
	var emonth = parseInt(objendDateMonth.value);    

	var objendDateYear = xgene360_cu.Element( 'EndDateYear' );
	var eyear = parseInt(objendDateYear.value);

	var objEndDateMinute = xgene360_cu.Element( 'EndDateMinute' );
	var emin = parseInt(objEndDateMinute.value);

	var objEndDateHour = xgene360_cu.Element( 'EndDateHour' );
	var ehour = parseInt(objEndDateHour.value);

	var objEndDateAPM = xgene360_cu.Element( 'EndDateAPM' );
	var eapm = objEndDateAPM.value;

	if (!sday || !smonth)
		{ alert('Start Date of problem is invalid.'); return false; }
    if (!eday || !emonth)
		{ alert('Due Date of problem is invalid.'); return false; }

	if (syear/4 == parseInt(syear/4))
		monthLength[1] = 29;

	if (sday > monthLength[smonth-1])
		{ alert('Start Date of problem is invalid.'); objstartDateDay.focus(); return false; }
	
	monthLength[1] = 28;
	
	if (eyear/4 == parseInt(eyear/4))
		monthLength[1] = 29;	
    if (eday > monthLength[emonth-1])
		{ alert('Due Date of problem is invalid.'); objendDateDay.focus(); return false; }

	var dateToCheck1 = new Date();
	dateToCheck1.setYear(syear);
	dateToCheck1.setMonth(smonth-1);
	dateToCheck1.setDate(sday);
	var startdatetime = dateToCheck1.getTime();
	
	var dateToCheck2 = new Date();
	dateToCheck2.setYear(eyear);
	dateToCheck2.setMonth(emonth-1);
	dateToCheck2.setDate(eday);
	var enddatetime = dateToCheck2.getTime();
	
	if ( enddatetime < startdatetime )
	{ alert('Problem due date is set before the start date.'); 
	  objstartDateDay.focus();
	  return false; }
	else {
	
		if (enddatetime == startdatetime)
		{   
			if ( eapm == 'AM' && sapm == 'PM' )
			{ alert('Problem due date (AM) is set before the start date (PM).'); 
			objstartDateHour.focus();
			return false; }
			else
			{ if ((eapm == 'AM' && sapm == 'AM') || (eapm == 'PM' && sapm == 'PM'))
			  {
			    if (ehour < shour)
			    {
			      alert('Problem due date hour is set before the start date hour.'); 
		          objstartDateHour.focus();
			      return false;
			    }
			    else
			    {
			      if ((ehour == shour) && (emin < smin))
			      {
			        alert('Problem due date minute is set before the start date minute.'); 
		            objstartDateMinute.focus();
			        return false;
			      }
			    }
			    
			    
			  }
			}
		}
    
	}

	return true;
}


function resetCreateProblemForm()
{
  return confirm( 'Clear the form?' );
}

function resetUpdateProblemForm()
{
  return confirm( 'Reset the form to original values?' );
}
