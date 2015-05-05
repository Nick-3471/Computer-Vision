#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define PRINT_CSV 0

// Function Declaration
vector<Point2f> readImage(const char[]);
vector<Point3f> readWorld(const char[]);

// Main Program
int main()
{
	// Initialize variables
	char load[128];
	float calibrateError;
	vector< vector<Point2f> > imgCoord;
	vector< vector<Point3f> > objCoord;
	Mat cameraMatrix, distCoeffs;
	Mat pointToMat(3, 1, CV_64FC1);
	vector<Mat> rvecs, tvecs;

	// Initialize both vector of vectors
	for( int i = 1; i <= 15; i++ )
	{
		// Read the pixel file
		sprintf( load, "data/pixel%02d.txt", i );
		imgCoord.push_back( readImage(load) );

		// Read the world file
		sprintf( load, "data/world%02d.txt", i );
		objCoord.push_back( readWorld(load) );
	}

	// Calibrate
	calibrateError = calibrateCamera( objCoord, imgCoord, Size(640, 480),
		cameraMatrix, distCoeffs, rvecs, tvecs );

	// Loop throught the images
	float multiSum = 0.0;
	for( int i = 0; i < 15; i++ )
	{
		// Project points
		vector<Point2f> output;
		projectPoints( objCoord[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, output );

		// Loop through the output
		float singleSum = 0.0;
		for( int j = 0; j < 96; j++ )
		{
			float err = sqrt( 
				pow(output[j].x - imgCoord[i][j].x, 2) + 
				pow(output[j].y - imgCoord[i][j].y, 2) );
			singleSum += err;

			#if PRINT_CSV == 1
			cout << i << ',' << err << endl;
			#endif
		}

		// Add to the multi-image error sum
		multiSum += singleSum / 96.0;

		#if PRINT_CSV == 0
		cout << "Image " << i << ": " << singleSum / 96.0 << endl;
		#endif
	}

	#if PRINT_CSV == 0
	cout << "For all images: " << multiSum / 15.0 << endl;
	#endif

	
	return 0;
}

// Function implementations
vector<Point2f> readImage(const char filename[])
{
	// Initialize variables
	Point2f temp(0, 0);
	vector<Point2f> result;

	// Open the file
	fstream fin(filename);

	// Loop
	for( int i = 0; i < 96; i++ )
	{
		// Read and push back the point
		fin >> temp.x >> temp.y;
		result.push_back(temp);
	}

	
	return result;
}

vector<Point3f> readWorld(const char filename[])
{
	// Initialize variables
	Point3f temp(0, 0, 0);
	vector<Point3f> result;

	// Open the file
	fstream fin(filename);

	// Loop
	for( int i = 0; i < 96; i++ )
	{
		// Read and push back the point
		fin >> temp.x >> temp.y;
		result.push_back(temp);
	}

	
	return result;
}
