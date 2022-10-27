#pragma once
namespace Xperrty {

	class Color
	{
	public:
		Color();
		Color(float r, float g, float b, float a);
		Color(char cR, char cG, char cB, char cA);

		const float* getComponents() const;
		const char* getComponentsChar() const;
	private:
		float rgba[4];
		char crgba[4];
	};

}
