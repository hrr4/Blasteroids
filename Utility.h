#ifndef UTILITY_H
#define UTILITY_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <time.h>

namespace Utility {
	extern double PI, DEGTORAD, RADTODEG;
	template <class T>
    T UGen_Random(T min, T max) {
        boost::mt19937 rng(time(0));
        boost::uniform_real<T> u(min, max);
        boost::variate_generator<boost::mt19937&, boost::uniform_real<T> > gen(rng, u);
        return gen();
    }
	template <class T>
	T ClosestVal(T Control, T x1, T x2) {
		T temp1, temp2;
		temp1 = Control-x1;
		temp2 = Control-x2;
		return (temp1 > temp2 ? temp1 : temp2);
	}
}

#endif
