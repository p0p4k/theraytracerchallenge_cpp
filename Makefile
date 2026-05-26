CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# ONLY actual implementation source files go here
SHARED_SRCS = utilities.cpp tuple.cpp canvas.cpp matrix.cpp sphere.cpp ray.cpp intersection.cpp light_source.cpp world.cpp camera.cpp shapes.cpp plane.cpp pattern.cpp

# Header files used to track dependencies
DEPS = material.h utilities.h tuple.h canvas.h matrix.h sphere.h ray.h intersection.h light_source.h color.h world.h camera.h shapes.h plane.h pattern.h

all: test projectile_bin matrices clock sphere_wall sphere_light_source world_render

latest: world_render_with_pattern

test: main.cpp tests.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) main.cpp tests.cpp $(SHARED_SRCS) -o ./bin/test

projectile_bin: ch_02_projectile_on_canvas.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_02_projectile_on_canvas.cpp $(SHARED_SRCS) -o ./bin/projectile_sim

matrices: ch_03_matricies.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_03_matricies.cpp $(SHARED_SRCS) -o ./bin/matrices

clock: ch_04_clock.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_04_clock.cpp $(SHARED_SRCS) -o ./bin/clock

sphere_wall: ch_05_sphere_cast.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_05_sphere_cast.cpp $(SHARED_SRCS) -o ./bin/sphere_wall

sphere_light_source: ch_06_sphere_light.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_06_sphere_light.cpp $(SHARED_SRCS) -o ./bin/sphere_with_light_source

# world_render: ch_07_world_render.cpp $(SHARED_SRCS) $(DEPS)
# 	$(CXX) $(CXXFLAGS) ch_07_world_render.cpp $(SHARED_SRCS) -o ./bin/world_render

world_render: ch_08_world_with_shadows.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_08_world_with_shadows.cpp $(SHARED_SRCS) -o ./bin/world_render

world_render_with_plane: ch_09_world_with_plane.cpp $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_09_world_with_plane.cpp $(SHARED_SRCS) -o ./bin/world_render_with_plane

world_render_with_pattern: ch_10_world_with_patterns.cpp  $(SHARED_SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) ch_10_world_with_patterns.cpp  $(SHARED_SRCS) -o ./bin/world_render_with_pattern
	
clean:
	rm -f ./bin/test ./bin/projectile_sim ./bin/matrices ./bin/clock ./bin/sphere_wall ./bin/sphere_with_light_source ./bin/world_render ./bin/world_render_with_plane

# Tell Make that these targets aren't actual files on disk
.PHONY: all latest clean
