#include <sys/stat.h>

#include <err.h>
#include <errno.h>

#include "util.h"

int
chmodfile(const char *s, mode_t mode, int depth)
{
	struct stat st;

	if ((FS_FOLLOW(depth) ? stat : lstat)(s, &st) < 0) {
		warn("(l)stat %s", s);
		return 1;
	}

	if (chmod(s, mode ? mode : st.st_mode) < 0) {
		warn("chmod %s", s);
		return 1;
	}

	return 0;
}

int
chmoddir(const char *s, mode_t mode, int depth)
{
	FS_DIR dir;
	int rd, rval;

	rval = 0;

	if (open_dir(&dir, s) < 0) {
		if (!(rval = errno != ENOTDIR))
			rval = chmodfile(s, mode, depth);
		else
			warn("open_dir %s", s);

		return rval;
	}

	while ((rd = read_dir(&dir, depth)) == FS_EXEC) {
		if (ISDOT(dir.name))
			continue;

		rval |= chmodfile(dir.path, mode, depth);

		if (S_ISDIR(dir.info.st_mode))
			rval |= chmoddir(dir.path, mode, depth+1);
	}

	if (rd < 0) {
		warn("read_dir %s", dir.path);
		return 1;
	}

	return rval;
}