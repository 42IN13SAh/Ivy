#pragma once
#include <boost\any.hpp>
#include "BadCastException.h"
class Cast{
public:
	template<class T>
	static T cast(boost::any val) {
		try {
			return boost::any_cast<T>(val);
		}
		catch (std::exception& e) {
			throw BadCastException(typeid(T).name(), val.type().name());
		}
	}
};