#pragma once
#include "PackHelper.h"

namespace bondage
{

class Function
  {
public:
  typedef bondage::Builder::Call Call;
  typedef bondage::Builder::CanCall CanCall;

  Function(const char *name, Call fn, bool st)
      : m_name(name),
        m_function(fn),
        m_static(st)
    {
    REFLECT_ASSERT(m_function);
    }

  Call getCallFunction() const
    {
    return m_function;
    }

  bool isStatic() const
    {
    return m_static;
    }

  const std::string &name() const { return m_name; }

private:
  std::string m_name;
  Call m_function;
  bool m_static;
  };

class FunctionCaller : public bondage::Builder
  {
public:
  typedef Function::Call Result;
  typedef Function::CanCall CanCallResult;

  template <typename T> struct Helper
    {
    typedef typename T::Helper WrappedHelper;
    typedef typename WrappedHelper::ArgumentCount ArgumentCount;
    typedef typename WrappedHelper::Static Static;
    };

  template <typename Function, typename Builder> static Result buildWrappedCall()
    {
    return wrapCall<Function, Builder>;
    }

  template <typename Function, typename Builder> static CanCallResult buildWrappedCanCall()
    {
    return wrapCanCall<Function, Builder>;
    }
  };

}
