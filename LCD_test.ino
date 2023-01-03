#include "lcd.h"
#include "valves.h"

#define valve_1_PIN 50
#define valve_2_PIN 51
#define valve_3_PIN 52
#define valve_4_PIN 53

LCD_controll start;

Valve_Controll valve;

long unsigned int current_time;

//const int* valve_timers = start.vtGetter();

void setup() {
  // put your setup code here, to run once:
   start.startLCD();
  Serial.begin(9600);
   pinMode(valve_1_PIN, OUTPUT);
   pinMode(valve_2_PIN, OUTPUT);
   pinMode(valve_3_PIN, OUTPUT);
   pinMode(valve_4_PIN, OUTPUT);

   start.initialCursor();
  
}

void loop() {

  int x = analogRead(0);

  if(start.StateGetter() == 0 && !(start.StateModeGetter()))
  {
    current_time=0;
    start.ReadInput(x);
    delay(100);
  }
  else if(start.StateGetter() >= 1 && start.StateGetter() < 5 && !(start.StateModeGetter()))
  {
    current_time=0;
    start.ValveInput(x,start.CursorGetter()[0],
    start.CursorGetter()[1]);
    delay(250);
  }
  else if(start.StateModeGetter()){
    start.StateInput(x, start.CursorGetter()[0],
    start.CursorGetter()[1]);
    delay(200);
  }
  else if(start.StateGetter() == 5 && !(start.StateModeGetter())){
    current_time = millis();
    start.ReadRunning(x);
  for(int i = 0; i<valves; i++){
    if(start.vtGetter()[i] > 0){
    valve.valveStateSetter(i, start.ValveStateGetter()[i]);
    valve.valveInvervalSetter(start.vtGetter()[i], i);
    // valve.valveSwitch(current_time, &valve.valveTimeGetter()[i],
    //  valve.valveInvervalGetter()[i],valve.valveStateGetter()[i]);
    valve.valveSwitch(current_time, i, start.ValveStateGetter());}
  }

  digitalWrite(valve_1_PIN, valve.valveStateGetter()[0]);
  digitalWrite(valve_2_PIN, valve.valveStateGetter()[1]);
  digitalWrite(valve_3_PIN, valve.valveStateGetter()[2]);
  digitalWrite(valve_4_PIN, valve.valveStateGetter()[3]);

  Serial.print("current time = ");
  Serial.println(current_time);
  for(int i=1 ; i<=valves; i++) {
  Serial.print("valve ");
  Serial.print(i);
  Serial.print(" time = ");
  Serial.println(valve.valveTimeGetter()[i-1]);
  Serial.print(" min = ");
  Serial.println(start.vtGetter()[i-1]);
  Serial.print(" interval = ");
  Serial.print(valve.valveInvervalGetter()[i-1]);
  Serial.print("valve ");
  Serial.print(i);
  Serial.print(" state = ");
  Serial.println(valve.valveStateGetter()[i-1]);
  Serial.println("");

  }

  //delay(100);
  }



  
  
  // put your main code here, to run repeatedly:

}
