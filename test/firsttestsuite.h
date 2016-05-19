#ifndef FIRSTTESTSUITE_H
#define FIRSTTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include "../src/myclass.h"

class FirstTestSuite : public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        TS_ASSERT(1 + 1 > 1);
        TS_ASSERT_EQUALS(testObj.addition(1,1), 2);
    }

    MyClass testObj;
};


#endif // FIRSTTESTSUITE_H
