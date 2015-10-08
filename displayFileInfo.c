/*
 * Filename: displayFileInfo.c
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Date: Dec 9, 2014
 */

#include <stdio.h>
#include <stdlib.h>

//strlen
#include <string.h>

//Basename
#include <libgen.h>

//lstat
#include <unistd.h>
#include <dirent.h>

//for major minor
#include <sys/types.h>
#include <sys/mkdev.h>

//time
#include <time.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: displayFileInfo()
 * Function prototype: int displayFileInfo( struct fileInfo* const table, 
 *                                    const int entries, const int displayMode )
 * Description: displayFileInfo() will check to see if the table should be 
 * sorted by file size (st_size) [-S option] and if so whether it should be
 * sorted in reverse order of the default [-r option]. Else we are displaying 
 * via default alphabetic order on the name of the files so check to see if 
 * the -r flag had been specified to determine if the sort is reverse of the 
 * default. 
 *       arg1 -- struct fileInfo* const table: struct fileInfo pointer to a
 *                                             table with all the files
 *       arg2 -- const int entire: number of entries
 *       arg2 -- const int displayMode: int that represent corresponding flags
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 */

void
displayFileInfo
( struct fileInfo* const table, const int entries, const int displayMode ){

    //used later for loops
    int i;

    //used later with ctime
    char* time;

    //used in string manip
    char* ptr;
    char* ptr2;
    char* ptr3;

    //for time since 01/01/1970
    struct timeval now;


    /* Sorting by Name */
    if((displayMode & SFLAG) == 0){
        //if r flag is set
        if((displayMode & RFLAG) == RFLAG){
            qsort(table, entries, sizeof(struct fileInfo), nameSortDescending);
        }
        else{
            //default (sort name in ascending order)
            qsort(table, entries, sizeof(struct fileInfo), nameSortAscending);
        }
    }

    /* Sorting by Size */
    if((displayMode & SFLAG) == SFLAG){
        //if r flag is set
        if((displayMode & RFLAG) == RFLAG){
            qsort(table, entries, sizeof(struct fileInfo), sizeSortAscending);
        }

        //if r flag is not set
        else{
            qsort(table, entries, sizeof(struct fileInfo), sizeSortDescending);
        }
    }


    for(i = 0; i < entries; i++){

        /* A flag */
        if( ((displayMode & AFLAG) == 0) && (table[i].name[0] == '.') ){
            //ignore invisible files
            continue;
        }

        /* B flag */

        if( ((displayMode & BFLAG) == BFLAG) && (table[i].name
                    [strlen(table[i].name)-1] == '~') ){
            //ignore files ending in ~
            continue;
        }


        /* if l flag was set */
        if((displayMode & LFLAG) == LFLAG){

            //if file is directory
            if(S_ISDIR(table[i].stbuf.st_mode)){
                (void) fprintf(stdout, "%c", 'd');
            }

            //if file is symbolic link
            else if(S_ISLNK(table[i].stbuf.st_mode)){
                (void) fprintf(stdout, "%c", 'l');
            }

            //if file is a block special file
            else if(S_ISBLK(table[i].stbuf.st_mode)){
                (void) fprintf(stdout, "%c", 'b');
            }

            //if file is a character special file
            else if(S_ISCHR(table[i].stbuf.st_mode)){
                (void) fprintf(stdout, "%c", 'c');
            }

            //default
            else{
                (void) fprintf(stdout, "%c", '-');
            }

            //display Permissions
            displayPermissions(table[i].stbuf.st_mode);

            //print number of links
            (void) fprintf(stdout, STR_NLINK, table[i].stbuf.st_nlink);

            //display OwnerName
            displayOwnerName(table[i].stbuf.st_uid);

            //display GroupName
            displayGroupName(table[i].stbuf.st_gid);

            //print size (major minor) for block and char special files
            if((S_ISBLK(table[i].stbuf.st_mode)) || 
                    (S_ISCHR(table[i].stbuf.st_mode))){
                (void) fprintf(stdout, STR_MAJOR_MINOR, 
                        major(table[i].stbuf.st_rdev), 
                        minor(table[i].stbuf.st_rdev));
            }
            //otherwise just print the size
            else{
                (void) fprintf(stdout, STR_SIZE, table[i].stbuf.st_size);
            }


            //print modification time (Month Day Hour:Min)
            // [15724800] seconds in six months
            time = ctime(&(table[i].stbuf.st_mtime));

            ptr = strchr(time, ' ');

            //get current time
            (void) gettimeofday (&now, NULL);
            //print month day year if the file's mod time is 6 months or older
            if(table[i].stbuf.st_mtime < (now.tv_sec-15724800)){
                ptr2 = strrchr(time,' ');
                ptr3 = strchr(time, ':');
                *(ptr3-3) = '\0';

                *(ptr2+(((int)strlen(ptr2))-1)) = '\0';

                (void) fprintf(stdout, "%s ", ptr+1);
                (void) fprintf(stdout, "%s ", ptr2);

            }
            //otherwise just print month day and time
            else{
                ptr2 = strrchr(time,':');
                *ptr2 = '\0';
                (void) fprintf(stdout, "%s ", ptr+1);
            }


        }


        //print every file
        (void) fprintf(stdout, "%s\n", table[i].name);
    }

    return;
}
