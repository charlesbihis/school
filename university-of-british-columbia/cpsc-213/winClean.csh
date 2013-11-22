#!/bin/csh
# winClean.csh

echo "*** winClean ***"
set files = (*.txt *.TXT)
foreach file ($files)
  if (-d "$file") then
    echo "   ERROR: $file is a directory."
  else if (! (-r "$file")) then
    echo "   ERROR: You do not have read permission on $file."
  else if (! (-w "$file")) then
    echo "   ERROR: You do not have write permission on $file."
  else 
    echo "   $file has been converted." 
    dos2unix -437 -ascii $file $file
  endif
end
echo "*** Done! ***"
