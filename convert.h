#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class BadConversion : public std::runtime_error {
public:
	BadConversion(std::string const& s)
		: std::runtime_error(s)
	{ }
};

inline std::string itos(int Val) {
	std::ostringstream o;
	if (! (o << Val))
		throw BadConversion("itos(int)");
	return o.str();
}
#endif