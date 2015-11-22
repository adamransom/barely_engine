//
// gfx/textured_quad.cpp
// Copyright (c) 2015 Adam Ransom
//

#include "textured_quad.h"
#include "texture.h"

namespace BarelyEngine {
const BarelyGL::VertexAttributeArray TexturedQuad::kAttributes_ =
{
  BarelyGL::VertexAttribute::Position, BarelyGL::VertexAttribute::UV,
  BarelyGL::VertexAttribute::Color
};

TexturedQuad::TexturedQuad(const float x, const float y, const float w, const float h,
                           const uint8_t layer, const uint8_t depth, const Texture* texture)
  : TexturedQuad(x, y, w, h, layer, depth, texture, Color::White)
{
}

TexturedQuad::TexturedQuad(const float x, const float y, const float w, const float h,
                           const uint8_t layer, const uint8_t depth, const Texture* texture,
                           const Color color)
  : RenderElement(layer, depth, kAttributes_, texture)
{
  int values_per_vertex = 0;

  for (const auto attribute : attributes())
  {
    values_per_vertex += attribute.size;
  }

  std::vector<float> vertices(kVerticesPerElement_ * values_per_vertex);

  vertices[0] = x;                  // x position
  vertices[1] = y;                  // y position
  vertices[2] = 0;                  // z position
  vertices[3] = 0;                  // u coordinate
  vertices[4] = 0;                  // v coordinate
  vertices[5] = color.r() / 255.0f; // red tint component
  vertices[6] = color.g() / 255.0f; // green tint component
  vertices[7] = color.b() / 255.0f; // blue tint component

  vertices[8] = x + w;
  vertices[9] = y;
  vertices[10] = 0;
  vertices[11] = 1;
  vertices[12] = 0;
  vertices[13] = color.r() / 255.0f;
  vertices[14] = color.g() / 255.0f;
  vertices[15] = color.b() / 255.0f;

  vertices[16] = x;
  vertices[17] = y + h;
  vertices[18] = 0;
  vertices[19] = 0;
  vertices[20] = 1;
  vertices[21] = color.r() / 255.0f;
  vertices[22] = color.g() / 255.0f;
  vertices[23] = color.b() / 255.0f;

  vertices[24] = x + w;
  vertices[25] = y;
  vertices[26] = 0;
  vertices[27] = 1;
  vertices[28] = 0;
  vertices[29] = color.r() / 255.0f;
  vertices[30] = color.g() / 255.0f;
  vertices[31] = color.b() / 255.0f;

  vertices[32] = x;
  vertices[33] = y + h;
  vertices[34] = 0;
  vertices[35] = 0;
  vertices[36] = 1;
  vertices[37] = color.r() / 255.0f;
  vertices[38] = color.g() / 255.0f;
  vertices[39] = color.b() / 255.0f;

  vertices[40] = x + w;
  vertices[41] = y + h;
  vertices[42] = 0;
  vertices[43] = 1;
  vertices[44] = 1;
  vertices[45] = color.r() / 255.0f;
  vertices[46] = color.g() / 255.0f;
  vertices[47] = color.b() / 255.0f;

  set_vertices(vertices);
}

TexturedQuad::TexturedQuad(const float x, const float y, const float w, const float h,
                           const int clip_x, const int clip_y, const int clip_w, const int clip_h,
                           const uint8_t layer, const uint8_t depth, const Texture* texture)
  : TexturedQuad(x, y, w, h, clip_x, clip_y, clip_w, clip_h, layer, depth, texture, Color::White)
{
}

TexturedQuad::TexturedQuad(const float x, const float y, const float w, const float h,
                           const int clip_x, const int clip_y, const int clip_w, const int clip_h,
                           const uint8_t layer, const uint8_t depth, const Texture* texture,
                           const Color color)
  : RenderElement(layer, depth, kAttributes_, texture)
{
  const float texture_w = static_cast<float>(texture->width());
  const float texture_h = static_cast<float>(texture->height());

  int values_per_vertex = 0;

  for (const auto attribute : attributes())
  {
    values_per_vertex += attribute.size;
  }

  std::vector<float> vertices(kVerticesPerElement_ * values_per_vertex);

  vertices[0] = x;                  // x position
  vertices[1] = y;                  // y position
  vertices[2] = 0;                  // z position
  vertices[3] = clip_x / texture_w; // u coordinate
  vertices[4] = clip_y / texture_h; // v coordinate
  vertices[5] = color.r() / 255.0f; // red tint component
  vertices[6] = color.g() / 255.0f; // green tint component
  vertices[7] = color.b() / 255.0f; // blue tint component

  vertices[8] = x + w;
  vertices[9] = y;
  vertices[10] = 0;
  vertices[11] = (clip_x + clip_w) / texture_w;
  vertices[12] = clip_y / texture_h;
  vertices[13] = color.r() / 255.0f;
  vertices[14] = color.g() / 255.0f;
  vertices[15] = color.b() / 255.0f;

  vertices[16] = x;
  vertices[17] = y + h;
  vertices[18] = 0;
  vertices[19] = clip_x / texture_w;
  vertices[20] = (clip_y + clip_h) / texture_h;
  vertices[21] = color.r() / 255.0f;
  vertices[22] = color.g() / 255.0f;
  vertices[23] = color.b() / 255.0f;

  vertices[24] = x + w;
  vertices[25] = y;
  vertices[26] = 0;
  vertices[27] = (clip_x + clip_w) / texture_w;
  vertices[28] = clip_y / texture_h;
  vertices[29] = color.r() / 255.0f;
  vertices[30] = color.g() / 255.0f;
  vertices[31] = color.b() / 255.0f;

  vertices[32] = x;
  vertices[33] = y + h;
  vertices[34] = 0;
  vertices[35] = clip_x / texture_w;
  vertices[36] = (clip_y + clip_h) / texture_h;
  vertices[37] = color.r() / 255.0f;
  vertices[38] = color.g() / 255.0f;
  vertices[39] = color.b() / 255.0f;

  vertices[40] = x + w;
  vertices[41] = y + h;
  vertices[42] = 0;
  vertices[43] = (clip_x + clip_w) / texture_w;
  vertices[44] = (clip_y + clip_h) / texture_h;
  vertices[45] = color.r() / 255.0f;
  vertices[46] = color.g() / 255.0f;
  vertices[47] = color.b() / 255.0f;

  set_vertices(vertices);
}
} // end of namespace BarelyEngine
