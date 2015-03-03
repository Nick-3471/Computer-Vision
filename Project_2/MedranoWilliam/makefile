all: face-normalizer

face-normalizer:
	gcc -c src/solve_system.c src/svbksb.c src/svdcmp.c
	g++ -c src/Image.cpp src/Matrix.cpp src/face_normalizer.cpp
	g++ solve_system.o svbksb.o svdcmp.o Image.o Matrix.o face_normalizer.o -oface-normalizer
face-one:
	./face-normalizer < face_one.txt
face-two:
	./face-normalizer < face_two.txt
