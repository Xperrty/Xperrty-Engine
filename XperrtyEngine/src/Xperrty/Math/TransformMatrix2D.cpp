#include "xppch.h"
#include "TransformMatrix2D.h"

namespace Xperrty {
	TransformMatrix2D::TransformMatrix2D(float a, float b, float c, float d, float tx, float ty) :variables{ a, b, c, d, tx, ty }
	{
	}
	TransformMatrix2D::TransformMatrix2D() :variables{ 1, 0, 0, 1, 0, 0 }
	{
	}
}