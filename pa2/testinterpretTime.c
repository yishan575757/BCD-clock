/*
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Unit test program to test the function interpretTime.c
 * Date: May 2nd 2018
 * Sources of Help: Shanfeng Feng, Writeup
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for interpretTime.c
 *
 * unsigned long interpretTime( struct tInfo * tInfoPtr, const char * time )
 *
 * The interpretTime function will interpret the string time and store it 
 * in the members of struct accodingly and return the bitmap which contains 
 * the information of errors.
 *
 * Purpose: Tests our interpretTime implementation by passing a variety of 
 * values in as test cases for our function. It will test different errors.
 */
void testinterpretTime() {

  struct tInfo tInfoPtr;  // The struct used for call of function
  unsigned long bitmap;  // The return value after call of function
  // No error occured
  bitmap = interpretTime(&tInfoPtr, "1:00:05a");
  TEST(bitmap == 0);
  // Format error
  bitmap = interpretTime(&tInfoPtr, "1a2:00:05");
  TEST(bitmap == 0x3);
  
  bitmap = interpretTime(&tInfoPtr, "1z0:15y20");
  TEST(bitmap == 0x1);
  
  bitmap = interpretTime(&tInfoPtr, "12:03:05b");
  TEST(bitmap == 0x1);
  // Invalid num
  bitmap = interpretTime(&tInfoPtr, "10x:00:05a");
  TEST(bitmap == 0x2);
  // Format error
  bitmap = interpretTime(&tInfoPtr, "1:32:aA");
  TEST(bitmap == 0x1);
  // Out of range
  bitmap = interpretTime(&tInfoPtr, "1:66:12a");
  TEST(bitmap == 0x4);
  // errno != 0
  bitmap = interpretTime(&tInfoPtr, "1:666666666666666666666666666666666:12a");
  TEST(bitmap == 0x2);
  // Out of range, invalid num, format error
  bitmap = interpretTime(&tInfoPtr, "12a:66:05");
  TEST(bitmap == 0x7);
  
  bitmap = interpretTime(&tInfoPtr, "1:66:99999999999999999999999999999a");
  TEST(bitmap == 0x6);
}


/*
 * Function Name: main()
 * Function Prototype: main( int argc, char * argv[] );
 * Description: Driver for the unit test of interpretTime, it will test the 
                cases above and show if it passes the test
 * Parameters: None
 * Side Effects: Print out the prompts to stderr and also the test cases
 * Error Conditions: When the test fail
 * Return Value: Always return 0
 */
int main( void ) {

  fprintf(stderr, "Running tests for interpretTime...\n");
  testinterpretTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
