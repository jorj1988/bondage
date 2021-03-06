#pragma once
#include <cstddef>

#define GEN_EXPORT

namespace Gen
{

/// \brief A CLASS!
///
/// \expose derivable managed
class GenCls
{
public:
  virtual ~GenCls() { }

  /// \brief This funciton is a test
  /// \param myint This is an int!
  /// \param myFloat This is a float.
  void test1(int myint, float myFloat, double)
    {
    (void)myint;
    (void)myFloat;
    }

  void test2(int, float = 2.0f, double = 4.0)
    {
    }

  static void test3(bool)
    {
    }

  static int test3(bool, int, bool = false)
    {
    return 5;
    }

  static int test3(float, float)
    {
    return 5;
    }
};

/// \expose
inline int test4(bool a, bool b)
  {
  (void)a;
  (void)b;
  return 3;
  }
  
/// \expose
inline int test5(bool a, bool b, float = 4.3f)
  {
  (void)a;
  (void)b;
  return 1;
  }

/// \expose
class InheritTest : public GenCls
{
public:
  void pork()
    {
    }

  int pork2()
    {
    return 0;
    }
};

/// \expose
class InheritTest2 : public InheritTest
{
public:
  /// \expose
  enum MyEnum
  {
    test,
    test2 = 2,
    test3 = 3,
  };
};

/// \expose
class MultipleReturnGen
{
public:
  /// \brief test
  /// \param[out] a test param
  /// \param[in,out] b test param
  void test(int *a = nullptr, MultipleReturnGen *gen = nullptr)
    {
    *a = 3;
    (void)gen;
    }

  /// \brief test again
  /// \param[in] a test
  /// \param[in,out] b test2
  /// \param[out] c test3
  double test(const int &a, MultipleReturnGen &b, const int &c)
    {
    (void)a;
    (void)b;
    (void)c;
    return 2.3;
    }
};

/// \expose
class CtorGen
{
public:
  CtorGen()
    {
    }

  /// \param[out] i an Output
  CtorGen(int *i)
    {
    (void)i;
    }
};

  /// \expose
enum GlbEnum
{
  A,
  B
};

}
