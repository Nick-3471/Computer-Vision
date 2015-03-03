#include <cstdlib>
#include <iostream>
#include <utility>
#include "Image.hpp"
#include "Matrix.hpp"

Matrix generateTransformationMatrix(std::pair<float, float> *start,
				    std::pair<float, float> *dest);
void markPoint(Image &im, std::pair<float, float> coord);
bool promptForYN();

int main(int argc, char* argv[])
{
  char input_file[128], output_file[128];
  std::pair<float, float> start_coordinates[3], dest_coordinates[3];
  std::pair<float, float> nose;
  Image image, modified_image;
  Matrix transformation_matrix;

  for (;;)
  {
    // Read image
    std::cout << "image file: ";
    std::cin >> input_file;
    // Get destination coordinates
    std::cout << "left eye destination: ";
    std::cin >> dest_coordinates[0].first >> dest_coordinates[0].second;
    std::cout << "right eye destination: ";
    std::cin >> dest_coordinates[1].first >> dest_coordinates[1].second;
    std::cout << "mouth coordinates: ";
    std::cin >> dest_coordinates[2].first >> dest_coordinates[2].second;
    std::cout << "nose coordinates: ";
    std::cin >> nose.first >> nose.second;
    // Get start coordinates
    std::cout << "left eye start: ";
    std::cin >> start_coordinates[0].first >> start_coordinates[0].second;
    std::cout << "right eye start: ";
    std::cin >> start_coordinates[1].first >> start_coordinates[1].second;
    std::cout << "mouth start: ";
    std::cin >> start_coordinates[2].first >> start_coordinates[2].second;
    std::cout << std::endl;
    // Read in image
    std::cout << "Reading image " << input_file << " ...\n";
    image.read8BitPGM(input_file);
    // Get transformation matrix
    std::cout << "Generating transformation matrix...\n";
    transformation_matrix = generateTransformationMatrix(dest_coordinates,
							 start_coordinates);
    // Show transformation matrix
    transformation_matrix.print();
    // Apply inverse of transformation_matrix
    std::cout << "Applying transformation...\n";
    modified_image = image.transformByInverse(transformation_matrix);
    modified_image = modified_image.crop(0, 0, 40, 48);
    // Highlighting features nose
    markPoint(modified_image, nose);
    markPoint(modified_image, dest_coordinates[0]);
    markPoint(modified_image, dest_coordinates[1]);
    markPoint(modified_image, dest_coordinates[2]);
    // Write out image
    std::cout << "Writing image...\n";
    sprintf(output_file, "normalized/%s", input_file);
    modified_image.write8BitPGM(output_file);
    // See if should continue
    std::cout << "Process another image?<y/n> ";
    if (!promptForYN())
    {
      break;
    }
  }

  return 0;
}

Matrix generateTransformationMatrix(std::pair<float, float> *start,
				    std::pair<float, float> *dest)
{
  Matrix transformation;
  Matrix A, x, b;

  // Format transformation matrix
  transformation.resize(3, 3, 0.f);
  transformation.at(3, 3) = 1.f;

  // Generate A matrix, as in Ax=b
  A.resize(3, 3, 0.f);
  A.at(1, 1) = start[0].first; A.at(1, 2) = start[0].second; A.at(1, 3) = 1.f;
  A.at(2, 1) = start[1].first; A.at(2, 2) = start[1].second; A.at(2, 3) = 1.f;
  A.at(3, 1) = start[2].first; A.at(3, 2) = start[2].second; A.at(3, 3) = 1.f;

  // Generate b from x-coords
  b.resize(3, 1, 0.f);
  b.at(1, 1) = dest[0].first;
  b.at(2, 1) = dest[1].first;
  b.at(3, 1) = dest[2].first;
  // Solve
  x = Matrix::solveWithSVD(A, b);
  transformation.at(1, 1) = x.get(1, 1);
  transformation.at(1, 2) = x.get(2, 1);
  transformation.at(1, 3) = x.get(3, 1);

  // Generate b from y-coords
  b.at(1, 1) = dest[0].second;
  b.at(2, 1) = dest[1].second;
  b.at(3, 1) = dest[2].second;
  // Solve
  x = Matrix::solveWithSVD(A, b);
  transformation.at(2, 1) = x.get(1, 1);
  transformation.at(2, 2) = x.get(2, 1);
  transformation.at(2, 3) = x.get(3, 1);

  // Done 
  return transformation;
}

void markPoint(Image &im, std::pair<float, float> coord)
{
  im.at(coord.first, coord.second) = 0.f;
}

bool promptForYN()
{
  char input;
  for (input = '\0';
       input != 'y' && input != 'Y' &&
	 input != 'n' && input != 'N';
       std::cin >> input)
  {
  }
  return (input == 'y' || input == 'Y');
}
