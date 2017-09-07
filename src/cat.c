/* This file is part of the UtilChest from EltaninOS
 * See LICENSE file for copyright and license details.
 */
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

#define ISDASH(x) (x[0] == '-' && x[1] == '\0')

SET_USAGE = "%s [-u] [file ...]";

static void
cat(int f, const char *name)
{
	char buf[BUFSIZ];
	ssize_t n;

	while ((n = read(f, buf, sizeof(buf))) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err(1, "write %s", name);

	if (n < 0)
		err(1, "read %s", name);
}

int
main(int argc, char *argv[])
{
	int f, rval = 0;

	setprogname(argv[0]);

	ARGBEGIN {
	case 'u':
		break;
	default:
		wrong(usage);
	} ARGEND

	if (!argc)
		cat(STDIN_FILENO, "<stdin>");

	for (; *argv; argv++) {
		if (ISDASH(*argv)) {
			*argv = "<stdin>";
			f = STDIN_FILENO;
		} else if ((f = open(*argv, O_RDONLY, 0)) < 0) {
			warn("open %s", *argv);
			rval = 1;
			continue;
		}

		cat(f, *argv);

		if (f != STDIN_FILENO)
			close(f);
	}

	return rval;
}
