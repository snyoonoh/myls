/*
 * Filename: nameSortDescending.c
 * Author: Seung Yoon Oh
 * Date: Dec 9, 2014
 */

#include <stdio.h>
#include <stdlib.h>

//for strcmp
#include <string.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: nameSortDescending 
 * Function prototype: int nameSortDescending ( const void *p1, const void *p2)
 * Description: sorts according to name
 *              returns a negative value if p1 is greater than p2
 *              returns a positive value if p1 is less than p2
 *              returns 0 if p1 == p2
 * Parameters:
 *      arg1: const void* p1 -- pointer to a struct fileInfo
 *      arg2: const void* p2 -- pointer to a struct fileInfo
 * Side Effects: None
 * Error Conditions: None
 * Return Value: returns a negative value if p1 is greater than p2
 *               returns a positive value if p1 is less than p2
 *               returns 0 if p1 == p2
 */

int
nameSortDescending( const void *p1, const void *p2 ){

    char* p1Name = ((struct fileInfo*) p1)->name;
    char* p2Name = ((struct fileInfo*) p2)->name;

    int result = strcmp(p1Name, p2Name);

    //To make it descending
    result *= -1;

    return result;
}
