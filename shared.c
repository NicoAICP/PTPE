#include "shared.h"
#include "menu.h"

int DeviceNum = 0;
int WifiAllowed = 0;
int Selected = 0;
int Connected = 0;
int SDLines = 25;
int currSel = 0;
int maxSel = 2;
int SkylanderCount = 0;

void reboot(){
    clearScreen();
    sleep_ms(100);
    watchdog_enable(1, 1);
    watchdog_reboot(0,0,1);
    while(1);
}