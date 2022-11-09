#include "math/vector.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
    function("a_quaternion2euler", &a_quaternion2euler);
    value_object<avector>("avector")
        .field("h", &avector::h)
        .field("e", &avector::e)
        .field("b", &avector::b);
    value_object<quaternion>("quaternion")
        .field("d", &quaternion::d)
        .field("w", &quaternion::w);
    value_object<cvector>("cvector")
        .field("x", &cvector::x)
        .field("x", &cvector::y)
        .field("y", &cvector::z);
}
