#include "IO/Directory.h"

Directory::Directory()
{
}

Directory::~Directory()
{
}

Directory *Directory::Open(char *directory)
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("c:\\src\\")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
	else {
		perror("");
		return EXIT_FAILURE;
	}
}
