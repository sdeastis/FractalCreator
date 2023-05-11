#pragma once

namespace deastisconsulting
{
	class Mandelbrot
	{
	public:
		static const int MAX_ITERATIONS = 3000;

	public:
		Mandelbrot();
		virtual ~Mandelbrot();

		static int getIterations(double x, double y);
	};
}


