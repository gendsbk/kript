all: main.cpp arifm.cpp
	g++ -c -fPIC arifm.cpp
	g++ -shared -o libarifm.so arifm.o
	LD_LIBRARY_PATH=./ g++ main.cpp -larifm -I. -Wl,-rpath,. -L. -o larifm
	
windows: main.cpp arifm.cpp
	g++ -c arifm.cpp
	g++ -shared -o arifm.dll arifm.o
	g++ main.cpp Barifm.dll -I. -Wl,-rpath,. -L. -o larifm.exe