/*
 * Filename: testsizeSortAscending.c
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Description: Unit test for sizeSortAscending
 * Date: Dec 2, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "globals.c"
#include "myls.h"
#include "test.h"

void
testsizeSortAscending() {
	struct fileInfo* a = (struct fileInfo*) malloc 
		(sizeof(struct fileInfo));
	struct fileInfo* b = (struct fileInfo*) malloc
		(sizeof(struct fileInfo));
	struct stat temporary;
	int i = 0;

	/* Test 1 */
	lstat("/home/solaris/ieng9/cs30x/public/sample_hard_link", &temporary);
	a -> stbuf = temporary;
	lstat("/home/solaris/ieng9/cs30x/public/sample_hard_link", &temporary);
	b -> stbuf = temporary;
	i = sizeSortAscending(a,b);
	TEST(i == 0);

	/* Test 2 */
	lstat("/home/solaris/ieng9/cs30x/public/sample_file",&temporary);
	a -> stbuf = temporary;
	lstat("/home/solaris/ieng9/cs30x/public/sample_file2",&temporary);
	b -> stbuf = temporary;
	i = sizeSortAscending(a, b);
	TEST(i == 0);

	/* Test 3 */
	lstat("/home/solaris/ieng9/cs30x/public/links",&temporary);
	a -> stbuf = temporary;
	lstat("/home/solaris/ieng9/cs30x/public/link_target",&temporary);
	b -> stbuf = temporary;
	i = sizeSortAscending(a, b);
	TEST(i > 0);

	/* Test 4 */
	lstat("/home/solaris/ieng9/cs30x/public/sparc.vim",&temporary);
	a -> stbuf = temporary;
	lstat("/home/solaris/ieng9/cs30x/public/vihelp",&temporary);
	b -> stbuf = temporary;
	i = sizeSortAscending(a, b);
	TEST(i < 0);

}

int main (){

	fprintf(stdout, "Running tests for sizeSortAscending...\n");
	testsizeSortAscending();
	fprintf(stdout, "Done running tests!\n");

	return 0;
}
