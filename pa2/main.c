/*
 * Filename: main.c
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: This is the main driver of this program, it will print out
 *              the BCD clock pattern
 * Date: May 9th 2018
 * Source of help: Katarina Melendez, Daniel Hoang Nguyen, Thomas Ren, 
 *                 Megan Wang, Christoph Steefel, Eli Qin, Piazza
 */
#include "pa2.h"
#include <stdio.h>  
#include "pa2Strings.h"
#include <stdlib.h>  //strtol
#include <errno.h>
#include <string.h>  //strncmp strlen
#include <time.h>
#include <sys/time.h>  // gettimeofday()

/*
 * Function Name: main()
 * Function Prototype: int main( void );
 * Description: The function will read the user input and print the output
 *              based on what the user demands, it will call the function
 *              populateNameData to read in the information from files and
 *              presents it to user in a format based on the user's choice.
 * Parameters: argc - # of command line + 1
 *             *argv[] - array of command line
 * Side Effects: Prints out error messages and usage msg when the input is 
 *               invalid or usage msg for --help command, otherwise the
 *               BCD clocks
 * Error Conditions: invalid user input
 * Return Value: return success when BCD clock printed out
 *               return failure when error(s) occured
 */

int main( int argc, char *argv[] ){
  unsigned char clock [CLOCK_ARR_SIZE] = {0};
  int ret;  // Result from string comparision
  int len;  // Length of string 
  long numTicks;  // Number of ticks 
  long result;  // Number used to hold the return value of strtol 
  char *endPtr;  // Used as the second param of strtol
  //int trn;  // Return value of timeRightNow()
  struct timeval tv;  // Used as parameter for timeRightNow
  struct tm* lt;  // Store the pointer to struct from call of localtime
  struct tInfo ourTime;  // Parameter for convertTime, tInfo struct to store
                         // the converted time 
  unsigned long bitmap;  // Hold the return value of interpretTime

  // Check the number of arg
  if( argc > MAX_ARGS ){ 
    fprintf( stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, 
             MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
    return EXIT_FAILURE;
  }
 

  // --help string 
  if( argc >= MIN_ARGS ){
    if( strlen(argv[HELP_INDEX]) >= strlen(STR_HELP) ){
      len = strlen(STR_HELP);
    } else{
      len = strlen(argv[HELP_INDEX]);
    }  // Determine the length to compare for the string

    ret = strncmp( argv[HELP_INDEX], STR_HELP, len + 1);  // Compare the string

    if( ret == 0 ){
      fprintf( stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, 
               MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
      return EXIT_SUCCESS;
    }  // Successfully print out usage message with --help 
  }


  // Parse numTicks
  if( argc == 1 ){
    numTicks = DEF_TICKS;  // No numTicks specified 
  }
  if( argc >= MIN_ARGS ){
    errno = 0;
    result = strtol( argv[NUM_TICKS_INDEX], &endPtr, BASE );

    // If errno being set, result out of range
    if( errno ){
      // Specific error msg
      fprintf( stderr,  STR_TICK_PARSE_ERR );
      // Usage msg
      fprintf( stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, 
               MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
      return EXIT_FAILURE;
    }
    
    // Check if it's a non-numeric char 
    if( *endPtr != '\0' ){
      // Specific error msg
      fprintf( stderr, STR_TICK_PARSE_ERR);
      // Usage msg
      fprintf( stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, 
               MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
      return EXIT_FAILURE;
    }

    // Check for the range of numTicks
    if( result <= MAX_TICKS && result >= MIN_TICKS ){
      numTicks = result;
    } else{
      // Specific error msg
      fprintf( stderr, STR_TICKS_RANGE_ERR, (int)result, MIN_TICKS, MAX_TICKS );
      // Usage msg
      fprintf( stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, 
               MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
      return EXIT_FAILURE;
    }
  }


  // Parse startTime

  // Lack of second command argument to set the time, initialized with current
  //  time
  if( argc < MAX_ARGS ){
    timeRightNow( &tv, NULL );
    lt =  localtime( &tv.tv_sec );
    convertTime( &ourTime, lt );
    printf( STR_DEF_TIME, asctime(lt) );
  }
  
  if( argc == MAX_ARGS ){
    // Parse the input time 
    bitmap = interpretTime( &ourTime, argv[START_TIME_INDEX] );
    // Error checking for the time passed in 
    if( bitmap != 0 ){
      // Check error for format 
      if( isEven(bitmap) == 0 ){
        fprintf( stderr, STR_TIME_FORMAT_ERR );
      }
      if( bitmap >= ERR_TIME_RANGE ){
        fprintf( stderr, STR_TIME_RANGE_ERR );
      } 
      if( bitmap == ERR_TW || bitmap == ERR_TH || 
          bitmap == ERR_SI || bitmap == ERR_SE ){      
        fprintf( stderr, STR_TIME_PARSE_ERR );
      }
      // Print out usage msg and return
      fprintf( stderr, STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, 
               MIN_HR, MAX_HR, MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
      return EXIT_FAILURE;
    }
  }
  // print out current time
  setClock( clock, &ourTime );
  
  printClock( clock );  // Print the clock with the initial startTime
  printf("\n");
  for( int i = 0; i < numTicks; i++ ){
    tickClock( clock );
    printClock( clock );
    printf("\n");
  }

  return EXIT_SUCCESS;
}
