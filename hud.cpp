#include "hud.h"

//HUD::HUD(std::shared_ptr<FontEngine> _fe, bool _thrust, bool _score, bool _amount)  :
HUD::HUD(FontEngine* _fe, bool _thrust, bool _score, bool _amount)  :
      thrust(_thrust), score(_score), amount(_amount) {
          fe = _fe;
}

HUD::~HUD() {}

/*void HUD::Render() {
    if (thrust) {
        drawThrust();
    }
    if (score) {
        drawScore();
    }
    if(amount) {
        drawAmount();
    }
}*/

void HUD::Score(int& _s) {
    glColor4f(1, 1, 1, .4);
    fe->Draw(itos(_s).c_str(), 12, "04b_11", 0, 10);
}