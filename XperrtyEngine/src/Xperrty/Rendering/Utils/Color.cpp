#include "xppch.h"
#include "Color.h"

namespace Xperrty {
	Color::Color() :rgba{ 0.0f,0.0f,0.0f,1.0f }, crgba{ (char)0,(char)0,(char)0,(char)255 }
	{
	}
	Color::Color(float r, float g, float b, float a) :rgba{ r,g,b,a }, crgba{ (char)r * 255,(char)g * 255 ,(char)b * 255 ,(char)a * 255 }
	{
	}
	Color::Color(char cR, char cG, char cB, char cA) :rgba{ cR / 255.0f,cG / 255.0f,cB / 255.0f,cA / 255.0f }, crgba{ cR,cG,cB,cA }
	{
	}
	const float* Color::getComponents() const
	{
		return rgba;
	}
	const char* Color::getComponentsChar() const
	{
		return crgba;
	}
}