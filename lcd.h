#ifndef LCD_H_
#define LCD_H_
#include "LiquidCrystal.h" 

#define valves 4
#define pointer 2


class LCD_controll{
    private:

        LiquidCrystal lcd;

        int cursor_location[pointer];
        long unsigned int valve_timer[valves];
        int temp_valve_timer[valves];
        int v_state[valves];
        int temp_v_state[valves];
        int temp;
        int state;
        bool timeChange;
        bool stateMode;

        

    public:
    
       void initialCursor();
       void startLCD();
       void runningLCD();
       void ReadInput(int x);
       
       void MoveCursorUp(int CLx);
       void MoveCursorDown(int CLx);
       void MoveCursorLeft(int CLy);
       void MoveCursorRight(int CLy);

       void ValveControll(int CLx,int CLy);

       void StateControll(int CLx, int CLy);

       void ReadRunning(int x);

       int StateGetter();

       bool StateModeGetter();
       int* ValveStateGetter();

        void CursorSetter(int* cursor_location);
        int* CursorGetter();

       void vtSetter(unsigned int* valve_timer);
       long unsigned int* vtGetter();

       void ValveInput(int x, int CLx, int CLy);
        void StateInput(int x, int CLx, int CLy);
       LCD_controll();

    

};

#endif