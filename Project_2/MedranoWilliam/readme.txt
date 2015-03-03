Requirements for compiling:
	gcc c compiler
	g++ compiler
	make utility

Images Generated:
	Information is gotten through standard in or use "make face-one" and "make face-two" for quick input.
	All generated images to to the normalized folder
	A black dot appears on the pixel in which the user declared the nose should be at

Compiling:
	make

Process the first face:
	make face-one

Process the second face:
	make face-two

Improvements that can be done:
	Change Image::transformByInverse() function from using rounded down coordinate to something ie: bilinear, nearest neighbor etc...
