#include "valve_menu.h"
ValveMenu v;
void setup(){
    //v.StartTest();
    Serial.begin(115200);
}

void loop(){
    v.MainMenu();
}