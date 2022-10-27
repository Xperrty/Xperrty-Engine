#pragma once
#include <vector>
#include "Xperrty/Core.h"
template<typename T>
class Array : public std::vector<T> {
public:
	bool remove(const T& val, bool continueAfterFirst = true)
	{
		int removedItems = 0;
		for (int i = 0; i < size(); i++)
		{
			T& el = (*this)[i];
			if (el == val) {
				erase(begin() + i);
				i--;
				removedItems++;
				if (!continueAfterFirst) break;
			}
		}
		return removedItems;
	}

	inline bool contains(T item) {
		return std::find(begin(), end(), item)!=end();
	}
};
