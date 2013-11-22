int main (int argc, char *argv[])
{
  char *fname;

  SayHello ();
  fname = argv[1];
  if (decode (fname))
    printf ("\nProgram terminated.\n\n");
  SayGoodbye ();
}  // main
