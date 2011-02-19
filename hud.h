#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include <SDL_opengl.h>
#include "fontengine.h"
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
      Status Messages - Small text near player or comets on death. Allows game to explain basic things to 
         player and display how much comet is worth.
*/

class HUD {
public:
    HUD(FontEngine* _fe, bool _thrust, bool _score, bool _amount);
    ~HUD();
    void Thrust(const float _x, const float _y, const float _t, const float scale);
    void Simple(const int& _s, const int _size, const float _x, const float _y);
    void Amount(int& _a);
    void Announcement(const std::string _m, const std::string _f, float _x, float _y, int& _isize);
    void Status(const std::string& _m, const std::string _f, float _x, float _y, int _size, int _time);
    void Lives(const float _x, const float _y, const int _num);

private:
    void GetBBoxMiddle(const FTBBox& _x);

    FontEngine* fe;
    FTBBox box;
    bool thrust, score, amount, maxHit;
    static float thrustMeter[12], livesArray[9];
    float* pMeter, *pLives;
    float aX, aY, j;
};

#endif