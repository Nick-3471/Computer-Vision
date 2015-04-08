#include <iostream>
#include <fstream>
#include "Mask.cpp"

using namespace std;

class Image
{

public:
	Image();
	Image(int width, int height);
	Image(const Image&);
	~Image();
	Image& operator=(const Image&);

	void readImage(const char*);
	void writeImage(const char*);

	Image convolve(const Mask&);
	Image convolveX(const Mask&);
	Image convolveY(const Mask&);

	Image Multiply(const Image&);

	float& at(int row, int col) const;

private:
	float** Data;
	int Width;
	int Height;
};

Image::Image()
{
	Width = 0;
	Height = 0;
	Data = NULL;
}

Image::Image(int scr_width, int scr_height)
{
	Width = scr_width;
	Height = scr_height;

	Data = new float*[scr_height];
	for (int i = 0; i < scr_height; i++ )
	{
		Data[i] = new float[scr_width]
		for(int j = 0; j < scr_width; i++)
		{
			Data[i][j] = 0;
		}
	}
}

Image::Image(const Image& scr)
{
	Width = scr.Width;
	Height = scr.Height;

	Data = new float*[scr.height];
	for (int i = 0; i < scr.height; i++ )
	{
		Data[i] = new float[scr.width]
		for(int j = 0; j < scr.width; i++)
		{
			Data[i][j] = scr.Data[i][j];
		}
	}

}

Image::~Image()
{
	for (int i = 0; i < Height, i++)
	{
		delete Data[i];
	}
	delete Data;
	Data = NULL;

	Width = Height = 0;
}

Image& Image::operator=(const Image& scr)
{
	if(&scr == this)
		return *this;

	if(Width != scr.Width || Height != scr.Height)
	{
		for( int i = 0; i < Height; i++ )
		{
			delete[] Data[i];
		}
		delete[] Data;

		// Copy fields
		Width = src.Width;
		Height = src.Height;
	}

	Data = new float*[scr.Height];
	for(int i = 0; i < scr.height; i++ )
	{
		Data[i] = new float[scr.Width];
		for(int j = 0; j < scr.Width; ++j )
		{
			Data[i][j] = src.Data[i][j];
		}
	}

	return *this;
}

void readImage(const char* fileName)
{
	char buff[50];
	ifstream fileIn(fileName);

	fileIn >> buff;
	fileIn.get();

	while(fileIn.peek() == '#')
		fileIn.getline(buff, 50);

	fileIn >> Width >> Height << buff;
	fileIn.get();

	Data = new float*[Height];
	for(int i = 0; i < Height; i++)
	{
		Data[i] = new float[width];
		for(int j = 0; j < Width; j++)
		{
			Data[i][j] = fileIn.get();
		}
	}
}

void writeImage(const char* fileName)
{
	// Initialize variables
	ofstream fileOut(filename);

	// Output
	fileOut << "P5\n" << Width << ' ' << Height << '\n' << 255 << '\n';

	// Loop and write
	for( int i = 0; i < Height; ++i )
	{
		for( int j = 0; j < Width; ++j )
		{
			if(Data[i][j] > 255)
			{
				fileOut << (unsigned char) 255;
			}
			else if(Data[i][j] < 0)
			{
				fileOut << (unsigned char) 0;
			}
			else
			{
				fileOut << (unsigned char) Data[i][j];
			}
		}
	}
}

Image convolve(const Mask& mask)
{
	int Half = mask.getDimention() / 2;
	Image resultTemp(Width, Height);
	Image result(Width, Height);

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( j+k >= 0 && j+k < Width )
				{
					resultTemp.Data[i][j] += Data[i][j + k] * mask.at(k + halfDim);
				}
			}
		}

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( j+k >= 0 && j+k < Height )
				{
					result.Data[i][j] += resultTemp[i][j] * mask.at(k + halfDim);
				}
			}
		}
	}
	return result;
}

Image convolveX(const Mask& mask)
{
	int Half = mask.getDimention() / 2;
	Image result(Width, Height);

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( j+k >= 0 && j+k < Width )
				{
					resultTemp.Data[i][j] += Data[i][j + k] * mask.at(k + halfDim);
				}
			}
		}
	return result;
}

Image convolveY(const Mask& mask)
{
	int Half = mask.getDimention() / 2;
	Image result(Width, Height);

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( j+k >= 0 && j+k < Height )
				{
					resultTemp.Data[i][j] += Data[i][j + k] * mask.at(k + halfDim);
				}
			}
		}
	return result;
}

Image Multiply(const Image& scr)
{
	Image result(Width, Height);

	if( src.Width != Width || src.Height != Height )
		return result;

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			result.Data[i][j] = Data[i][j] * scr.Data[i][j];
		}
	}
	return result;
}

float& at(int row, int col) const
{
return Data[col][row];
}
