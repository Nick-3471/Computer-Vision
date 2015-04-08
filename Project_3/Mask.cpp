#include "Gauss.cpp"

class Mask
{
public:
	Mask(float, int);
	~Mask();

	int getDimention() const;
	const float& at(int) const;

private:
	int Dimention;
	float* Data;
};