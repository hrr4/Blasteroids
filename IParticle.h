#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "Particle.h"

/* ####### PARTICLE ENGINE MANIFESTO #######
    *** GOALS ***
        - The engine should be initialized in Application top.
        - Outside should be able to call multiple particle functions easily
        - Once Engine is given instruction to draw formation of particles,
            it will put that type of particle, in the correct formation and
            will draw until fade out.
        - Keep everything VERY fast! THIS WILL BE INTENSIVE IM SURE OF IT!

BTW: ITS OVER 9000!
*/
class IParticle {
public:
    typedef Particle::drawType particleType;
    enum formationType {radialOut};
public:
    IParticle();
    ~IParticle();

    // Drawing Functions
    void DrawExplosion(formationType _formation, float _intensity, float _fade, float _x, float _y, particleType _type=particleType::pPoint);
};

#endif