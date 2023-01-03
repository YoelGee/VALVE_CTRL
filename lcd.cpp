#include "lcd.h"
#include "LiquidCrystal.h" 
//check different values for each button


LCD_controll::LCD_controll():lcd(8,9,4,5,6,7){
    lcd.begin(16,2);
    lcd.clear();
}

void LCD_controll::initialCursor(){
    lcd.setCursor(0,0);
    lcd.print(">");
    cursor_location[0] = 0;
    cursor_location[1] = 0;
}

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

void LCD_controll::MoveCursorRight(int CLy){
    
    if(CLy == 0 && CursorGetter()[0] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(8,0);
    lcd.print(">");
    cursor_location[0]= 8;
    cursor_location[1] = 0;
    }
    else if(CLy == 1 &&  CursorGetter()[0] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(8,1);
     lcd.print(">");
     cursor_location[0]= 8;
    cursor_location[1] = 1;
    }
}

void LCD_controll::MoveCursorLeft(int CLy){
    if(CLy == 0 && CursorGetter()[0] == 8){
    lcd.clear();
    startLCD();
    lcd.setCursor(0,0);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 0;
    }
    else if(CLy == 1 && CursorGetter()[0] == 8){
    lcd.clear();
    startLCD();
    lcd.setCursor(0,1);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 1;
    }
}

void LCD_controll::MoveCursorUp(int CLx){
    if(CLx == 0 && CursorGetter()[1] == 1){
    lcd.clear();
    startLCD();
    lcd.setCursor(CLx,0);
    lcd.print(">");
     cursor_location[0]= 0;
    cursor_location[1] = 0;
    }
    else if(CLx == 8 && CursorGetter()[1] == 1){
    lcd.clear();
    startLCD();
    lcd.setCursor(CLx,0);
    lcd.print(">");
    cursor_location[0]= 8;
    cursor_location[1] = 0;
    }
}

void LCD_controll::MoveCursorDown(int CLx){
    if(CLx == 0 && CursorGetter()[1] == 0){
    lcd.clear();
    startLCD();
    lcd.setCursor(CLx,1);
    lcd.print(">");
    cursor_location[0]= 0;
    cursor_location[1] = 1;
    }
    else if(CLx == 8 && CursorGetter()[1] == 0 ){
    lcd.clear();
    startLCD();
    lcd.setCursor(CLx,1);
    lcd.print(">");
    cursor_location[0]= 8;
    cursor_location[1] = 1;
    }
}

/// @brief 
/// @param x 
/// @param y /

void LCD_controll::ValveControll(int x, int y){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("L 2 CONF");
    lcd.setCursor(9,1);
    lcd.print("R 4 STE");

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
    state=6;
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
   // lcd.setCursor(0,0);
    //  lcd.print(valve_timer[state-1]);
    //   lcd.setCursor(0,1);
    //  lcd.print(temp_valve_timer[state-1]);
    timeChange = true;
    state = 5;
  }
  else if(x<800){
    //select
  }
}

bool LCD_controll::StateModeGetter(){
    return stateMode;
}

int* LCD_controll::ValveStateGetter(){
    return v_state;
}

void LCD_controll::StateControll(int x, int y){
    stateMode=true;
    lcd.clear();
    lcd.setCursor(0,1);

    if(temp_v_state[state-1] == 1){
    
        lcd.print("HIGH");
    }
    else{

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
    lcd.print("exit on up");
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
    MoveCursorRight(cursor_location[1]);
  }
  else if(x<200 && state==0){
    //up
     MoveCursorUp(cursor_location[0]);
  }
  else if (x<400 && state==0){
    //down
    MoveCursorDown(cursor_location[0]);
  }
  else if(x<600 && state==0){
    //left
    MoveCursorLeft(cursor_location[1]);
  }
  else if(x<800 && state==0){
    //select
    ValveControll(cursor_location[0], cursor_location[1]);
  }
}

int LCD_controll::StateGetter(){
    return state;
}

unsigned int* LCD_controll::vtGetter() {
    return valve_timer;
}

int* LCD_controll::CursorGetter(){
    return cursor_location;
}

void LCD_controll::CursorSetter(int* cursor_location){

    for (int i=0; i<pointer; i++){
        this->cursor_location[i] = cursor_location[i];
    }
}

// int Valve_Controll::valveSwitch(long unsigned int currentTime, long unsigned int* valveTime, int valveInterval, int valveState){
//   if(currentTime - *valveTime >= valveInterval && valve_interval != 0){
    
//     valve_time[] = currentTime;
//     valveState = !valveState;
//     return valveState;
//   }
// }
