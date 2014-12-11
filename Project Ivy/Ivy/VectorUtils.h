#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <string>
#include <sstream>
#include <vector>

class VectorUtils {
public:
	static std::string JoinVector(std::vector<std::string> v, const char* delim) {
		std::stringstream ss;
		for (int i = 0; i < v.size(); ++i)
		{
			if (i != 0)
				ss << delim;
			ss << v[i];
		}
		return ss.str();
	}
};


#endif