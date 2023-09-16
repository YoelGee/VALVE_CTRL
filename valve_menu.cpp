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
            invalid = false;
            Serial.print("Inside MAIN MENU");
            SerialCheck();
            if(invalid == false)
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
    parse_data.trim();
    Serial.println(parse_data);
    if(parse_data == "stop"){
        Serial.println("In serialcheck stop");
        invalid = false;
    }
    else{
        int length = parse_data.length();
        char parseChar [length+1];
        strcpy(parseChar, parse_data.c_str());
        char* token;
        int token_counter = 0;
        int time_on = 0;
        int time_off = 0;
        int state = 0;
        token = strtok(parseChar, " ,");
        while(token!=NULL){
            switch (token_counter)
            {
            case 0 :
                valve_index = atoi(token);
                break;
            case 1:
                time_off = atoi(token);
                break;
            case 2:
                time_on = atoi(token);
                break;
            case 3:
                state = atoi(token);
                break;
            default:
                break;
            }
            token_counter++;
            if(token_counter > 3){
                token_counter = 0;
                if(valve_index > 3 || valve_index < 0 || state < 0 ||
                    state > 1 || time_off < 0 || time_off > 20 || time_on < 0 || time_on > 20)
                    invalid = true;
            }
            //Serial.println(valve_index);
            Serial.println(token);
            token = strtok(NULL, " ,");
        }
        Serial.println(invalid);
    }
}

void ValveMenu::HandleGru(){
    int valve_index = 0;
    int token_counter = 0;
    int valve_counter = 4;
    int time_off = 0;
    int time_on = 0;
    int state = 0;
    if(parse_data == "stop"){
        Serial.println("Stop command received");
        stop = true;
    }
    else{
        int length = parse_data.length();
        char parseChar [length+1];
        strcpy(parseChar, parse_data.c_str());
        char* token;
        Serial.println(parse_data);
        token = strtok(parseChar, " ,");
        while(token!=NULL){

            // Serial.println(token);
            switch (token_counter)
            {
            case 0:
                valve_index = atoi(token);
                 break;
            case 1:
                time_off = atoi(token);
                 break;
            case 2:
                time_on = atoi(token);
                 break;
            case 3:
                state = atoi(token);
                 break;
            default:
                 continue;
            }
            // Serial.println(valve_index);
            // Serial.println(time_off);
            // Serial.println(time_on);
            token_counter++;

            if(token_counter > 3)
            {
                ChangeValveSettings(valve_index, time_off, 0);
                ChangeValveSettings(valve_index, time_on, 1);
                ChangeValveSettings(valve_index, state, 2);
                valve_counter++;
                token_counter = 0;
            }

            token = strtok(NULL, " ,");
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
        int time_remaining_first;
        int time_remaining_second;
        char first_line[17];
        char second_line[17];
        ButtonPressed pressed = NotPressed;
        long unsigned int start[4];
        int valve_time_remaining[4][4] = {{0,valve_settings[0][0],valve_settings[0][1],valve_settings[0][2]}, 
                                          {1,valve_settings[1][0],valve_settings[1][1],valve_settings[0][2]},
                                          {2,valve_settings[2][0],valve_settings[2][1],valve_settings[0][2]},
                                          {3,valve_settings[3][0],valve_settings[3][1],valve_settings[0][2]}};
        for(int i = 0; i < 4; i++){
            if(valve_settings[i][2] == 0){
                valves[i].TurnRelayOff();
            }
            else{
                valves[i].TurnRelayOn();
            }
            if(valve_settings[i][valve_settings[i][2]] > 0)
                start[i] = millis() + 60000 * valve_settings[i][valve_settings[i][2]];
            else 
                start[i] = 0;
            //Serial.println(valve_settings[i][valve_settings[i][2]]);
            Serial.println(start[i]);
        }
        long unsigned int current = millis();
        long unsigned int start_gru = millis();
        while(true){
            if(Serial.available()){
                SerialCheck();
                if(!invalid){
                    HandleGru();
                }
            }
            if(stop){
                for(int i = 0; i < 4; i++)
                    ChangeValveSettings(i, 0, 0 );
                return;
            }
            else{
                for(int i = 0; i < 4; i++){
                    if(!valve_settings[i][2]){
                        valve_time_remaining[i][1] = (start[i] == 0) ? 0 : (start[i] - current) / 60000 + 1;
                        valve_time_remaining[i][2] = valve_settings[i][1];
                    }
                    else{
                        valve_time_remaining[i][1] = valve_settings[i][0];
                        valve_time_remaining[i][2] = (start[i] == 0) ? 0 : (start[i] - current) / 60000 + 1;
                    }
                    valve_time_remaining[i][3] = valve_settings[i][2];
                }
                if(current - start_gru > 1000){
                    char buff[30];
                    sprintf(buff, "%d,%d,%d,%d %d,%d,%d,%d %d,%d,%d,%d %d,%d,%d,%d", 
                                0, valve_time_remaining[0][1], valve_time_remaining[0][2], valve_time_remaining[0][3],
                                1, valve_time_remaining[1][1], valve_time_remaining[1][2], valve_time_remaining[1][3],
                                2, valve_time_remaining[2][1], valve_time_remaining[2][2], valve_time_remaining[2][3],
                                3, valve_time_remaining[3][1], valve_time_remaining[3][2], valve_time_remaining[3][3]);
                    Serial.println(buff);
                    start_gru = current;
                }
                time_remaining_first = valve_time_remaining[valve_cursor][valve_settings[valve_cursor][3]];
                time_remaining_second = valve_time_remaining[valve_cursor + 1][valve_settings[valve_cursor + 1][3]];
                // if(start[valve_cursor] != 0)
                //     time_remaining_first = (start[valve_cursor] - current) / 60000 + 1;
                // else
                //     time_remaining_first = 0;
                // if(start[valve_cursor+1] != 0)
                //     time_remaining_second = (start[valve_cursor + 1] - current) / 60000 + 1;
                // else
                //     time_remaining_second = 0;
                //Serial.println(start[valve_cursor] - current);
                //int time_remaining_first = 0;
                //int time_remaining_second = 0;
                sprintf(first_line, "V%d %dmin %s", valve_cursor + 1, time_remaining_first, on_off_str[valve_settings[valve_cursor][2]]); 
                sprintf(second_line, "V%d %dmin %s", valve_cursor + 2, time_remaining_second, on_off_str[valve_settings[valve_cursor + 1][2]]); 
                lcd.PrintBothLine(first_line, second_line);
                pressed = UpdateMenuCursor(&valve_cursor, num_of_options);
                for(int i = 0; i < 4; i++){
                    lcd.TurnOnDisplay();
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