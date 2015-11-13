//
// texture.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_TEXTURE_H
#define BE_TEXTURE_H

#include <memory>
#include <OpenGL/gltypes.h>
#include <BarelyGL/texture.h>

namespace BarelyEngine {
/**
 * @class Texture
 * @brief Wrapper around GL::Texture
 */
class Texture
{
public:
  /**
  * @brief Construct a texture
  *
  * @param width width of the texture
  * @param height height of the texture
  * @param format pixel format of the texture
  * @param pixels raw pixel data of the texture
  */
  Texture(int width, int height, GLenum format, const void* pixels);

  /**
   * @brief Bind the texture for the next set of draw calls
   */
  void bind() const;

  /**
   * @brief Unbinds the texture
   */
  void unbind() const;

  /**
   * @brief Get the width of the texture
   *
   * @return an int representing the width
   */
  int width() const;

  /**
   * @brief Get the height of the texture
   *
   * @return an int representing the height
   */
  int height() const;

  /**
   * @brief Get the id of the texture
   *
   * @return an uint32_t representing the id
   */
  uint32_t id() const;

  Texture(const Texture& other) = delete;
  Texture& operator=(const Texture& other) = delete;

private:
  /// The underlying BarelyGL::Texture object
  std::unique_ptr<BarelyGL::Texture> texture_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_TEXTURE_H)
