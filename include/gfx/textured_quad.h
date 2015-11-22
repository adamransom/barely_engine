//
// gfx/textured_quad.h
// Copyright (c) 2015 Adam Ransom
//

#ifndef BE_TEXTURED_QUAD_H
#define BE_TEXTURED_QUAD_H

#include <vector>
#include <BarelyGL/vertex_attribute.h>
#include "render_element.h"
#include "color.h"

namespace BarelyEngine {
class Texture;

/**
 * @class TexturedQuad
 * @brief An element to be placed on the rendering queue and then processed by a
 *        batcher.
 *
 * This is the underlying component of everything that is drawn onscreen. It
 * contains the vertices to be drawn and the corresponding texture.
 */
class TexturedQuad : public RenderElement
{
public:
  /**
   * @brief Create a new TexturedQuad to be placed on the queue
   *
   * @param x the x position of the element
   * @param y the y position of the element
   * @param w the width of the element
   * @param h the height of the element
   * @param layer the layer to be drawn onto (0 is back/bottom)
   * @param depth the depth to be drawn onto (0 is back/bottom)
   * @param attributes the vertex attributes describing the vertices
   * @param texture the texture to be used when rendering the vertices
   */
  TexturedQuad(float x, float y, float w, float h, uint8_t layer, uint8_t depth,
               const Texture* texture);

  /**
   * @brief Create a new TexturedQuad to be placed on the queue
   *
   * @param x the x position of the element
   * @param y the y position of the element
   * @param w the width of the element
   * @param h the height of the element
   * @param layer the layer to be drawn onto (0 is back/bottom)
   * @param depth the depth to be drawn onto (0 is back/bottom)
   * @param attributes the vertex attributes describing the vertices
   * @param texture the texture to be used when rendering the vertices
   * @param color the color to tint the texture with
   */
  TexturedQuad(float x, float y, float w, float h, uint8_t layer, uint8_t depth,
               const Texture* texture, Color color);

  /**
   * @brief Create a new TexturedQuad to be placed on the queue
   *
   * @param x the x position of the element
   * @param y the y position of the element
   * @param w the width of the element
   * @param h the height of the element
   * @param clip_x the x position inside of the texture
   * @param clip_y the y position inside of the texture
   * @param clip_w the width of the clip inside the texture
   * @param clip_h the height of the clip inside the texture
   * @param layer the layer to be drawn onto (0 is back/bottom)
   * @param depth the depth to be drawn onto (0 is back/bottom)
   * @param attributes the vertex attributes describing the vertices
   * @param texture the texture to be used when rendering the vertices
   */
  TexturedQuad(float x, float y, float w, float h, int clip_x, int clip_y, int clip_w, int clip_h,
               uint8_t layer, uint8_t depth, const Texture* texture);

  /**
   * @brief Create a new TexturedQuad to be placed on the queue
   *
   * @param x the x position of the element
   * @param y the y position of the element
   * @param w the width of the element
   * @param h the height of the element
   * @param clip_x the x position inside of the texture
   * @param clip_y the y position inside of the texture
   * @param clip_w the width of the clip inside the texture
   * @param clip_h the height of the clip inside the texture
   * @param layer the layer to be drawn onto (0 is back/bottom)
   * @param depth the depth to be drawn onto (0 is back/bottom)
   * @param attributes the vertex attributes describing the vertices
   * @param texture the texture to be used when rendering the vertices
   * @param color the color to tint the texture with
   */
  TexturedQuad(float x, float y, float w, float h, int clip_x, int clip_y, int clip_w, int clip_h,
               uint8_t layer, uint8_t depth, const Texture* texture, Color color);

private:
  /// This assumes we are always drawing rectangles made of 2 triangles
  static const int kVerticesPerElement_ = 6;
  static const BarelyGL::VertexAttributeArray kAttributes_;
};
} // end of namespace BarelyEngine

#endif // defined(BE_TEXTURED_QUAD_H)
