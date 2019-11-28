# Define the flags for compiling with C++
CXXFLAGS = -Wall -std=c++11 -O2

all: build_kernels

build_kernels: build_kernels.cc
	$(CXX) $(CXXFLAGS) build_kernels.cc -o $@        

clean:
	rm -f build_kernels
