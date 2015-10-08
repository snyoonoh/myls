/*
 * Filename: displayPermissions.c
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Date: Dec 2, 2014
 */

#include <stdio.h>
#include <stdlib.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: displayPermissions 
 * Function prototype: void displayPermissions (const mode_t mode)
 * Description: This routine prints out the various rwx permissions for 
 * the owner, group, and others. A - (dash) indicates that permission bit 
 * is not set.
 * Parameters:
 *      arg1: const mode_t mode -- the permissions that are flagged according
 *                                 to the file
 * Side Effects: None
 * Error Conditions: None
 * Return Value: print statements that print the permissions to the file
 */


void
displayPermissions (const mode_t mode){

    /* OWNER */

    //Read
    if((mode & S_IRUSR) == S_IRUSR){
        (void) fprintf(stdout, "%c", 'r');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    //Write
    if((mode & S_IWUSR) == S_IWUSR){
        (void) fprintf(stdout, "%c", 'w');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    //Execute/Search
    if((mode & S_IXUSR) == S_IXUSR){
        (void) fprintf(stdout, "%c", 'x');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }



    /* GROUP */

    //Read
    if((mode & S_IRGRP) == S_IRGRP){
        (void) fprintf(stdout, "%c", 'r');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    //Write
    if((mode & S_IWGRP) == S_IWGRP){
        (void) fprintf(stdout, "%c", 'w');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    //Execute/Search
    if((mode & S_IXGRP) == S_IXGRP){
        (void) fprintf(stdout, "%c", 'x');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    /* OTHERS */

    //Read
    if((mode & S_IROTH) == S_IROTH){
        (void) fprintf(stdout, "%c", 'r');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    //Write
    if((mode & S_IWOTH) == S_IWOTH){
        (void) fprintf(stdout, "%c", 'w');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }

    //Execute/Search
    if((mode & S_IXOTH) == S_IXOTH){
        (void) fprintf(stdout, "%c", 'x');
    }
    else{
        (void) fprintf(stdout, "%c", '-');
    }


    (void) fprintf(stdout, "%c", ' ');
    return;
}
