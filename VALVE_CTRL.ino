#include "valve_menu.h"
ValveMenu v;
void setup(){
    Serial.begin(115200);
    v.StartTest();
    
}

void loop(){
    v.MainMenu();
}