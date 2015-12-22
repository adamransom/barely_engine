//
// gfx/render_element.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_RENDER_ELEMENT_H
#define BE_RENDER_ELEMENT_H

#include <vector>
#include <BarelyGL/vertex_attribute_array.h>
#include "texture.h"

namespace BarelyEngine {
/**
 * @class RenderElement
 * @brief An element to be placed on the rendering queue and then processed by a
 *        batcher.
 *
 * This is the underlying component of everything that is drawn onscreen. It
 * contains the vertices to be drawn and the corresponding texture. If you don't
 * provide a texture it can be used with only the vertices for use with GL_LINES etc.
 */
class RenderElement
{
public:
  /**
   * @brief Create a new RenderElement to be placed on the queue
   *
   * @param layer the layer to be drawn onto (0 is back/bottom)
   * @param depth the depth to be drawn onto (0 is back/bottom)
   * @param attributes the vertex attributes describing the vertices
   * @param texture the texture to be used when rendering the vertices
   */
  RenderElement(uint8_t layer, uint8_t depth, BarelyGL::VertexAttributeArray attributes, const Texture* texture = nullptr)
    : layer_(layer)
    , depth_(depth)
    , attributes_(std::move(attributes))
    , texture_(texture)
  {
    id_ = generate_id();
  }

  /**
   * @brief Create a new RenderElement to be placed on the queue
   *
   * @param vertices the vertices to be rendered
   * @param layer the layer to be drawn onto (0 is back/bottom)
   * @param depth the depth to be drawn onto (0 is back/bottom)
   * @param attributes the vertex attributes describing the vertices
   * @param texture the texture to be used when rendering the vertices
   */
  RenderElement(std::vector<float> vertices, uint8_t layer, uint8_t depth,
                BarelyGL::VertexAttributeArray attributes, const Texture* texture = nullptr)
    : vertices_(vertices)
    , layer_(layer)
    , depth_(depth)
    , attributes_(std::move(attributes))
    , texture_(texture)
  {
    id_ = generate_id();
  }

  bool operator<(const RenderElement& other) const { return id() < other.id(); }
  bool operator>(const RenderElement& other) const { return id() > other.id(); }

  /**
   * @brief Set the vertices for the element
   *
   * @param vertices array of floats to be used as vertices
   */
  void set_vertices(std::vector<float> vertices) { vertices_ = std::move(vertices); }

  /**
   * @brief Gets the ID for this element
   *
   * @returns a uint64_t representing the ID
   */
  uint64_t id() const { return id_; }

  /**
   * @brief Gets the vertices to be drawn
   *
   * @returns a vector of floats representing the vertices
   */
  const std::vector<float>& vertices() const { return vertices_; }

  /**
   * @brief Gets the layer for this element
   *
   * @returns a uint8_t representing the layer (0 is back/bottom)
   */
  uint8_t layer() const { return layer_; }

  /**
   * @brief Gets the depth for this element
   *
   * @returns a uint8_t representing the depth (0 is back/bottom)
   */
  uint8_t depth() const { return depth_; }

  /**
   * @brief Gets the texture to be used for drawing
   *
   * @returns the texture currently being used
   */
  const Texture* texture() const { return texture_; }

  /**
   * @brief Gets the vertex attributes describing the vertices
   *
   * @returns the vertex attributes describing the vertices
   */
  const BarelyGL::VertexAttributeArray& attributes() const { return attributes_; }

protected:
  /**
   * @brief Generates an ID based on the texture and layering, to be used when
   * sorting the draw calls

   * Groups the textures as follows:
   *      (8 bits)  layer   - could be a UI layer, background layer etc
   *      (8 bits)  depth   - the z-order depth within that layer
   *      (32 bits) texture - the ID of the texture
   *
   * @returns a uint64_t of the combined texture, layer and depth bits
   */
  virtual uint64_t generate_id() const
  {
    uint64_t texture_id = 0;

    if (texture_ != nullptr)
    {
      texture_id = texture_->id();
    }

    return uint64_t(layer_) << 56 | uint64_t(depth_) << 48 | texture_id;
  }

  /// The ID for this element
  uint64_t id_ = 0;

private:
  /// A list of vertices
  std::vector<float> vertices_;
  /// The layer this should be rendered on (0 is the back/bottom)
  uint8_t layer_ = 0;
  /// The depth this should be rendered at, within the layer (0 is the back/bottom)
  uint8_t depth_ = 0;
  /// The attributes describing the vertices
  BarelyGL::VertexAttributeArray attributes_;
  /// The texture to be used when rendering the vertices
  const Texture* texture_ = nullptr;
};
} // end of namespace BarelyEngine

#endif // defined(BE_RENDER_ELEMENT_H)
