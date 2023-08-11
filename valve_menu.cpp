#include "valve_menu.h"

ValveMenu::ValveMenu(){
    for(int i = 0; i < 4; i++){
        valves[i] = Relay(i + VALVE_PIN_START);
    }
}

void ValveMenu::MainMenu(){
    const int num_of_options = 2;
    int cursor = 0;
    char menu_options[num_of_options][17] = {"> Valve Settings", "> Start Sampling"};
    while(true){
        if(Serial.available()){
            SerialCheck();
            if(invalid = false)
                HandleGru();
        }        
        lcd.PrintBothLine("Main Menu", menu_options[cursor]);
        ButtonPressed pressed = UpdateMenuCursor(&cursor, num_of_options);
        if(pressed == Select || pressed == Right){
            if(cursor == 0){
                SelectValve();
            }
            else{
                Start();
                return;
            }
        }
        else if(pressed == Left) return;
        delay(MENU_DELAY);
    }
}
void ValveMenu::SelectValve(){
    const int num_of_options = 4;
    int cursor = 0;
    char second_line[17];
    ButtonPressed pressed = NotPressed;
    while(true){
        sprintf(second_line, "Valve %d", cursor + 1);
        lcd.PrintBothLine("Select a Valve", second_line);
        pressed = UpdateMenuCursor(&cursor, num_of_options);
        if(pressed == Select || pressed == Right){
            ChangeValveSettingsMenu(cursor);
        }
        else if(pressed == Left) return;
        delay(MENU_DELAY);
    }
}
void ValveMenu::ChangeValveSettingsMenu(int valve_num){
    const int num_of_options = 3;
    int cursor = 0;
    char menu_options[num_of_options][17] = {"Valve Off Timer", "Valve On Timer", "Valve State"};
    char first_line[17];
    char second_line[17];
    char on_off_str[2][4] = {"Off", "On"};
    ButtonPressed pressed = NotPressed;
    while(true){
        lcd.PrintBothLine("Select Option", menu_options[cursor]);
        pressed = UpdateMenuCursor(&cursor, num_of_options);
        if(pressed == Select || pressed == Right){
            if(cursor == 2) {
                sprintf(first_line, "Valve #%d State", valve_num + 1);
                int num_of_options2 = 2;
                int cursor_state = valve_settings[valve_num][cursor];
                ButtonPressed pressed_state = NotPressed;
                while(true){
                    lcd.PrintBothLine(first_line, on_off_str[cursor_state]);
                    pressed_state = UpdateMenuCursor(&cursor_state, num_of_options2);
                    if(pressed_state == Select || pressed_state == Right){
                        //valve_settings[valve_num][cursor] = cursor_state;
                        ChangeValveSettings(valve_num, cursor_state, cursor);
                        break;
                    }
                    else if(pressed_state == Left){
                        break;
                    }
                    delay(MENU_DELAY);
                }
                
            }
            else{
                sprintf(first_line, "Valve %d %s Time", valve_num + 1, on_off_str[cursor]);
                int new_time = valve_settings[valve_num][cursor];
                //int cursor_time = 0;
                ButtonPressed pressed_time = NotPressed;
                bool exit = false;
                while(true){
                    sprintf(second_line, "%d min", new_time);
                    lcd.PrintBothLine(first_line, second_line);
                    pressed_time = lcd.GetButtonPressed();
                    switch(pressed_time){
                        case Up_button:
                            new_time++;
                            break;
                        case Down_button:
                            new_time = (new_time == 0) ? 0 : new_time - 1;
                            break;
                        case Select:
                        case Right:
                            ChangeValveSettings(valve_num, new_time, cursor);
                        case Left:
                            exit = true;
                            break;

                    }
                    if(exit) break;
                    delay(MENU_DELAY);
                }
            }
        }
        else if(pressed == Left) return;
        delay(MENU_DELAY);
    }
}

