#ifndef COMET_H
#define COMET_H

#include "Entity.h"
#include "collider.h"
#include "icollide.h"
#include "fps.h"
#include <vector>
#include <math.h>
#include <time.h>
#include "Utility.h"

class Comet : public Collider {
public:
	Comet(ICollide* c, float _x, float _y, float _w, float _h, int _n, float _vel, Vectorf _vec, int _r=1, int _g=1, int _b=1, int _a=1);
	virtual ~Comet();
	virtual void Draw();
	virtual void Logic();
	virtual void Handle_Events();
    virtual void Update(Subject*);
    void SetWrap(const bool isWrap);

private:
	void Randomize_Points(int w, int h, int n);
	void Render(int r, int g, int b, int a);
    float r, g, b, a;
	float n, centerx, centery;
	std::vector<float> vertVec;
    bool inBounds;
    static std::vector<int> testVec;
};
#endif