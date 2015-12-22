//
// gfx/vertex_batcher.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "vertex_batcher.h"
#include "render_element.h"
#include "texture.h"

namespace BarelyEngine {
VertexBatcher::VertexBatcher(const GLuint draw_mode,
                             const BarelyGL::VertexAttributeArray attributes,
                             const int max_vertices)
  : draw_mode_(draw_mode)
  , attributes_(std::move(attributes))
{
  max_size_ = attributes_.size() * max_vertices;
  vertices_.reserve(max_size_);

  /*
   * Set up state for the VAO
   */

  vao_.bind();
  // Create an empty buffer
  vbo_.bind();
  vbo_.init_buffer(max_size_);
  // Enable the vertex attributes for this buffer
  attributes_.enable();
  // Unbind the VBO and VAO so as not to overwrite the state by mistake
  vbo_.unbind();
  vao_.unbind();
}

/*
 * 'Draws' a RenderElement
 *
 * 1. Checks if the batcher needs to be flushed based on the new RenderElement.
 * 2. Sets the current properties from the new RenderElement.
 * 3. Adds the RenderElements vertices to the current collection
 *    vertices since the last flush.
 */
void VertexBatcher::draw(const RenderElement* render_element)
{
  if (needs_flush(render_element))
  {
    flush();
  }

  current_element_ = render_element;

  vertices_.insert(vertices_.end(), render_element->vertices().begin(),
                   render_element->vertices().end());
}

void VertexBatcher::begin()
{
  draw_count_ = 0;
}

void VertexBatcher::end()
{
  flush();
  current_element_ = nullptr;
  last_bound_texture_ = nullptr;
}

//
// =============================
//        Private Methods
// =============================
//

void VertexBatcher::flush()
{
  if (vertices_.size() > 0)
  {
    const auto texture = current_element_->texture();

    // Only bind the texture if the current element needs a different a texture
    // than the one that was bound last
    if (texture != nullptr && texture != last_bound_texture_)
    {
      if (last_bound_texture_ != nullptr) last_bound_texture_->unbind();

      texture->bind();
      last_bound_texture_ = texture;
    }

    // Update the vertices in the buffer
    vbo_.bind();
    vbo_.sub_vertices(vertices_);
    vbo_.unbind();

    // Draw using the saved state (buffer & attributes) of the VAO
    vao_.bind();
    vao_.draw(draw_mode_);
    vao_.unbind();

    vertices_.clear();
    draw_count_++;
  }
}

bool VertexBatcher::needs_flush(const RenderElement* render_element) const
{
  // If it's a new texture, we need to flush
  if (current_element_ != nullptr && current_element_->id() != render_element->id())
  {
    return true;
  }

  // If we have too many vertices in the batch, we need to flush
  if (vertices_.size() + render_element->vertices().size() > max_size_)
  {
    return true;
  }

  return false;
}
} // end of namespace BarelyEngine
