#include <iostream>
#include <cstdint>
#include <bitset>
#include "TelemetryBlackBox.h"
#include "Memory.h"


using namespace std;

int main()
{
    TelemetryBlackBox box = TelemetryBlackBox();
    box.onBaroReading (false, 120);
    box.onRocketStateChange(ARM);
    box.recordCurrentState();
    box.getLastDataframe();
    box.onBaroReading (true, 700);
    box.recordCurrentState();
    box.getLastDataframe();




    return 0;
}
