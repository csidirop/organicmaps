#include "testing/testing.hpp"

#include "routing/routing_callbacks.hpp"
#include "routing/routing_options.hpp"

#include "routing/routing_integration_tests/routing_test_tools.hpp"

#include "geometry/mercator.hpp"

#include <limits>

namespace route_test
{
using namespace routing;
using namespace std;

  UNIT_TEST(StrangeCaseInAfrica)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(19.20789, 30.50663), {0., 0.},
        mercator::FromLatLon(19.17289, 30.47315), 7645.0);
  }

  UNIT_TEST(MoscowKashirskoeShosseCrossing)
  {
    // OSRM agrees here: https://www.openstreetmap.org/directions?engine=fossgis_osrm_car&route=55.66216%2C37.63259%3B55.66237%2C37.63560
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.66216, 37.63259), {0., 0.},
        mercator::FromLatLon(55.66237, 37.63560), 2877.81);
  }

  UNIT_TEST(MoscowToSVOAirport)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.75100, 37.61790), {0.0, 0.0},
        mercator::FromLatLon(55.97310, 37.41460), 37284.0);
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.97310, 37.41460), {0.0, 0.0},
        mercator::FromLatLon(55.75100, 37.61790), 39129.8);
  }

  // Restrictions tests. Check restrictions generation, if there are any errors.
  UNIT_TEST(RestrictionTestNeatBaumanAndTTK)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.77398, 37.68469), {0., 0.},
        mercator::FromLatLon(55.77201, 37.68789), 1032.);
  }

  UNIT_TEST(RestrictionTestNearMetroShodnenskaya)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.85043, 37.43824), {0., 0.},
        mercator::FromLatLon(55.85191, 37.43910), 510.);
  }

  // Strange asserts near Cupertino test
  UNIT_TEST(CaliforniaCupertinoFindPhantomAssertTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(37.33409, -122.03458), {0., 0.},
        mercator::FromLatLon(37.33498, -122.03575), 1438.);
  }

  // Path in the last map through the other map.
  UNIT_TEST(RussiaUfaToUstKatavTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car), mercator::FromLatLon(54.7304, 55.9554), {0., 0.}, mercator::FromLatLon(54.9228, 58.1469), 164667.);
  }

  UNIT_TEST(RussiaMoscowNoServiceCrossing)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.77787, 37.70405), {0., 0.},
        mercator::FromLatLon(55.77682, 37.70391), 3140.);
  }

  UNIT_TEST(RussiaMoscowShortWayToService)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.77787, 37.70405), {0., 0.},
        mercator::FromLatLon(55.77691, 37.70428), 171.);
  }

  UNIT_TEST(PriceIslandLoadCrossGeometryTest)
  {
    size_t constexpr kExpectedPointsNumber = 56;
    // Forward
    TRouteResult route =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(46.16255, -63.81643), {0., 0.},
                                    mercator::FromLatLon(46.25401, -63.70213));
    TEST_EQUAL(route.second, RouterResultCode::NoError, ());
    CHECK(route.first, ());
    integration::TestRoutePointsNumber(*route.first, kExpectedPointsNumber);
    // And backward case
    route = integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                        mercator::FromLatLon(46.25401, -63.70213), {0., 0.},
                                        mercator::FromLatLon(46.16255, -63.81643));
    TEST_EQUAL(route.second, RouterResultCode::NoError, ());
    CHECK(route.first, ());
    integration::TestRoutePointsNumber(*route.first, kExpectedPointsNumber);
  }

  // Cross mwm tests.
  UNIT_TEST(RussiaMoscowLeningradskiy39GerPanfilovtsev22RouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        {37.53758809983519, 67.536162466434234}, {0., 0.}, {37.40993977728661, 67.644784047393685},
        14296.);
  }

  UNIT_TEST(NederlandLeeuwardenToDenOeverTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car), mercator::FromLatLon(53.2076, 5.7082), {0., 0.}, mercator::FromLatLon(52.9337, 5.0308), 59500.);
  }

  UNIT_TEST(RussiaMoscowGerPanfilovtsev22SolodchaPravdiRouteTest)
  {
    // OSRM agrees here to use motorways instead of city roads.
    // https://www.openstreetmap.org/directions?engine=fossgis_osrm_car&route=55.858%2C37.410%3B54.794%2C39.837
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.85792, 37.40992), {0., 0.},
        mercator::FromLatLon(54.79390, 39.83656), 263920.);
  }

  UNIT_TEST(RussiaMoscowBelarusMinsk)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.750650, 37.617673), {0., 0.},
        mercator::FromLatLon(53.902114, 27.562020), 712649.0);
  }

  UNIT_TEST(UKRugbyStIvesRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(52.37076, -1.26530), {0., 0.},
        mercator::FromLatLon(50.21480, -5.47994), 455902.);
  }

  UNIT_TEST(RussiaMoscow_ItalySienaCenter_SplittedMotorway)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.79690, 37.53759), {0., 0.},
        mercator::FromLatLon(43.32677, 11.32792), 2870710.);
  }

  UNIT_TEST(PeruSingleRoadTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(-14.22061, -73.35969), {0., 0.},
        mercator::FromLatLon(-14.22389, -73.44281), 15900.);
  }

  UNIT_TEST(RussiaMoscowFranceParisCenterRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.75271, 37.62618), {0., 0.}, mercator::FromLatLon(48.86123, 2.34129), 2840940.);
  }

  UNIT_TEST(EnglandToFranceRouteLeMansTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(51.09276, 1.11369), {0., 0.}, mercator::FromLatLon(50.93227, 1.82725), 64755.6);
  }

  UNIT_TEST(RussiaMoscowStartAtTwowayFeatureTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car), mercator::FromLatLon(55.771, 37.5184), {0., 0.}, mercator::FromLatLon(55.7718, 37.5178), 147.4);
  }

  UNIT_TEST(RussiaMoscowRegionToBelarusBorder)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.464182, 35.943947), {0.0, 0.0},
        mercator::FromLatLon(52.442467, 31.609642), 554000.);
  }

  UNIT_TEST(GermanyToTallinCrossMwmRoute)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(48.397416, 16.515289), {0.0, 0.0},
        mercator::FromLatLon(59.437214, 24.745355), 1650000.);
  }

  // Strange map edits in Africa borders. Routing not linked now.
  /*
  UNIT_TEST(RussiaMoscowLenigradskiy39RepublicOfSouthAfricaCapeTownCenterRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.79721, 37.53786), {0., 0.},
              mercator::FromLatLon(-33.9286, 18.41837), 13701400.0);
  }
  */

  UNIT_TEST(MoroccoToSahrawiCrossMwmTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(27.15587, -13.23059), {0., 0.},
        mercator::FromLatLon(27.94049, -12.88800), 100864);
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(27.94049, -12.88800), {0., 0.},
        mercator::FromLatLon(27.15587, -13.23059), 100864);
  }

  UNIT_TEST(AlbaniaToMontenegroCrossTest)
  {
    // Road from Albania to Montenegro. Test turnaround finding at border (when start/stop
    // points are inside borders and one of segments has outside points).
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(42.01535, 19.40044), {0., 0.},
        mercator::FromLatLon(42.01201, 19.36286), 3674.);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(42.01201, 19.36286), {0., 0.},
        mercator::FromLatLon(42.01535, 19.40044), 3674.);
  }

  UNIT_TEST(CanadaBridgeCrossToEdwardIsland)
  {
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(46.13418, -63.84656), {0., 0.},
        mercator::FromLatLon(46.26739, -63.63907), 23000.);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(46.26739, -63.63907), {0., 0.},
        mercator::FromLatLon(46.13418, -63.84656), 23000.);
  }

  UNIT_TEST(ParisCrossDestinationInForwardHeapCase)
  {
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(49.85015, 2.24296), {0., 0.}, mercator::FromLatLon(48.85458, 2.36291), 127162.0);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(48.85458, 2.36291), {0., 0.}, mercator::FromLatLon(49.85027, 2.24283), 137009.0);
  }

  UNIT_TEST(RussiaSmolenskRussiaMoscowTimeTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(54.7998, 32.05489), {0., 0.}, mercator::FromLatLon(55.753, 37.60169));

    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    integration::TestRouteTime(route, 18045.9);
  }

  UNIT_TEST(RussiaMoscowLenigradskiy39GeroevPanfilovtsev22TimeTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.7971, 37.53804), {0., 0.}, mercator::FromLatLon(55.8579, 37.40990));
    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    integration::TestRouteTime(route, 1044.42);
  }

  UNIT_TEST(RussiaMoscowLenigradskiy39GeroevPanfilovtsev22SubrouteTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.7971, 37.53804), {0., 0.}, mercator::FromLatLon(55.8579, 37.40990));

    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    TEST_EQUAL(route.GetSubrouteCount(), 1, ());
    vector<RouteSegment> info;
    route.GetSubrouteInfo(0, info);
    TEST_EQUAL(route.GetPoly().GetSize(), info.size() + 1, ());
    size_t constexpr kExpectedPointsNumber = 335;
    integration::TestRoutePointsNumber(route, kExpectedPointsNumber);
  }

  UNIT_TEST(USALosAnglesAriaTwentyninePalmsHighwayTimeTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(34.0739, -115.3212), {0.0, 0.0},
                                    mercator::FromLatLon(34.0928, -115.5930));
    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());
    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    TEST_LESS(route.GetTotalTimeSec(), numeric_limits<double >::max() / 2.0, ());
  }

  // Test on routing along features with tag man_made:pier.
  UNIT_TEST(CanadaVictoriaVancouverTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(48.47831, -123.32749), {0.0, 0.0},
                                    mercator::FromLatLon(49.26242, -123.11553));
    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());
  }

  // Test on the route with the finish near zero length edge.
  UNIT_TEST(BelarusSlonimFinishNearZeroEdgeTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(53.08279, 25.30036), {0.0, 0.0},
                                    mercator::FromLatLon(53.09443, 25.34356));
    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());
  }

  // Test on the route with the start near zero length edge.
  UNIT_TEST(BelarusSlonimStartNearZeroEdgeTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(53.09422, 25.34411), {0.0, 0.0},
                                    mercator::FromLatLon(53.09271, 25.3467));
    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());
  }

  // Test on roads with tag maxspeed=none.
  UNIT_TEST(GermanyBerlinMunichTimeTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(52.51172, 13.39468), {0., 0.},
                                    mercator::FromLatLon(48.13294, 11.60352));

    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    integration::TestRouteTime(route, 19053.0);
  }

  // Test on roads with tag route=shuttle_train. This train has defined maxspeed=100.
  UNIT_TEST(GermanyShuttleTrainTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(54.78370, 8.83528), {0., 0.}, mercator::FromLatLon(54.91681, 8.31346));

    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    integration::TestRouteLength(route, 44116.7);
    integration::TestRouteTime(route, 2509.81);
  }

  UNIT_TEST(TolyattiFeatureThatCrossSeveralMwmsTest)
  {
    TRouteResult const routeResult =
      integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(52.67316, 48.22478), {0., 0.},
                                    mercator::FromLatLon(53.49143, 49.52386));

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;

    integration::TestRouteTime(route, 8102.0);
  }

  // Test on removing speed cameras from the route for maps from Jan 2019,
  // and on the absence of speed cameras in maps for later maps for Switzerland.
  UNIT_TEST(SwitzerlandNoSpeedCamerasInRouteTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car), mercator::FromLatLon(47.5194, 8.73093), {0., 0.}, mercator::FromLatLon(46.80592, 7.13724));

    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    auto const & routeSegments = route.GetRouteSegments();
    for (auto const & routeSegment : routeSegments)
    {
      TEST(routeSegment.GetSpeedCams().empty(),
           (routeSegment.GetSegment(), routeSegment.GetRoadNameInfo().m_name));
    }
  }

  // Test on warning about speed cameras for countries where speed cameras partly prohibited.
  UNIT_TEST(GermanyWarningAboutSpeedCamerasTest)
  {
    TRouteResult const routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(52.38465, 13.41906), {0., 0.},
                                    mercator::FromLatLon(52.67564, 13.27453));

    RouterResultCode const result = routeResult.second;
    TEST_EQUAL(result, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *routeResult.first;
    TEST(route.CrossMwmsPartlyProhibitedForSpeedCams(), ());
  }

  // TODO (@gmoryes) uncomment this after many-via restrictions will be in mwms.
