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
        /// @brief Used to switch the PINMODE of the specific valve using millis() timer
        //* takes current time and compared it to the ms interval and if condition holds states are flipped
        /// @param currentTime how much time has passed since the valves started
        /// @param valveNumber used to identify what valve is being changed
        /// @param vState refrence pointers to an array of states the user set within the LCD_Controll class
        /// @param tmpVS refrence pointers to the temporary array of states the user set within the LCD_Controll class
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