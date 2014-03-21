#pragma once
#include "Reflect/Type.h"
#include "Crate/Traits.h"
#include "bondage/Function.h"
#include "bondage/Boxer.h"

#define BONDAGE_ARRAY_COUNT(arr) (sizeof(arr)/sizeof(arr[0]))
#define BONDAGE_IMPLEMENT_EXPOSED_CLASS(lib, name, fns) bondage::WrappedClass class_##fns (lib, Reflect::findType<name>(), fns, BONDAGE_ARRAY_COUNT(fns))

namespace bondage
{

class Library;

class WrappedClass
  {
public:
  WrappedClass(Library &owningLib, const Reflect::Type *type, const Function *fn, std::size_t count);

  const Reflect::Type *type() const;

  const Function *functions() const;
  size_t functionCount();

private:
  const Reflect::Type *m_type;
  const Function *m_functions;
  size_t m_functionCount;
  };

template <typename T> class WrappedClassHelper
  {
public:
  typedef Crate::Traits<T> Traits;

  template <typename... Args> static T *create(Args &&... args)
    {
    return new T(std::forward<Args>(args)...);
    }
  };

}
