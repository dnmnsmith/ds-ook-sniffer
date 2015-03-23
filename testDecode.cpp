#include <stdint.h>
#include <iostream>

#include "ClimeMetDecoder.h"

#define TEST_DATA_SIZE 96

unsigned short int testdata[TEST_DATA_SIZE] = {
520, 1005, 515, 1010, 520,1005,520,1005,520,1010,520,1000,520,1010,520,1005,
1495,1010,520,1000,1500,1005,1500,1000,520,1010,520,1005,1495,1005,1500,1005,
515,1010,1500,1005,520,1005,1495,1010,1495,1005,1495,1005,1500,1000,1500,1010,
520,1000,520,1010,1495,1010,515,1005,520,1005,1500,1005,1495,1005,520,1010,
520,1000,520,1010,520,1005,520,1010,520,1000,520,1010,515,1010,520,1005,
520,1005,520,1010,520,1000,525,1005,1495,1010,515,1010,1490,1010,520,1054 };



ClimeMetDecoder cmd;


int main( int argc, char ** argv)
{
 for (int i = 0; i < TEST_DATA_SIZE; i++)
 {
     unsigned short int p = testdata[ i ];
 	  if (cmd.nextPulse(p)) 	{ cmd.print("CMD"); cmd.resetDecoder(); }
 }

 return 0;

}