CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# List of shared source files needed by both targets
SHARED_SRCS = tuple.cpp utilities.cpp canvas.cpp

all: test projectile_bin

test: main.cpp tests.cpp $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) main.cpp tests.cpp $(SHARED_SRCS) -o ./bin/test

projectile_bin: ch_02_projectile_on_canvas.cpp $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) ch_02_projectile_on_canvas.cpp $(SHARED_SRCS) -o ./bin/projectile_sim

clean:
	rm -f ./bin/test ./bin/projectile_sim
