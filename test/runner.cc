/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_FirstTestSuite_init = false;
#include "/home/acce/datagrabber_laskenta/test/firsttestsuite.h"

static FirstTestSuite suite_FirstTestSuite;

static CxxTest::List Tests_FirstTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FirstTestSuite( "firsttestsuite.h", 7, "FirstTestSuite", suite_FirstTestSuite, Tests_FirstTestSuite );

static class TestDescription_suite_FirstTestSuite_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FirstTestSuite_testAddition() : CxxTest::RealTestDescription( Tests_FirstTestSuite, suiteDescription_FirstTestSuite, 10, "testAddition" ) {}
 void runTest() { suite_FirstTestSuite.testAddition(); }
} testDescription_suite_FirstTestSuite_testAddition;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
