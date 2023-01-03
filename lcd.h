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

        //Used to ceate a condtion to prevent .ino from running mutiple things at once
        bool stateMode;

        

    public:
    
       void initialCursor();

       void startLCD();

       void MoveCursorUp();
       void MoveCursorDown();
       void MoveCursorLeft();
       void MoveCursorRight();


        /// @brief
        //* Function allows user to move cursor around in order to choose which valve to controll
        //* Uses MoveCursorRight, MoveCursorLeft, etc functions in order to re-print LCD output
        //* On select changes the state to ValveControll mode which allows you to change the selected valve time 
        /// @param x analog pin being read
       void ReadInput(int x);
       
       //Function used in ReadRunning function
       void runningLCD();
    
        /// @brief 
        //* Used to desplay all Valves and the configuration they are set to
        //* Uses runingLCD function in order to display to make sure the user doesn't exit with an illegal input
        /// @param x analog pin being read
        void ReadRunning(int x);

        //Function used to display valve settings. Sets the display state to its appropriate valve using the cursors x,y coordinates
       void ValveControll(int CLx,int CLy);

        /// @brief Used to controll the valve timer as well as enter the valve state settings 
        //* Uses ValveControll function to display the valve settings information to the LCD
        //* Uses StateInput to go into the valve state settings uppon clicking right
        //* Uppon left click the state is set to 5 and uses runningLCD function to display all valves and their configs
        /// @param x analog pin being read
        /// @param CLx the last recorded x position of the cursor; saved within valve_coordinate variable
        /// @param CLy the last recorded y position of the cursor; saved within valve_coordinate variable
       void ValveInput(int x, int CLx, int CLy);

        //Function used in StateInput for LCD display
        void StateControll(int CLx, int CLy);

        /// @brief 
        //* Used to controll the state the selected valve should start at.
        //* Uses StateControll function to display the selected valve state on the LCD screen
        //* On select allows user to set the appropriate valve to the users desired state
        //* Uppon pressing select the valve state is set and boolen stateMode is set to false
        /// @param x analog input being read
        /// @param CLx the last recorded x position of the cursor; saved within valve_coordinate variable
        /// @param CLy the last recorded y position of the cursor; saved within valve_coordinate variable
        void StateInput(int x, int CLx, int CLy);

        //Used to get the display state we are in ie. valve i settings, main menu
        int StateGetter();

        //Used to get if we are in valve state display state. Used within .ino for checking purposes. 
       bool StateModeGetter();

       //Used to get the array that has all of the valve states saved
       int* ValveStateGetter();

        //void CursorSetter(int* cursor_location);

        int* CursorGetter();

       void vtSetter(unsigned int* valve_timer);
       long unsigned int* vtGetter();

       LCD_controll();

};

#endif