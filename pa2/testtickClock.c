/*
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Unit test program to test the function tickClock.c
 * Date: May 2nd 2018
 * Sources of Help: Pushpak Gautam, discussion slide
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for tickClock.c
 *
 * void tickClock( unsigned char clock[] );
 *
 * The tick clock will increment the clock by one second, it will change the
 * value of second, and the value of min, hour, and am_pm if necessary.
 *
 * Purpose: Tests our tickClock implementation by passing a variety of values
 * in as test cases for our function. Test the edge cases like changing the
 * a to p, and increment to value hour.
 */
void testtickClock() {
  unsigned char clock[CLOCK_ARR_SIZE];  // Initialized the clock array
  // Test the simple case only increment second
  clock[0] =0x05;
  clock[1] =0x12;
  clock[2] =0x09;
  clock[3] = 'a';
  tickClock(clock);
  TEST(clock[0] == 0x05 && clock[1] == 0x12 && 
       clock[2] == 0x10 && clock[3] == 'a');
  // When there is a carryout from sec to min
  clock[0] =0x11;
  clock[1] =0x11;
  clock[2] =0x59;
  clock[3] = 'p';
  tickClock(clock);
  TEST(clock[0] == 0x11 && clock[1] == 0x12 && 
       clock[2] == 0x00 && clock[3] == 'p');
  // Changing the am_pm from 'p' to 'a'
  clock[0] =0x11;
  clock[1] =0x59;
  clock[2] =0x59;
  clock[3] = 'p';
  tickClock(clock);
  TEST(clock[0] == 0x12 && clock[1] == 0x00 && 
       clock[2] == 0x00 && clock[3] == 'a');
  // Changing from 12 to 01 for hour
  clock[0] =0x12;
  clock[1] =0x59;
  clock[2] =0x59;
  clock[3] = 'p';
  tickClock(clock);
  TEST(clock[0] == 0x01 && clock[1] == 0x00 && 
       clock[2] == 0x00 && clock[3] == 'p');
  // Changing the am_pm from 'a' to 'p'
  clock[0] = 0x11;
  clock[1] = 0x59;
  clock[2] = 0x59;
  clock[3] = 'a';
  tickClock(clock);
  TEST(clock[0] == 0x12 && clock[1] == 0x00 && 
       clock[2] == 0x00 && clock[3] == 'p');

// Test the simple case only increment second
  clock[0] =0x00;
  clock[1] =0x00;
  clock[2] =0x01;
  clock[3] = 'a';
  tickClock(clock);
  TEST(clock[0] == 0x00 && clock[1] == 0x00 &&
  clock[2] == 0x2 && clock[3] == 'a');

  clock[0] = 0x11;
  clock[1] = 0x02;
  clock[2] = 0x59;
  clock[3] = 'a';
  tickClock(clock);
  TEST(clock[0] == 0x11 && clock[1] == 0x03 &&
       clock[2] == 0x00 && clock[3] == 'a');

  clock[0] =0x00;
  clock[1] =0x59;
  clock[2] =0x59;
  clock[3] = 'a';
  tickClock(clock);
  TEST(clock[0] == 0x01 && clock[1] == 0x00 &&
       clock[2] == 0x00 && clock[3] == 'a');

}

/*
 * Function Name: main()
 * Function Prototype: main( int argc, char * argv[] );
 * Description: Driver for the unit test of tickClock, it will test the cases
 *              above and show if it passes the test
 * Parameters: None
 * Side Effects: Print out the prompts to stderr and also the test cases
 * Error Conditions: When the test fail
 * Return Value: Always return 0
 */

int main( void ) {

  fprintf(stderr, "Running tests for tickClock...\n");
  testtickClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
