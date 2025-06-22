#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char filePath[1024];
    const char *name = "TEMP";
#ifdef _WIN32
    const char *pathSep = "\\";
#else
    const char *pathSep = "/";
#endif
    const char *fileName = "soundfont.dls";
    const char *tmpdir = getenv(name);

    memset(filePath, 0, sizeof(filePath));
    strcpy(filePath, tmpdir);
    if (tmpdir[strlen(tmpdir) - 1] != *pathSep) {
        strcat(filePath, pathSep);
    }
    strcat(filePath, fileName);

    fprintf(stderr, "%s is: %s\n", name, tmpdir);
    fprintf(stderr, "filePath is: %s\n", filePath);

    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        fprintf(stderr, "File opening failed!\n");
        return EXIT_FAILURE;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
