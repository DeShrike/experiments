#include "image.hpp"

#include <istream>
#include <fstream>

Image::Image(int width, int height)
	: width(width), height(height)
{
	data = new Color[width * height];
}

Image::~Image()
{
	delete[] data;
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

Color* Image::getPixel(int x, int y)
{
	return data + (x + y * width);
}

void Image::saveImage(std::string filename, float exposure, float gamma) const
{
	u_char* imgData = new u_char[3 * width * height];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Color curColor = data[x + y * width];
			curColor.applyGammaCorrection(exposure, gamma);
			curColor.clamp();

			// imgData[4 * (x + y * width) + 3] = 255;
			imgData[3 * (x + y * width) + 2] = (u_char)(curColor.r * 255.0f);
			imgData[3 * (x + y * width) + 1] = (u_char)(curColor.g * 255.0f);
			imgData[3 * (x + y * width) + 0] = (u_char)(curColor.b * 255.0f);
		}
	}

	// QImage img(imgData, width, height, QImage::Format_RGB32);
	// img.save(QString(filename.c_str()));

	writeBitmap(filename, width, height, imgData);

	delete[] imgData;
}

void Image::writeBitmap(const std::string path, const int width, const int height, const u_char* imgData) const
{
    const int pad = (4 - (3 * width) % 4) % 4;
    const int filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for (int i = 0; i < 4; i++) 
    {
        header[ 2+i] = (char)((filesize>>(8 * i)) & 255);
        header[18+i] = (char)((width   >>(8 * i)) & 255);
        header[22+i] = (char)((height  >>(8 * i)) & 255);
    }

    char* img = new char[filesize];
    for (int i = 0; i < 54; i++) 
    { 
    	img[i] = header[i];
    }

    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            const int ii = 3 * (x + y * width);
            const int i = 54 + 3 * x + y * (3 * width + pad);
            img[i    ] = (char)(imgData[ii + 0]);
            img[i + 1] = (char)(imgData[ii + 1]);
            img[i + 2] = (char)(imgData[ii + 2]);
        }

        for (int p = 0; p < pad; p++) 
        {
        	img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
        }
    }

    std::fstream file(path, std::ios::out | std::ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}
