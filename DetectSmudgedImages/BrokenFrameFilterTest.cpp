#include "BrokenFrameFilterTest.h"

#include "BrokenFrameFilter.h"

BrokenFrameFilterTest::BrokenFrameFilterTest()
{
}

BrokenFrameFilterTest::~BrokenFrameFilterTest()
{
}

void BrokenFrameFilterTest::setUp(void)
{
}

void BrokenFrameFilterTest::tearDown(void)
{
}

void BrokenFrameFilterTest::testBrokenImage()
{
  BrokenFrameFilter filter;
  CPPUNIT_ASSERT(!filter.filter("broken/frame1.jpg"));
}

void BrokenFrameFilterTest::testValidImage()
{
  BrokenFrameFilter filter;
  CPPUNIT_ASSERT(filter.filter("valid/frame1.jpg"));
}
