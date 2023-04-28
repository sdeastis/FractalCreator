#pragma once

namespace deastisconsulting {
	
	struct RGB
	{

		double r, g, b;

		RGB(double r, double g, double b);
	};

	RGB operator-(const RGB& first, const RGB& second);
}