void ValveMenu::SerialCheck(){
    int valve_index = 0;
    parse_data= Serial.readStringUntil('\n');
    if(parse_data == "Stop"){
        invalid = false;
    }
    else{
        int length = parse_data.length();
        char parseChar [length+1];
        strcpy(parseChar, parse_data.c_str());
        char* token;
        int time_on = 0;
        int time_off = 0;
        int state = 0;
        token = strtok(parseChar, " ");
        while(token!=NULL){
            time_on = token[1] - '0';
            valve_index = token[0] - '0';
            time_off = token[2] - '0';
            state = token[3] - '0';
            
            if(valve_index > 3 || valve_index < 0 || state < 0 ||
                state > 1 || time_off < 0 && time_on < 0)
                invalid = true;
            // Serial.println(valve_index);
            // Serial.println(token);
            token = strtok(NULL, " ");
        }
    }
}

void ValveMenu::HandleGru(){
    int valve_index = 0;
    if(parse_data == "Stop"){
        stop = true;
    }
    else{
        int length = parse_data.length();
        char parseChar [length+1];
        strcpy(parseChar, parse_data.c_str());
        char* token;
        token = strtok(parseChar, " ");
        while(token!=NULL){
            valve_index = token[0] - '0';
            //Serial.println(token[0]);
            for(int i = 0; i<3;i++)
            ChangeValveSettings(valve_index, token[i+1]  - '0', i);
            // Serial.println(valve_index);
            // Serial.println(token);
            token = strtok(NULL, " ");
        }
        Start();
    }
}

void ValveMenu::ChangeValveSettings(int valve_num, int value, int on_off_state){
    valve_settings[valve_num][on_off_state] = value;
}

ButtonPressed ValveMenu::UpdateMenuCursor(int *cursor, int num_of_options)
{
    ButtonPressed pressed = lcd.GetButtonPressed();
    switch (pressed)
    {
    case Up_button:
        *cursor = (!*cursor) ? num_of_options - 1: *cursor - 1;
        break;
    case Down_button:
        *cursor = (*cursor == num_of_options - 1) ? 0 : *cursor + 1;
        break;
    }
    return pressed;
}

void ValveMenu::Start(){
        char on_off_str[2][4] = {"Off", "On"};
        int valve_cursor = 0;
        int num_of_options = 3;
        char first_line[17];
        char second_line[17];
        ButtonPressed pressed = NotPressed;
        long unsigned int start[4];
        for(int i = 0; i < 4; i++){
            if(valve_settings[i][2] == 0){
                valves[i].TurnRelayOff();
            }
            else{
                valves[i].TurnRelayOn();
            }
            start[i] = millis() + 60000 * valve_settings[i][valve_settings[i][2]];
        }
        long unsigned int current = millis();
        while(true){
            if(stop){
                for(int i = 0; i < 4; i++)
                    ChangeValveSettings(i, 0, 0 );
                return;
            }
            else{

                int time_remaining_first = (start[valve_cursor] - current) / 60000 + 1;
                int time_remaining_second = (start[valve_cursor + 1] - current) / 60000 + 1;
                sprintf(first_line, "Valve%d %d min %s", valve_cursor + 1, time_remaining_first, on_off_str[valve_settings[valve_cursor][2]]); 
                sprintf(second_line, "Valve%d %d min %s", valve_cursor + 2, time_remaining_second, on_off_str[valve_settings[valve_cursor + 1][2]]); 
                lcd.PrintBothLine(first_line, second_line);
                pressed = UpdateMenuCursor(&valve_cursor, num_of_options);
                for(int i = 0; i < 4; i++){
                    if(!valve_settings[i][valve_settings[i][2]]) continue;
                    if(current > start[i]){
                        valves[i].SwitchRelayState();
                        valve_settings[i][2] = !valve_settings[i][2];
                        start[i] = millis() + 60000 * valve_settings[i][valve_settings[i][2]];
                    }
                }
                current = millis();
                delay(MENU_DELAY - 100);
            }
    }
}

void ValveMenu::StartTest(){
    valve_settings[0][0]= 1;
    valve_settings[0][1] = 2;
    valve_settings[0][2] = 0;

    valve_settings[1][0]= 1;
    valve_settings[1][1] = 2;
    valve_settings[1][2] = 1;

    valve_settings[2][0]= 2;
    valve_settings[2][1] = 1;
    valve_settings[2][2] = 0;

    valve_settings[3][0]= 2;
    valve_settings[3][1] = 2;
    valve_settings[3][2] = 1;

    Start();
}