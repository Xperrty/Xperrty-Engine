#pragma once
#include <unordered_map>
#include "Xperrty/Core.h"
template <typename T_Key, typename T_Value>
class Dictionary : public std::unordered_map<T_Key, T_Value>
{
public:
	inline void add(const T_Key& key, const T_Value& value) {
		(*this)[key]=value;
	}

	inline bool contains(const T_Key& key) {
		return find(key) != end();
	}
	bool tryGet(const T_Key& key, T_Value& outVar) {
		bool containsKey = contains(key);
		if (containsKey) outVar = (*this)[key];
		return containsKey;
	}
	
};

