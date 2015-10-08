/*
 * Filename: main.c
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Date: Dec 9, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: main()
 * Function prototype: int main( const void* p1, const void* p2 )
 * Description: First, myls.c will need to handle checking command-line options.
 * This functionality should be contained in its own module - in 
 * setDisplayMode(). After a call to setDisplayMode() to parse the 
 * command-line options, first check whether the error bit was set in the 
 * unsigned int mode variable returned from setDisplayMode().
 *       arg1 -- const void* p1: struct fileInfo pointer
 *       arg2 -- const void* p2: struct fileInfo pointer
 * Side Effects: None
 * Error Conditions: None
 * Return Value: EXIT_FAILURE or EXIT_SUCCESS
 */


int
main (int argc, char* argv[]){
    unsigned int flag;
    int numOfEntries;
    char* noArg;
    struct fileInfo* tablePointer;
    (void) memset(&tablePointer, 0, sizeof(tablePointer));

    flag = setDisplayMode(argc, argv);

    //if there are any errors in setDisplayMode, print Usage and exit
    if((flag & ERR_FLAG) == ERR_FLAG){
        (void) fprintf(stderr, STR_USAGE, argv[0]);
        return EXIT_FAILURE;
    }

    //if there are no other arguments
    if(optind == argc){
        noArg = ".";
        numOfEntries = buildFileInfoTable(noArg, &tablePointer);
        displayFileInfo(tablePointer, numOfEntries, flag);
        
        //freeing memory
        free (tablePointer);
    }
    else{
        int i;
        for(i = optind; i < argc; i ++){
            numOfEntries = buildFileInfoTable(argv[i], &tablePointer);
            displayFileInfo(tablePointer, numOfEntries, flag);

            //freeing mem
            free (tablePointer);
        }
    }
    
    return EXIT_SUCCESS;
}
