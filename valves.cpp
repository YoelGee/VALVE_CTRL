#include "valves.h"

void Valve_Controll::valveSwitch(long unsigned int currentTime, int valveNumber, int* vState, int* tmpVS){
  if(currentTime - valve_time[valveNumber] >= valve_interval[valveNumber]){
    valve_time[valveNumber] = currentTime;
    valve_state[valveNumber] = !valve_state[valveNumber];
    vState[valveNumber] = !vState[valveNumber];
    tmpVS[valveNumber] = !tmpVS[valveNumber];
    state_changed = true;
  }
  else{
  state_changed = false;
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

long unsigned int* Valve_Controll::valveInvervalGetter(){
    return valve_interval;
}

void Valve_Controll::valveInvervalSetter(int valveInterval, int valveNumber){

        /* code */
        valve_interval[valveNumber] = valveInterval * 60000;
        //valve_inttt = valveInterval * 60000;

}


// bool Valve_Controll::stateChangeGetter(){

//     return state_changed;

// }
// int Valve_Controll::valveInttGetter(){
//     return valve_inttt;
// }