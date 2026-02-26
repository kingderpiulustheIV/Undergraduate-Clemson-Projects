// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 4
// 11/12/2025
//-------------------------------------------------------

// Fractal.C

// Implementation of JuliaSet warp and ApplyFractalWarpLUT

//-------------------------------------------------------
#include "Fractal.h"
#include "ImgProc.h"
#include <complex>
#include <cmath>
#include <vector>
#include <limits>
#include <iostream>

using namespace starter;
using namespace starter::img;

Point JuliaSet::operator()(const Point& P) const
{
    std::complex<double> Pc(P.x, P.y);
    std::complex<double> cc(c.x, c.y);

    // Exterior coloring with smooth escape-time; interior stays black
    const double R = 2.0;        // escape radius (standard for quadratic)
    const double R2 = R * R;     // squared for fast norm check
    for (int i = 0; i < nb_iterations; ++i) {
        std::complex<double> temp = Pc;
        
        // raise Pc to the power 'cycles'
        for (int k = 1; k < cycles; ++k) {
            temp = temp * Pc;
        }
        Pc = temp + cc;

        // Early escape: outside the filled set
        if (std::norm(Pc) > R2) {
            
            // Smooth escape-time coloring
            double mag = std::abs(Pc);
            double nu = (double)i + 1.0 - std::log(std::log(mag) / std::log(R)) / std::log((double)cycles);
            
            // Normalize to [0,1]
            double t = nu / (double)nb_iterations;
            if (t < 0.0) t = 0.0;
            if (t > 1.0) t = 1.0;
            
            // Smooth step interpolation
            Point escaped;
            escaped.x = t;  
            escaped.y = 1.0; 
            return escaped;
        }
    }

    // Did not escape within nb_iterations -> interior: keep black
    Point Pout;
    Pout.x = 0.0;  
    Pout.y = 0.0;  
    return Pout;
}

// Apply fractal warp LUT into ImgProc 'out'.
void img::ApplyFractalWarpLUT( const Point& center, const double range, const Warp& w, const ColorLUT& lut, ImgProc& out )
{
    if (!out.IsLoaded()) {
        std::cerr << "ApplyFractalWarpLUT: output image not allocated/loaded" << std::endl;
        return;
    }

    int nx = out.GetWidth();
    int ny = out.GetHeight();
    int nc = out.GetChannels();
    if (nc < 3) {
        std::cerr << "ApplyFractalWarpLUT: output image must have at least 3 channels" << std::endl;
        return;
    }

    // Iterate over rows and columns. We parallelize outer loop for threadsafety on different pixels.
    for (int j = 0; j < ny; ++j) {
#pragma omp parallel for
        for (int i = 0; i < nx; ++i) {
            
            // Supersampling 2x2 around pixel center
            const double offsets[2] = { -0.25, 0.25 };
            float accR = 0.0f, accG = 0.0f, accB = 0.0f;
            for (int oy = 0; oy < 2; ++oy) {
                for (int ox = 0; ox < 2; ++ox) {
                    // Map pixel (i,j) + offset to fractal space
                    double fx = ((double)i + 0.5 + offsets[ox]) / (double)nx;
                    double fy = ((double)j + 0.5 + offsets[oy]) / (double)ny;

                    // Map to fractal space
                    Point P;
                    P.x = 2.0 * fx - 1.0;
                    P.y = 2.0 * fy - 1.0;
                    P.x *= range;
                    P.y *= range;
                    P.x += center.x;
                    P.y += center.y;

                    Point PP = w(P);
                    // Exterior: PP.y > 0.5, with PP.x as normalized t in [0,1]
                    if (PP.y > 0.5) {
                        double t = PP.x;
                        std::vector<float> v(3, 0.0f);
                        lut(t, v);
                        float r = v[0]; if (r < 0.0f) r = 0.0f; if (r > 1.0f) r = 1.0f;
                        float g = v[1]; if (g < 0.0f) g = 0.0f; if (g > 1.0f) g = 1.0f;
                        float b = v[2]; if (b < 0.0f) b = 0.0f; if (b > 1.0f) b = 1.0f;
                        accR += r; accG += g; accB += b;
                    } else {
                        // Interior sample contributes black
                    }
                }
            }

            // Average the 4 samples
            out.SetPixel(i, j, 0, accR * 0.25f);
            out.SetPixel(i, j, 1, accG * 0.25f);
            out.SetPixel(i, j, 2, accB * 0.25f);

            // If the image has an alpha or extra channel, set to 1.0
            for (int c = 3; c < nc; ++c) {
                out.SetPixel(i, j, c, 1.0f);
            }
        }
    }
}