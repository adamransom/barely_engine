//
// exception.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_EXCEPTION_H
#define BE_EXCEPTION_H

#include <stdexcept>

using namespace std;

namespace BarelyEngine {
/**
 * @brief General exception used by the engine
 */
class Exception : public runtime_error
{
public:
  Exception(const string& what_arg) : runtime_error(what_arg) {};
};
} // end of namespace BarelyEngine

#endif // defined(BE_EXCEPTION_H)
