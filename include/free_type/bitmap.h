//
// free_type/bitmap.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FREE_TYPE_BITMAP_H
#define BE_FREE_TYPE_BITMAP_H

#include <memory>

typedef struct FT_Bitmap_ FT_Bitmap;

namespace BarelyEngine {
namespace FreeType {
class Library;
/**
 * @brief Wrapper around FT_Bitmap, implementing RAII
 */
class Bitmap
{
public:
  /**
   * @brief Construct a new bitmap object
   *
   * @param library pointer to the library used to create the bitmap
   */
  Bitmap(Library* library);
  ~Bitmap();

  /// Move construction & assignment operator
  Bitmap(Bitmap&& other);
  Bitmap& operator=(Bitmap&& other);

  /// Copy construction & assignment operator (deleted)
  Bitmap(const Bitmap& other) = delete;
  Bitmap& operator=(const Bitmap& other) = delete;

  /**
   * @brief Get the underlying FT_Bitmap pointer
   *
   * @return the underlying FT_Bitmap pointer
   */
  FT_Bitmap* get() const { return bitmap_.get(); }

  /**
   * @brief Get the number of rows in the bitmap
   *
   * @return the number of rows (the bitmaps height)
   */
  unsigned int rows() const;

  /**
   * @brief Get the width of the bitmap
   *
   * @return the width of the bitmap
   */
  unsigned int width() const;

  /**
   * @brief Get the pitch of the bitmap
   *
   * @return the pitch of the bitmap
   */
  int pitch() const;

  /**
   * @brief Get a pointer to the data buffer of the bitmap
   *
   * @return a pointer to the data buffer of the bitmap
   */
  unsigned char* buffer() const;

private:
  /// The underlying FT_Bitmap
  std::unique_ptr<FT_Bitmap> bitmap_;
  /// The library used to create & destroy the bitmap
  Library* library_;
};
} // end of namespace FreeType
} // end of namespace BarelyEngine

#endif // defined(BE_FREE_TYPE_BITMAP_H)
