/*
 * Filename: pa2.h
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Constants and function prototypes used in PA2.
 * Date: May 2nd 2018
 * Sources of Help: Given.
 */

#ifndef PA2_H
#define PA2_H

#include <time.h>  /* For struct timeval and struct tInfo(below) */
#include <sys/time.h>

/* tInfo struct used to store time values: sec, min, hr, am_pm flag */
struct tInfo {
  int tm_sec;
  int tm_min;
  int tm_hour;
  unsigned char am_pm;
};

/* C routines */
unsigned long interpretTime( struct tInfo * tmPtr, const char * time );
void printClock( const unsigned char clock[] );
void chime( const unsigned char clock[] );
void tickClock( unsigned char clock[] );
int timeRightNow( struct timeval * tp, void * p );

/* Assembly routines */
void setClock( unsigned char clock[], const struct tInfo * tmPtr );
void convertTime( struct tInfo * ourTime, const struct tm * tmPtr );
unsigned char incrementClockValue( unsigned char BCDbits,
                                   const unsigned int maxValue );
long isInRange( long num, long min, long max );
long isEven( long value );
void printChar( char c );
long myRemainder( long dividend, long divisor );


/* Min and max number of optional command line args (includes program name) */
#define MIN_ARGS 2
#define MAX_ARGS 3

/* Indicies of optional arguments in argv */
#define HELP_INDEX       1
#define NUM_TICKS_INDEX  1
#define START_TIME_INDEX 2

/* Size of the clock array */
#define CLOCK_ARR_SIZE 4

/* Start time ranges */
#define MIN_HR  0
#define MAX_HR  12
#define MIN_MIN 0
#define MAX_MIN 59
#define MIN_SEC 0
#define MAX_SEC 59

/* Default hour value */
#define DEFAULT_HR 12

/* Max values of clock digits */
#define MAX_ONES_SEC 9
#define MAX_TENS_SEC 5
#define MAX_ONES_MIN 9
#define MAX_TENS_MIN 5
#define MAX_ONES_HR 9
#define MAX_TENS_HR 1

/* Indicies of bcd clock array */
#define HR_INDEX  0
#define MIN_INDEX 1
#define SEC_INDEX 2
#define AM_PM_INDEX 3

#define BASE 10

/* Number of clock ticks ranges */
#define MIN_TICKS 0
#define MAX_TICKS 61
#define DEF_TICKS 7

#define ONES_BITMASK 0x0F
#define TENS_BITMASK 0xF0

/* Number of segments in our time format i.e., hours, minutes, and seconds. */
#define NUM_TIME_SEGMENTS  3
#define NUM_BITS_IN_NIBBLE 4
#define REQ_SEPARATORS     2

#define CHAR_BIT_SET    'O'
#define CHAR_BIT_UNSET  '.'
#define CHAR_SPACER     ' '
#define CHAR_SEPARATOR  ':'
#define CHAR_BORDER     '#'
#define CHAR_M          'M'

/* interpretTime errors: Check for the following errors */
#define ERR_TIME_FORMAT   0x1   /* Invalid start time format */
#define ERR_TIME_NUM      0x2   /* Time values (hh/mm/ss) not a valid num */ 
#define ERR_TIME_RANGE    0x4   /* Time values (hh/mm/ss) out of range */


/* Values to use for the Extra Credit */
#define MIN_HR_EC  0
#define MAX_HR_EC  23

/* TODO: Add more constants here if necessary. */
#define BIT_SHIFT 4
#define EDGE_HR 0x2
#define ROW_LENGTH 12
#define BODY_LENGTH 4
#define DIVISOR 3
#define ERR_TW 2
#define ERR_TH 3
#define ERR_SI 6
#define ERR_SE 7

#endif /* PA2_H */
