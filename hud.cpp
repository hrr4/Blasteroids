#include "hud.h"

float HUD::thrustMeter[12] = {
    10, 1, 0, -10, 1, 0,
    -10, 0, 0, 10, 0, 0
};

HUD::HUD(FontEngine* _fe, bool _thrust, bool _score, bool _amount)  :
      thrust(_thrust), score(_score), amount(_amount), fe(_fe), pMeter(thrustMeter),
      j(0), maxHit(false) {}

HUD::~HUD() {
    pMeter = 0;
    delete pMeter;
}

void HUD::Simple(const int& _s, const int _size, const float _x, const float _y) {
glPushMatrix();
    glColor4f(1, 1, 1, .4);
    fe->Draw(itos(_s).c_str(), _size, "04b_11", _x, _y);
glPopMatrix();
}

void HUD::Thrust(const float _x, const float _y, const float _t, const float scale) {
glPushMatrix();
    if (_t > .1 && _t < 5) {
        pMeter[0] = pMeter[9] -= _t*.1;
    } else {
        pMeter[0] = pMeter[9] = 10;
    }
	glEnableClientState(GL_VERTEX_ARRAY);
    glTranslatef(_x, _y, 0);
    for (float i = 0; i <= _t; i+=0.01) {
        glColor4f(.2, .2, .2, i);
    }
    glScalef(scale, scale, 0);
	glVertexPointer(3, GL_FLOAT, 0, &thrustMeter);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
glPopMatrix();
}

void HUD::Announcement(std::string _m, const std::string _f, float _x, float _y, int& _isize) {
    /*box = fe->GetBBox(_m.c_str(), _f.c_str());
    GetBBoxMiddle(box);*/

glPushMatrix();
    if (_isize > 0) {
        if (j >= 1) {
            glColor4f(.8, .8, .8, j);
            j-=0.1;
        }
        fe->Draw(_m.c_str(), _isize, "04b_11", _x, _y);
        _isize-=2;
    }
glPopMatrix();
};

void HUD::GetBBoxMiddle(const FTBBox& _b) {
    FTGL_DOUBLE test = _b.Upper().Xf();
    FTGL_DOUBLE test2 = _b.Upper().Yf();
    aX = (_b.Upper().Xf()/2);
    //aY = (_b.Upper().Xf()/2);
    //aY = (y1+y2)/2);
}

void HUD::Status(const std::string& _m, const std::string _f, float _x, float _y, int _size, int _time) {
    static size_t lastpos = _m.find("\n");
    static size_t nextpos = _m.find("\n");
    static std::string statusText = _m.substr(0, nextpos);

    std::string statusText2;

    static int maxTime = SDL_GetTicks() + (_time * 1000);
glPushMatrix();
    if (SDL_GetTicks() < maxTime) {
        glColor4f(1, 1, 1, 1);
        fe->Draw(statusText.c_str(), _size, _f.c_str(), _x, _y);
    } else if (_m.find("\n", lastpos) != _m.npos) {
        //nextpos += 1;
        lastpos += 1;
        //statusText2 = _m.substr(statusText.size()+1, _m.find_first_of("\n"));
        /*pos = statusText.begin();
        subSize += statusText.length()+1;*/
        //statusText2 = _m.substr(
        //nextpos = _m.find_first_of("\n", statusText2);
        nextpos = _m.find("\n", lastpos);
        statusText = _m.substr(lastpos, nextpos);
        lastpos = nextpos;
        maxTime = SDL_GetTicks() + (_time * 1000);
    } else {
        maxTime = SDL_GetTicks() + (_time * 1000);
    };
glPopMatrix();
};