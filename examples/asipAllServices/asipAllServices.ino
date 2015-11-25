/*    
 * Example sketch to show how to incorporate additional
 * services: distance, servo, tone all included here.
 * Servo is connected to pin 3, distance to pin 4
 * and tone to pin 9.
 */



#include <asip.h>       // the base class definitions
#include <asipIO.h>     // the core I/O class definition
#include <asipTone.h> // square wave tone generator
#include <asipDistance.h> // ultrasonics distance sensor
#include <asipServos.h> // derived definitions for servo
#include <Servo.h> // needed for the servo service 


char const *sketchName = "asipAllServices";

//declare servo object(s) 
const byte NBR_SERVOS =1; // Could be more than one!
const byte servoPins[]    = {3}; // Pin to which servo is attached: change as appropriate
Servo myServos[NBR_SERVOS];  // create servo objects
asipCHECK_PINS(servoPins[NBR_SERVOS]);  // compiler will check if the number of pins is same as number of servos

const byte NBR_DISTANCE_SENSORS = 1; // Could be more than one!
const byte distancePins[] = {4}; // Pin to which distance sensor is attached: change as appropriate
asipCHECK_PINS(distancePins[NBR_DISTANCE_SENSORS]); //this declaration tests for correct nbr of pin initializers

const byte tonePin = 9;
asipToneClass asipTone(id_TONE_SERVICE, NO_EVENT);
asipServoClass asipServos(id_SERVO_SERVICE, NO_EVENT);
asipDistanceClass asipDistance(id_DISTANCE_SERVICE);
                 
// make a list of the created services
asipService services[] = { 
                                 &asipIO, // the core class for pin level I/O
                                 &asipTone, 
                                 &asipServos,                                 
                                 &asipDistance
				 };

void setup()
{
  Serial.begin(57600);
  asipIO.begin(); 
  // start the services
  asipDistance.begin(NBR_DISTANCE_SENSORS,distancePins); 
  asipServos.begin(NBR_SERVOS,servoPins,myServos);
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
  Serial.println("!AsipAllServices is ready");	
}

void loop() 
{
  asip.service();
}

  
