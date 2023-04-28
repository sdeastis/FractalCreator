// FractalCreator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include "FractalCreator.h"
#include "Zoom.h"

using namespace deastisconsulting;


FractalCreator::FractalCreator(int width, int height):
    m_width(width),
    m_height(height),
    m_bitmap(m_width, m_height),
    m_zoomList(m_width, m_height)
{
    m_histogram = std::unique_ptr<int[]>(new int[Mandelbrot::MAX_ITERATIONS]{ 0 });
    m_fractal = std::unique_ptr<int[]>(new int[m_width * m_height]{ 0 });
    m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

FractalCreator::~FractalCreator()
{
}

void FractalCreator::run(string name)
{
    calculateIteration();
    calculateTotalIterations();
    drawFractal();
    writeBitmap(name);
}

void FractalCreator::calculateIteration()
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            //double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT;
            //double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            std::pair<double, double> coords = m_zoomList.doZoom(x, y);

            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            m_fractal[y * m_width + x] = iterations;
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                m_histogram[iterations]++;
            }
        }
    }
}

void FractalCreator::drawFractal()
{
    RGB startColor(0, 0, 20);
    RGB endColor(255, 128, 74);
    RGB colorDiff = startColor - endColor;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iterations = m_fractal[y * m_width + x];

            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                double hue = 0.0;
                for (int i = 0; i <= iterations; i++)
                {
                    hue += ((double)m_histogram[i]) / m_total;
                }

                //green = (255 * hue);
                red = startColor.r + colorDiff.r * hue;
                green = startColor.g + colorDiff.g * hue;
                blue = startColor.b + colorDiff.b * hue;
            }

            m_bitmap.setPixel(x, y, red, green, blue);

        }
    }


}

void FractalCreator::addZoom(const Zoom& zoom)
{
    m_zoomList.add(zoom);
}

void FractalCreator::addRange(double rangeEnd, const RGB& rgb)
{
    m_ranges.push_back(rangeEnd*Mandelbrot::MAX_ITERATIONS);
    m_colors.push_back(rgb);
}

void FractalCreator::calculateTotalIterations()
{
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        m_total += m_histogram[i];
    }
}

void FractalCreator::writeBitmap(std::string name)
{
    m_bitmap.write(name);
}

int main()
{
    FractalCreator fractalCreator(800, 600);

    fractalCreator.addRange(0.3, RGB(255, 0, 0));
    fractalCreator.addRange(0.5, RGB(255, 255, 0));
    fractalCreator.addRange(10, RGB(255, 255, 255));

    fractalCreator.addZoom(Zoom(295, 202, 0.1));
    fractalCreator.addZoom(Zoom(312, 304, 0.1));
    fractalCreator.run("test.bmp");

    std::cout << "Finished." << std::endl;
    
    return 0;
}