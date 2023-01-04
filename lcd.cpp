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
    cursor_location[0]= 8;
    cursor_location[1] = 0;
    }
    else if(cursor_location[1] == 1 &&  cursor_location[0] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(8,1);
     lcd.print(">");
     cursor_location[0]= 8;
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
void LCD_controll::ValveControll(int x, int y){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("L2CON");
    lcd.setCursor(8,1);
    lcd.print("R4STA");

    if(x==0 && y == 0){

        lcd.setCursor(0,0);
        lcd.print("V1 Time:");
        lcd.setCursor(9,0);
        lcd.print(temp_valve_timer[0]);
        state = 1;

    }else if(x==8 && y == 0){

        lcd.setCursor(0,0);
        lcd.print("V2 Time:");
        lcd.setCursor(9,0);
        lcd.print(temp_valve_timer[1]);
        state = 2;

    }else if(x==0 && y == 1){

        lcd.setCursor(0,0);
        lcd.print("V3 Time:");
        lcd.setCursor(9,0);
        lcd.print(temp_valve_timer[2]);
        state = 3;

    }else if(x==8 && y == 1){

        lcd.setCursor(0,0);
        lcd.print("V4 Time:");
        lcd.setCursor(9,0);
        lcd.print(temp_valve_timer[3]);
        state = 4;
    }
}

void LCD_controll::ValveInput(int x, int CLx, int CLy){
    ValveControll(CLx,CLy);

    if(x<60){
    //right
    StateInput(x,CLx,CLy);  

  }
    else if(x<200){
    //up
    temp_valve_timer[state-1] = temp_valve_timer[state-1]+1;
    ValveControll(CLx,CLy);

  }
  else if (x<400){
    //down
    if(temp_valve_timer[state-1]>0){
    temp_valve_timer[state-1] = temp_valve_timer[state-1]-1;
    ValveControll(CLx,CLy);}
    
  }
  else if(x<600){
    //left
    valve_timer[state-1] = temp_valve_timer[state-1];
    lcd.clear();
    runningLCD();
    timeChange = true;
    state = 5;

  }
  else if(x<800){
    //select
    ValveControll(CLx,CLy);
  }
}



void LCD_controll::StateControll(int x, int y){
    stateMode=true;
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("SEL 2 CONFIRM");

    lcd.setCursor(11,0);
    if(temp_v_state[state-1] == 1){
        lcd.print("HIGH");
    }
    else if (temp_v_state[state-1] == 0){
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
    StateControll(CLx,CLy);
  }
    else if(x<200){
    //up
   temp_v_state[state-1] = 1;
    StateControll(CLx,CLy);

  }
  else if (x<400){
    //down
    temp_v_state[state-1] = 0;
    StateControll(CLx,CLy);
    
  }
  else if(x<600){
    //left
    StateControll(CLx,CLy);
  }
  else if(x<800){
    //select
    v_state[state-1] =  temp_v_state[state-1];
    stateMode = false;
    lcd.clear();
    ValveControll(CLx, CLy);
  }
}

void LCD_controll::runningLCD(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("V1=");
    lcd.print(valve_timer[0]);
    lcd.setCursor(5,0);
    lcd.print("V2=");
    lcd.print(valve_timer[1]);
    lcd.setCursor(10,0);
    lcd.print("V3=");
    lcd.print(valve_timer[2]);
    lcd.setCursor(0,1);
    lcd.print("V4=");
    lcd.print(valve_timer[3]);
    lcd.setCursor(5,1);
    lcd.print("exit on up ");
    lcd.print(valve_timer[3]);
}

void LCD_controll::ReadRunning(int x){
    if(x<60){
    //right
    runningLCD();
  }
  else if(x<200){
    //up
    state = 0;
    lcd.clear();
    startLCD();
    initialCursor();
  }
  else if (x<400){
    //down
    runningLCD();
  }
  else if(x<600){
    //left
    runningLCD();
  }
  else if(x<800){
    //select
    runningLCD();
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
    ValveControll(cursor_location[0], cursor_location[1]);
  }
}

int LCD_controll::StateGetter(){
    return state;
}

long unsigned int* LCD_controll::vtGetter() {
    return valve_timer;
}

int* LCD_controll::CursorGetter(){
    return cursor_location;
}

bool LCD_controll::StateModeGetter(){
    return stateMode;
}

int* LCD_controll::ValveStateGetter(){
    return v_state;
}

void LCD_controll::tempValveStateSetter(){
    for(int i = 0; i<valves; i++){
        temp_valve_timer[i] = v_state[i];
    }
}

int* LCD_controll::tempValveStateGetter(){
    return temp_v_state;
}