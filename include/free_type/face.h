//
// free_type/face.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_FREE_TYPE_FACE_H
#define BE_FREE_TYPE_FACE_H

#include <string>

typedef struct FT_FaceRec_* FT_Face;
typedef struct FT_GlyphSlotRec_* FT_GlyphSlot;

namespace BarelyEngine {
namespace FreeType {
typedef int Error;
class Library;
/**
 * @brief Wrapper around FT_Face, implementing RAII
 */
class Face
{
public:
  /**
   * @brief Construct a new Face object
   *
   * @param library the library to use for face creation
   * @param path the path of the font file use to create the face
   *
   * @throws Exception if the face fails to be constructed
   */
  Face(const Library& library, std::string path);
  ~Face();

  /**
   * @brief Get the underlying FT_Face pointer
   *
   * @return the underlying FT_Face pointer
   */
  FT_Face get() const { return face_; }

  /**
   * @brief Get the glyph slot
   *
   * @return the glyph slot
   */
  FT_GlyphSlot glyph() const;

  /**
   * @brief Sets the size of the face
   *
   * Note: Call before `load_glyph()` or `render_glyph()`
   *
   * @param size the size in pixels
   */
  void set_size(int size);

  /**
   * @brief Loads the specified character into the face's glyph slot
   *
   * @param characte the character to load
   * @param render whether or not to also render the glyph to a bitmap
   */
  void load_glyph(char character, bool render = false);

  /**
   * @brief Renders the glyph as a bitmap to the face's glyph slot
   */
  void render_glyph();

private:
  /// The FT_LOAD_TARGET to use when loading (and rendering)
  static const int32_t load_target_;

  /// The underlying FT_Face pointer
  FT_Face face_;
  /// The path to the font file
  std::string path_;
};
} // end of namespace FreeType
} // end of namespace BarelyEngine

#endif // defined(BE_FREE_TYPE_FACE_H)
