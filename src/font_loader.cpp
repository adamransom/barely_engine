//
// font_loader.cpp
// Copyright (c) 2015 Adam Ransom
//

#include <string>
#include "font_loader.h"
#include "font.h"
#include "font_generator.h"
#include "logging.h"
#include "exception.h"

using namespace std::literals;

namespace BarelyEngine {
FontLoader::FontLoader()
  : font_generator_(std::make_unique<FreeType::FontGenerator>())
{
}

FontLoader::~FontLoader() = default;

std::unique_ptr<Font> FontLoader::load(const std::string& filename,
                                       const LoaderOptions<FontLoader>& options)
{
  const auto path = "resources/fonts/" + filename;

  loading(path);

  try
  {
    auto font = font_generator_->generate(path, options.size);
    loaded(path);

    return font;
  }
  catch (Exception& e)
  {
    failed(path, e.what());

    return nullptr;
  }
}
} // end of namespace BarelyEngine
