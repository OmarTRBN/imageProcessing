#include <stdint.h>
#include <cstdio>

typedef enum OmarImageType
{
    PNG, BMP, JPG, TGA
} OmarImageType;

struct OmarImage
{
    uint8_t* data = NULL; // A pointer to the image data
    size_t size = 0; // The size of the image data
    
    int w; // Width
    int h; // Height
    int channels; // 3 for RGB, 4 for RGBA

    OmarImage(const char* filename);
    OmarImage(int w, int h, int ch); // For specified w, h, channels
    OmarImage(const OmarImage& img); // Copy constructor
    ~OmarImage(); // Destructor to free allocated resources

    bool read(const char* filename);
    bool write(const char* filename);

    OmarImageType getFileType(const char* filename);

    OmarImage& grayScaleLum();
    OmarImage& grayScaleAvg();

    OmarImage& colorMask(float, float, float);
};