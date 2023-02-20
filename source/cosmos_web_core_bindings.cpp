#include "support/convertlib.h"
#include "math/vector.h"
#include <emscripten/bind.h>
#include <array>

using namespace emscripten;
using namespace Cosmos::Convert;

geoidpos ecitogeod(locstruc loc)
{
    pos_eci(loc);
    return loc.pos.geod;
}

EMSCRIPTEN_BINDINGS(my_module)
{
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
        .field("y", &cvector::y)
        .field("z", &cvector::z);
    function("ecitogeod", &ecitogeod);
    value_object<locstruc>("locstruc")
        .field("utc", &locstruc::utc)
        .field("pos", &locstruc::pos)
        .field("att", &locstruc::att);
    value_object<posstruc>("posstruc")
        .field("utc", &posstruc::utc)
        .field("icrf", &posstruc::icrf)
        .field("eci", &posstruc::eci)
        .field("sci", &posstruc::sci)
        .field("geoc", &posstruc::geoc)
        .field("selc", &posstruc::selc)
        .field("geod", &posstruc::geod)
        .field("selg", &posstruc::selg)
        .field("geos", &posstruc::geos)
        .field("extra", &posstruc::extra)
        .field("earthsep", &posstruc::earthsep)
        .field("moonsep", &posstruc::moonsep)
        .field("sunsize", &posstruc::sunsize)
        .field("sunradiance", &posstruc::sunradiance)
        .field("bearth", &posstruc::bearth)
        .field("orbit", &posstruc::orbit);
    value_object<cartpos>("cartpos")
        .field("cartpos", &cartpos::utc)
        .field("s", &cartpos::s)
        .field("v", &cartpos::v)
        .field("a", &cartpos::a)
        .field("pass", &cartpos::pass);
    value_object<rvector>("rvector")
        .field("col", &rvector::col);
    value_array<std::array<double, 3> >("array_double_3")
        .element(emscripten::index<0>())
        .element(emscripten::index<1>())
        .element(emscripten::index<2>());
}