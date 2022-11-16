#pragma once
namespace Xperrty {
	//ToDo: Find a better way to implement this.
	class EventData {

	};


	class FloatEventData :public EventData {
	public:
		//Event data containing 1 float.
		FloatEventData(float val) :value(val) {}
		//Returns the value of this event.
		inline float getValue() { return value; }
		//Sets the value of this event.
		inline void setValue(float val) { value = val; }

	private:
		float value;
	};

	class DoubleFloatEventData :public EventData {
	public:
		//Event data containing 2 floats.
		DoubleFloatEventData(float val1, float val2) :value1(val1),value2(val2) {}
		//Returns the first float value.
		inline float getValue1() { return value1; }
		//Returns the second float value.
		inline float getValue2() { return value2; }
		//Sets both float values.
		inline void setValue(float val1, float val2) { value1 = val1; value2:val2; }

	private:
		float value1;
		float value2;
	};
}