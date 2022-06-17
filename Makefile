PYLIB=$(shell python3-config   --ldflags)
PYINC=$(shell python3-config --cflags )

build:
	g++ -fPIC  -std=c++11 -Wno-attributes  $(PYINC) -g -O0 -I.  -o a.out call.cpp -L.  $(PYLIB)
