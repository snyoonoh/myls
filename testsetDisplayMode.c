/*
 * Filename: testsetDisplayMode.c
 * Author: Seung Yoon Oh
 * Description: Unit test for setDisplayMode.c
 * Date: Dec 2, 2014
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>

#include "myls.h"
#include "test.h"
#include "strings.h"

void
testsetDisplayMode()
{
    printf( "Testing testsetDisplayMode()\n\n");

    /* test 1 */
    int argc = 2;
    char* argv1[2] = {"./pa4","-l"};
    unsigned int temp = setDisplayMode( argc, argv1 );
    unsigned int answer = 2;
    TEST(temp == answer);

    optind = 1;
    optarg = NULL;

    /* test 2 */
    argc = 2;
    char* argv2[2] = {"./pa4","-a"};
    temp = setDisplayMode( argc, argv2 );
    answer = 1;
    TEST(temp == answer);

    optind = 1;
    optarg = NULL;

    /* test 3 */
    argc = 3;
    char* argv3[3] = {"./pa4","-l","-r"};
    temp = setDisplayMode( argc, argv3 );
    answer = 6;
    TEST(temp == answer);

    optind = 1;
    optarg = NULL;

    /* test 4 */
    argc = 6;
    char* argv4[6] = {"./pa4","-l","-a","-r","-S","-B"};
    temp = setDisplayMode( argc, argv4 );
    answer = 31;
    TEST(temp == answer);

    optind = 1;
    optarg = NULL;

    /* test 5 */
    argc = 2;
    char* argv5[2] = {"./pa4","-R"};
    temp = setDisplayMode( argc, argv5 );
    answer = 2147483648;
    TEST(temp == answer);

    optind = 1;
    optarg = NULL;

    /* test 6 */
    argc = 2;
    char* argv6[2] = {"./pa4","-o"};
    temp = setDisplayMode( argc, argv6 );
    answer = 2147483648;
    TEST(temp == answer);

 

    printf( "\n\nFinished running tests on setDisplayMode()\n");
}

int
main()
{
    testsetDisplayMode();
    return 0;
}
