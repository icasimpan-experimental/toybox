/* vi: set sw=4 ts=4:
 *
 * nice.c - Run a program at a different niceness level.
 *
 * Copyright 2010 Rob Landley <rob@landley.net>
 *
 * See http://www.opengroup.org/onlinepubs/9699919799/utilities/nice.html

USE_NICE(NEWTOY(nice, "^<1n#", TOYFLAG_USR|TOYFLAG_BIN))

config NICE
	bool "nice"
	default y
	help
	  usage: nice [-n PRIORITY] command [args...]

	  Run a command line at an increased or decreased scheduling priority.

	  Higher numbers make a program yield more CPU time, from 20 (lowest
	  priority) to -19 (highest).  By default processes inherit their parent's
	  niceness (usually 0).  By default this command adds 10 to the parent's
	  priority.  Only root can set a negative niceness level.
*/

#include "toys.h"

// Hello doesn't use these globals, they're here for example/skeleton purposes.

DEFINE_GLOBALS(
	long priority;
)

#define TT this.nice

void nice_main(void)
{
	if (!toys.optflags) TT.priority = 10;

	nice(TT.priority);
	if (getpriority(PRIO_PROCESS, getpid()) != TT.priority)
		perror_exit("Can't set priority");

	xexec(toys.optargs);
}
