#pragma once

#include <string>
#include <memory>
#include <math.h>
#include <utility>
#include <vector>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "Zoom.h"
#include "RGB.h"

namespace deastisconsulting {

	class FractalCreator {
	private:
		unique_ptr<int[]> m_histogram;
		unique_ptr<int[]> m_fractal;
		
		int m_width;
		int m_height;
		int m_total;

		Bitmap m_bitmap;
		ZoomList m_zoomList;

		vector<int> m_ranges;
		vector<RGB> m_colors;
		vector<int> m_rangeTotals;

		bool m_bGotFirstRange{ false };

	private:
		void calculateIteration();
		void calculateTotalIterations();
		void calulateRangeTotals();
		void drawFractal();
		void writeBitmap(std::string name);
		int getRange(int iterations) const;

	public:
		FractalCreator(int width, int height);
		virtual ~FractalCreator();
		void addZoom(const Zoom& zoom);
		void addRange(double rangeEnd, const RGB& rgb);
		void run(string name);
	};
}
