/*
 * Filename: setDisplayMode.c
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Date: Dec 2, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: setDisplayMode 
 * Function prototype: unsigned int setDisplayMode (int argc, char *argv[])
 * Description: setDisplayMode()'s job is to parse the command-line options with
 * getOpt(), and set the necessary flags in an unsigned int variable by turning 
 * on bits of this variable to signify which command line options have been 
 * entered. 
 * Parameters:
 *      arg1: int argc -- number of arguments 
 *      arg2: char* argv[] -- array of argument strings from the commandline
 * Side Effects: None
 * Error Conditions: None
 * Return Value: unsigned int that corresponds to the flags that are set
 */

unsigned int
setDisplayMode (int argc, char* argv[]){
    unsigned int flag = 0;
    int c;

    while((c = getopt(argc, argv, STR_GETOPT_OPTIONS )) != -1){
        switch(c) {

            //List all entries including those beginning with (.)
            case 'a':
                flag = flag | AFLAG;
                break;

                //List in long format
            case 'l':
                flag = flag | LFLAG;
                break;

                //Reverse the order of sort
            case 'r':
                flag = flag | RFLAG;
                break;

                //Sort by file size instead of name (largest first)
            case 'S':
                flag = flag | SFLAG;
                break;

                //Ignore Backups. Do not list implied entries ending with ~
            case 'B':
                flag = flag | BFLAG;
                break;

                //default -- set ERR_FLAG
            default:
                flag = flag | ERR_FLAG;
                return flag;
        }
    }
    return flag;
}

