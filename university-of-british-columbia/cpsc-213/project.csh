#!/bin/csh
# project.csh

echo "*** project ***"
set mailList = (i8a3 i3b2 someID anotherID)
foreach name (`sessask -l prevost gambier valdes bowen pender | cut -d ' ' -f1 | sort | uniq`)
  foreach groupName ($mailList)
    if ($name == $groupName) then
      /usr/lib/sendmail $name@ugrad.cs.ubc.ca <<EOF
      REMINDER: We have a group meeting this Thursday!"
EOF
      echo "   $name is currently logged onto the system."
      echo "     -mailing $name...Done"
    endif
  end
end
echo "*** Done! ***" 
