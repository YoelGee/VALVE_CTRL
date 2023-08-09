#include "lcd.h"
#include "LiquidCrystal.h" 
//check different values for each button

//Initialzes the LCD controll pins
LCD_controll::LCD_controll():lcd(8,9,4,5,6,7){
    lcd.begin(16,2);
    lcd.clear();
}

//Function used to set the cursor to it's initial position.
void LCD_controll::initialCursor(){
    lcd.setCursor(0,0);
    lcd.print(">");
    cursor_location[0] = 0;
    cursor_location[1] = 0;
}

//Function used in main menu display, as well as within the cursor movement functions.
void LCD_controll::startLCD(){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Valve1");
    lcd.setCursor(9,0);
    lcd.print("Valve2");
    lcd.setCursor(1,1);
    lcd.print("Valve3");
    lcd.setCursor(9,1);
    lcd.print("Valve4");
}

void LCD_controll::MoveCursorRight(){
    
    if(cursor_location[1] == 0 && cursor_location[0] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(8,0);
    lcd.print(">");
    cursor_location[0] = 8;
    cursor_location[1] = 0;
    }
    else if(cursor_location[1] == 1 &&  cursor_location[0] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(8,1);
    lcd.print(">");
    cursor_location[0] = 8;
    cursor_location[1] = 1;
    }
}

void LCD_controll::MoveCursorLeft(){
    if(cursor_location[1] == 0 && cursor_location[0] == 8){
    lcd.clear();
    startLCD();
    lcd.setCursor(0,0);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 0;
    }
    else if(cursor_location[1] == 1 && cursor_location[0] == 8){
    lcd.clear();
    startLCD();
    lcd.setCursor(0,1);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 1;
    }
}

void LCD_controll::MoveCursorUp(){
    if(cursor_location[0] == 0 && cursor_location[1] == 1){
    lcd.clear();
    startLCD();
    lcd.setCursor(cursor_location[0],0);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 0;
    }
    else if(cursor_location[0] == 8 && cursor_location[1] == 1){
    lcd.clear();
    startLCD();
    lcd.setCursor(cursor_location[0],0);
    lcd.print(">");
    cursor_location[0]= 8;
    cursor_location[1] = 0;
    }
}

void LCD_controll::MoveCursorDown(){
    if(cursor_location[0] == 0 && cursor_location[1] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(cursor_location[0],1);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 1;
    }
    else if(cursor_location[0] == 8 && cursor_location[1] == 0 ){
    lcd.clear();
    startLCD();
    lcd.setCursor(cursor_location[0],1);
    lcd.print(">");
    cursor_location[0]= 8;
    cursor_location[1] = 1;
    }
}


//Function used to display valve settings. Sets the display state to its appropriate valve using the cursors x,y coordinates
void LCD_controll::ValveControllON(int x, int y){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("L-BACK");
    lcd.setCursor(8,1);
    lcd.print("R-NEXT");

    if(x==0 && y == 0){

        lcd.setCursor(0,0);
        lcd.print("V1 Time ON:");
        lcd.setCursor(12,0);
        lcd.print(temp_valve_timer_on[0]);
        state = 1;

    }else if(x==8 && y == 0){

        lcd.setCursor(0,0);
        lcd.print("V2 Time ON:");
        lcd.setCursor(12,0);
        lcd.print(temp_valve_timer_on[1]);
        state = 2;

    }else if(x==0 && y == 1){

        lcd.setCursor(0,0);
        lcd.print("V3 Time ON:");
        lcd.setCursor(12,0);
        lcd.print(temp_valve_timer_on[2]);
        state = 3;

    }else if(x==8 && y == 1){

        lcd.setCursor(0,0);
        lcd.print("V4 Time ON:");
        lcd.setCursor(12,0);
        lcd.print(temp_valve_timer_on[3]);
        state = 4; //different valve time controll screens
    }
}

//Function used to display valve settings. Sets the display state to its appropriate valve using the cursors x,y coordinates
void LCD_controll::ValveControllOFF(int x, int y){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("L-BACK");
    lcd.setCursor(8,1);
    lcd.print("R-NEXT");

    if(x==0 && y == 0){

        lcd.setCursor(0,0);
        lcd.print("V1 Time OFF:");
        lcd.setCursor(13,0);
        lcd.print(temp_valve_timer_off[0]);
        state = 5;

    }else if(x==8 && y == 0){

        lcd.setCursor(0,0);
        lcd.print("V2 Time OFF:");
        lcd.setCursor(13,0);
        lcd.print(temp_valve_timer_off[1]);
        state = 6;

    }else if(x==0 && y == 1){

        lcd.setCursor(0,0);
        lcd.print("V3 Time OFF:");
        lcd.setCursor(13,0);
        lcd.print(temp_valve_timer_off[2]);
        state = 7;

    }else if(x==8 && y == 1){

        lcd.setCursor(0,0);
        lcd.print("V4 Time OFF:");
        lcd.setCursor(13,0);
        lcd.print(temp_valve_timer_off[3]);
        state = 8; //different valve time controll screens
    }
}

