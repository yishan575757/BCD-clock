#
# Makefile for CSE 30 -- PA2
# You should not need to change anything in this file.
#

HEADERS		= pa2.h pa2Strings.h
C_SRCS		= main.c printClock.c pa2Globals.c tickClock.c \
		  timeRightNow.c interpretTime.c
ASM_SRCS	= isInRange.s setClock.s incrementClockValue.s printChar.s \
		  isEven.s myRemainder.s convertTime.s

EC_C_SRCS	= mainEC.c printClock.c pa2Globals.c tickClock.c \
		  timeRightNow.c interpretTimeEC.c chime.c

C_OBJS		= $(C_SRCS:.c=.o)
EC_C_OBJS	= $(EC_C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)
EC_OBJS		= $(EC_C_OBJS) $(ASM_OBJS)

EXE		= pa2
EC_EXE		= pa2EC
TEST_EXES	= testinterpretTime testsetClock testincrementClockValue \
		  testtickClock

GCC		= gcc
ASM		= $(GCC)
RM		= rm

GCC_FLAGS	= -c -g -std=c99 -pedantic -Wall -D__EXTENSIONS__
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall

#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(EC_EXE): $(EC_OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EC_EXE) $(EC_OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(EXE) $(EC_EXE) $(TEST_EXES) *.o *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make

#
# Unit test targets
#
testinterpretTime: test.h pa2.h interpretTime.o testinterpretTime.o \
	isInRange.o
	@echo "Compiling testinterpretTime.c"
	$(GCC) $(LD_FLAGS) -o testinterpretTime testinterpretTime.o \
	interpretTime.o isInRange.o
	@echo "Compilation Successful!"

testsetClock: test.h pa2.h setClock.o testsetClock.o pa2Globals.o \
	myRemainder.o isEven.o
	@echo "Compiling testsetClock.c"
	$(GCC) $(LD_FLAGS) -o testsetClock testsetClock.o \
	setClock.o pa2Globals.o myRemainder.o isEven.o
	@echo "Compilation Successful!"

testincrementClockValue: test.h pa2.h incrementClockValue.o \
	testincrementClockValue.o
	@echo "Compiling testincrementClockValue.c"
	$(GCC) $(LD_FLAGS) -o testincrementClockValue testincrementClockValue.o \
	incrementClockValue.o
	@echo "Compilation Successful!"

testtickClock: test.h pa2.h testtickClock.o tickClock.o \
	incrementClockValue.o pa2Globals.o
	@echo "Compiling testtickClock.c"
	$(GCC) $(LD_FLAGS) -o testtickClock testtickClock.o \
	tickClock.o incrementClockValue.o pa2Globals.o
	@echo "Compilation Successful!"


