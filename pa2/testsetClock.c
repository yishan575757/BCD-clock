/*
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Unit test program to test the function setClock.s
 * Date: May 2nd 2018
 * Sources of Help: Given, Writeup
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for setClock.s
 *
 * void setClock( unsigned char clock[], const struct tInfo * tmPtr );
 *
 * The setClock function should set the Binary coded decimal values for the
 * time into our clock arrauy.
 *
 * Purpose: Tests our setClock implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testsetClock() {

  // Declare our struct tInfo to hold our times
  struct tInfo time;

  // Set the times to all 0 for a zeroed out test
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;
  time.am_pm = 'A'; 
  unsigned char clock [CLOCK_ARR_SIZE];
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  TEST(clock[HR_INDEX] == 0 && clock[MIN_INDEX] == 0 && clock[SEC_INDEX] == 0 
       && clock[AM_PM_INDEX] == 'A');

  // Test some random times
  time.tm_sec = 50;
  time.tm_min = 23;
  time.tm_hour = 12;
  time.am_pm = 'P'; 
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  TEST(clock[HR_INDEX] == 0x12 && clock[MIN_INDEX] == 0x23 &&
      clock[SEC_INDEX] == 0x50 && clock[AM_PM_INDEX] == 'P');

  // Test some random times
  time.tm_sec = 1;
  time.tm_min = 63;
  time.tm_hour = 10;
  time.am_pm = 'Y'; 
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  TEST(clock[HR_INDEX] == 0x10 && clock[MIN_INDEX] == 0x63 &&
      clock[SEC_INDEX] == 0x01 && clock[AM_PM_INDEX] == 'Y');

  // Test some random times
  time.tm_sec = 0;
  time.tm_min = 75;
  time.tm_hour = 2;
  time.am_pm = 'c';  
  clock[0] = 0;
  clock[1] = 0;
  clock[2] = 0;
  clock[3] = 0;
  setClock(clock, &time);
  TEST(clock[HR_INDEX] == 0x02 && clock[MIN_INDEX] == 0x75 &&
       clock[SEC_INDEX] == 0 && clock[AM_PM_INDEX] == 'c');


}

/*
 * Function Name: main()
 * Function Prototype: main( int argc, char * argv[] );
 * Description: Driver for the unit test of setClock, it will test the cases
 *              above and show if it passes the test
 * Parameters: None
 * Side Effects: Print out the prompts to stderr and also the test cases
 * Error Conditions: When the test fail
 * Return Value: Always return 0
 */

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testsetClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
