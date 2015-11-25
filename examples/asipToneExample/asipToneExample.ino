/*    
 * Example sketch to show how to incorporate additional
 * services: distance, servo, tone all included here.
 * Servo is connected to pin 3, distance to pin 4
 * and tone to pin 9.
 */



#include <asip.h>       // the base class definitions
#include <asipIO.h>     // the core I/O class definition
#include <asipTone.h> // square wave tone generator

#include <Servo.h> // needed for the servo service 


char const *sketchName = "asipToneExample";

const byte tonePin = 9;
asipToneClass asipTone(id_TONE_SERVICE, NO_EVENT);
                 
// make a list of the created services
asipService services[] = { 
                                 &asipIO, // the core class for pin level I/O
                                 &asipTone
				 };

void setup()
{
  Serial.begin(57600);
  asipIO.begin(); 
  // start the services
  asipTone.begin(tonePin);

  asip.sendPinModes(); // for debug
  asip.sendPortMap(); 

  for(int i=0; i < asipServiceCount(services); i++)
  {
    services[i]->reportName(&Serial); 
    Serial.print(" is service ");
    Serial.write(services[i]->getServiceId());
    Serial.println();  
  }
  Serial.println("!AsipToneExample is ready");	
}

void loop() 
{
  asip.service();
}

  
