#include "lcd.h"
#include "valves.h"

LCD_controll start;

Valve_Controll valve;

bool launch = false;

long unsigned int current_time;
long unsigned int temp_current_time;

void timer(long unsigned int currentTime){
  temp_current_time = currentTime;
  launch = true;
}

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
    launch = false;
    //current_time=0;
    start.ReadInput(x);
    delay(100);

  }
  else if(start.StateGetter() >= 1 && start.StateGetter() < 5 && !(start.StateModeGetter()))
  {

    //current_time=0;
    launch = false;
    start.ValveInput(x,start.CursorGetter()[0],
    start.CursorGetter()[1]);
    delay(250);

  }

  else if(start.StateModeGetter()){

    start.StateInput(x, start.CursorGetter()[0],
    start.CursorGetter()[1]);
    delay(200);
    Serial.println(start.StateGetter());

  }

  else if(start.StateGetter() == 5 && !(start.StateModeGetter())){
    current_time = millis();


    if(!launch){
      timer(current_time);
    }

    current_time = current_time - temp_current_time;
    
    start.ReadRunning(x);

  for(int i = 0; i<valves; i++){

    if(start.vtGetter()[i] > 0){
    valve.valveStateSetter(i, start.ValveStateGetter()[i]);
    valve.valveInvervalSetter(start.vtGetter()[i], i);
    valve.valveSwitch(current_time, i, start.ValveStateGetter(), start.tempValveStateGetter());


    }
  }

  digitalWrite(valve_1_PIN, valve.valveStateGetter()[0]);
  digitalWrite(valve_2_PIN, valve.valveStateGetter()[1]);
  digitalWrite(valve_3_PIN, valve.valveStateGetter()[2]);
  digitalWrite(valve_4_PIN, valve.valveStateGetter()[3]);

  Serial.print("current time = ");
  Serial.println(current_time);
  // for(int i=1 ; i<=valves; i++) {
  Serial.print("valve ");
  Serial.print(1);

  // Serial.print(" time = ");
  // Serial.println(valve.valveTimeGetter()[0]);

  // Serial.print(" min = ");
  // Serial.println(start.vtGetter()[0]);

  // // Serial.print(" test Interval = ");
  // // Serial.println(valve.valveInttGetter());

  // Serial.print(" interval = ");
  // Serial.print(valve.valveInvervalGetter()[0]);

  Serial.print("valve.valveState state = ");
  Serial.println(valve.valveStateGetter()[0]);
  Serial.print("start.valveState state = ");
  Serial.println(start.ValveStateGetter()[0]);
  Serial.print("start.Temp valve State state = ");
  Serial.println(start.tempValveStateGetter()[0]);

  
  Serial.println("");

  //}

  //delay(100);
  }



  
  
  // put your main code here, to run repeatedly:

}
