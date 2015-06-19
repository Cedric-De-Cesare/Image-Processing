#ifndef BROKENFRAMEFILTERTEST_H_
#define BROKENFRAMEFILTERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class BrokenFrameFilterTest : public CPPUNIT_NS :: TestFixture
{
  CPPUNIT_TEST_SUITE(BrokenFrameFilterTest);
  CPPUNIT_TEST(testBrokenImage);
  CPPUNIT_TEST(testValidImage);
  CPPUNIT_TEST_SUITE_END();
 public:
  BrokenFrameFilterTest();
  virtual ~BrokenFrameFilterTest();

  void setUp(void);
  void tearDown(void);

 protected:
  void testBrokenImage();
  void testValidImage();
};

#endif /* BROKENFRAMEFILTERTEST_H_ */
