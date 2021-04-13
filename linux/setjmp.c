#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

jmp_buf main_loop;

void
abort_to_main_loop (int status)
{
  longjmp (main_loop, status);
}

void
do_command (void)
{
	char buffer[128];
	if (fgets (buffer, 128, stdin) == NULL)
		abort_to_main_loop (-1);
	else
		exit (EXIT_SUCCESS);
}

int
main (void)
{
	while (1)
		if (setjmp (main_loop))
			puts ("Back at main loop....");
		else
			do_command ();
}


