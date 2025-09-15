// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
#include <OpenImageIO/imageio.h>
using namespace OIIO;

void
simple_write()
{
    const char* filename = "simple.tif";
    const int xres = 320, yres = 240, channels = 3;
    float pixels[xres * yres * channels] = { 0 };

    std::unique_ptr<ImageOutput> out = ImageOutput::create(filename);
    if (!out)
        return;  // error
    ImageSpec spec(xres, yres, channels, TypeDesc::FLOAT);
    out->open(filename, spec);
    out->write_image(TypeDesc::FLOAT, pixels);
    out->close();
}



void
simple_read()
{
    const char* filename = "tahoe.tif";

    auto inp = ImageInput::open(filename);
    if (!inp)
        return;
    const ImageSpec& spec = inp->spec();
    int xres              = spec.width;
    int yres              = spec.height;
    int nchannels         = spec.nchannels;
    auto pixels           = std::unique_ptr<float[]>(
        new float[xres * yres * nchannels]);
    inp->read_image(0, 0, 0, nchannels, TypeDesc::FLOAT, &pixels[0]);
    inp->close();
}