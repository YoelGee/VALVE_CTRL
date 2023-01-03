#include "valves.h"

void Valve_Controll::valveSwitch(long unsigned int currentTime, int valveNumber, int* vState){
  if(currentTime - valve_time[valveNumber] >= valve_interval[valveNumber]){
    valve_time[valveNumber] = currentTime;
    valve_state[valveNumber] = !valve_state[valveNumber];
    vState[valveNumber] = !vState[valveNumber];
  }
}

long unsigned int* Valve_Controll::valveTimeGetter(){
    return valve_time;
}

void Valve_Controll::valveStateSetter(int* vState){
    for(int i = 0; i<4; i++){
    valve_state[i]=vState[i];
    }

}

void Valve_Controll::valveStateSetter(int valveNumber, int state){
    valve_state[valveNumber] = state;
}


int* Valve_Controll::valveStateGetter(){
    return valve_state;
}

unsigned int* Valve_Controll::valveInvervalGetter(){
    return valve_interval;
}

void Valve_Controll::valveInvervalSetter(int valveInterval, int valveNumber){

        /* code */
        valve_interval[valveNumber] = valveInterval * 60000;

}