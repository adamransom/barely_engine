//
// texture.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <OpenGL/gl3.h>
#include "texture.h"

namespace BarelyEngine {
Texture::Texture(const int width, const int height, const GLenum format,
                 const GLenum internal_format, const uint8_t unpack_alignment, const void* pixels)
{
  texture_ = std::make_unique<BarelyGL::Texture>(width, height, format, internal_format,
                                                 unpack_alignment, pixels);
}

// Construct and default to an unpack alignment of 4 bytes, which is the most usual
Texture::Texture(int width, int height, GLenum format, GLenum internal_format, const void* pixels)
  : Texture(width, height, format, internal_format, 4, pixels) {};

// Construct and default to an internal format of GL_RGBA8
Texture::Texture(int width, int height, GLenum format, const void* pixels)
  : Texture(width, height, format, GL_RGBA8, pixels) {};

void Texture::bind() const
{
  texture_->bind();
}

void Texture::sub_data(int x_offset, int y_offset, int width, int height, const void* data)
{
  texture_->sub_data(x_offset, y_offset, width, height, data);
}

void Texture::unbind() const
{
  texture_->unbind();
}

int Texture::width() const
{
  return texture_->width();
}

int Texture::height() const
{
  return texture_->height();
}

uint32_t Texture::id() const
{
  return texture_->id();
}
} // end of namespace BarelyEngine
