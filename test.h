/*
 * Filename: test.h
 * Author: Seung Yoon Oh
 * Description: test.h used for unit testing
 * Date: Dec 2, 2014
 */


#ifndef TEST

#include <stdio.h>

#define TEST(EX) (void)((fprintf( stderr, "(%s:%d) %s:", __FILE__, __LINE__, #EX)) && \
                ( (EX && fprintf(stderr, "\tPASSED\n")) || (fprintf(stderr, "\tFAILED\n")) ))

#define TEST_INC(EX, COUNTVAR, INCVAL) (void)((fprintf( stderr, "(%s:%d) %s:", __FILE__, __LINE__, #EX)) && \
                ( (EX && (COUNTVAR += INCVAL) && fprintf(stderr, "\tPASSED\n")) || (fprintf(stderr, "\tFAILED\n")) ))

#endif
