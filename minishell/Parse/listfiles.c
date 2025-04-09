#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    if (errno && !entry) {  // Check if readdir() failed mid-loop
        perror("readdir");
    }

    if (closedir(dir) == -1) {
        perror("closedir");
    }

    return 0;
}

// gcc listfiles.c -o listfiles

/*
These functions are used for directory operations in Unix-like systems, allowing you to open, read, and close directories. They are declared in <dirent.h> and are essential for traversing filesystem directories programmatically.

1. opendir() – Open a Directory
Purpose: Opens a directory stream for reading.
Syntax:

c
Copy
#include <dirent.h>
DIR *opendir(const char *dirname);
Parameters:

dirname: Path to the directory (e.g., "." for current directory, "/home/user" for an absolute path).

Return Value:

On success: Returns a pointer to a DIR structure (used for subsequent readdir() calls).

On failure: Returns NULL (errno is set to indicate the error, e.g., ENOENT if the directory does not exist).

Example:

c
Copy
DIR *dir = opendir(".");
if (!dir) {
    perror("opendir failed");
    exit(1);
}
2. readdir() – Read Directory Entries
Purpose: Reads the next entry in a directory stream.
Syntax:

c
Copy
#include <dirent.h>
struct dirent *readdir(DIR *dirp);
Parameters:

dirp: Pointer to the DIR structure returned by opendir().

Return Value:

On success: Returns a pointer to a struct dirent containing the next directory entry.

On failure/end-of-directory: Returns NULL (check errno to distinguish errors from EOF).

struct dirent Fields:

d_name: Name of the file/subdirectory (null-terminated string).

d_type: File type (if supported, e.g., DT_REG for regular files, DT_DIR for directories).

Example:

c
Copy
struct dirent *entry;
while ((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
}
3. closedir() – Close a Directory Stream
Purpose: Closes an open directory stream and releases resources.
Syntax:

c
Copy
#include <dirent.h>
int closedir(DIR *dirp);
Parameters:

dirp: Pointer to the DIR structure returned by opendir().

Return Value:

On success: Returns 0.

On failure: Returns -1 (errno is set, e.g., EBADF if the directory stream is invalid).
File Types:

Use d_type (if available) to filter files vs. directories:

c
Copy
if (entry->d_type == DT_DIR) {
    printf("Directory: %s\n", entry->d_name);
}
Thread Safety:

These functions are not thread-safe by default. Use readdir_r() (deprecated in newer POSIX) or mutexes in multithreaded programs.

*/