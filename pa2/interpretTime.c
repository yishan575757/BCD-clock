/* 
 * Filename: interpretTime.c
 * Name: Yishan Li
 * Userid: cs30xdp
 * Description: This function will evaluate and parse the time string, if
 *              there is no error, it will return 0 and store the time 
 *              information into struct tInfo
 * Date: May 2nd 2018
 * Sources of help: Discussion slide, lecture notes, Christopher Pence, 
 *                  Griffin Stamp, piazza
 */
#include <stdlib.h>  // strtol
#include <stdio.h>  // fprintf, printf 
#include "pa2.h"  
#include "pa2Strings.h"
#include <errno.h>  // errno
#include <string.h>  // strcpy
/*
 * Function Name: interpretTime
 * Function Prototype: 
 *   unsigned long interpretTime( struct tInfo * tInfoPtr, const char * time )
 * Description: This function will interpret the time string give and while
 *              parsing the string it will do the error checking to check if
 *              the input is within the range, if it has correct format and 
 *              form of num, if any error occured it will be recorded in the
 *              bitmap and returned.
 * Parameters: tInforPtr - points to the struct members
 *             time - the string that has the information of time
 * Error conditions: when the number to be parsed is out of range
 *                        the format of string is not correct
 *                        lack of necessary elements like ':'
 * Return Value: the bitmap that contains the information of which errors
 *               has occured; if no error occurs, the bitmap is 0. 
 */
unsigned long interpretTime( struct tInfo * tInfoPtr, const char * time ){
  
  char buffer[BUFSIZ] = {'\0'};  // Array with the index value of '\0'
  unsigned long bitmap = 0;  // Return value to check the error
  int i = 0;  // loop index 
  int sepCheck = 0;  // Record the amount of separator 
  char *endPtr;  // Used as second param of strtol
  long parseHr;  // Value of hour after parsed from string
  long parseMin;  // Value of min after parsed from string
  long parseSec;  // Value of sec after parsed frin string
  long rangeCheck;  // Check the range of parsed value 
  long stringLength;  // Get the length of parsed array
  char ampm;  // Check the ending char of the string

  strncpy( buffer, time, BUFSIZ );  // Copy the time string to buffer

  stringLength = strlen( time );

  for( i = 0; i < stringLength; i++ ){
    // Check if the char store at ith index is ':'
    if( time[i] == CHAR_SEPARATOR ){
      ++sepCheck;
    }
  }

  if( sepCheck != REQ_SEPARATORS ){
    bitmap = bitmap | ERR_TIME_FORMAT;
    return bitmap;
  }
  
  // Parse the hour value 
  errno = 0; 
  parseHr = strtol( time, &endPtr, BASE );
  if( errno ){
    bitmap = bitmap | ERR_TIME_NUM;
  } 

  // Check if the char separator is at where the endPtr point
  if( *endPtr != CHAR_SEPARATOR ){
    bitmap = bitmap | ERR_TIME_NUM;
  }

  // Check if the input value of hour is 0
  if( parseHr == 0 ){
    parseHr = DEFAULT_HR;
  }

  // Check if the input value of hour is in range
  rangeCheck = isInRange( parseHr, MIN_HR, MAX_HR + 1 );
  if( rangeCheck != 1 && errno == 0 ){
    bitmap = bitmap | ERR_TIME_RANGE;
  }


  // Parse the min Value
  char * ret = strchr( time, CHAR_SEPARATOR );
  errno = 0;
  parseMin = strtol( ret + 1, &endPtr, BASE );

  if( errno ){
    bitmap = bitmap | ERR_TIME_NUM;
  }

  // Check if the char separator is at where the endPtr point
  if( *endPtr != CHAR_SEPARATOR ){
    bitmap = bitmap | ERR_TIME_NUM;
  }
 
  // Check if the input value of min is in range
  rangeCheck = isInRange( parseMin, MIN_MIN, MAX_MIN + 1);
  if( rangeCheck != 1 && errno == 0 ){
    bitmap = bitmap | ERR_TIME_RANGE;
  }


  // Parse the sec Value  
  ret = strchr( ret + 1, CHAR_SEPARATOR );
  errno = 0;
  parseSec = strtol( ret + 1, &endPtr, BASE );

  if( errno ){
    bitmap = bitmap | ERR_TIME_NUM;
  }

  // Check if the input value of Second is in range
  rangeCheck = isInRange( parseSec, MIN_SEC, MAX_SEC + 1);
  if( rangeCheck != 1 && errno == 0 ){
    bitmap = bitmap | ERR_TIME_RANGE;
  } 

  
  // Parse the am_pm
  ampm = *endPtr;
  // Check if the string is too long
  if( *(endPtr + 1) != '\0' ){
    bitmap = bitmap | ERR_TIME_FORMAT;
  }

  // Check if the string has ampm
  if( ampm == '\0' ){
     bitmap = bitmap | ERR_TIME_FORMAT;
  }

  // Check if am_pm is represented by proper char
  if( ampm == 'a' || ampm == 'A' || ampm == 'p' || ampm == 'P'){
  } else{
    bitmap = bitmap | ERR_TIME_FORMAT;
  }
  // Store the value to struct members 
  tInfoPtr->tm_sec = parseSec;
  tInfoPtr->tm_min = parseMin;
  tInfoPtr->tm_hour = parseHr;
  tInfoPtr->am_pm = ampm;

  return bitmap;
}

