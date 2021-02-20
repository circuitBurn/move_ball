#ifndef Sound_h_
#define Sound_h_

#include "Arduino.h"
#include "Configuration.h"
#include "DFRobotDFPlayerMini.h"

class Sound
{
public:
    Sound();
    void setup();
    void process(uint16_t *channels);
private:
    DFRobotDFPlayerMini myDFPlayer;
};

#endif //Sound_h_