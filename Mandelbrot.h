#pragma once

namespace deastisconsulting
{
	class Mandelbrot
	{
	public:
		static const int MAX_ITERATIONS = 1000;

	public:
		Mandelbrot();
		virtual ~Mandelbrot();

		static int getIterations(double x, double y);
	};
}


