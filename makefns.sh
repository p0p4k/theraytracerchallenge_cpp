cat <<'EOF' >tests.h
#ifndef TESTS_H
#define TESTS_H

#include "canvas.h"
#include "color.h"
#include "intersection.h"
#include "light_source.h"
#include "matrix.h"
#include "ray.h"
#include "sphere.h"
#include "tuple.h"
#include "utilities.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <sstream>
#include <cassert>

EOF

grep -E "^void test_" tests.cpp | sed 's/ *{/;/' >>tests.h
echo -e "\n#endif" >>tests.h

# 2. Rebuild run_tests.cpp to call every test found
echo -e "#include \"tests.h\"\n\nvoid run_tests() {" >run_tests.cpp
grep -E "^void test_" tests.cpp | awk '{print "    " $2}' | sed 's/()/();/' >>run_tests.cpp
echo -e "\n}" >>run_tests.cpp
