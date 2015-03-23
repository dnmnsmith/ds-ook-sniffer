#include <iostream>
#include <stdio.h>
#include <pigpio.h>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <utility>

//#include "RCSwitch.h"

#include "ClimeMetDecoder.h"


bool powerState = 0;
uint32_t calls = 0;

struct sample_t { sample_t( uint32_t t, int g, int l ) : time(t),gpio(g),level(l) {} uint32_t time; int gpio; int level; }; 


std::vector< sample_t > samples;

ClimeMetDecoder cmd;



void powerFunction(int gpio, int level, uint32_t tick)
{
   std::cerr << "Power " << (level ? "On":"Off") << std::endl;
   powerState = level;
}

void dataFunction(int gpio, int level, uint32_t tick)
{
 static bool infn = 0;
 static uint32_t prev = 0;
 
 calls++;
 
 if (infn)
    return;
    
 infn = 1;
 if (powerState)
 {
   samples.push_back( sample_t( tick, gpio, level ) );
 }
 
 uint32_t duration = tick - prev;
 prev = tick; 
 
 if (cmd.nextPulse(duration)) 	
 { 
//   cmd.print("CMD"); 

   int code;
   float temp;
   int humidity; 
   bool ok =  cmd.getDeviceCode( code ) && cmd.getTemperature( temp );
   bool gotHumidity = cmd.getHumidity( humidity );

   if (ok && !gotHumidity)   
      printf("Device code = %02X Temperature = %02.1f\n",code,temp);
   else if (ok && gotHumidity)   
      printf("Device code = %02X Temperature = %02.1f Humidity = %d\n",code,temp,humidity);

   cmd.resetDecoder(); 
 }

 infn=0;
}


int main( int argc, char ** argv)
{

 std::cerr << "Hello" << std::endl;

 samples.push_back( sample_t( 0, 18, 0 ) );
 samples.push_back( sample_t( 0, 23, 0 ) );

 if (gpioInitialise() < 0)
 {
   // pigpio initialisation failed.
   
   std::cerr << "gpioInitialise failed" << std::endl;
   exit(1);
 }

 gpioSetMode(18, PI_INPUT);
  
 if (gpioSetAlertFunc(18, &dataFunction) != 0)
 {
  std::cerr << "gpioSetAlertFunc 18 failed.\n" << std::endl;
 }

 while (1) sleep(1);
   
 std::cerr << "Calls : "<< calls << std::endl;

 gpioTerminate();


 return 0;
}