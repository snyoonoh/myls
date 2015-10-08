/*
 * Filename: buildFileInfoTable.c
 * Author: Seung Yoon Oh
 * Date: Dec 2, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//lstat
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: buildFileInfoTable 
 * Function prototype: int buildFileInfoTable (const char* filename, 
 *                                             struct fileInfo** const tablePtr)
 * Description: buildFileInfoTable() takes the file/directory name and the 
 * address of the pointer to struct fileInfo back in main() that we will fill 
 * in based on our dynamic building of this fileInfo table. This second arg is 
 * just like endptr in strtol() -- strtol() needs to set the pointer back in 
 * the calling function -- buildFileInfoTable() needs to set this pointer back 
 * in the calling function main(). 
 * Parameters:
 *      arg1: const char* filename -- character pointer to filename
 *      arg2: struct fileInfo** const tablePtr -- struct fileInfo type double
 *                                             pointer to const tablePtr
 * Side Effects: None
 * Error Conditions: None
 * Return Value: number of entries
 */

int
buildFileInfoTable 
(const char* filename, struct fileInfo** const tablePtr){
    struct stat mode;
    struct fileInfo* fi = NULL;
    struct fileInfo* fi2;
    char filePath[BUFSIZ];
    int numOfEntries = 0;

    //Use memset so structs dont have garbage
    (void) memset(&mode, 0, sizeof(mode));
    (void) memset(&fi, 0, sizeof(fi));
    (void) memset(&fi2, 0, sizeof(fi2));

    /* 
     * Update stat to see if it is directory and print an error if file does
     * not exist
     */
    if((lstat(filename, &mode)) == -1){
        (void) fprintf(stderr, "%s", STR_LSTAT_ERR);
        perror(filename);
        return 0;
    }


    //this is a directory
    if(S_ISDIR(mode.st_mode)){

        (void) fprintf(stdout, "%s:\n", filename);
        DIR *dir;
        struct dirent *dp;
        dir = opendir(filename);

        //displaying opendir error
        if(dir == NULL){
            (void) fprintf(stderr, STR_OPENDIR_ERR);
            perror(filename);
            return 0;
        }

        //loop to read all the files within a directory
        while((dp=readdir(dir)) != NULL) {
            (void) snprintf( filePath, BUFSIZ, 
                                           "%s/%s", filename, dp -> d_name); 
            //(void) fprintf(stdout, "%s\n", filePath);


            if((lstat( filePath , &mode )) == -1){
                (void) fprintf(stderr, "%s", STR_LSTAT_ERR);
                perror(filePath);
                return 0;
            }

            fi2 = (struct fileInfo*) realloc (fi, 
                    (sizeof(struct fileInfo))*(numOfEntries+1));

            //realloc error
            if(fi2 == NULL){
                perror(STR_ALLOC_ERR);
                (void) fprintf(stderr, STR_PARTIAL_INFO);
                *(tablePtr) = fi;
                (void) closedir(dir);
                return numOfEntries;
            }

            fi = fi2;
            (void) strcpy((*(fi2+numOfEntries)).name, dp -> d_name);
            (*(fi2+numOfEntries)).stbuf = mode;
            *tablePtr = fi2;

            numOfEntries++;
        }
        (void) closedir(dir);
        return numOfEntries;

    }

    //this is not a directory
    else{
        fi = (struct fileInfo*) malloc(sizeof(struct fileInfo));

        //if we get a malloc error
        if( fi == NULL){
            perror(STR_ALLOC_ERR);
            (void) fprintf(stderr, STR_PARTIAL_INFO);
            return 0;
        }

        //copying the info from struct fileInfo into the malloc
        (void) strcpy(fi->name, filename);
        fi -> stbuf = mode;
        *tablePtr = fi;
        numOfEntries = 1;
        return numOfEntries;
    }

}
