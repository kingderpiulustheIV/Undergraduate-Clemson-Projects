// Fractal.h
// Small fractal/wrap utilities for generating Julia sets
// Uses std::complex for the iteration

#ifndef STARTER_FRACTAL_H
#define STARTER_FRACTAL_H

#include <vector>
#include <functional>
// Need ImgProc definition for function signature
#include "ImgProc.h"

namespace starter {
namespace img {

// Simple 2D point used by warps
struct Point {
    double x;
    double y;
};

// Abstract warp (functor) that maps a point to another point
struct Warp {
    virtual Point operator()(const Point& P) const = 0;
    virtual ~Warp() {}
};

// Julia set warp
struct JuliaSet : public Warp {
    Point c;            // complex constant (c = c.x + i c.y)
    int nb_iterations;  // number of iterations
    int cycles;         // power/cycles (usually 2)

    JuliaSet() : c{0.0,0.0}, nb_iterations(100), cycles(2) {}

    // Implemented in the .C file
    virtual Point operator()(const Point& P) const override;
};

// Color lookup: given a rate in [0,inf) (escape/magnitude related) fill rgb vector (size 3)
using ColorLUT = std::function<void(double, std::vector<float>&)>;

// Apply a fractal warp and color lookup table into an output image
// The implementation uses the public ImgProc interface (GetWidth/GetHeight/SetPixel).
// See implementation in base/Fractal.C
void ApplyFractalWarpLUT(const Point& center, const double range, const Warp& w, const ColorLUT& lut, ::starter::ImgProc& out);

} // namespace img
} // namespace starter

#endif