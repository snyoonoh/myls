/*
 * Filename: displayOwnerName.c
 * Author: Seung Yoon Oh
 * Date: Dec 9, 2014
 */

#include <stdio.h>
#include <stdlib.h>

//pwd
#include <pwd.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: displayOwnerName 
 * Function prototype: void displayOwnerName (const uid_t uid)
 * Description: This routine will call getpwuid() to get a pointer to the 
 * struct passwd for this uid so we can get the owner's name as a string 
 * (pw_name member). If the passwd entry cannot be found, just print the 
 * numeric value of the uid.
 * Parameters:
 *      arg1: const uid_t uid -- user id
 * Side Effects: None
 * Error Conditions: None
 * Return Value: print statements that print userid or if there is error, prints
 * uid
 */

void
displayOwnerName (const uid_t uid){
    struct passwd* pd;
    pd = getpwuid(uid);

    //if passwd entry cannot be found print UID
    if(pd == 0){
        (void) fprintf(stdout, STR_UID, uid);
        return;
    }

    char* usrName = pd->pw_name;

    //if successful print PW Name
    (void) fprintf(stdout, STR_PWNAME, usrName);

    return;
}
