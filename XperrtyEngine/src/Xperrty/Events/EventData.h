#pragma once
namespace Xperrty {

	class EventData {

	};


	class FloatEventData :public EventData {
	public:
		FloatEventData(float val) :value(val) {}
		inline float getValue() { return value; }
		inline void setValue(float val) { value = val; }

	private:
		float value;
	};

	class DoubleFloatEventData :public EventData {
	public:
		DoubleFloatEventData(float val1, float val2) :value1(val1),value2(val2) {}
		inline float getValue1() { return value1; }
		inline float getValue2() { return value2; }
		inline void setValue(float val1, float val2) { value1 = val1; value2:val2; }

	private:
		float value1;
		float value2;
	};
}