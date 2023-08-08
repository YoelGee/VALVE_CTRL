#include "valves.h"

void Valve_Controll::valveSwitch(long unsigned int currentTime, int valveNumber, int* vState, int* tmpVS){
  if(valve_state[valveNumber] && state_changed_on == false && currentTime - valve_time_on[valveNumber] >= valve_on[valveNumber]){
    valve_time_on[valveNumber] = currentTime;
    valve_state[valveNumber] = 0;
    vState[valveNumber] = 0;
    tmpVS[valveNumber] = 0;
    state_set = false;
    state_changed_on = true;
    state_changed_off = false;
  }
  else if(!valve_state[valveNumber] &&  state_changed_off == false && currentTime - valve_time_off[valveNumber] >= valve_off[valveNumber]){
    valve_time_off[valveNumber] = currentTime;
    valve_state[valveNumber] = 1;
    vState[valveNumber] = 1;
    tmpVS[valveNumber] = 1;
    state_set = false;
    state_changed_on = false;
    state_changed_off = true;
  }
 
}


long unsigned int* Valve_Controll::valveTimeONGetter(){
    return valve_time_on;
}

long unsigned int* Valve_Controll::valveTimeOFFGetter(){
    return valve_time_off;
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

long unsigned int* Valve_Controll::valveInvervalONGetter(){
    return valve_on;
}

long unsigned int* Valve_Controll::valveInvervalOFFGetter(){
    return valve_off;
}

void Valve_Controll::valveInvervalONSetter(int valveInterval, int valveNumber){
        /* code */
        valve_on[valveNumber] = valveInterval * 60000;
        //valve_inttt = valveInterval * 60000;
}

void Valve_Controll::valveInvervalOFFSetter(int valveInterval, int valveNumber){
        /* code */
        valve_off[valveNumber] = valveInterval * 60000;
        //valve_inttt = valveInterval * 60000;
}

bool Valve_Controll::states_set(){
    return state_set;
}

void Valve_Controll::states_set_bool(){
    state_set = true;
}
// bool Valve_Controll::stateChangeGetter(){

//     return state_changed;

// }
// int Valve_Controll::valveInttGetter(){
//     return valve_inttt;
// }