/*
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Unit test program to test the function setClock.s
 * Date: May 2nd 2018
 * Sources of Help: Writeup
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for incrementClockValue.s
 *
 * unsigned char incrementClockValue( unsigned char BCDbits,
 *                                    const unsigned int maxValue);
 *
 * The incrementClockValue function should increment the Binary coded decimal 
 * values by 1 as long as it's within the range maxValue
 *
 * Purpose: Tests incrementClockValue implementation by passing a variety of 
 * values in as test cases the our function.
 */
void testincrementClockValue() {
   unsigned char testRet;  // Return value of function incrementClockValue
   unsigned char BCDbits;  // BCDbits to be added 
   unsigned int maxValue;  // The maximum value that BCDbits can be
   // BCDbits = maxValue
   BCDbits = 1;
   maxValue = 1;
   testRet = incrementClockValue( BCDbits, maxValue );
   TEST( testRet == 0 );

   // BCDbits < maxValue
   BCDbits = 1;
   maxValue = 2;
   testRet = incrementClockValue( BCDbits, maxValue );
   TEST( testRet == 2 );

   // BCDbits < maxValue
   BCDbits = 1;
   maxValue = 3;
   testRet = incrementClockValue( BCDbits, maxValue );
   TEST( testRet == 2 );

   // BCDbits > maxValue
   BCDbits = 2;
   maxValue = 1;
   testRet = incrementClockValue( BCDbits, maxValue );
   TEST( testRet == 0 );

}
/*
 * Function Name: main()
 * Function Prototype: main( int argc, char * argv[] );
 * Description: Driver for the unit test of incrementClockValue, it will test 
 *              the cases above and show if it passes the test
 * Parameters: None
 * Side Effects: Print out the prompts to stderr and also the test cases
 * Error Conditions: When the test fail
 * Return Value: Always return 0
 */
int main( void ) {

  fprintf(stderr, "Running tests for incrementClockValue...\n");
  testincrementClockValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