void LCD_controll::ValveInputON(int x, int CLx, int CLy){ // CLx, CLy = Cursor location (x,y)
    ValveControllON(CLx,CLy);

    if(x<60){
    //right
    //StateInput(x,CLx,CLy);
    ValveControllOFF(CLx,CLy);

  }
    else if(x<200){
    //up
    temp_valve_timer_on[state-1] = temp_valve_timer_on[state-1]+1;
    ValveControllON(CLx,CLy);
  }

  else if (x<400){
    //down
    if(temp_valve_timer_on[state-1]>0){
    temp_valve_timer_on[state-1] = temp_valve_timer_on[state-1]-1;
    ValveControllON(CLx,CLy);}
  }

  else if(x<600){
    //left
    state = 0;
    startLCD();
    initialCursor();
    
  
  }
  else if(x<800){
    //select
    // valve_timer[state-1] = temp_valve_timer_on[state-1];
    // lcd.clear();
    // runningLCD();
    // timeChange = true;
    //state = 5;
    
  }
}


void LCD_controll::ValveInputOFF(int x, int CLx, int CLy){ // CLx, CLy = Cursor location (x,y)
    ValveControllOFF(CLx,CLy);

    if(x<60){
    //right
    //StateInput(x,CLx,CLy);
    StateControll(CLx,CLy);

  }
    else if(x<200){
    //up
    temp_valve_timer_off[state-5] = temp_valve_timer_off[state-5]+1;
    ValveControllOFF(CLx,CLy);
  }
  else if (x<400){
    //down
    if(temp_valve_timer_off[state-5]>0){
    temp_valve_timer_off[state-5] = temp_valve_timer_off[state-5]-1;
    ValveControllOFF(CLx,CLy);}  
  }
  else if(x<600){
    //left
    ValveControllON(CLx, CLy);

  }
  else if(x<800){
    //select
    

  }
}


void LCD_controll::StateControll(int x, int y){
    stateMode=true;
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Sel-START");
    lcd.setCursor(10,1);
    lcd.print("R-HOME");
    lcd.setCursor(11,0);

    if(temp_v_state[state-5] == 1){
        lcd.print("HIGH");
    }
    else if (temp_v_state[state-5] == 0){
        lcd.print("LOW");
    }

    lcd.setCursor(0,0);

    if(x==0 && y == 0){

        lcd.print("V1 State:");

    }else if(x==8 && y == 0){
        
        lcd.print("V2 State:");

    }else if(x==0 && y == 1){

        lcd.print("V3 State:");

    }else if(x==8 && y == 1){

        lcd.print("V4 State:");

    }

}


void LCD_controll::StateInput(int x, int CLx, int CLy){
    StateControll(CLx,CLy);
    if(x<60){
    //right

    startLCD();
    initialCursor();
    v_state[state-5] = temp_v_state[state-5];
    valve_timer_on[state-5] = temp_valve_timer_on[state-5];
    valve_timer_off[state-5] = temp_valve_timer_off[state-5];
    state = 0;
    stateMode = false;
  }
    else if(x<200){
    //up
    temp_v_state[state-5] = 1;
    StateControll(CLx,CLy);

  }
  else if (x<400){
    //down
    temp_v_state[state-5] = 0;
    StateControll(CLx,CLy);
    
  }
  else if(x<600){
    //left
    ValveControllOFF(CLx, CLy);
    stateMode = false;

  }
  else if(x<800){
    //select
    timeChange = true;
    stateMode = false;
    v_state[state-5] = temp_v_state[state-5];
    valve_timer_on[state-5] = temp_valve_timer_on[state-5];
    valve_timer_off[state-5] = temp_valve_timer_off[state-5];
    state = 9;
    lcd.clear();
    runningLCD();

  }
}


