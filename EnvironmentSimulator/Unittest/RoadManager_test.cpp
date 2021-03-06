#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <stdexcept>

#include "RoadManager.hpp"

using namespace roadmanager;

#define TRIG_ERR_MARGIN 0.001

//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Polynomial //////////
//////////////////////////////////////////////////////////////////////

class PolynomialTestFixture: public testing::Test
{
    public:
        PolynomialTestFixture();
        PolynomialTestFixture(double a, double b, double c, double d, double p_scale);
        virtual ~PolynomialTestFixture();
    protected:
        Polynomial polynomial;
};



PolynomialTestFixture::PolynomialTestFixture()
{
}

PolynomialTestFixture::PolynomialTestFixture(double a, double b, double c, double d, double p_scale)
{
}

PolynomialTestFixture::~PolynomialTestFixture()
{
}

TEST_F(PolynomialTestFixture, TestConstructorEmpty)
{
    ASSERT_EQ(0, polynomial.GetA());
    ASSERT_EQ(0, polynomial.GetB());
    ASSERT_EQ(0, polynomial.GetC());
    ASSERT_EQ(0, polynomial.GetD());
    ASSERT_EQ(1, polynomial.GetPscale());
}

TEST_F(PolynomialTestFixture, TestConstructorArgument)
{
    Polynomial polynomial = Polynomial(1,-2,3,-4);
    ASSERT_EQ(1, polynomial.GetA());
    ASSERT_EQ(-2, polynomial.GetB());
    ASSERT_EQ(3, polynomial.GetC());
    ASSERT_EQ(-4, polynomial.GetD());
    ASSERT_EQ(1, polynomial.GetPscale());
}

TEST_F(PolynomialTestFixture, TestConstructorArgumentPscale)
{
    Polynomial polynomial = Polynomial(1,-2,3,-4,2);
    ASSERT_EQ(1, polynomial.GetA());
    ASSERT_EQ(-2, polynomial.GetB());
    ASSERT_EQ(3, polynomial.GetC());
    ASSERT_EQ(-4, polynomial.GetD());
    ASSERT_EQ(2, polynomial.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGet)
{
    polynomial.Set(1,-2,3,-4);
    ASSERT_EQ(1, polynomial.GetA());
    ASSERT_EQ(-2, polynomial.GetB());
    ASSERT_EQ(3, polynomial.GetC());
    ASSERT_EQ(-4, polynomial.GetD());
    ASSERT_EQ(1, polynomial.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGetPscale)
{
    polynomial.Set(1,-2,3,-4, 2);
    ASSERT_EQ(1, polynomial.GetA());
    ASSERT_EQ(-2, polynomial.GetB());
    ASSERT_EQ(3, polynomial.GetC());
    ASSERT_EQ(-4, polynomial.GetD());
    ASSERT_EQ(2, polynomial.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGetIndividual)
{
    polynomial.SetA(1);
    polynomial.SetB(-2);
    polynomial.SetC(3);
    polynomial.SetD(-4);
    ASSERT_EQ(1, polynomial.GetA());
    ASSERT_EQ(-2, polynomial.GetB());
    ASSERT_EQ(3, polynomial.GetC());
    ASSERT_EQ(-4, polynomial.GetD());
}

class PolynomialTestEvaluateEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial polynomial_empty;
};

TEST_P(PolynomialTestEvaluateEmptyParametrized, TestEvaluateEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    polynomial_empty.SetA(1);
    polynomial_empty.SetB(-2);
    polynomial_empty.SetC(3);
    polynomial_empty.SetD(-4);
    ASSERT_EQ(polynomial_empty.Evaluate(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamEmpty, PolynomialTestEvaluateEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-23),
                                                std::make_tuple(0, 1)));

class PolynomialTestEvaluateArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial polynomial_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluateArgumentParametrized, TestEvaluateArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(polynomial_argument.Evaluate(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamArgument, PolynomialTestEvaluateArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-215),
                                                std::make_tuple(0, 1)));


class PolynomialTestEvaluatePrimEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial polynomial_empty;
};

TEST_P(PolynomialTestEvaluatePrimEmptyParametrized, TestEvaluatePrimEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    polynomial_empty.SetA(1);
    polynomial_empty.SetB(-2);
    polynomial_empty.SetC(3);
    polynomial_empty.SetD(-4);
    ASSERT_EQ(polynomial_empty.EvaluatePrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimParamEmpty, PolynomialTestEvaluatePrimEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-38),
                                                std::make_tuple(0, -2)));

class PolynomialTestEvaluatePrimArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial polynomial_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluatePrimArgumentParametrized, TestEvaluatePrimArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(polynomial_argument.EvaluatePrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimParamArgument, PolynomialTestEvaluatePrimArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-170),
                                                std::make_tuple(0, -2)));

class PolynomialTestEvaluatePrimPrimEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial polynomial_empty;
};

TEST_P(PolynomialTestEvaluatePrimPrimEmptyParametrized, TestEvaluatePrimPrimEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    polynomial_empty.SetA(1);
    polynomial_empty.SetB(-2);
    polynomial_empty.SetC(3);
    polynomial_empty.SetD(-4);
    ASSERT_EQ(polynomial_empty.EvaluatePrimPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimPrimParamEmpty, PolynomialTestEvaluatePrimPrimEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-42),
                                                std::make_tuple(0, 6)));

class PolynomialTestEvaluatePrimPrimArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial polynomial_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluatePrimPrimArgumentParametrized, TestEvaluatePrimPrimArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(polynomial_argument.EvaluatePrimPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimPrimParamArgument, PolynomialTestEvaluatePrimPrimArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-90),
                                                std::make_tuple(0, 6)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> OSIPoints //////////
//////////////////////////////////////////////////////////////////////

class OSIPointsTestFixture: public testing::Test
{
    public:
        OSIPointsTestFixture();
        OSIPointsTestFixture(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h);
        virtual ~OSIPointsTestFixture();
    protected:
        OSIPoints osi_points;
};

OSIPointsTestFixture::OSIPointsTestFixture()
{
}

OSIPointsTestFixture::OSIPointsTestFixture(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h)
{
}

OSIPointsTestFixture::~OSIPointsTestFixture()
{
}

TEST_F(OSIPointsTestFixture, TestConstructorEmpty)
{
    ASSERT_EQ(0, osi_points.GetS().size());
    ASSERT_EQ(0, osi_points.GetX().size());
    ASSERT_EQ(0, osi_points.GetY().size());
    ASSERT_EQ(0, osi_points.GetZ().size());
    ASSERT_EQ(0, osi_points.GetH().size());
}

