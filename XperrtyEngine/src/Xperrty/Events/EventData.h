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
}