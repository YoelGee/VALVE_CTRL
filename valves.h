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
        bool state_set = false;
        int itt[valves];
        int valve_state[valves];
        long unsigned int valve_time_on[valves];
        long unsigned int valve_time_off[valves];
        long unsigned int valve_on[valves];
        long unsigned int valve_off[valves];
        bool state_changed_on = false;
        bool state_changed_off = false;

    public:
        /// @brief Used to switch the PINMODE of the specific valve using millis() timer
        //* takes current time and compared it to the ms interval and if condition holds states are flipped
        /// @param currentTime how much time has passed since the valves started
        /// @param valveNumber used to identify what valve is being changed
        /// @param vState refrence pointers to an array of states the user set within the LCD_Controll class
        /// @param tmpVS refrence pointers to the temporary array of states the user set within the LCD_Controll class

        void valveSwitch(long unsigned int currentTime, int valveNumber, int* vState, int* tmpVS, long unsigned int* ON, long unsigned int* OFF);

        void valveInvervalONSetter(int valve_interval, int valve_number);
        void valveInvervalOFFSetter(int valve_interval, int valve_number);
        
        long unsigned int* valveInvervalONGetter();
        long unsigned int* valveInvervalOFFGetter();

        int valveInttGetter();
        void valveStateSetter(int* vState);

        long unsigned int* valveTimeONGetter();
        long unsigned int* valveTimeOFFGetter();

        void valveStateSetter(int valve_number, int valve_state);
        int* valveStateGetter();

        bool stateChangeGetter();

        bool states_set();
        void states_set_bool();

};

#endif