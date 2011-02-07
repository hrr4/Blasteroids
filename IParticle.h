#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "Particle.h"
#include <map>

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
    typedef ParticleType particleType;
public:
    IParticle();
    ~IParticle();
    void Logic();

    // Drawing Functions
    void DrawExplosion(formationType _formation, float _intensity, float _fade, float _x, float _y, particleType _type=particleType::Create);

private:
    static int totalID;
    std::map<int, Particle*> particleMap;
    std::map<int, Particle*>::iterator pIt;
};

#endif