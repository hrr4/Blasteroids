#include "hud.h"

float HUD::thrustMeter[12] = {
    10, 1, 0, -10, 1, 0,
    -10, 0, 0, 10, 0, 0
};

//HUD::HUD(std::shared_ptr<FontEngine> _fe, bool _thrust, bool _score, bool _amount)  :
HUD::HUD(FontEngine* _fe, bool _thrust, bool _score, bool _amount)  :
      thrust(_thrust), score(_score), amount(_amount), fe(_fe) {}

HUD::~HUD() {}

void HUD::Score(int& _s) {
    glColor4f(1, 1, 1, .4);
    fe->Draw(itos(_s).c_str(), 12, "04b_11", 0, 10);
}

void HUD::Thrust(float _x, float _y, float _t, float scale) {
    float* test = thrustMeter;
    //if (_t != 0) {
    if (_t > 0) {
        test[0] = test[9] -= _t*.1;
    } else {
        test[0] = test[9] = 10;
    }
glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
    glTranslatef(_x, _y, 0);
    for (float i = 0; i <= _t; i+=0.01) {
        glColor4f(.1, .1, .1, i);
    }
    glScalef(scale, scale, 0);
	glVertexPointer(3, GL_FLOAT, 0, &thrustMeter);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
glPopMatrix();
}

void HUD::Announcement(std::string _m, float _x, float _y, int _isize, int _fsize) {
glPushMatrix();
    // Lets try to avoid a copy in the for loop
    for (float i = 0; i < 100; ++i) {
        //i *= .01;
        glColor4f(.8, .8, .8, i);
        // INFINITE LOOP NIGHT NIGHT
        for (int i = _isize; i < _fsize; ++i) {
            fe->Draw(_m.c_str(), i, "04b_11", _x, _y);
        }
    }
    /*for (int i = _isize; i < _fsize; ++i) {
        fe->Draw(_m.c_str(), i, "04b_11", _x, _y);
    }*/
glPopMatrix();
};