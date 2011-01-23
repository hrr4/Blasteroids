#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include <SDL_opengl.h>
#include "fontengine.h"
#include <memory>
#include <string>
#include "convert.h"

/* CLASS HUD \\
 Init: Choose what to draw...some sort of component system? \\
 Look & Feel: Minimalistic, KISS and out of the way.
 Comprised of:
      Thrust Meter - Rectangular box with amount of thrust filled
          ^^^^^ - Above player or in it's own seperate area?
      Score - Just a number incrementing?
      Amount - Amount of enemies... left?
      Level Num / Messages - In the middle, sort of flash for a second or two. Have them fade in then out.
*/

class HUD {
public:
    //HUD(std::shared_ptr<FontEngine> _fe, bool _thrust, bool _score, bool _amount);
    HUD(FontEngine* _fe, bool _thrust, bool _score, bool _amount);
    ~HUD();
    void Thrust(float _x, float _y, float _t, float scale);
    void Score(int& _s);
    void Amount(int& _a);
    void Announcement(std::string _m, float _x, float _y, int _isize, int _fsize);

private:
    //std::shared_ptr<FontEngine> fe;
    FontEngine* fe;
    bool thrust, score, amount;
    static float thrustMeter[12];
};

#endif