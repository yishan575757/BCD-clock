 /* 
  * Filename: printClock.c
  * Name: Yishan Li
  * Userid: cs30xdp
  * Description: This function will display the BCD clock based on the given
  *              time from the clock array
  *         
  * Date: May 6th 2018
  * Sources of help: Discussion slide, lecture notes, Thiago Goncalves Marback,
  *                  Aniket Mathur, Akansha Dey
  *      
  */
#include <stdlib.h>  // strtol
#include <stdio.h>  // fprintf, printf 
#include "pa2.h"
#include "pa2Strings.h"
#include <errno.h>  // errno
#include <string.h>  // strcpy

/*
 * Function name: printClock
 * Function Prototype:
 *   void printClock( const unsigned char clock[] );
 * Description: This function will print out the time information, it will be
 *              printed out in the BCD clock format, each nibble will be
 *              printed out in a separated column. 'a'/'A' or 'p'/'P' will 
 *              surronded the clock format.
 * Parameters: clock - is the array contains the information of hour, min, and
 *                     sec
 * Error conditions: None
 *
 * Return value: no return value, but BCD clock will be printed out
 */
void printClock( const unsigned char clock[] ){
  int i = 0;  // For the index of loop 
  int j = 0;  // For the index of loop
  unsigned char printing = 0;  // Result to be printed out 
  unsigned char P_BITMASK = 0x8;  // The bitmask used to extract the bit
  int checkTime = 0;  // Used to make sure is printing out the '.'/'O'

  // Print out the first row
  for ( i = 0; i < ROW_LENGTH; i++ ){
    printChar(clock[AM_PM_INDEX]);
  }


  printf("\n");
  
  // Run through each row than column  
  for( j = 0; j < BODY_LENGTH; j++){
      
    for( i = 0; i < ROW_LENGTH; i++ ){
      
      // The front and the end of the row
      if( i == 0 || i == ROW_LENGTH - 1 ){
        // Determine should print out 'M' or 'A'/'P'
        if( isEven( j ) ){
          printChar( CHAR_M );
        } else{
          printChar( clock[AM_PM_INDEX] );
        }
      }

      // Print out the space 
      if( myRemainder( i, DIVISOR ) == 1 ){
        printChar( CHAR_SPACER );
      }

      // Upper nibble 
      if( (i % 3) == 2 && i != (ROW_LENGTH - 1) ){
        printing = clock[(i-2) / 3] & TENS_BITMASK;
        printing = printing >> 4;
        checkTime = 1;
      }
      // Lower nibble 
      if( (i % 3) == 0 && i != 0 ){
        printing = clock[(i / 3) - 1] & ONES_BITMASK;
        checkTime = 1;
      }

      P_BITMASK = P_BITMASK >> j;

      printing = printing & P_BITMASK;
      // Print out '.' and 'O'
      if( printing == 0 && checkTime == 1 ){
        printChar(CHAR_BIT_UNSET);
        checkTime = 0;
      } else if ( printing != 0 && checkTime == 1 ){
        printChar(CHAR_BIT_SET);
        checkTime = 0;
      }

      P_BITMASK = 0x8;

    }  // Looping through i for the row
      printf("\n");

  }  // Looping through j for the column


  // Print out the decimal value row
  for( i = 0; i < ROW_LENGTH; i++ ){ 
    
    // Print out 'M' at the end and begining
    if( i == 0 || i == ROW_LENGTH - 1 ){
      printChar( CHAR_M ); 
    }
   
    // Print out the space 
    if( i == 1 ){
      printChar( CHAR_SPACER );
    }

    if( (i % 3) == 2 && i != (ROW_LENGTH - 1) ){
      printf( STR_BCD_TIME, clock[(i-2) / 3] );
    }

  }  // Finish print out the second last line
  
  printf("\n");


  // Print out the last row
  for( i = 0; i < ROW_LENGTH; i++ ){
    printChar(clock[AM_PM_INDEX]);
  }

  printf("\n");

    
      
}




































