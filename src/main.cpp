// COMP-10184 – Mohawk College 
// ALARM SYSTEM
//  
// This program would represent an alarm system
// when Motion is detected and a 10s countdown starts. 
// The user has 10 seconds to press the alarmSwitch before the alarm activates. 
// If the alarmSwitch is not pressed within 10 seconds, the alarm will activate. 
// If the user presses the alarmSwitch with 10 seconds, the alarm is de-activated. 
// and if deactivated user has to press alarmSwitch again to activate it 

// @Author  ADEBOWALE ATOFARATI
// @Id      000789108
// 
// I created this work and I have not shared it with anyone else. 


#include <Arduino.h>
// digital input pin definitions
#define motionSensors D5
#define alarmSwitch D6 
//delay in milliseconds
#define blinkDelay 125
#define breakDelay 1000
#define StartDelay 300


// *************************************************************
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);
  // PIR motionSensors is an INPUT
  pinMode(motionSensors, INPUT);
  // alarmSwitch is an INPUT
  pinMode(alarmSwitch, INPUT_PULLUP);
  Serial.println("ALARM LOADING");

  delay(StartDelay);
  digitalWrite(LED_BUILTIN, HIGH);
  
}
// *************************************************************
// To get and set alarm state 
// 
// @param bool a
// return bool alarmState
// 
class AlarmState{
  public:
    void set(bool a){
      alarmState= a;
    }
    bool get(){
      return alarmState;
    }

  private:
  bool alarmState;

};
// To get and set motion state
// 
// @param bool a
// return bool motion
// 
class MotionState{
  public:
    void set(bool a){
      motion= a;
    }
    bool get(){
      return motion;
    }

  private:
  bool motion;

};


// to check if the Alarm Switch was Pressed
// 
// @param none
// return int 
// 
int ialarmSwitchPressed(){
  int x;
  x= 0; 
  Serial.println(digitalRead(alarmSwitch));
  if (digitalRead(alarmSwitch) == 0)
  {
  x = 1;
  }

  return x;
}

// To make the light blink
// 
// @param none
// return none
// 
void blinkLights(){
        digitalWrite(LED_BUILTIN, LOW);
        delay(blinkDelay);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(blinkDelay);
}
// *************************************************************

void loop()
{
// bool sensorStatusON ;
//  read PIR sensor (true = Motion detected!). As long as there
//  is motion, this signal will be true. About 2.5 seconds after
//  motion stops, the PIR signal will become false.
// sensorStatusON  = digitalRead(sensor);

// DEBUG SENSOR

// send the PIR signal directly to the LED
// but invert it because true = LED off!

// digitalWrite(LED_BUILTIN, !sensorStatusON );
// delay(10000);

  AlarmState Alarm;
  MotionState motion;

  Serial.println("The ALARM IS SWITCHED ON, WAITING FOR MOTION");

  motion.set(false);
  Alarm.set(true);

  // if motion is detected  
  if (digitalRead(motionSensors) == HIGH)
  {
    motion.set(true);
    Alarm.set(true);
  }

  if (motion.get() == true)
  {

    for (int x = 0; x < 40; x++)
    {
      Serial.println("LIGHT IS BLINKING");

      if (ialarmSwitchPressed() != 1)
      {
        blinkLights();
        
      }
      else
      {
        Alarm.set(false);
        Serial.println("THE ALARM SWITCH IS PRESSED");
        delay(breakDelay);
        break;
      }
    }
  }
  else
  {
   Alarm.set(true);
   motion.set(false);
  }


  // loop until alarm is switched back on
   while( Alarm.get()  ==  false){
    Serial.println("The ALARM IS SWITCHED OFF");
    if (ialarmSwitchPressed() == 1)
      {

       Alarm.set(true);
        break;
        }
        continue;
   } 

}

