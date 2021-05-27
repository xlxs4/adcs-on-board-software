#include <catch2/catch.hpp>
#include "Albedo.h"

using namespace albedo;

TEST_CASE("Calculate cell area test") {
    uint16_t i = 40;
    uint16_t j = 50;

    float cellArea = calculateCellArea(i, j);
    REQUIRE(cellArea == Approx(1.003737674791411e+10).epsilon(0.01));
}

TEST_CASE("Calculate grid area test") {

    uint16_t loopI = 78;
    uint16_t loopJ = 24;
    int8_t sunIndexI = 56;
    int8_t sunIndexJ = 95;

    float gridAngleResult = gridAngle(loopI, loopJ, sunIndexI, sunIndexJ);
    REQUIRE(gridAngleResult == Approx(1.442580854116471).epsilon(0.01));
}

TEST_CASE("Indices to radians test") {
    uint16_t i = 40;
    uint16_t j = 50;

    Vector2f radians = albedo::indicesToRadians(i, j);
    REQUIRE(radians(0) == Approx(-2.039853563268373).epsilon(0.01));
    REQUIRE(radians(1) == Approx(2.434734306532090).epsilon(0.01));
}

TEST_CASE("Radians to indices test") {
    Vector<int16_t, 2> indices1 = radiansToIndices(20, 40);
    REQUIRE(indices1(0) == Approx(-2110).epsilon(0.01));
    REQUIRE(indices1(1) == Approx(1060).epsilon(0.01));

    Vector<int16_t, 2> indices2 = radiansToIndices(1.0e+06 * 0.000000674740942,
                                                   1.0e+06 * 0.000001446501385);
    REQUIRE(indices2(0) == Approx(97).epsilon(0.01));
    REQUIRE(indices2(1) == Approx(174).epsilon(0.01));
}

TEST_CASE("Albedo test") {

    Vector3f satellite = {100000000, 200000000, 300000000};
    Vector3f sunPosition = {5000000, 4000000, 8000000};
    Matrix<float, 180, 288> reflectivityData1 = Matrix<float, 180, 288>::Identity() * 100000;
    Matrix<float, 180, 288> reflectivityData2 = Matrix<float, 180, 288>::Identity() * 5000;


    Matrix<float, 180, 288> albedo1 = calculateAlbedo(satellite, sunPosition, reflectivityData1);
    REQUIRE(albedo1.sum() == Approx(0.065217631207925).epsilon(0.01));

    Matrix<float, 180, 288> albedo2 = calculateAlbedo(satellite, sunPosition, reflectivityData2);
    REQUIRE(albedo2.sum() == Approx(0.003260881560396).epsilon(0.01));
}