#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "Particle.h"
#include "Utility.h"
#include <math.h>
#include <map>
#include "vector.h"

/* ####### PARTICLE ENGINE MANIFESTO #######
    *** GOALS ***
        - The engine should be initialized in Application top.
        - Outside should be able to call multiple particle functions easily
        - Once Engine is given instruction to draw formation of particles,
            it will put that type of particle, in the correct formation and
            will draw until fade out.
        - Keep everything VERY fast! THIS WILL BE INTENSIVE IM SURE OF IT!
        -!! For now, took out shapes, sizes. will just make a buttload of dots !!-

BTW: ITS OVER 9000!
*/

enum formationType {radialOut};

class IParticle {
public:
    IParticle();
    ~IParticle();
    void Logic();

    void createParticleSet(formationType _type, float _x, float _y, float _intensity, float _time);
    void updateParticleSet();
    //void updateParticleSet(int _id);
    //void drawParticleSet(int _id);
    void drawParticleSet();

private:
    Vectorf tempPosition;
    static int totalID;
    std::multimap<int, Particle*> particleMap;
    std::multimap<int, Particle*>::iterator pIt;
};

#endif
