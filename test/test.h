#pragma once
#include "test_2.h"

namespace Test
{
namespace Detail
{

// Test
class PORK Bar : private Foo
{
  Bar(int a);
  ~Bar();
  
  void test(const Test<Foo>& ) const;
};

}

}