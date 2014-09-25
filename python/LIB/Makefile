all: 	
	swig -c++ -python arifm.i
	g++ -fPIC -c arifm.cpp
	g++ -fPIC -c arifm_wrap.cxx -I/usr/include/python2.7/
	g++ -shared arifm.o arifm_wrap.o -o _arifm.so
