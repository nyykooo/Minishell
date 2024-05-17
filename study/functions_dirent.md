## <dirent.h>

### 1. _opendir_  

_DIR *opendir(const char *name);_  

-- const char *name: This is the path of the directory you want to open.

Return: The function returns a pointer to a DIR type that can be used with other functions in the <dirent.h> library to read the contents of the directory. 
If an error occurs when opening the directory (for example, if the directory doesn't exist or if the process doesn't have permission to read the directory), the function will return NULL.

When you have finished reading the directory, you must close it using the closedir function to avoid resource leaks.

### 2. _closedir_

_int closedir(DIR *dirp);_  

-- dirp: This is a pointer to an open directory, which was returned by opendir

Return: The function returns 0 in case of success. If an error occurs, -1 is returned and errno is set appropriately. For example, if dirp is not a valid pointer to an open directory, closeir will fail.

### 3. _readdir_

_struct dirent *readdir(DIR *dirp);_  

-- dirp: This is a pointer to an open directory, which was returned by opendir.

The function returns a pointer to a dirent structure representing the next entry in the directory. If there are no more entries or if an error occurs, it returns NULL.

The dirent structure has several members, but the most commonly used are:

	d_name: The name of the entry.
	d_ino: The inode number of the entry.

You normally use readdir in a loop to read all the entries in a directory. Remember that the first two entries returned by readdir are usually “.” (the current directory) and “..” (the parent directory).

## Example of usage
```
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dirp = opendir(".");
    if (dirp == NULL) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        printf("%s\n", dp->d_name);
    }

    closedir(dirp);
    return 0;
}
```

## What is an Inode Number?

The inode number (or “index node”) is a unique identifier for a file or directory on a Unix/Linux file system. Each file or directory has an inode that contains information about the file/directory, such as its size, creation date, modification date, owner and permissions.

The inode number is used internally by the file system to identify the file or directory. For example, when you open a file, the operating system uses the inode number to find the file data on the disk.

It is important to note that the name of the file is not stored in the inode, but in the directory containing the file. A directory is essentially a list of pairs (file name, inode number). This allows the same file (i.e. the same inode) to have several different names in different directories, which is the basis for creating symbolic links and hard links.
