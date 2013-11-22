#!/bin/csh
# toLower.csh

echo "*** toLower ***"
set lettersString = 'y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/'
set files = (*.cpp *.CPP *.h *.H)
foreach file ($files)
  if (-d "$file") then
    echo "   ERROR: $file is a directory and will not be renamed."
  else if (`echo $file | sed $lettersString` == $file) then
    echo "   ERROR: $file is already named in lowercase so it will not be renamed."
  else if (-e `echo $file | sed $lettersString`) then
    echo "   ERROR: `echo $file | sed $lettersString` already exists and $file will not be renamed."
  else
    mv ./$file ./`echo $file | sed $lettersString`
    echo "   $file has been successfully renamed to `echo $file | sed $lettersString`"
  endif
end
echo "*** Done! ***"
