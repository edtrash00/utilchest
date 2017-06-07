/* This file is part of the UtilChest from Draco Project
 * See LICENSE file for copyright and license details.
 */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

static void
usage(void) {
	perr(1, "usage: %s [name]", argv0);
}

int
main(int argc, char *argv[]) {
	char host[HOST_NAME_MAX+1];

	argv0 = *argv, argc--, argv++;

	if (argc > 1)
		usage();

	if (argc == 1) {
		if (sethostname(*argv, strlen(*argv)))
			perr(1, "sethostname:");
	} else {
		if (gethostname(host, sizeof(host)))
			perr(1, "gethostname:");

		puts(host);
	}

	return (fshut(stdout, "<stdout>"));
}