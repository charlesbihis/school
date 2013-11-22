/*
 * Copyright (c) 1983, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef linux
#include <sys/ttydefaults.h> 
#endif
#include "hangman.h"

/*
 * getguess: Get another guess
 */
void getguess()
{
    int i;
    int ch;
    bool correct;
    
    leaveok(stdscr, FALSE);
    for (;;) 
    {
        /* Get a character from the user */
        move(PROMPTY, PROMPTX + sizeof "Guess: ");
        refresh();
        ch = readch();
        if (isalpha(ch)) 
        {
            if (isupper(ch))
            {
	        /* We only want lower-case characters */
                ch = tolower(ch);
            }
            
            if (Guessed[ch - 'a'])	// fixes bug 3
            {
	        /* The character has already been guessed */
                mvprintw(MESGY, MESGX, "Already guessed '%c'", ch);
            }
            else
            {
                break;
            }
        } 
        else
        {
	    /* Not a letter */
            mvprintw(MESGY, MESGX, "Not a valid guess: '%s'", unctrl(ch));
        }
    }
    leaveok(stdscr, TRUE);
    move(MESGY, MESGX);
    clrtoeol();
    
    /* Mark the current letter that has been guessed */
    Guessed[ch - 'a'] = TRUE;
    correct = FALSE;

    /* Fill in this letter in the word wherever it should appear */
    for (i = 0; Word[i] != '\0'; i++)
    {
        if (Word[i] == ch) 
        {
            Known[i] = ch;
            correct = TRUE;
        }
    }
    
    if (!correct)
    {
        Errors++;
    }
}

/*
 * readch: Read a character from the input
 */
int readch()
{
    int count;
    char ch;
    
    count = 0;
    for (;;) 
    {
        /* Attempt to read a character */
        if (read(0, &ch, sizeof ch) <= 0) 
        {
            if (++count > 100)
            {
                die(0);
            }
        } 
        else
        {
	  return ch;	  
        }
    }
}

