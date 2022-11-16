#pragma once
namespace Xperrty {

	class TransformMatrix2D
	{
	public:
		//a=scaleX,b=skewX,c=skewY,d=scaleY,tx=translationX,ty=translationY
		TransformMatrix2D(float a, float b, float c, float d, float tx, float ty);
		TransformMatrix2D();
		inline void setA(float a) { variables[0] = a; }
		inline void setB(float b) { variables[1] = b; }
		inline void setC(float c) { variables[2] = c; }
		inline void setD(float d) { variables[3] = d; }
		inline void setTx(float tx) { variables[4] = tx; }
		inline void setTy(float ty) { variables[5] = ty; }

		inline float getA() { return variables[0]; }
		inline float getB() { return variables[1]; }
		inline float getC() { return variables[2]; }
		inline float getD() { return variables[3]; }
		inline float getTx() { return variables[4]; }
		inline float getTy() { return variables[5]; }
	private:
		float variables[6];
	};


}