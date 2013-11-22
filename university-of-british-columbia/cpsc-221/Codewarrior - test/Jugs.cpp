#include <iostream.h>
#include "Jugs.h"

JugType :: JugType ()
{
  Capacity = 10;
  Contents = 0;
}

JugType :: JugType (int Cap)
{
  Capacity = Cap;
  Contents = 0;
}

int JugType :: GetContents () const
{
  return Contents;
}

int JugType :: GetCapacity () const
{
  return Capacity;
}

void JugType :: Fill ()
{
  Contents = Capacity;
}

void JugType :: Empty ()
{
  Contents = 0;
}