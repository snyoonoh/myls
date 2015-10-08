/*
 * Filename: sizeSortDescending.c
 * Author: Seung Yoon Oh
 * Date: Dec 9, 2014
 */

#include <stdio.h>
#include <stdlib.h>

#include "myls.h"
#include "strings.h"

/*
 * Function name: sizeSortDescending()
 * Function prototype: int sizeSortDescending( const void* p1, const void* p2 )
 * Description: sorts from low values to high values by size. The return value
 *              will be used in qsort().
 *       arg1 -- const void* p1: struct fileInfo pointer
 *       arg2 -- const void* p2: struct fileInfo pointer
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 0 if p1 and p2 are equal
 *               negative if p1 is after p2
 *               positive if p1 is before p2
 */

int
sizeSortDescending( const void* p1, const void* p2){

    //descending
    int result = (((struct fileInfo*) p2)->stbuf.st_size - 
                ((struct fileInfo*) p1)->stbuf.st_size);

    return result;
}
