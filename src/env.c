#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

extern char **environ;

static void
usage(void)
{
	fprintf(stderr, "usage: %s [-i] [name=value ...] [command]\n",
	        getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	setprogname(argv[0]);

	ARGBEGIN {
	case 'i':
		*environ = NULL;
		break;
	default:
		usage();
	} ARGEND

	for (; *argv && strchr(*argv, '='); argc--, argv++)
		putenv(*argv);

	if (*argv) {
		execvp(*argv, argv);
		err(126 + (errno == ENOENT), "execvp %s", *argv);
	}

	for (; *environ; environ++)
		puts(*environ);

	return (ioshut());
}
