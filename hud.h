#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include <SDL_opengl.h>
#include "fontengine.h"
#include <memory>
#include "convert.h"

// CLASS HUD \\
// Init: Choose what to draw...some sort of component system? \\
// Look & Feel: Minimalistic, KISS and out of the way.
// Comprised of:
//      Thrust Meter - Rectangular box with amount of thrust filled
//          ^^^^^ - Above player or in it's own seperate area?
//      Score - Just a number incrementing?
//      Amount - Amount of enemies... left?
class HUD {
public:
    //HUD(std::shared_ptr<FontEngine> _fe, bool _thrust, bool _score, bool _amount);
    HUD(FontEngine* _fe, bool _thrust, bool _score, bool _amount);
    ~HUD();
public:
    void Thrust(int& _t);
    void Score(int& _s);
    void Amount(int& _a);
private:
    //std::shared_ptr<FontEngine> fe;
    FontEngine* fe;
    bool thrust, score, amount;
};

#endif