/*
  UNIT_TEST(SpainRestirctionOnlyMany)
  {
    integration::CalculateRouteAndTestRouteLength(
      integration::GetVehicleComponents(VehicleType::Car),
      mercator::FromLatLon(43.38234, -5.67648), {0.0, 0.0},
      mercator::FromLatLon(43.38222, -5.69083), 8289.0);
  }

  UNIT_TEST(RussiaMoscowRestirctionOnlyMany)
  {
    integration::CalculateRouteAndTestRouteLength(
      integration::GetVehicleComponents(VehicleType::Car),
      mercator::FromLatLon(55.991578, 37.212476), {0.0, 0.0},
      mercator::FromLatLon(55.991845, 37.215312), 799.0);
  }
*/

  // Test that fake segments are not built from start to roads with hwtag=nocar for car routing.
  UNIT_TEST(SpainBilbaoAirportNoCarTest)
  {
    TRouteResult routeResult =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(43.29969, -2.91312), {0., 0.},
                                    mercator::FromLatLon(43.29904, -2.9108));
    TEST_EQUAL(routeResult.second, RouterResultCode::NoError, ());

    CHECK(routeResult.first, ());
    Route const & route = *(routeResult.first);
    std::vector<RouteSegment> const & routeSegments = route.GetRouteSegments();
    TEST_GREATER(routeSegments.size(), 2, ());

    // Note. routeSegments[0] is a start segment(point). routeSegments[1] is a fake segment
    // which goes from the route start to a segment of the road graph.
    // routeSegments[1].GetDistFromBeginningMeters() is the length of the first fake segment.
    // Start point is located near a road with hwtag=no.
    // So if routeSegments[1].GetDistFromBeginningMeters() is long enough the segment
    // with hwtag=no is no used.
    TEST_GREATER(routeSegments[1].GetDistFromBeginningMeters(), 20.0, ());
  }

  // Test when start is located near mwm border. In that case it's possible that one of
  // closest edges is a dead end within one mwm. The end of this dead end should
  // be taken into account in |IndexGraphStarterJoints<Graph>::FindFirstJoints()|.
  UNIT_TEST(EnglandLondonStartNearMwmBorderTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(51.603582, 0.266995), {0., 0.},
        mercator::FromLatLon(51.606785, 0.264055), 416.8);
  }

  // Test that toll road is not crossed by a fake edge if RouingOptions are set to Road::Toll.
  // Test on necessity calling RectCoversPolyline() after DataSource::ForEachInRect() while looking for fake edges.
  UNIT_TEST(RussiaMoscowNotCrossingTollRoadTest)
  {
    auto & vehicleComponents = integration::GetVehicleComponents(VehicleType::Car);

    auto const start = mercator::FromLatLon(55.93934, 37.406);
    m2::PointD finish[] = { mercator::FromLatLon(55.9414245, 37.4489627), mercator::FromLatLon(55.9421391, 37.4484832) };

    {
      // Avoid motorway toll road and build route through minor residential roads (short but slow).
      RoutingOptionSetter optionsGuard(RoutingOptions::Road::Toll);

      // 1. End point is near the motorway toll road, but choose a minor track as end segment.
      integration::CalculateRouteAndTestRouteLength(vehicleComponents, start, {0.0, 0.0}, finish[0], 8427.71);

      // 2. End point is near the service road via the motorway toll road, but choose a minor track as end segment.
      integration::CalculateRouteAndTestRouteLength(vehicleComponents, start, {0.0, 0.0},finish[1], 8972.7);
    }

    {
      // Normal route via the motorway toll road (long but fast).
      integration::CalculateRouteAndTestRouteLength(vehicleComponents, start, {0.0, 0.0}, finish[0], 20604.9);
      integration::CalculateRouteAndTestRouteLength(vehicleComponents, start, {0.0, 0.0}, finish[1], 20689.6);
    }
  }

  UNIT_TEST(NoCrash_RioGrandeCosmopolis)
  {
    TRouteResult route =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(-32.17641, -52.16350), {0., 0.},
                                    mercator::FromLatLon(-22.64374, -47.19720));

    TEST_EQUAL(route.second, RouterResultCode::NoError, ());
  }

  UNIT_TEST(AreMwmsNear_HelsinkiPiter)
  {
    TRouteResult route =
        integration::CalculateRoute(integration::GetVehicleComponents(VehicleType::Car),
                                    mercator::FromLatLon(60.87083, 26.53612), {0., 0.},
                                    mercator::FromLatLon(60.95360, 28.53979));

    TEST_EQUAL(route.second, RouterResultCode::NoError, ());
  }

  // Test RussiaShorterFakeEdges1 and RussiaShorterFakeEdges2 are on reducing
  // |kSpeedOffroadKMpH| for car routing. This lets us make
  // fake edges shorter that prevent crossing lakes, forests and so on.
  UNIT_TEST(RussiaBlackLakeShorterFakeEdges1)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.62466, 39.71385), {0., 0.},
        mercator::FromLatLon(55.63114, 39.70979), 1469.54);
  }

  UNIT_TEST(RussiaShorterFakeEdges2)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.31103, 38.80954), {0., 0.}, mercator::FromLatLon(55.31155, 38.8217), 2489.8);
  }

  // https://github.com/organicmaps/organicmaps/issues/1788
  UNIT_TEST(Germany_ShortRouteWithPassThroughChanges)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(49.512076, 8.284476), {0., 0.},
        mercator::FromLatLon(49.523783, 8.288701), 2014.);
  }

  // https://github.com/organicmaps/organicmaps/issues/821
  UNIT_TEST(Ukraine_UmanOdessa)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(48.7498, 30.2203), {0., 0.},
        mercator::FromLatLon(46.4859, 30.6837), 265163.);
  }

  // https://github.com/organicmaps/organicmaps/issues/1736
  UNIT_TEST(Belgium_LiegeBrugge)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(50.645205, 5.573507), {0., 0.},
        mercator::FromLatLon(51.208479, 3.225558), 193436.);
  }

  // https://github.com/organicmaps/organicmaps/issues/1627
  UNIT_TEST(Spain_MadridSevilla)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(40.415322, -3.703517), {0., 0.},
        mercator::FromLatLon(37.388667, -5.995355), 528667.);
  }

  UNIT_TEST(Belarus_Lithuania_MinskVilnius)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(53.902837, 27.562144), {0., 0.},
        mercator::FromLatLon(54.686821, 25.283189), 183231.);
  }

  // https://github.com/organicmaps/organicmaps/issues/338
  UNIT_TEST(Russia_MendeleevoReutov)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(56.036866, 37.232630), {0., 0.},
        mercator::FromLatLon(55.762128, 37.856665), 66261.9);
  }

  // https://github.com/organicmaps/organicmaps/issues/1721
  UNIT_TEST(Austria_Croatia_SalzburgZagreb)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(47.795928, 13.047597), {0., 0.},
        mercator::FromLatLon(45.812822, 15.977049), 414275);
  }

  // https://github.com/organicmaps/organicmaps/issues/1071
  UNIT_TEST(Russia_MoscowDesnogorsk)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.715208, 37.396528), {0., 0.},
        mercator::FromLatLon(54.151853, 33.287128), 355887);
  }

  // https://github.com/organicmaps/organicmaps/issues/1271
  UNIT_TEST(USA_DontLeaveHighway)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(34.1801345, -118.885005), {0., 0.},
        mercator::FromLatLon(34.1767471, -118.869327), 1523);
  }

  // https://github.com/organicmaps/organicmaps/issues/2085
  UNIT_TEST(USA_NorthCarolina_CrossMWMs)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(35.6233244, -78.3917262), {0., 0.},
        mercator::FromLatLon(36.0081839, -81.5245347), 333425);
  }

  // https://github.com/organicmaps/organicmaps/issues/1565
  UNIT_TEST(Cyprus_NoUTurnFromFake)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(34.70639, 33.1184951), {0., 0.},
        mercator::FromLatLon(34.7065239, 33.1184222), 384.238);

    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(34.7068976, 33.1199084), {0., 0.},
        mercator::FromLatLon(34.7070505, 33.1198391), 670.077);
  }

  UNIT_TEST(Crimea_UseGravelTertiary)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(45.362591, 36.471533), {0., 0.},
        mercator::FromLatLon(45.475055, 36.341766), 18815.6);

    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(45.470764, 36.331289), {0., 0.},
        mercator::FromLatLon(45.424964, 36.080336), 55220.2);
  }

  // https://github.com/organicmaps/organicmaps/issues/2475
  UNIT_TEST(Spain_LinksJunction)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(38.8031, 0.0383), {0., 0.},
        mercator::FromLatLon(38.8228, 0.0357), 3479.63);
  }

  // https://github.com/organicmaps/organicmaps/issues/1773
  UNIT_TEST(Netherlands_CrossMwm_A15)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(51.847656, 4.089189), {0., 0.},
        mercator::FromLatLon(51.651632, 4.725924), 70596.3);
  }

  // https://github.com/organicmaps/organicmaps/issues/2494
  UNIT_TEST(Netherlands_CrossMwm_GoudaToApenheul)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(52.0181, 4.7111), {0., 0.},
        mercator::FromLatLon(52.2153, 5.9187), 103576);
  }

  // https://github.com/organicmaps/organicmaps/issues/2285
  UNIT_TEST(Hawaii_KeepH1)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(21.277841, -157.779314), {0., 0.},
        mercator::FromLatLon(21.296098, -157.823823), 5289.31);
  }

  // https://github.com/organicmaps/organicmaps/issues/1668
  UNIT_TEST(Russia_Moscow_KeepPrimary)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.7083688, 37.6213856), {0., 0.},
        mercator::FromLatLon(55.724623, 37.62588), 1921.88);
  }

  // https://github.com/organicmaps/organicmaps/issues/1727
  // https://github.com/organicmaps/organicmaps/issues/2020
  // https://github.com/organicmaps/organicmaps/issues/2057
  UNIT_TEST(DontUseLinksWhenRidingOnMotorway)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(32.16881, 34.90656), {0., 0.},
        mercator::FromLatLon(32.1588823, 34.9330855), 2847.33);

    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(43.587808, 1.495385), {0., 0.},
        mercator::FromLatLon(43.600145, 1.490489), 1457.16);

    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(34.0175371, -84.3272339), {0., 0.},
        mercator::FromLatLon(34.0298011, -84.3182477), 1609.76);
  }

  UNIT_TEST(Russia_UseDonMotorway)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(54.5775321, 38.2206224), {0., 0.},
        mercator::FromLatLon(49.9315563, 40.5529881), 608031);
  }

  UNIT_TEST(Germany_Italy_Malcesine)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(48.4101446, 11.5892265), {0., 0.},
        mercator::FromLatLon(45.7662964, 10.8111554), 427135);
  }

  // https://github.com/organicmaps/organicmaps/issues/3363
  UNIT_TEST(Belarus_UseP27_PastawyBraslaw)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetVehicleComponents(VehicleType::Car),
        mercator::FromLatLon(55.1187744, 26.8460319), {0., 0.},
        mercator::FromLatLon(55.6190911, 27.0938092), 86239.8);
  }
} // namespace route_test
