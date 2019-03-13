/* tickClock.c
 * Name: Yishan Li
 * Userid: cs30xdp
 * Description: This function will add one second to the clock 
 * Date: May 2nd 2018
 * Sources of help: Discussion slide, lecture notes, Pushpak Gautam,
 *                  Katarina Melendez
 */
#include "pa2.h"
#include "pa2Strings.h"
#include <stdio.h>

/*
 * Function Name: tickClock()
 * Function Prototype: void tickClock( unsigned char clock[] );
 * Description: The function will increment the second by 1, and may
 *              increment the value of min and hour if there is a
 *              carryout and change am_pm if necessary.
 * Parameter: unsigned char clock[] - the char array that hold the information
 *            of time. The changed time will be store back to the array.
 * Side Effects: Increment the time by one second.
 * Error Conditions: None
 * Return Value: None
 */
void tickClock( unsigned char clock[] ){
  unsigned char BCDbits;  // The value from each index of clock[]
  unsigned char ones;  // Only hold the lower nibble
  unsigned char tens;  // Only hold the higher nibble
  unsigned char result;  // Store the result after increment 
  int carryout = 0;  // Check if there is carryout 
  int tensVal = 0;  // Check if tens original value is 0

  // Handle the increment of SEC
  // Get the value of second
  BCDbits = clock[SEC_INDEX];
  ones = BCDbits & ONES_BITMASK;  // Getting the lower nibble
  tens = BCDbits & TENS_BITMASK;  // Getting the higher nibble
 
  // Check if tens value is 0
  if( tens == 0 ){
    tensVal = 1;
  }

  // Increment the ones 
  result = incrementClockValue( ones, MAX_ONES_SEC );
  // Check if there is a carryout for ones of sec
  if( result == 0 ){
    carryout = 1;
  }
  // Handle the carryout in seconds
  if( carryout == 1 ){
    tens = tens >> BIT_SHIFT;  // Shift right 4bits for increment
    tens = incrementClockValue( tens, MAX_TENS_SEC );
    tens = tens << BIT_SHIFT;  // Shift left 4bits to higher nibble
    carryout = 0;  // After handle the carryout of ones in sec set it back to 0
  }
  
  // Check if there is a carryout for tens of sec
  if( tens == 0 && tensVal != 1){
    carryout = 1;
  }
  
  // Store the sec to the clock[]
  result = result | tens; 
  clock[SEC_INDEX] = result;
  tensVal = 0;  // Set the tensVal back to 0 for later use
  
  // Handle the increment of MIN if there is a carryout of the tens of sec
  if( carryout == 1 ){
    BCDbits = clock[MIN_INDEX];
    ones = BCDbits & ONES_BITMASK;
    tens = BCDbits & TENS_BITMASK;
    
    // Check if tens value for min is 0
    if( tens == 0 ){
      tensVal = 1;
    }

    result = incrementClockValue( ones, MAX_ONES_MIN );  // Increment the ones
    carryout = 0; // Handled the carryout from sec

    // Check if there is carryout from ones of min
    if( result == 0 ){
      carryout = 1;  // Find a carryout from the ones
    } 
    // Handle the carryout from the ones of MIN
    if( carryout == 1 ){
      tens = tens >> BIT_SHIFT;  // Shift right for 4 bits
      tens = incrementClockValue( tens, MAX_TENS_SEC );
      tens = tens << BIT_SHIFT; // Shift back to tens
      carryout = 0;  // Handled the carryout from the ones of MIN
    }

    // Check if there is new carryout from the tens of MIN
    if( tens == 0 && tensVal != 1 ){
      carryout = 1;
    }

    // Store the min to the clock[]
    result = result | tens;
    clock[MIN_INDEX] = result;
    tensVal = 0;
  }
  
  // Handle the increment of Hour if there is a carryout from the tens of min
  if( carryout == 1 ){
    // Get the ones and tens of hour
    BCDbits = clock[HR_INDEX];
    ones = BCDbits & ONES_BITMASK;
    tens = BCDbits & TENS_BITMASK;
  
    // Check if the original tens value is 0
    if( tens == 0 ){
      tensVal = 1;
    }

    result = incrementClockValue( ones, MAX_ONES_HR );
    carryout = 0; // Handled the increment from the tens of min
    ones = result;
    // Check if there is new carryout from the ones of hour
    if( result == 0 ){
      carryout = 1;
    }

    // Handle the carryout from the ones of hour
    if( carryout == 1 ){
      tens = tens >> BIT_SHIFT;
      tens = incrementClockValue( tens, MAX_TENS_HR );
      tens = tens << BIT_SHIFT;
      carryout = 0;
    }

    // Check if there is new carryout from the tens of hour
    if( tens == 0 && tensVal != 1){
      carryout = 1;
    }
    
    // Changing the am_pm when the hour turns to 12
    if( tens == 0x10 && ones == EDGE_HR ){
      if( clock[AM_PM_INDEX] == 'a' || clock[AM_PM_INDEX] == 'A'){
        clock[AM_PM_INDEX] = 'p';
      } else{ 
        clock[AM_PM_INDEX] = 'a';
      }
    }
    // When the tens is 1 and the ones is exceeding 2 
    if( tens == 0x10 && ones > EDGE_HR ){
      tens = 0;
      ones = ones - 2;
    } 
    // Store back the result 
    result = ones | tens;
    clock[HR_INDEX] = result;
    tensVal = 0;
  }


}
