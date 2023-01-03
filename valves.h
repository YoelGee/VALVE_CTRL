#ifndef VALVES_H_
#define VALVES_H_
#include "LiquidCrystal.h" 

#define valves 4

class Valve_Controll{
    private:
        int valve_state[valves];
        long unsigned int valve_time[valves];    
        unsigned int valve_interval[valves];

    public:
        // int valveSwitch(long unsigned int currentTime, long unsigned int *valveTime,
        //  int valveInterval, int valveState);
        void valveSwitch(long unsigned int currentTime, int valveNumber, int* vState);

        void valveInvervalSetter(int valve_interval, int valve_number);
        unsigned int* valveInvervalGetter();

        void valveStateSetter(int* vState);

        long unsigned int* valveTimeGetter();

        void valveStateSetter(int valve_number, int valve_state);
        int* valveStateGetter();


        
};

#endif