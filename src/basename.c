/* This file is part of the UtilChest from Draco Project
 * See LICENSE file for copyright and license details.
 */
#include <libgen.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

static void
usage(void) {
	perr(1, "usage: %s string [suffix]\n", argv0);
}

int
main(int argc, char *argv[]) {
	char *p;
	ssize_t off;

	argv0 = *argv, argc--, argv++;

	if (argc != 1 && argc != 2)
		usage();

	p = basename(*argv++);
	if (*argv) {
		off = strlen(p) - strlen(*argv);
		if (off > 0 && !strcmp(p + off, *argv))
			p[off] = '\0';
	}
	puts(p);

	return (fshut(stdout, "<stdout>"));
}