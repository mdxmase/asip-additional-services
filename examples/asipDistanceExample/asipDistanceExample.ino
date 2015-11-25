/*    
 * Example sketch to show how to incorporate a sonar distance
 * sensor (assuming that trigger and echo pin are the same
 * pin: pin 4).
 */



#include <asip.h>       // the base class definitions
#include <asipIO.h>     // the core I/O class definition
#include <asipDistance.h> // ultrasonics distance sensor

#include <Servo.h> // needed for the servo service 

char const *sketchName = "asipDistanceExample";

const byte NBR_DISTANCE_SENSORS = 1; // Could be more than one!
const byte distancePins[] = {4}; // Pin to which distance sensor is attached: change as appropriate
asipCHECK_PINS(distancePins[NBR_DISTANCE_SENSORS]); //this declaration tests for correct nbr of pin initializers

asipDistanceClass asipDistance(id_DISTANCE_SERVICE);
                 
// make a list of the created services
asipService services[] = { 
                                 &asipIO, // the core class for pin level I/O
                                 &asipDistance
				 };

void setup()
{
  Serial.begin(57600);
  asipIO.begin(); 
  // start the services
  asipDistance.begin(NBR_DISTANCE_SENSORS,distancePins); 

  asip.sendPinModes(); // for debug
  asip.sendPortMap(); 

  for(int i=0; i < asipServiceCount(services); i++)
  {
    services[i]->reportName(&Serial); 
    Serial.print(" is service ");
    Serial.write(services[i]->getServiceId());
    Serial.println();  
  }
  Serial.println("!AsipDistanceExample is ready");	
}

void loop() 
{
  asip.service();
}

  
