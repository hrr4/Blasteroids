#ifndef HUD_H
#define HUD_H

#include "fontengine.h"

// CLASS HUD \\
// Init: Choose what to draw...some sort of component system? \\
// Comprised of:
//      Thrust Meter - Rectangular box with amount of thrust filled
//      Score
class HUD {
public:
    HUD(FontEngine& _fe, bool thrust, bool score, bool amount);
    ~HUD();
private:
    FontEngine fe;
};

#endif