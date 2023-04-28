#include "RGB.h"

using namespace deastisconsulting;

RGB::RGB(double r, double g, double b):
	r(r), g(g), b(b)
{

}

RGB deastisconsulting::operator-(const RGB& first, const RGB& second)
{
	return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
}
