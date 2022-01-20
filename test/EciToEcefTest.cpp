#include <catch2/catch.hpp>
#include "EciToEcef.hpp"
#include <cmath>

using namespace Eigen;

TEST_CASE("EciToEcef Test1")
{
    Vector3d vec_eci = {-6733.04064617925, -1382.68992247076, -14.6876088752119};
    double gstime = 4.883067536994346;
    Vector3d vec = eci_to_ecef(vec_eci, gstime);

    REQUIRE(vec[0] == Approx(218.984818755685));
    REQUIRE(vec[1] == Approx(-6870.05920017860));
    REQUIRE(vec[2] == Approx(-14.6876088752119));

}
TEST_CASE("EciToEcef Test2")
{
    Vector3d vec_eci = {-2.3, 0, 1212};
    double gstime = 3.3453224;
    Vector3d vec = eci_to_ecef(vec_eci, gstime);

    REQUIRE(vec[0] == Approx(2.25243318591924));
    REQUIRE(vec[1] == Approx(-0.465343682636487));
    REQUIRE(vec[2] == Approx(1212));

}

TEST_CASE("EciToEcef Test3")
{
    Vector3d vec_eci = {-1234, -74329.123, 0.1432};
    double gstime = 12234909;
    Vector3d vec = eci_to_ecef(vec_eci, gstime);

    REQUIRE(vec[0] == Approx(-74334.9817031508));
    REQUIRE(vec[1] == Approx(-807.327158822088));
    REQUIRE(vec[2] == Approx(0.143200000000000));

}
