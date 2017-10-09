#include <sys/stat.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static void
usage(void)
{
	fprintf(stderr, "usage: %s [-m mode] file ...\n", getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	int rval = 0;
	mode_t mode = DEFFILEMODE;

	setprogname(argv[0]);

	ARGBEGIN {
	case 'm':
		mode = strtomode(EARGF(usage()), DEFFILEMODE);
		break;
	default:
		usage();
	} ARGEND

	if (!argc)
		usage();

	for (; *argv; argc--, argv++) {
		if (mkfifo(*argv, mode) < 0) {
			warn("mkfifo %s", *argv);
			rval = 1;
		}
	}

	return rval;
}
