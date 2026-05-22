CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# List of shared source files needed by both targets
SHARED_SRCS = tuple.cpp utilities.cpp canvas.cpp matrix.cpp sphere.cpp ray.cpp intersection.cpp

all: test projectile_bin matrices clock sphere_wall

latest: sphere_wall

test: main.cpp tests.cpp $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) main.cpp tests.cpp $(SHARED_SRCS) -o ./bin/test

projectile_bin: ch_02_projectile_on_canvas.cpp $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) ch_02_projectile_on_canvas.cpp $(SHARED_SRCS) -o ./bin/projectile_sim

matrices: ch_03_matricies.cpp $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) ch_03_matricies.cpp $(SHARED_SRCS) -o ./bin/matrices

clock: ch_04_clock.cpp $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) ch_04_clock.cpp $(SHARED_SRCS) -o ./bin/clock

sphere_wall: ch_05_sphere_cast.cpp  $(SHARED_SRCS)
	$(CXX) $(CXXFLAGS) ch_05_sphere_cast.cpp $(SHARED_SRCS) -o ./bin/sphere_wall

clean:
	rm -f ./bin/test ./bin/projectile_sim
