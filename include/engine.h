//
// engine.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_ENGINE_H
#define BE_ENGINE_H

namespace BarelyEngine {
/**
 * @class Engine
 * @brief Simple engine-level functionality
 */
class Engine
{
public:
  /**
   * @brief Initialises various parts of the engine including SDL
   */
  static void init();
  
private:
};
} // end of namespace BarelyEngine

#endif // defined(ENGINE_H)
