/*
 * Filename: testbuildFileInfoTable.c
 * Author: Seung Yoon Oh
 * Description: Unit test for buildFileInfoTable
 * Date: Dec 2, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#include <string.h>

#include "myls.h"
#include "test.h"

#define SYSRUN(CMD) (system(CMD))

jmp_buf jump;
int ref_buildFileInfoTable(const char *filename,
                           struct fileInfo **const tablePtr);

void segf_handler(int sig) {
  if (sig == SIGSEGV) {
    fprintf(stderr, "GOT A SEGFAULT!\n");
    longjmp(jump, 1);
  }
}

void testbuildFileInfoTable() {

  char* fileName;

  struct fileInfo* myPtr;
  struct fileInfo* refPtr;

  SYSRUN("cp ~/../public/normal_file .");
  SYSRUN("cp ~/../public/empty_file .");
  SYSRUN("touch no_permissions_file");
  SYSRUN("chmod -wrx no_permissions_file");
  
  //creating directory with 1 file (3 including . and ..)
  SYSRUN("mkdir dir1 && touch dir1/1");
  //create directory with 2 files (4 including . and ..)
  SYSRUN("mkdir dir2 && touch dir2/1 dir2/2 dir2/3");


  /* ----------------------------TESTING FOR NON DIR--------------------------*/

  /* Test 1 */
  fileName = "normal_file";
  if (setjmp(jump) == 0) {
    TEST(buildFileInfoTable(fileName, &myPtr) == 1);
  }

  ref_buildFileInfoTable(fileName, &refPtr);
  TEST(memcmp(myPtr, refPtr, sizeof(struct fileInfo)) == 0);

  /* Test 2 */
  fileName = "empty_file";
  if (setjmp(jump) == 0) {
    TEST(buildFileInfoTable(fileName, &myPtr) == 1);
  }

  ref_buildFileInfoTable(fileName, &refPtr);
  TEST(memcmp(myPtr, refPtr, sizeof(struct fileInfo)) == 0);

  /* Test 3 */
  fileName = "no_permissions_file";
  if (setjmp(jump) == 0) {
    TEST(buildFileInfoTable(fileName, &myPtr) == 1);
  }

  ref_buildFileInfoTable(fileName, &refPtr);
  TEST(memcmp(myPtr, refPtr, sizeof(struct fileInfo)) == 0);

  /* Test 4 */
  fileName = "non_existent_file";
  if (setjmp(jump) == 0) {
    TEST(buildFileInfoTable(fileName, &myPtr) == 0);
  }

  /* Test 5 */
  fileName = "/home/solaris/ieng9/cs30x/public/pa4test";
  if (setjmp(jump) == 0) {
    TEST(buildFileInfoTable(fileName, &myPtr) == 1);
  }

  ref_buildFileInfoTable(fileName, &refPtr);
  TEST(memcmp(myPtr, refPtr, sizeof(struct fileInfo)) == 0);

 /* ----------------------------TESTING FOR DIR--------------------------*/

 /* testing on dir1 that has 3 files*/
  fileName = "dir1";

  int dir = 3;
  int mine;

  mine = buildFileInfoTable(fileName, &myPtr);

    if (setjmp(jump) == 0) {
    TEST(mine==dir);
  }

 /* testing on dir1 that has 5 files*/
  fileName = "dir2";

  int dir2 = 5;
  int mine2;

  mine2 = buildFileInfoTable(fileName, &myPtr);

    if (setjmp(jump) == 0) {
    TEST(mine2==dir2);
  }



}

int main( void ) {

  if (signal(SIGSEGV, segf_handler) == SIG_ERR) {
    perror("Problem!");
    exit(2);
  }

  fprintf(stderr, "Running tests for buildFileInfoTable...\n");
  testbuildFileInfoTable();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