TEST_F(OSIPointsTestFixture, TestConstructorArgument)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);

    std::vector<double> s_expected = osi_points.GetS();
    std::vector<double> x_expected = osi_points.GetX();
    std::vector<double> y_expected = osi_points.GetY();
    std::vector<double> z_expected = osi_points.GetZ();
    std::vector<double> h_expected = osi_points.GetH();

    ASSERT_EQ(s, s_expected);
    ASSERT_EQ(x, x_expected);
    ASSERT_EQ(y, y_expected);
    ASSERT_EQ(z, z_expected);
    ASSERT_EQ(h, h_expected);
}

TEST_F(OSIPointsTestFixture, TestSetGet)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};
    
    osi_points.Set(s,x,y,z,h);

    std::vector<double> s_expected = osi_points.GetS();
    std::vector<double> x_expected = osi_points.GetX();
    std::vector<double> y_expected = osi_points.GetY();
    std::vector<double> z_expected = osi_points.GetZ();
    std::vector<double> h_expected = osi_points.GetH();

    ASSERT_EQ(s, s_expected);
    ASSERT_EQ(x, x_expected);
    ASSERT_EQ(y, y_expected);
    ASSERT_EQ(z, z_expected);
    ASSERT_EQ(h, h_expected);
}

TEST_F(OSIPointsTestFixture, TestGetFromIdxEmpty)
{
    ASSERT_THROW(osi_points.GetXfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetXfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetXfromIdx(1), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(1), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(1), std::runtime_error);
}

TEST_F(OSIPointsTestFixture, TestGetFromIdx)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);

    ASSERT_EQ(osi_points.GetXfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetXfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetXfromIdx(2), (double)2);

    ASSERT_EQ(osi_points.GetYfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetYfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetYfromIdx(2), (double)2);

    ASSERT_EQ(osi_points.GetZfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetZfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetZfromIdx(2), (double)2);
}

TEST_F(OSIPointsTestFixture, TestGetNumOfOSIPointsCorrupt)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);
    ASSERT_THROW(osi_points.GetNumOfOSIPoints(), std::runtime_error);
}

TEST_F(OSIPointsTestFixture, TestGetNumOfOSIPoints)
{
    ASSERT_EQ(osi_points.GetNumOfOSIPoints(), 0);
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points_second = OSIPoints(s, x, y, z, h);
    ASSERT_EQ(osi_points_second.GetNumOfOSIPoints(), 3);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Line (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class LineGeomTestFixture: public testing::Test
{
    public:
        LineGeomTestFixture();
        LineGeomTestFixture(double s, double x, double y, double hdg, double length);
        virtual ~LineGeomTestFixture();
    protected:
        Line line;
};

LineGeomTestFixture::LineGeomTestFixture()
{
}

LineGeomTestFixture::LineGeomTestFixture(double s, double x, double y, double hdg, double length)
{
}

LineGeomTestFixture::~LineGeomTestFixture()
{
}

TEST_F(LineGeomTestFixture, TestConstructorArgument)
{
    ASSERT_EQ(0, line.GetS());
    ASSERT_EQ(0, line.GetX());
    ASSERT_EQ(0, line.GetY());
    ASSERT_EQ(0, line.GetHdg());
    ASSERT_EQ(0, line.GetLength());
    EXPECT_EQ(line.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);

    Line line_second = Line(2, -1, 1, 5*M_PI, 4);
    ASSERT_EQ(2, line_second.GetS());
    ASSERT_EQ(-1, line_second.GetX());
    ASSERT_EQ(1, line_second.GetY());
    ASSERT_EQ(M_PI, line_second.GetHdg());
    ASSERT_EQ(4, line_second.GetLength());
    EXPECT_EQ(line_second.GetType(), Geometry::GEOMETRY_TYPE_LINE);

    Line line_third = Line(2, -1, 1, -5*M_PI, 4);
    ASSERT_EQ(2, line_third.GetS());
    ASSERT_EQ(-1, line_third.GetX());
    ASSERT_EQ(1, line_third.GetY());
    ASSERT_EQ(M_PI, line_third.GetHdg());
    ASSERT_EQ(4, line_third.GetLength());
    EXPECT_EQ(line_third.GetType(), Geometry::GEOMETRY_TYPE_LINE);
}

TEST_F(LineGeomTestFixture, TestEvaluateCurvatureDS)
{
    ASSERT_EQ(line.EvaluateCurvatureDS(0), 0.0);
    ASSERT_EQ(line.EvaluateCurvatureDS(10), 0.0);
    ASSERT_EQ(line.EvaluateCurvatureDS(100), 0.0);
    ASSERT_EQ(line.EvaluateCurvatureDS(1000), 0.0);
}


class LineGeomTestEvaluateDsEmptyConstructor: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Line line;
};

TEST_P(LineGeomTestEvaluateDsEmptyConstructor, TestLineGeomEvaluateDsEmpty)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = line.GetX();
    double my_y = line.GetY();
    double my_h = line.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    line.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_EQ(*x, std::get<1>(tuple));
    ASSERT_EQ(*y, std::get<2>(tuple));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateDsEmptyParam, LineGeomTestEvaluateDsEmptyConstructor, testing::Values(
                                                std::make_tuple(0, 0, 0, 0),
                                                std::make_tuple(1, 1, 0, 0),
                                                std::make_tuple(100, 100, 0, 0)));

class LineGeomTestEvaluateDsArgumentConstructor: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Line line{2.0, -1.0, 1.0, 5*M_PI, 4.0};
};

