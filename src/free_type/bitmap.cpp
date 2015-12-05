//
// free_type/bitmap.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <ft2build.h>
#include FT_FREETYPE_H
#include <ftbitmap.h>
#include "bitmap.h"
#include "library.h"

namespace BarelyEngine {
namespace FreeType {
Bitmap::Bitmap(Library* library)
  : bitmap_(std::make_unique<FT_Bitmap>())
  , library_(library)
{
  FT_Bitmap_New(bitmap_.get());
}

Bitmap::~Bitmap()
{
  FT_Bitmap_Done(library_->get(), bitmap_.get());
}

Bitmap::Bitmap(Bitmap&& other)
  : bitmap_(std::move(other.bitmap_))
  , library_(other.library_)
{
}

Bitmap& Bitmap::operator=(Bitmap&& other)
{
  bitmap_ = std::move(other.bitmap_);
  library_ = other.library_;

  return *this;
}

unsigned int Bitmap::rows() const
{
  return bitmap_->rows;
}

unsigned int Bitmap::width() const
{
  return bitmap_->width;
}

int Bitmap::pitch() const
{
  return bitmap_->pitch;
}

unsigned char* Bitmap::buffer() const
{
  return bitmap_->buffer;
}
} // end of namespace FreeType
} // end of namespace BarelyEngine
