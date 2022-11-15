#pragma once
#include <chrono>
#include <iostream>
#include "Xperrty/Utils/Log.h"
class Stopwatch
{
public:
	Stopwatch()
	{
		if (msArr.capacity() < 10000)msArr.reserve(10000);
		Reset();
	}

	void Reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	float Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
	}

	void printArr() {
		std::lock_guard<std::mutex> mtx(arrMtx);
		for (int i = 0; i < msArr.size(); i++)
		{
			XP_INFO("Time Spent in block {0}ms.", msArr[i]);

		}
		msArr.clear();
	}

	float ElapsedMillis()
	{
		return Elapsed() * 1000.0f;
	}
	~Stopwatch() {
		XP_INFO("Time Spent in block {0}ms.", ElapsedMillis());
		//std::cout << ElapsedMillis() << "ms." << std::endl;
		//std::lock_guard<std::mutex> mtx(arrMtx);
		//msArr.push_back(ElapsedMillis());
	}
	static Array<float> msArr;
	static std::mutex arrMtx;
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};

//Stopwatch::msArr.reserve()