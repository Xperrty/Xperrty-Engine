#pragma once
#include <unordered_map>
#include "Xperrty/Core.h"
//Quality of life implementation of std::unordered_map<>
template <typename T_Key, typename T_Value>
class Dictionary : public std::unordered_map<T_Key, T_Value>
{
public:
	/// <summary>
	/// Adds an itme in the Dictionary. If key already exists value is overwrittern.
	/// </summary>
	/// <param name="key">Key to add.</param>
	/// <param name="value">Value to add.</param>
	inline void add(const T_Key& key, const T_Value& value) {
		(*this)[key]=value;
	}
	/// <summary>
	/// Checks if key is present in the Dictionary.
	/// </summary>
	/// <param name="key">Key to search.</param>
	/// <returns>True if key exists.</returns>
	inline bool contains(const T_Key& key) {
		return find(key) != end();
	}
	/// <summary>
	/// Adds the value of the key in outVar if it exists.
	/// </summary>
	/// <param name="key">Key to get.</param>
	/// <param name="outVar">Contains value if key exists.</param>
	/// <returns>True if outVar was successfully assigned.</returns>
	bool tryGet(const T_Key& key, T_Value& outVar) {
		bool containsKey = contains(key);
		if (containsKey) outVar = (*this)[key];
		return containsKey;
	}
};

