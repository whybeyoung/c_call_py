build:
	g++ -Wall  -fPIC    wrapper.cpp fibonacci.cpp  -o pybind-test   `python3-config --cflags --ldflags --libs`
clean:
	rm -rf pybind-test

test:
	./pybind-test