TEST_P(LineGeomTestEvaluateDsArgumentConstructor, TestLineGeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = line.GetX();
    double my_y = line.GetY();
    double my_h = line.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    line.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_EQ(*x, std::get<1>(tuple));
    ASSERT_EQ(*y, std::get<2>(tuple));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateLineDsArgumentParam, LineGeomTestEvaluateDsArgumentConstructor, testing::Values(
                                                std::make_tuple(0.0, -1.0, 1.0, M_PI),
                                                std::make_tuple(1.0, -2.0, 1.0+sin(M_PI), M_PI),
                                                std::make_tuple(100.0, -101.0, 1.0+100*sin(M_PI), M_PI)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Arc (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class ArcGeomTestFixture: public testing::Test
{
    public:
        ArcGeomTestFixture();
        ArcGeomTestFixture(double s, double x, double y, double hdg, double length, double curvature);
        virtual ~ArcGeomTestFixture();
    protected:
        Arc arc;
};

ArcGeomTestFixture::ArcGeomTestFixture()
{
}

ArcGeomTestFixture::ArcGeomTestFixture(double s, double x, double y, double hdg, double length, double curvature)
{
}

ArcGeomTestFixture::~ArcGeomTestFixture()
{
}

TEST_F(ArcGeomTestFixture, TestConstructorArgument)
{
    ASSERT_EQ(0.0, arc.GetCurvature());
    EXPECT_EQ(arc.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);

    Arc arc_second = Arc(2, -1, 1, 5*M_PI, 4, 5);
    ASSERT_EQ(5.0, arc_second.GetCurvature());
    EXPECT_EQ(arc_second.GetType(), Geometry::GEOMETRY_TYPE_ARC);
}

TEST_F(ArcGeomTestFixture, TestEvaluateCurvatureDS)
{
    ASSERT_EQ(arc.EvaluateCurvatureDS(0), 0.0);
    ASSERT_EQ(arc.EvaluateCurvatureDS(10), 0.0);
    ASSERT_EQ(arc.EvaluateCurvatureDS(100), 0.0);
    ASSERT_EQ(arc.EvaluateCurvatureDS(1000), 0.0);

    Arc arc_second = Arc(2, -1, 1, 5*M_PI, 4, 5);

    ASSERT_EQ(arc_second.EvaluateCurvatureDS(0), 5.0);
    ASSERT_EQ(arc_second.EvaluateCurvatureDS(10), 5.0);
    ASSERT_EQ(arc_second.EvaluateCurvatureDS(100), 5.0);
    ASSERT_EQ(arc_second.EvaluateCurvatureDS(1000), 5.0);
}

TEST_F(ArcGeomTestFixture, TestGetRadius)
{
    Arc arc_second = Arc(2, -1, 1, 5*M_PI, 4, 5);
    ASSERT_EQ(arc_second.GetRadius(), 0.2);

    Arc arc_third = Arc(2, -1, 1, 5*M_PI, 4, -10);
    ASSERT_EQ(arc_third.GetRadius(), 0.1);
}

class ArcGeomTestEvaluateDsCurvPositive: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Arc arc{2.0, -1.0, 1.0, 5*M_PI, 4.0, 1.0};
};

TEST_P(ArcGeomTestEvaluateDsCurvPositive, TestArcGeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = arc.GetX();
    double my_y = arc.GetY();
    double my_h = arc.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    arc.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_THAT(*x, testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_THAT(*y,  testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateArcDsArgumentParam, ArcGeomTestEvaluateDsCurvPositive, testing::Values(
                                                std::make_tuple(0.0, -1.0, 1.0, M_PI),
                                                std::make_tuple(M_PI/2, -2.0, 0.0, M_PI+M_PI/2),
                                                std::make_tuple(M_PI, -1.0, -1.0, 2*M_PI)));

class ArcGeomTestEvaluateDsCurvNegative: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Arc arc{2.0, -1.0, 1.0, 5*M_PI, 4.0, -1.0};
};

TEST_P(ArcGeomTestEvaluateDsCurvNegative, TestArcGeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = arc.GetX();
    double my_y = arc.GetY();
    double my_h = arc.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    arc.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_THAT(*x, testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_THAT(*y,  testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateArcDsArgumentParam, ArcGeomTestEvaluateDsCurvNegative, testing::Values(
                                                std::make_tuple(0.0, -1.0, 1.0, M_PI),
                                                std::make_tuple(M_PI/2, -2.0, 2.0, M_PI-M_PI/2),
                                                std::make_tuple(M_PI, -1.0, 3.0, 0)));                                    

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Spiral (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class SpiralGeomTestFixture: public testing::Test
{
    public:
        SpiralGeomTestFixture();
        SpiralGeomTestFixture(double s, double x, double y, double hdg, double length, double curv_start, double curv_end);
        virtual ~SpiralGeomTestFixture();
    protected:
        Spiral spiral;
};

SpiralGeomTestFixture::SpiralGeomTestFixture()
{
}

SpiralGeomTestFixture::SpiralGeomTestFixture(double s, double x, double y, double hdg, double length, double curv_start, double curv_end)
{
}

SpiralGeomTestFixture::~SpiralGeomTestFixture()
{
}

TEST_F(SpiralGeomTestFixture, TestConstructorArgument)
{
    ASSERT_EQ(0.0, spiral.GetCurvStart());
    ASSERT_EQ(0.0, spiral.GetCurvEnd());
    ASSERT_EQ(0.0, spiral.GetCDot());
    ASSERT_EQ(0.0, spiral.GetX0());
    ASSERT_EQ(0.0, spiral.GetY0());
    ASSERT_EQ(0.0, spiral.GetH0());
    ASSERT_EQ(0.0, spiral.GetS0());
    EXPECT_EQ(spiral.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);

    Spiral spiral_second = Spiral(2, -1, 1, 5*M_PI, 4, 2, 10);
    ASSERT_EQ(2.0, spiral_second.GetCurvStart());
    ASSERT_EQ(10.0, spiral_second.GetCurvEnd());
    // EMIL added constructor definition for Spiral constructor. Will be fixed later.
    /*ASSERT_EQ(0.0, spiral_second.GetCDot());
    ASSERT_EQ(0.0, spiral_second.GetX0());
    ASSERT_EQ(0.0, spiral_second.GetY0());
    ASSERT_EQ(0.0, spiral_second.GetH0());
    ASSERT_EQ(0.0, spiral_second.GetS0());*/
    EXPECT_EQ(spiral_second.GetType(), Geometry::GEOMETRY_TYPE_SPIRAL);
}

TEST_F(SpiralGeomTestFixture, TestGetSet)
{
    spiral.SetX0(5);
    spiral.SetY0(-10);
    spiral.SetH0(15);
    spiral.SetS0(-20);
    spiral.SetCDot(0);
    
    ASSERT_EQ(5.0, spiral.GetX0());
    ASSERT_EQ(-10.0, spiral.GetY0());
    ASSERT_EQ(15.0, spiral.GetH0());
    ASSERT_EQ(-20.0, spiral.GetS0());
    ASSERT_EQ(0.0, spiral.GetCDot());
}

TEST_F(SpiralGeomTestFixture, TestEvaluateCurvatureDS)
{
    Spiral spiral_second = Spiral(2, -1, 1, 5*M_PI, 4, 2, 10);

    ASSERT_EQ(spiral_second.EvaluateCurvatureDS(0), 2.0);
    ASSERT_EQ(spiral_second.EvaluateCurvatureDS(10), 22.0);
    ASSERT_EQ(spiral_second.EvaluateCurvatureDS(100), 202.0);
    ASSERT_EQ(spiral_second.EvaluateCurvatureDS(1000), 2002.0);
}

/*
TODO: Remaining Test for this class is to test EvaluateDs function which inclides odrSpiral function
as extern void -> Check this later.
*/

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Poly3 (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class Poly3GeomTestFixture: public testing::Test
{
    public:
        Poly3GeomTestFixture();
        Poly3GeomTestFixture(double s, double x, double y, double hdg, double length, double a, double b, double c, double d);
        virtual ~Poly3GeomTestFixture();
    protected:
        Poly3 poly3;
};

Poly3GeomTestFixture::Poly3GeomTestFixture()
{
}

Poly3GeomTestFixture::Poly3GeomTestFixture(double s, double x, double y, double hdg, double length, double a, double b, double c, double d)
{
}

Poly3GeomTestFixture::~Poly3GeomTestFixture()
{
}

TEST_F(Poly3GeomTestFixture, TestPoly3UMaxGetSetArgumentConstructor)
{
    ASSERT_EQ(0.0, poly3.GetUMax());
    EXPECT_EQ(poly3.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);
    poly3.SetUMax(5);
    ASSERT_EQ(poly3.GetUMax(), 5.0);

    Poly3 poly3_second = Poly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4);
    ASSERT_EQ(0.0, poly3_second.GetUMax());
    EXPECT_EQ(poly3_second.GetType(), Geometry::GEOMETRY_TYPE_POLY3);
    ASSERT_EQ(poly3_second.poly3_.GetA(), 1.0);
    ASSERT_EQ(poly3_second.poly3_.GetB(), -2.0);
    ASSERT_EQ(poly3_second.poly3_.GetC(), 3.0);
    ASSERT_EQ(poly3_second.poly3_.GetD(), -4.0);
    ASSERT_EQ(poly3_second.poly3_.GetPscale(), 1.0);

    Polynomial my_polynomial = poly3_second.GetPoly3();
    ASSERT_EQ(poly3_second.poly3_.GetA(), my_polynomial.GetA());
    ASSERT_EQ(poly3_second.poly3_.GetB(), my_polynomial.GetB());
    ASSERT_EQ(poly3_second.poly3_.GetC(), my_polynomial.GetC());
    ASSERT_EQ(poly3_second.poly3_.GetD(), my_polynomial.GetD());
    ASSERT_EQ(poly3_second.poly3_.GetPscale(), my_polynomial.GetPscale());
}

TEST_F(Poly3GeomTestFixture, TestEvaluateCurvatureDS)
{
    Poly3 poly3_second = Poly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4);

    ASSERT_EQ(poly3_second.EvaluateCurvatureDS(0), 6.0);
    ASSERT_EQ(poly3_second.EvaluateCurvatureDS(10), -234.0);
    ASSERT_EQ(poly3_second.EvaluateCurvatureDS(100), -2394.0);
    ASSERT_EQ(poly3_second.EvaluateCurvatureDS(1000), -23994.0);
}

class Poly3GeomTestEvaluateDsCurvUmaxZero: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Poly3 poly3 = Poly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4);
};

TEST_P(Poly3GeomTestEvaluateDsCurvUmaxZero, TestPoly3GeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = poly3.GetX();
    double my_y = poly3.GetY();
    double my_h = poly3.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    poly3.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_THAT(*x, testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_THAT(*y,  testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePoly3DsArgumentParam, Poly3GeomTestEvaluateDsCurvUmaxZero, testing::Values(
                                                std::make_tuple(0.0, -1.0, 0.0, M_PI-2),
                                                std::make_tuple(10.0, -1.0, 0.0, M_PI-2),
                                                std::make_tuple(100.0, -1.0, 0.0, M_PI-2),
                                                std::make_tuple(1000.0, -1.0, 0.0, M_PI-2)));

class Poly3GeomTestEvaluateDsCurvUmaxNonZero: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        Poly3 poly3 = Poly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4);
};

TEST_P(Poly3GeomTestEvaluateDsCurvUmaxNonZero, TestPoly3GeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = poly3.GetX();
    double my_y = poly3.GetY();
    double my_h = poly3.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    poly3.SetUMax(1.0);
    poly3.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_THAT(*x, testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_THAT(*y,  testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePoly3DsArgumentParam, Poly3GeomTestEvaluateDsCurvUmaxNonZero, testing::Values(
                                                std::make_tuple(0.0, -1.0, 0.0, M_PI-2.0),
                                                std::make_tuple(4.0, -2.0, 3.0, M_PI-8.0)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> ParamPoly3 (Geometry) //////////
//////////////////////////////////////////////////////////////////////

class ParamPoly3GeomTestFixture: public testing::Test
{
    public:
        ParamPoly3GeomTestFixture();
        ParamPoly3GeomTestFixture(double s, double x, double y, double hdg, double length, 
        double aU, double bU, double cU, double dU, double aV, double bV, double cV, double dV, ParamPoly3::PRangeType p_range);
        virtual ~ParamPoly3GeomTestFixture();
    protected:
        ParamPoly3 parampoly3;
};

ParamPoly3GeomTestFixture::ParamPoly3GeomTestFixture()
{
}

ParamPoly3GeomTestFixture::ParamPoly3GeomTestFixture(double s, double x, double y, double hdg, double length, 
        double aU, double bU, double cU, double dU, double aV, double bV, double cV, double dV, ParamPoly3::PRangeType p_range)
{
}

ParamPoly3GeomTestFixture::~ParamPoly3GeomTestFixture()
{
}

TEST_F(ParamPoly3GeomTestFixture, TestParamPoly3ArgumentConstructor)
{

    EXPECT_EQ(parampoly3.GetType(), Geometry::GEOMETRY_TYPE_UNKNOWN);

    ParamPoly3 parampoly3_second = ParamPoly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4, 1, -2, 3, -4, ParamPoly3::PRangeType::P_RANGE_NORMALIZED);
    EXPECT_EQ(parampoly3_second.GetType(), Geometry::GEOMETRY_TYPE_PARAM_POLY3);
    ASSERT_EQ(parampoly3_second.poly3U_.GetA(), 1.0);
    ASSERT_EQ(parampoly3_second.poly3U_.GetB(), -2.0);
    ASSERT_EQ(parampoly3_second.poly3U_.GetC(), 3.0);
    ASSERT_EQ(parampoly3_second.poly3U_.GetD(), -4.0);
    ASSERT_EQ(parampoly3_second.poly3U_.GetPscale(), 1.0/4.0);
    ASSERT_EQ(parampoly3_second.poly3V_.GetPscale(), 1.0/4.0);

    ParamPoly3 parampoly3_third = ParamPoly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4, 1, -2, 3, -4, ParamPoly3::PRangeType::P_RANGE_UNKNOWN);
    ASSERT_EQ(parampoly3_third.poly3U_.GetPscale(), 1.0);
    ASSERT_EQ(parampoly3_third.poly3V_.GetPscale(), 1.0);

    Polynomial my_polynomialU = parampoly3_second.GetPoly3U();
    ASSERT_EQ(parampoly3_second.poly3U_.GetA(), my_polynomialU.GetA());
    ASSERT_EQ(parampoly3_second.poly3U_.GetB(), my_polynomialU.GetB());
    ASSERT_EQ(parampoly3_second.poly3U_.GetC(), my_polynomialU.GetC());
    ASSERT_EQ(parampoly3_second.poly3U_.GetD(), my_polynomialU.GetD());
    ASSERT_EQ(parampoly3_second.poly3U_.GetPscale(), my_polynomialU.GetPscale());

    Polynomial my_polynomialV = parampoly3_second.GetPoly3V();
    ASSERT_EQ(parampoly3_second.poly3V_.GetA(), my_polynomialV.GetA());
    ASSERT_EQ(parampoly3_second.poly3V_.GetB(), my_polynomialV.GetB());
    ASSERT_EQ(parampoly3_second.poly3V_.GetC(), my_polynomialV.GetC());
    ASSERT_EQ(parampoly3_second.poly3V_.GetD(), my_polynomialV.GetD());
    ASSERT_EQ(parampoly3_second.poly3V_.GetPscale(), my_polynomialV.GetPscale());
}

TEST_F(ParamPoly3GeomTestFixture, TestEvaluateCurvatureDS)
{
    ParamPoly3 parampoly3_second = ParamPoly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4, 1, -2, 3, -4, ParamPoly3::PRangeType::P_RANGE_UNKNOWN);

    ASSERT_EQ(parampoly3_second.EvaluateCurvatureDS(0), -3.0);
    ASSERT_EQ(parampoly3_second.EvaluateCurvatureDS(10), 234.0/1142.0);
    ASSERT_EQ(parampoly3_second.EvaluateCurvatureDS(100), 2394.0/119402.0);
    ASSERT_EQ(parampoly3_second.EvaluateCurvatureDS(1000), 23994.0/11994002.0);
}

class ParamPoly3GeomTestEvaluateDsCurv: public testing::TestWithParam<std::tuple<double, double, double, double>>
{
    public:
    protected:
        ParamPoly3 parampoly3 = ParamPoly3(2, -1, 1, 5*M_PI, 4, 1, -2, 3, -4, 1, -2, 3, -4, ParamPoly3::PRangeType::P_RANGE_UNKNOWN);
};

TEST_P(ParamPoly3GeomTestEvaluateDsCurv, TestParamPoly3GeomEvaluateDsArgument)
{
    std::tuple<double, double, double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    double *x, *y, *h;
    double my_x = parampoly3.GetX();
    double my_y = parampoly3.GetY();
    double my_h = parampoly3.GetHdg();
    x = &my_x;
    y = &my_y;
    h = &my_h;
    parampoly3.EvaluateDS(std::get<0>(tuple), x, y, h);
    ASSERT_THAT(*x, testing::AllOf(testing::Gt(std::get<1>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<1>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_THAT(*y,  testing::AllOf(testing::Gt(std::get<2>(tuple)-TRIG_ERR_MARGIN), testing::Lt(std::get<2>(tuple)+TRIG_ERR_MARGIN)));
    ASSERT_EQ(*h, std::get<3>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamPoly3DsArgumentParam, ParamPoly3GeomTestEvaluateDsCurv, testing::Values(
                                                std::make_tuple(0.0, -2.0, 0.0, M_PI+atan2(-2.0,-2.0)),
                                                std::make_tuple(10.0, 3718.0, 3720.0, M_PI+atan2(-2.0,-2.0))));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Elevation /////////////////////////////
//////////////////////////////////////////////////////////////////////

class ElevationTestFixture: public testing::Test
{
    public:
        ElevationTestFixture();
        ElevationTestFixture(double s, double a, double b, double c, double d); 
        virtual ~ElevationTestFixture();
    protected:
        Elevation elevation;
};

ElevationTestFixture::ElevationTestFixture()
{
}

ElevationTestFixture::ElevationTestFixture(double s, double a, double b, double c, double d)
{
}

ElevationTestFixture::~ElevationTestFixture()
{
}

TEST_F(ElevationTestFixture, TestElevation)
{
    ASSERT_EQ(elevation.GetLength(), 0.0);
    ASSERT_EQ(elevation.GetS(), 0.0);

    elevation.SetLength(4.0);
    ASSERT_EQ(elevation.GetLength(), 4.0);

    Elevation elevation_second = Elevation(2.0, 1.0, -2.0, 3.0, -4.0);
    ASSERT_EQ(elevation_second.GetS(), 2.0);
    ASSERT_EQ(elevation_second.poly3_.GetA(), 1.0);
    ASSERT_EQ(elevation_second.poly3_.GetB(), -2.0);
    ASSERT_EQ(elevation_second.poly3_.GetC(), 3.0);
    ASSERT_EQ(elevation_second.poly3_.GetD(), -4.0);
    ASSERT_EQ(elevation_second.poly3_.GetPscale(), 1.0);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneLink /////////////////////////////
//////////////////////////////////////////////////////////////////////

TEST(LaneLinkTest, DefaultConstructor) {
    LaneLink lane_link(UNKNOWN, 0);
    EXPECT_EQ(UNKNOWN, lane_link.GetType());
    EXPECT_EQ(0,lane_link.GetId());
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneWidth /////////////////////////////
//////////////////////////////////////////////////////////////////////

TEST(LaneWidthTest, DefaultConstructor) {
    LaneWidth lane_width(1, 1, 1, 1, 1);
    EXPECT_EQ(1, lane_width.GetSOffset());
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneBoundaryOSI ////////////////////////
//////////////////////////////////////////////////////////////////////

// TODO
// TODO
// TODO

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneRoadMarkTypeLine ///////////////////
//////////////////////////////////////////////////////////////////////

class LaneRoadMarkTypeLineTest :public ::testing::TestWithParam<std::tuple<double,double,double,double,LaneRoadMarkTypeLine::RoadMarkTypeLineRule,double>> {};
// inp: length,space,t_offset,s_offset,rule,width

TEST_P(LaneRoadMarkTypeLineTest, DefaultConstructor) {
    LaneRoadMarkTypeLine lane_roadmarking = LaneRoadMarkTypeLine(
        std::get<0>(GetParam()),
        std::get<1>(GetParam()),
        std::get<2>(GetParam()),
        std::get<3>(GetParam()),
        std::get<4>(GetParam()),
        std::get<5>(GetParam()));

    EXPECT_EQ(lane_roadmarking.GetLength(),std::get<0>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetSpace(),std::get<1>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetTOffset(),std::get<2>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetSOffset(),std::get<3>(GetParam()));

    // Test SetGlobalId method
    // OSI related stuff not implemented yet
    //lane_roadmarking.SetGlobalId();
    //EXPECT_EQ(lane_roadmarking.GetGlobalId(), 0);
}

INSTANTIATE_TEST_CASE_P(LaneRoadMarkTypeLineTests,LaneRoadMarkTypeLineTest,::testing::Values(
    std::make_tuple(100,100,0,0,LaneRoadMarkTypeLine::NO_PASSING,2),
    std::make_tuple(10,10,-1,1,LaneRoadMarkTypeLine::CAUTION,6)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneRoadMarkType ///////////////////////
//////////////////////////////////////////////////////////////////////

class LaneRoadMarkTypeTest : public ::testing::Test {
    protected:
    void SetUp() override { lane_test_0 = new LaneRoadMarkType("test", 0.2); }
    LaneRoadMarkType* lane_test_0;
};

TEST_F(LaneRoadMarkTypeTest, DefaultConstructor) {
    EXPECT_EQ(lane_test_0->GetName(),"test");
    EXPECT_EQ(lane_test_0->GetWidth(),0.2);
}

TEST_F(LaneRoadMarkTypeTest,AddLine) {
    LaneRoadMarkTypeLine * line_0 = new LaneRoadMarkTypeLine(100,100,0,0,LaneRoadMarkTypeLine::NO_PASSING,2);
    lane_test_0->AddLine(line_0);
    EXPECT_EQ(lane_test_0->GetNumberOfRoadMarkTypeLines(), 1);

    // test GetLaneRoadMarkTypeLineByIdx method
    EXPECT_EQ(lane_test_0->GetLaneRoadMarkTypeLineByIdx(0)->GetLength(), line_0->GetLength());
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneRoadMark ///////////////////////////
//////////////////////////////////////////////////////////////////////

class LaneRoadMarkTest :public ::testing::TestWithParam<std::tuple<double,LaneRoadMark::RoadMarkType,LaneRoadMark::RoadMarkWeight,LaneRoadMark::RoadMarkColor,LaneRoadMark::RoadMarkMaterial,LaneRoadMark::RoadMarkLaneChange,double,double>> {};
// inp: s_offset,type,weight,color,material,lane_change,width,height

TEST_P(LaneRoadMarkTest, DefaultConstructor) {
    LaneRoadMark lane_test_0 = LaneRoadMark(
        std::get<0>(GetParam()),
        std::get<1>(GetParam()),
        std::get<2>(GetParam()),
        std::get<3>(GetParam()),
        std::get<4>(GetParam()),
        std::get<5>(GetParam()),
        std::get<6>(GetParam()),
        std::get<7>(GetParam()));

    EXPECT_EQ(lane_test_0.GetSOffset(),std::get<0>(GetParam()));
    EXPECT_EQ(lane_test_0.GetType(),std::get<1>(GetParam()));
    EXPECT_EQ(lane_test_0.GetColor(),std::get<3>(GetParam()));
    EXPECT_EQ(lane_test_0.GetWidth(),std::get<6>(GetParam()));
    EXPECT_EQ(lane_test_0.GetHeight(),std::get<7>(GetParam()));

    LaneRoadMarkType * type_test_0 = new LaneRoadMarkType("test", 0.2);
    lane_test_0.AddType(type_test_0);
    EXPECT_EQ(lane_test_0.GetNumberOfRoadMarkTypes(),1);
    EXPECT_EQ(lane_test_0.GetLaneRoadMarkTypeByIdx(0)->GetName(),type_test_0->GetName());
}

INSTANTIATE_TEST_CASE_P(LaneRoadMarkTests,LaneRoadMarkTest,::testing::Values(
    std::make_tuple(0,LaneRoadMark::NONE_TYPE,
        LaneRoadMark::STANDARD,
        LaneRoadMark::STANDARD_COLOR,
        LaneRoadMark::STANDARD_MATERIAL,
        LaneRoadMark::INCREASE,0.2,0),
    std::make_tuple(100,LaneRoadMark::SOLID,
        LaneRoadMark::BOLD,
        LaneRoadMark::BLUE,
        LaneRoadMark::STANDARD_MATERIAL,
        LaneRoadMark::DECREASE,0.2,-1)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> LaneOffSet ///////////////////////////
//////////////////////////////////////////////////////////////////////

class LaneOffsetTestFixture: public testing::Test
{
    public:
        LaneOffsetTestFixture();
        LaneOffsetTestFixture(double s, double a, double b, double c, double d); 
        virtual ~LaneOffsetTestFixture();
    protected:
        LaneOffset laneoffset;
};

LaneOffsetTestFixture::LaneOffsetTestFixture()
{
}

LaneOffsetTestFixture::LaneOffsetTestFixture(double s, double a, double b, double c, double d)
{
}

LaneOffsetTestFixture::~LaneOffsetTestFixture()
{
}

TEST_F(LaneOffsetTestFixture, TestLaneOffSetCommon)
{
    ASSERT_EQ(laneoffset.GetLength(), 0.0);
    ASSERT_EQ(laneoffset.GetS(), 0.0);

    laneoffset.SetLength(4.0);
    ASSERT_EQ(laneoffset.GetLength(), 4.0);

    LaneOffset laneoffset_second = LaneOffset(2.0, 1.0, -2.0, 3.0, -4.0);
    laneoffset_second.Set(2.0, 1.0, -2.0, 3.0, -4.0);
    ASSERT_EQ(laneoffset_second.GetS(), 2.0);
    ASSERT_EQ(laneoffset_second.GetPolynomial().GetA(), 1.0);
    ASSERT_EQ(laneoffset_second.GetPolynomial().GetB(), -2.0);
    ASSERT_EQ(laneoffset_second.GetPolynomial().GetC(), 3.0);
    ASSERT_EQ(laneoffset_second.GetPolynomial().GetD(), -4.0);
    ASSERT_EQ(laneoffset_second.GetPolynomial().GetPscale(), 1.0);
}


class LaneOffsetGetLaneOffsetTest: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        LaneOffset laneoffset = LaneOffset(2.0, 1.0, -2.0, 3.0, -4.0);
};

TEST_P(LaneOffsetGetLaneOffsetTest, TestGetLaneOffset)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_EQ(laneoffset.GetLaneOffset(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestGetLaneOffsetParam, LaneOffsetGetLaneOffsetTest, testing::Values(
                                                std::make_tuple(0.0, 49.0),
                                                std::make_tuple(10.0, -1871.0)));
                                            

class LaneOffsetGetLaneOffsetPrimTest: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        LaneOffset laneoffset = LaneOffset(2.0, 1.0, -2.0, 3.0, -4.0);
};

TEST_P(LaneOffsetGetLaneOffsetPrimTest, TestGetLaneOffsetPrim)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_EQ(laneoffset.GetLaneOffsetPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestGetLaneOffsetPrimParam, LaneOffsetGetLaneOffsetPrimTest, testing::Values(
                                                std::make_tuple(0.0, -62),
                                                std::make_tuple(10.0, -722.0)));

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
////////// TESTS FOR CLASS -> Lane ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

class LaneTestFixture: public testing::Test
{
    public:
        LaneTestFixture();
        LaneTestFixture(double s, double a, double b, double c, double d); 
        virtual ~LaneTestFixture();
    protected:
        Lane lane;
};

LaneTestFixture::LaneTestFixture()
{
}

LaneTestFixture::LaneTestFixture(double s, double a, double b, double c, double d)
{
}

LaneTestFixture::~LaneTestFixture()
{
}

TEST_F(LaneTestFixture, TestLaneBaseGetConstructor)
{
    ASSERT_EQ(lane.GetId(), 0);
    ASSERT_EQ(lane.GetOffsetFromRef(), 0.0);
    ASSERT_EQ(lane.GetLaneType(), Lane::LaneType::LANE_TYPE_NONE);
    ASSERT_EQ(lane.GetGlobalId(), 0.0);

    Lane lane_second = Lane(1, Lane::LaneType::LANE_TYPE_DRIVING);
    ASSERT_EQ(lane_second.GetId(), 1);
    ASSERT_EQ(lane_second.GetOffsetFromRef(), 0.0);
    ASSERT_EQ(lane_second.GetLaneType(), Lane::LaneType::LANE_TYPE_DRIVING);
    ASSERT_EQ(lane_second.GetGlobalId(), 0.0);
}

TEST_F(LaneTestFixture, TestLaneAddFunctions)
{
    ASSERT_EQ(lane.GetNumberOfLinks(), 0);
    ASSERT_EQ(lane.GetNumberOfRoadMarks(), 0);
    ASSERT_EQ(lane.GetNumberOfLaneWidths(), 0);

    LaneLink *lanelink = new LaneLink(LinkType::SUCCESSOR, 3);
    LaneWidth *lanewidth = new LaneWidth(2.0, 1.0, -2.0, -3.0, 4.0);
    LaneRoadMark *laneroadmark = new LaneRoadMark(2.0, LaneRoadMark::RoadMarkType::BROKEN, LaneRoadMark::RoadMarkWeight::STANDARD,
    LaneRoadMark::RoadMarkColor::RED,LaneRoadMark::RoadMarkMaterial::STANDARD_MATERIAL, LaneRoadMark::RoadMarkLaneChange::BOTH, 4.0, 2.0);

    lane.AddLink(lanelink);
    lane.AddLaneWidth(lanewidth);
    lane.AddLaneRoadMark(laneroadmark);

    ASSERT_EQ(lane.GetNumberOfLinks(), 1);
    ASSERT_EQ(lane.GetNumberOfLaneWidths(), 1);
    ASSERT_EQ(lane.GetNumberOfRoadMarks(), 1);

    delete lanelink;
    delete lanewidth;
    delete laneroadmark;
}

TEST_F(LaneTestFixture, TestLaneGetLink)
{
    LaneLink *lanelink = new LaneLink(LinkType::SUCCESSOR, 3);
    lane.AddLink(lanelink);
    LaneLink *mylanelink = lane.GetLink(LinkType::PREDECESSOR);
    LaneLink *dummylink = 0;
    ASSERT_EQ(mylanelink, dummylink);
    LaneLink *mylanelink_second = lane.GetLink(LinkType::SUCCESSOR);
    ASSERT_EQ(mylanelink_second->GetType(), LinkType::SUCCESSOR);
    ASSERT_EQ(mylanelink_second->GetId(), 3);
    
    delete lanelink;
}

TEST_F(LaneTestFixture, TestLaneGetWidth)
{
    LaneWidth *lanewidth = new LaneWidth(2.0, 1.0, -2.0, 3.0, -4.0);
    LaneWidth *lanewidth_second = new LaneWidth(10.0, 2.0, -3.0, 4.0, -5.0);

    LaneWidth *dummywidth = 0;
    ASSERT_EQ(lane.GetWidthByS(0), dummywidth);
    ASSERT_EQ(lane.GetWidthByS(5), dummywidth);
    ASSERT_EQ(lane.GetWidthByS(10), dummywidth);

    lane.AddLaneWidth(lanewidth);
    lane.AddLaneWidth(lanewidth_second);

    ASSERT_THROW(lane.GetWidthByIndex(-1), std::runtime_error);
    ASSERT_THROW(lane.GetWidthByIndex(2), std::runtime_error);
    ASSERT_THROW(lane.GetWidthByIndex(3), std::runtime_error);

    LaneWidth *mylanewidth = lane.GetWidthByIndex(0);
    LaneWidth *mylanewidth_s = lane.GetWidthByS(1);
    ASSERT_EQ(mylanewidth->GetSOffset(), 2.0);
    ASSERT_EQ(mylanewidth->poly3_.GetA(), 1.0);
    ASSERT_EQ(mylanewidth->poly3_.GetB(), -2.0);
    ASSERT_EQ(mylanewidth->poly3_.GetC(), 3.0);
    ASSERT_EQ(mylanewidth->poly3_.GetD(), -4.0);
    ASSERT_EQ(mylanewidth->poly3_.GetPscale(), 1.0);
    ASSERT_EQ(mylanewidth_s->GetSOffset(), 2.0);
    ASSERT_EQ(mylanewidth_s->poly3_.GetA(), 1.0);
    ASSERT_EQ(mylanewidth_s->poly3_.GetB(), -2.0);
    ASSERT_EQ(mylanewidth_s->poly3_.GetC(), 3.0);
    ASSERT_EQ(mylanewidth_s->poly3_.GetD(), -4.0);
    ASSERT_EQ(mylanewidth_s->poly3_.GetPscale(), 1.0);

    LaneWidth *mylanewidth_second = lane.GetWidthByIndex(1);
    LaneWidth *mylanewidth_s_second = lane.GetWidthByS(5);
    ASSERT_EQ(mylanewidth_second->GetSOffset(), 10.0);
    ASSERT_EQ(mylanewidth_second->poly3_.GetA(), 2.0);
    ASSERT_EQ(mylanewidth_second->poly3_.GetB(), -3.0);
    ASSERT_EQ(mylanewidth_second->poly3_.GetC(), 4.0);
    ASSERT_EQ(mylanewidth_second->poly3_.GetD(), -5.0);
    ASSERT_EQ(mylanewidth_second->poly3_.GetPscale(), 1.0);
    ASSERT_EQ(mylanewidth_s_second->GetSOffset(), 2.0);
    ASSERT_EQ(mylanewidth_s_second->poly3_.GetA(), 1.0);
    ASSERT_EQ(mylanewidth_s_second->poly3_.GetB(), -2.0);
    ASSERT_EQ(mylanewidth_s_second->poly3_.GetC(), 3.0);
    ASSERT_EQ(mylanewidth_s_second->poly3_.GetD(), -4.0);
    ASSERT_EQ(mylanewidth_s_second->poly3_.GetPscale(), 1.0);

    LaneWidth *mylanewidth_s_final = lane.GetWidthByS(1000000);
    ASSERT_EQ(mylanewidth_s_final->GetSOffset(), 10.0);
    ASSERT_EQ(mylanewidth_s_final->poly3_.GetA(), 2.0);
    ASSERT_EQ(mylanewidth_s_final->poly3_.GetB(), -3.0);
    ASSERT_EQ(mylanewidth_s_final->poly3_.GetC(), 4.0);
    ASSERT_EQ(mylanewidth_s_final->poly3_.GetD(), -5.0);
    ASSERT_EQ(mylanewidth_s_final->poly3_.GetPscale(), 1.0);

    delete lanewidth;
    delete lanewidth_second;
}

TEST_F(LaneTestFixture, TestLaneGetRoadMark)
{
    LaneRoadMark *laneroadmark = new LaneRoadMark(2.0, LaneRoadMark::RoadMarkType::BROKEN, LaneRoadMark::RoadMarkWeight::STANDARD,
    LaneRoadMark::RoadMarkColor::RED,LaneRoadMark::RoadMarkMaterial::STANDARD_MATERIAL, LaneRoadMark::RoadMarkLaneChange::BOTH, 4.0, 2.0);
    lane.AddLaneRoadMark(laneroadmark);

    ASSERT_THROW(lane.GetLaneRoadMarkByIdx(-1), std::runtime_error);
    ASSERT_THROW(lane.GetLaneRoadMarkByIdx(1), std::runtime_error);
    ASSERT_THROW(lane.GetLaneRoadMarkByIdx(2), std::runtime_error);

    LaneRoadMark *mylaneroadmark = lane.GetLaneRoadMarkByIdx(0);
    ASSERT_EQ(mylaneroadmark->GetSOffset(), 2.0);
    ASSERT_EQ(mylaneroadmark->GetWidth(), 4.0);
    ASSERT_EQ(mylaneroadmark->GetHeight(), 2.0);
    ASSERT_EQ(mylaneroadmark->GetType(), LaneRoadMark::RoadMarkType::BROKEN);
    ASSERT_EQ(mylaneroadmark->GetWeight(), LaneRoadMark::RoadMarkWeight::STANDARD);
    ASSERT_EQ(mylaneroadmark->GetColor(), LaneRoadMark::RoadMarkColor::RED);
    ASSERT_EQ(mylaneroadmark->GetMaterial(), LaneRoadMark::RoadMarkMaterial::STANDARD_MATERIAL);
    ASSERT_EQ(mylaneroadmark->GetLaneChange(), LaneRoadMark::RoadMarkLaneChange::BOTH);

    delete laneroadmark;
}

/*
TODO: The test for Lane::GetRoadMarkInfoByS.
*/

TEST_F(LaneTestFixture, TestLaneGetOSIPoints)
{
    OSIPoints *osi_points = lane.GetOSIPoints();
    ASSERT_EQ(osi_points->GetS().size(), 0);
    ASSERT_EQ(osi_points->GetX().size(), 0);
    ASSERT_EQ(osi_points->GetY().size(), 0);
    ASSERT_EQ(osi_points->GetZ().size(), 0);
    ASSERT_EQ(osi_points->GetH().size(), 0);

    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};
    lane.osi_points_.Set(s, x, y, z, h);

    OSIPoints *osi_points_second = lane.GetOSIPoints();
    ASSERT_EQ(osi_points->GetS().size(), 3);
    ASSERT_EQ(osi_points->GetX().size(), 3);
    ASSERT_EQ(osi_points->GetY().size(), 3);
    ASSERT_EQ(osi_points->GetZ().size(), 3);
    ASSERT_EQ(osi_points->GetH().size(), 3);

    ASSERT_EQ(osi_points->GetS()[0], 0);
    ASSERT_EQ(osi_points->GetS()[1], -1);
    ASSERT_EQ(osi_points->GetS()[2], 2);
}

TEST_F(LaneTestFixture, TestLaneGetLineGlobalIds)
{
    LaneRoadMark *laneroadmark = new LaneRoadMark(0, LaneRoadMark::RoadMarkType::BROKEN, LaneRoadMark::RoadMarkWeight::STANDARD,
    LaneRoadMark::RoadMarkColor::STANDARD_COLOR, LaneRoadMark::RoadMarkMaterial::STANDARD_MATERIAL, LaneRoadMark::RoadMarkLaneChange::BOTH,
    1.0, 1.0);
    LaneRoadMark *laneroadmark_second = new LaneRoadMark(50, LaneRoadMark::RoadMarkType::BROKEN, LaneRoadMark::RoadMarkWeight::STANDARD,
    LaneRoadMark::RoadMarkColor::STANDARD_COLOR, LaneRoadMark::RoadMarkMaterial::STANDARD_MATERIAL, LaneRoadMark::RoadMarkLaneChange::BOTH,
    2.0, 2.0);

    LaneRoadMarkType *laneroadmarktype = new LaneRoadMarkType("type1", 1.0);
    LaneRoadMarkType *laneroadmarktype_second = new LaneRoadMarkType("type2", 1.0);
    
    LaneRoadMarkTypeLine *laneRoadMarktypeline = new LaneRoadMarkTypeLine(3.0, 1.0, 0.5, 0.0, LaneRoadMarkTypeLine::RoadMarkTypeLineRule::CAUTION, 1.0);
    LaneRoadMarkTypeLine *laneRoadMarktypeline_second = new LaneRoadMarkTypeLine(3.0, 1.0, 0.5, 50.0, LaneRoadMarkTypeLine::RoadMarkTypeLineRule::CAUTION, 1.0);

    laneroadmark->AddType(laneroadmarktype);
    laneroadmark->AddType(laneroadmarktype_second);

    laneroadmarktype->AddLine(laneRoadMarktypeline);
    laneroadmarktype->AddLine(laneRoadMarktypeline_second);
    laneroadmarktype_second->AddLine(laneRoadMarktypeline_second);

    lane.AddLaneRoadMark(laneroadmark);
    lane.AddLaneRoadMark(laneroadmark_second);

    OpenDrive *odr = new OpenDrive();
    odr->InitGlobalLaneIds();
    laneRoadMarktypeline->SetGlobalId();
    laneRoadMarktypeline_second->SetGlobalId();

    std::vector<int> all_glob_ids = lane.GetLineGlobalIds();

    ASSERT_THAT(all_glob_ids.size(),3);
    ASSERT_THAT(laneroadmarktype->GetLaneRoadMarkTypeLineByIdx(0)->GetGlobalId(), 0);
    ASSERT_THAT(laneroadmarktype->GetLaneRoadMarkTypeLineByIdx(1)->GetGlobalId(), 1);
    ASSERT_THAT(laneroadmarktype_second->GetLaneRoadMarkTypeLineByIdx(0)->GetGlobalId(), 1);

    delete odr;
    delete laneroadmark;
    delete laneroadmark_second;

    delete laneroadmarktype;
    delete laneroadmarktype_second;

    delete laneRoadMarktypeline;
    delete laneRoadMarktypeline_second;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}