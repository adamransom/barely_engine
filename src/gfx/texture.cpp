//
// texture.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "texture.h"

namespace BarelyEngine {
Texture::Texture(int width, int height, GLenum format, const void* pixels)
{
  texture_ = std::make_unique<GL::Texture>(width, height, format, pixels);
}

void Texture::bind() const
{
  texture_->bind();
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
