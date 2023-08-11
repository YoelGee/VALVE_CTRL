#ifndef VALVE_MENU_H_
#define VAVLE_MENU_H_

#include "lcd_screen.h"
#include "relay.h"

#define MENU_DELAY 200
#define VALVE_PIN_START 50

class ValveMenu{
private:
    bool stop = false;
    LCDScreen lcd;
    Relay valves[4];
    int valve_settings[4][3];//first element is valve # second element is setting. 0 - on time, 1 - off time, 2 - state
    void SelectValve();
    void ChangeValveSettingsMenu(int valve_num);
    void Start();
    void HandleGru();
    ButtonPressed UpdateMenuCursor(int *cursor, int num_of_options);
public:
    void MainMenu();
    ValveMenu();
    void ChangeValveSettings(int valve_num, int value, int on_off_state);
    void StartTest();
};

#endif //VALVE_MENU_H_