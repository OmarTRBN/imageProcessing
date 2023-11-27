#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "OmarImage.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>

OmarImage::OmarImage(const char *filename)
{
    if (read(filename) == true)
    {
        printf("Successfully read %s\n", filename);
        size = w*h*channels;
    }
    else
    {
        printf("Failed to read %s\n", filename);
    }
}

OmarImage::OmarImage(int w, int h, int channels) : w(w), h(h), channels(channels)
{
    size = w*h*channels;
    data = new uint8_t[size];
}

OmarImage::OmarImage(const OmarImage &img) : OmarImage(img.w, img.h, img.channels)
{
    memcpy(data, img.data, size);
}

OmarImage::~OmarImage()
{
    stbi_image_free(data); // Cleans up data
    // Call when image is deconstructed
}

bool OmarImage::read(const char *filename)
{
    data = stbi_load(filename, &w, &h, &channels, 0);
    // If x is instead of zero we force x channels
    // Function will fail if data is NULL
    return data != NULL;
}

bool OmarImage::write(const char *filename)
{
    OmarImageType type = getFileType(filename);
    int success;
    switch (type)
    {
    case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w*channels);
        break;
    case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;
    case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;
    case JPG:
        success = stbi_write_jpg(filename, w, h, channels, data, 100);
        break;
    default: 
        break;
    }
    return success != 0;
}


OmarImageType OmarImage::getFileType(const char* filename)
{
    const char* ext = strrchr(filename, '.');
    if (ext != nullptr)
    {
        if (strcmp(ext,".jpg") == 0)
        {
            return JPG;
        }
        else if (strcmp(ext, ".png") == 0)
        {
            return PNG;
        }
        else if (strcmp(ext, ".bmp") == 0)
        {
            return BMP;
        }
        else if (strcmp(ext, ".tga") == 0)
        {
            return TGA;
        }
    }
    return PNG;
    // If there is issue in filename it will return PNG
}

OmarImage& OmarImage::grayScaleLum()
{
    if (channels != 3)
    {
        printf("The images channels aren't equal to 3.\n");
    }
    else
    {
        int gray;
        for (int i = 0; i < size; i+=channels)
        {
            gray = 0.2126 * data[i] + 0.752 * data[i+1] + 0.0722* data[i+2];
            memset(data + i, gray, 3);                        
        }
    }
    return *this;   
}

OmarImage& OmarImage::grayScaleAvg()
{
    if (channels != 3)
    {
        printf("The images channels aren't equal to 3.\n");
    }
    else
    {
        for (int i = 0; i < size; i+=channels)
        {
            int gray = (data[i] + data[i+1] + data[i+2]) / 3;
            memset(data + i, gray, 3);
        }
    }
    return *this;
}

OmarImage& OmarImage::colorMask(float r, float g, float b)
{
    if (channels != 3)
    {
        printf("The images channels aren't equal to 3.\n");
    }
    else if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
    {
        printf("Input values must be in the range [0, 1].\n");
    }
    else
    {
        for (int i = 0; i < size; i += channels)
        {
            data[i] *= r;
            data[i + 1] *= g;
            data[i + 2] *= b;
        }
    }
    return *this;
}
