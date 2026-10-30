#include <iostream>
#include <cstdint>
#include <bitset>
#include "TelemetryBlackBox.h"
#include "Memory.h"


using namespace std;

int main() {
    TelemetryBlackBox box = TelemetryBlackBox();
    for (int i = 0; i < 10; i++){
    box.getLastDataframe();
    box.onBaroReading (false, 120);
    box.onRocketStateChange(ARM);
    box.recordCurrentState();
    box.getLastDataframe();
    box.onBaroReading (true, 700);
    box.recordCurrentState();
    box.getLastDataframe();
    box.onBaroReading (false, 2137);
    box.onParachuteDeployed();
    box.recordCurrentState();
    box.getLastDataframe();
    int memory;
        memory.show();
    }



    return 0;
}
