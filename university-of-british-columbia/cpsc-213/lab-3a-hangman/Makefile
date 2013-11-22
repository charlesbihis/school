#HANGMAN(6)                   BSD Reference Manual                   HANGMAN(6)
#
#NAME
#     hangman - Computer version of the game hangman
#
#SYNOPSIS
#     hangman
#
#DESCRIPTION
#     In hangman, the computer picks a word from the on-line word list and 
#     you must try to guess it.  The computer keeps track of which letters 
#     have been guessed and how many wrong guesses you have made on the screen 
#     in a graphic fashion.
#
#FILES
#     /usr/share/dict/words	On-line word list
#     or
#     words			Local word list
#
#AUTHOR
#     Ken Arnold
#
#
#BSDI BSD/OS                      May 31, 1993                                1

CC=	gcc
CFLAGS=	-g
PROG=   hangman
SRCS=   endgame.c  extern.c getguess.c getword.c main.c \
	playgame.c prdata.c prman.c    prword.c  setup.c
OBJS=	$(SRCS:.c=.o)
LIBS=	-lcurses	# may need termcap

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -rf $(PROG) $(OBJS) *~ *.bak *.gz


# DO NOT DELETE

endgame.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
endgame.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
endgame.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
endgame.o: /usr/include/sys/time.h /usr/include/sys/time.h
endgame.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
endgame.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
endgame.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
endgame.o: /usr/include/widec.h /usr/include/stdio.h
endgame.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
endgame.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
endgame.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
endgame.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
endgame.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
endgame.o: /usr/include/unctrl.h /usr/include/signal.h
endgame.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
endgame.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
endgame.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
endgame.o: /usr/include/string.h /usr/include/iso/string_iso.h
endgame.o: /usr/include/unistd.h pathnames.h
extern.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
extern.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
extern.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
extern.o: /usr/include/sys/time.h /usr/include/sys/time.h
extern.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
extern.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
extern.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
extern.o: /usr/include/widec.h /usr/include/stdio.h
extern.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
extern.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
extern.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
extern.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
extern.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
extern.o: /usr/include/unctrl.h /usr/include/signal.h
extern.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
extern.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
extern.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
extern.o: /usr/include/string.h /usr/include/iso/string_iso.h
extern.o: /usr/include/unistd.h pathnames.h
getguess.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
getguess.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
getguess.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
getguess.o: /usr/include/sys/time.h /usr/include/sys/time.h
getguess.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
getguess.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
getguess.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
getguess.o: /usr/include/widec.h /usr/include/stdio.h
getguess.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
getguess.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
getguess.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
getguess.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
getguess.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
getguess.o: /usr/include/unctrl.h /usr/include/signal.h
getguess.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
getguess.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
getguess.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
getguess.o: /usr/include/string.h /usr/include/iso/string_iso.h
getguess.o: /usr/include/unistd.h pathnames.h
getword.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
getword.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
getword.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
getword.o: /usr/include/sys/time.h /usr/include/sys/time.h
getword.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
getword.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
getword.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
getword.o: /usr/include/widec.h /usr/include/stdio.h
getword.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
getword.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
getword.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
getword.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
getword.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
getword.o: /usr/include/unctrl.h /usr/include/signal.h
getword.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
getword.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
getword.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
getword.o: /usr/include/string.h /usr/include/iso/string_iso.h
getword.o: /usr/include/unistd.h pathnames.h
main.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
main.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
main.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
main.o: /usr/include/sys/time.h /usr/include/sys/time.h
main.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
main.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
main.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
main.o: /usr/include/widec.h /usr/include/stdio.h
main.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
main.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h /usr/include/euc.h
main.o: /usr/include/sys/euc.h /usr/include/wchar.h
main.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
main.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
main.o: /usr/include/unctrl.h /usr/include/signal.h
main.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
main.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
main.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
main.o: /usr/include/string.h /usr/include/iso/string_iso.h
main.o: /usr/include/unistd.h pathnames.h
playgame.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
playgame.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
playgame.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
playgame.o: /usr/include/sys/time.h /usr/include/sys/time.h
playgame.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
playgame.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
playgame.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
playgame.o: /usr/include/widec.h /usr/include/stdio.h
playgame.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
playgame.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
playgame.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
playgame.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
playgame.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
playgame.o: /usr/include/unctrl.h /usr/include/signal.h
playgame.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
playgame.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
playgame.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
playgame.o: /usr/include/string.h /usr/include/iso/string_iso.h
playgame.o: /usr/include/unistd.h pathnames.h
prdata.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
prdata.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
prdata.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
prdata.o: /usr/include/sys/time.h /usr/include/sys/time.h
prdata.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
prdata.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
prdata.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
prdata.o: /usr/include/widec.h /usr/include/stdio.h
prdata.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
prdata.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
prdata.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
prdata.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
prdata.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
prdata.o: /usr/include/unctrl.h /usr/include/signal.h
prdata.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
prdata.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
prdata.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
prdata.o: /usr/include/string.h /usr/include/iso/string_iso.h
prdata.o: /usr/include/unistd.h pathnames.h
prman.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
prman.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
prman.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
prman.o: /usr/include/sys/time.h /usr/include/sys/time.h
prman.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
prman.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
prman.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
prman.o: /usr/include/widec.h /usr/include/stdio.h
prman.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
prman.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
prman.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
prman.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
prman.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
prman.o: /usr/include/unctrl.h /usr/include/signal.h
prman.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
prman.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
prman.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
prman.o: /usr/include/string.h /usr/include/iso/string_iso.h
prman.o: /usr/include/unistd.h pathnames.h
prword.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
prword.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
prword.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
prword.o: /usr/include/sys/time.h /usr/include/sys/time.h
prword.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
prword.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
prword.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
prword.o: /usr/include/widec.h /usr/include/stdio.h
prword.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
prword.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
prword.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
prword.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
prword.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
prword.o: /usr/include/unctrl.h /usr/include/signal.h
prword.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
prword.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
prword.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
prword.o: /usr/include/string.h /usr/include/iso/string_iso.h
prword.o: /usr/include/unistd.h pathnames.h
setup.o: hangman.h /usr/include/sys/types.h /usr/include/sys/isa_defs.h
setup.o: /usr/include/sys/feature_tests.h /usr/include/sys/machtypes.h
setup.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
setup.o: /usr/include/sys/time.h /usr/include/sys/time.h
setup.o: /usr/include/sys/stat.h /usr/include/sys/time_impl.h
setup.o: /usr/include/sys/stat_impl.h /usr/include/ctype.h
setup.o: /usr/include/iso/ctype_iso.h /usr/include/curses.h
setup.o: /usr/include/widec.h /usr/include/stdio.h
setup.o: /usr/include/iso/stdio_iso.h /usr/include/sys/va_list.h
setup.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
setup.o: /usr/include/euc.h /usr/include/sys/euc.h /usr/include/wchar.h
setup.o: /usr/include/iso/wchar_iso.h /usr/include/wchar_impl.h
setup.o: /usr/include/iso/time_iso.h /usr/include/sgtty.h
setup.o: /usr/include/unctrl.h /usr/include/signal.h
setup.o: /usr/include/iso/signal_iso.h /usr/include/sys/iso/signal_iso.h
setup.o: /usr/include/sys/unistd.h /usr/include/sys/signal.h
setup.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
setup.o: /usr/include/string.h /usr/include/iso/string_iso.h
setup.o: /usr/include/unistd.h pathnames.h