void LCD_controll::runningLCD(){
    lcd.clear();
    lcd.setCursor(0,0);
    switch(running_drop){
      case 0:
        lcd.clear();
        lcd.print("V1ON=");
        lcd.print(valve_timer_on[0]);
        lcd.setCursor(8,0);
        lcd.print("V1OFF=");
        lcd.print(valve_timer_off[0]);
        lcd.setCursor(0,1);
        lcd.print("STATE=");
        if(v_state[0])
        lcd.print("ON");
        else if(!v_state[0])
        lcd.print("OFF");
        lcd.setCursor(10,1);
        lcd.print("^ v");
        break;
      case 1:
        lcd.clear();
        lcd.print("V2ON=");
        lcd.print(valve_timer_on[1]);
        lcd.setCursor(8,0);
        lcd.print("V2OFF=");
        lcd.print(valve_timer_off[1]);
        lcd.setCursor(0,1);
        lcd.print("STATE=");
        if(v_state[1])
        lcd.print("ON");
        else if(!v_state[1])
        lcd.print("OFF");
        lcd.setCursor(10,1);
        lcd.print("^ v");
        break;
      case 2:
        lcd.clear();
        lcd.print("V3ON=");
        lcd.print(valve_timer_on[2]);
        lcd.setCursor(8,0);
        lcd.print("V3OFF=");
        lcd.print(valve_timer_off[2]);
        lcd.setCursor(0,1);
        lcd.print("STATE=");
        if(v_state[2])
        lcd.print("ON");
        else if(!v_state[2])
        lcd.print("OFF");
        lcd.setCursor(10,1);
        lcd.print("^ v");
        break;
      case 3:
        lcd.print("V4ON=");
        lcd.print(valve_timer_on[3]);
        lcd.setCursor(8,0);
        lcd.print("V4OFF=");
        lcd.print(valve_timer_off[3]);
        lcd.setCursor(0,1);
        lcd.print("STATE=");
        if(v_state[3])
        lcd.print("ON");
        else if(!v_state[3])
        lcd.print("OFF");
        lcd.setCursor(10,1);
        lcd.print("^ v");
        break;
      case 4:
        lcd.setCursor(0,0);
        lcd.print("Press RST to");
        lcd.setCursor(0,1);
        lcd.print("EXIT and STOP");
    }
    lcd.setCursor(13,1);
    //lcd.print("x-u ");
}


void LCD_controll::ReadRunning(int x){
    if(x<60){
    //right
    runningLCD();
  }
  else if(x<200){
    //up
    button_p = true;
    if(running_drop > 0){
    running_drop--;
    }
    runningLCD();

  }
  else if (x<400){
    //down
    button_p = true;
    if(running_drop < 4){
      running_drop++;
    }
    runningLCD();
  }
  else if(x<600){
    //left
    runningLCD();
  }
  else if(x<800){
    //select
    //button_p = true;
    // if(running_drop == 4){
    //   reset();
    //   stop_pressed = true;
    //   running_drop = 0;
    //   lcd.clear();
    //   startLCD();
    //   initialCursor();
    //   stop_pressed = false;
    //   state = 0;
    // }
    // else{
      runningLCD();
    //}

  }
}

void LCD_controll::ReadInput(int x){
    if(x<60 && state==0){
    //right
    MoveCursorRight();
  }
  else if(x<200 && state==0){
    //up
     MoveCursorUp();
  }
  else if (x<400 && state==0){
    //down
    MoveCursorDown();
  }
  else if(x<600 && state==0){
    //left
    MoveCursorLeft();
  }
  else if(x<800 && state==0){
    //select
    ValveControllON(cursor_location[0], cursor_location[1]);
  }
}

int LCD_controll::StateGetter(){
    return state;
}

long unsigned int* LCD_controll::vtONGetter() {
    return valve_timer_on;
}

void LCD_controll::button_pr(){
  button_p = false;
}

long unsigned int* LCD_controll::vtOFFGetter() {
    return valve_timer_off;
}

int* LCD_controll::CursorGetter(){
    return cursor_location;
}

bool LCD_controll::StateModeGetter(){
    return stateMode;
}

bool LCD_controll::stop(){
  return stop_pressed;
}

bool LCD_controll::button_pressed(){
    return button_p;
}

int* LCD_controll::ValveStateGetter(){
    return v_state;
}

void LCD_controll::reset(){
  for(int i = 0; i<valves; i++){
    valve_timer_off[i] = 0;
    valve_timer_on[i] = 0;
    v_state[i] = 0;
    temp_v_state[i] = 0;
    temp_valve_timer_off[i] = 0;
    temp_valve_timer_on[i] = 0;
  }
}

// void LCD_controll::tempValveStateSetter(){
//     for(int i = 0; i<valves; i++){
//         temp_valve_timer[i] = v_state[i];
//     }
// }

int* LCD_controll::tempValveStateGetter(){
    return temp_v_state;
}