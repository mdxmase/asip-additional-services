/*    
 * Example sketch to show how to add two servos to pin
 * 3 and 4
 */



#include <asip.h>       // the base class definitions
#include <asipIO.h>     // the core I/O class definition
#include <asipServos.h> // derived definitions for servo
#include <Servo.h> // needed for the servo service 


char const *sketchName = "asipServoExample";

//declare servo object(s) 
const byte NBR_SERVOS =2; // Specify the number of servos
const byte servoPins[]    = {3,4}; // Pin to which servos are attached: change as appropriate
Servo myServos[NBR_SERVOS];  // create servo objects
asipCHECK_PINS(servoPins[NBR_SERVOS]);  // compiler will check if the number of pins is same as number of servos

asipServoClass asipServos(id_SERVO_SERVICE, NO_EVENT);

// make a list of the created services
asipService services[] = { 
                                 &asipIO, // the core class for pin level I/O
                                 &asipServos
				 };

void setup()
{
  Serial.begin(57600);
  asipIO.begin(); 
  // start the services
  asipServos.begin(NBR_SERVOS,servoPins,myServos);

  asip.sendPinModes(); // for debug
  asip.sendPortMap(); 

  for(int i=0; i < asipServiceCount(services); i++)
  {
    services[i]->reportName(&Serial); 
    Serial.print(" is service ");
    Serial.write(services[i]->getServiceId());
    Serial.println();  
  }
  Serial.println("!AsipServoExample is ready");	
}

void loop() 
{
  asip.service();
}

  
