#ifndef VALVES_H_
#define VALVES_H_

#include "LiquidCrystal.h" 

#define valves 4
#define valve_1_PIN 50
#define valve_2_PIN 51
#define valve_3_PIN 52
#define valve_4_PIN 53

class Valve_Controll{
    private:

        int valve_state[valves];
        long unsigned int valve_time[valves];    
        long unsigned int valve_interval[valves];
        bool state_changed = false;

    public:

        void valveSwitch(long unsigned int currentTime, int valveNumber, int* vState, int* tmpVS);

        void valveInvervalSetter(int valve_interval, int valve_number);
        long unsigned int* valveInvervalGetter();

        int valveInttGetter();

        void valveStateSetter(int* vState);

        long unsigned int* valveTimeGetter();

        void valveStateSetter(int valve_number, int valve_state);
        int* valveStateGetter();

        bool stateChangeGetter();

};

#endif