//
// gfx/vertex_batcher.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_VERTEX_BATCHER_H
#define BE_VERTEX_BATCHER_H

#include <vector>
#include <OpenGL/gl3.h>
#include <BarelyGL/gl.h>

namespace BarelyEngine {
class RenderElement;
class Texture;

/**
 * @class VertexBatcher
 * @brief Class that batches drawing vertices from the same texture
 */
class VertexBatcher
{
public:
  /**
   * @brief Construct a new VertexBatcher with the specifed attributes and
   *        maximum number of vertices
   *
   * The attributes specify how properties of each vertex are organised. The
   * VertexAttribute vector we pass in here simply lists the size of the blocks
   * of properties for every vertex in this batcher. For example, if the vertex
   * was like:
   *    10, 20, 0, 1, 0 (which describes [x, y, z], [u, v])
   * then it is 2 blocks (one of size 3 and one of size 2).
   *
   * @param draw_mode the mode used to draw vertices (GL_TRIANGLES usually)
   * @param attributes the vertex attributes to be used when drawing vertices
   * @param max_vertices the maxium number of vertices to draw at once
   */
  VertexBatcher(GLuint draw_mode, BarelyGL::VertexAttributeArray attributes, int max_vertices);

  /**
   * @brief Setup the batcher to being receiving vertices
   */
  void begin();

  /**
   * @brief Add a render element to the batch to be drawn (containing all the
   * vertices that need to be drawn)
   *
   * @param render_element the element to be drawn
   */
  void draw(const RenderElement* render_element);

  /**
   * @brief End the batcher and flush the remaining draw calls
   */
  void end();

  /**
   * @brief Get the number of draw calls per frame
   *
   * @return the number of times an OpenGL draw was performed between `begin` and
   * `end`
   */
  int draw_count() const { return draw_count_; }

private:
  /**
   * @brief Checks whether the current set of vertices needs to be drawn before
   * adding a new set of vertices to the batch
   *
   * @param render_element the element which may need to cause a flush
   *
   * @return a bool indicating if a flush is needed
   */
  bool needs_flush(const RenderElement* render_element) const;

  /**
   * @brief Flush the current set of vertices and draw them
   */
  void flush();

  /// The mode to draw the vertices with
  GLuint draw_mode_;
  /// The attributes to use when drawing the vertices
  BarelyGL::VertexAttributeArray attributes_;
  /// The vertex buffer object to be used for the vertices
  BarelyGL::VertexBufferObject vbo_{GL_ARRAY_BUFFER, GL_STATIC_DRAW};
  /// The index buffer object to be used with the VBO (currently unused)
  BarelyGL::IndexBufferObject ibo_{GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW};
  /// The maximum size of the vertices array
  size_t max_size_ = 0;
  /// The array of vertices to be drawn at once
  std::vector<float> vertices_;
  /// The indices into the vertex array
  std::vector<int> indices_;
  /// The last texture that was bound (to avoid binding needlessly)
  const Texture* last_bound_texture_ = nullptr;
  /// The current element being drawn (or just drawn)
  const RenderElement* current_element_ = nullptr;
  /// The number of times an OpenGL draw was performed
  int draw_count_ = 0;
};
} // end of namespace BarelyEngine

#endif // defined(BE_VERTEX_BATCHER_H)
