#pragma once
#include <vector>
#include "Xperrty/Core.h"
template<typename T>
class Array : public std::vector<T> {
public:
	/// <summary>
	/// Removes the item from the Array. 
	/// </summary>
	/// <param name="val">Value to remove.</param>
	/// <param name="continueAfterFirst">Should continue removing after the first element is found?</param>
	/// <returns>Number of removed elements.</returns>
	int remove(const T& val, bool continueAfterFirst = true)
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
	/// Removes the item from the Array starting from the back of the array.
	int removeFromBack(const T& val, bool continueAfterFirst = true)
	{
		int removedItems = 0;
		for (int i = size()-1; i>=0; i--)
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

	//Removes the element at index.
	void removeAt(int index) {
		if (index > size()) return;
		erase(begin() + index);
	}
	/// <summary>
	/// Checks if the item exists in the Array.
	/// </summary>
	/// <param name="item">Item to check.</param>
	/// <returns>True if item found.</returns>
	inline bool contains(const T& item) {
		return std::find(begin(), end(), item)!=end();
	}
};
