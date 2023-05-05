#include "support/convertlib.h"
#include "support/datalib.h"
#include "support/jsondef.h"
#include "math/vector.h"
#include "math/matrix.h"
#include <emscripten/bind.h>
#include <array>
#include <string>
#include "physics/physicslib.h"

using namespace emscripten;
using namespace Cosmos::Convert;
using namespace Cosmos::Physics;

// locstruc loc // cartpos eci, qatt icrf
// return LVLH attstruc qatt ~ TODO this needs to be for att_icrf ~ att_icrf2lvlh
qatt loc2lvlh(locstruc loc)
{
    int32_t iretn = pos_eci(loc);
    if (iretn < 0)
    {
        loc.att.lvlh.utc = iretn;
    }
    return loc.att.lvlh;
}

// return ECI posstruc cartpos TODO remove this
cartpos loc2eci(locstruc loc)
{
    int32_t iretn = pos_eci(loc);
    if (iretn < 0)
    {
        loc.pos.eci.utc = iretn;
    }
    return loc.pos.eci;
}

// return GCS GEOS  posstruc spherpos ~ TODO update to take only eci, add to locstruc here...
spherpos loc2geos(locstruc loc)
{
    int32_t iretn = pos_eci(loc);
    if (iretn < 0)
    {
        loc.pos.geos.utc = iretn;
    }
    return loc.pos.geos;
}

// return posstruc geoidpos geodetic (lat/lon/alt) from eci input
geoidpos eci2geod(cartpos eci)
{
    locstruc loc;
    loc.pos.eci.utc = eci.utc;
    loc.pos.eci.v = eci.v;
    loc.pos.eci.a = eci.a;
    loc.pos.eci.s = eci.s;
    loc.pos.eci.pass = eci.pass;
    int32_t iretn = pos_eci(loc);
    if (iretn < 0)
    {
        loc.pos.geod.utc = iretn;
    }
    return loc.pos.geod;
}

// return posstruc geoidpos geodetic (lat/lon/alt) TODO remove this
geoidpos ecitogeod(locstruc loc)
{
    int32_t iretn = pos_eci(loc);
    if (iretn < 0)
    {
        loc.pos.geod.utc = iretn;
    }
    return loc.pos.geod;
}

string check_get_cos(bool create_flag)
{
    string getr = get_cosmosresources(create_flag);
    string fname;
    int32_t getri = get_cosmosresources(fname);
    string getrStr = fname;
    return getrStr;
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
    function("check_get_cos", &check_get_cos);
    function("loc2lvlh", &loc2lvlh);
    function("loc2eci", &loc2eci);
    function("loc2geos", &loc2geos);
    function("eci2geod", &eci2geod);
    function("ecitogeod", &ecitogeod);
    function("groundstation", &groundstation);
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
        .field("utc", &cartpos::utc)
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
    value_object<geoidpos>("geoidpos")
        .field("utc", &geoidpos::utc)
        .field("s", &geoidpos::s)
        .field("v", &geoidpos::v)
        .field("a", &geoidpos::a)
        .field("pass", &geoidpos::pass);
    value_object<gvector>("gvector")
        .field("lat", &gvector::lat)
        .field("lon", &gvector::lon)
        .field("h", &gvector::h);
    value_object<attstruc>("attstruc")
        .field("utc", &attstruc::utc)
        .field("topo", &attstruc::topo)
        .field("lvlh", &attstruc::lvlh)
        .field("geoc", &attstruc::geoc)
        .field("selc", &attstruc::selc)
        .field("icrf", &attstruc::icrf)
        .field("extra", &attstruc::extra);
    value_object<spherpos>("spherpos")
        .field("utc", &spherpos::utc)
        .field("s", &spherpos::s)
        .field("v", &spherpos::v)
        .field("a", &spherpos::a)
        .field("pass", &spherpos::pass);
    value_object<extrapos>("extrapos")
        .field("utc", &extrapos::utc)
        .field("tt", &extrapos::tt)
        .field("ut", &extrapos::ut)
        .field("tdb", &extrapos::tdb)
        .field("j2e", &extrapos::j2e)
        .field("dj2e", &extrapos::dj2e)
        .field("ddj2e", &extrapos::ddj2e)
        .field("e2j", &extrapos::e2j)
        .field("de2j", &extrapos::de2j)
        .field("dde2j", &extrapos::dde2j)
        .field("j2t", &extrapos::j2t)
        .field("j2s", &extrapos::j2s)
        .field("t2j", &extrapos::t2j)
        .field("s2j", &extrapos::s2j)
        .field("s2t", &extrapos::s2t)
        .field("ds2t", &extrapos::ds2t)
        .field("t2s", &extrapos::t2s)
        .field("dt2s", &extrapos::dt2s)
        .field("sun2earth", &extrapos::sun2earth)
        .field("sungeo", &extrapos::sungeo)
        .field("sun2moon", &extrapos::sun2moon)
        .field("moongeo", &extrapos::moongeo)
        .field("closest", &extrapos::closest);
    value_object<svector>("svector")
        .field("phi", &svector::phi)
        .field("lambda", &svector::lambda)
        .field("r", &svector::r);
    value_object<rmatrix>("rmatrix")
        .field("row", &rmatrix::row);
    value_array<std::array<rvector, 3> >("array_rvector_3")
        .element(emscripten::index<0>())
        .element(emscripten::index<1>())
        .element(emscripten::index<2>());
    value_object<qatt>("qatt")
        .field("utc", &qatt::utc)
        .field("s", &qatt::s)
        .field("v", &qatt::v)
        .field("a", &qatt::a)
        .field("pass", &qatt::pass);
    value_object<extraatt>("extraatt")
        .field("utc", &extraatt::utc)
        .field("j2b", &extraatt::j2b)
        .field("b2j", &extraatt::b2j);
}