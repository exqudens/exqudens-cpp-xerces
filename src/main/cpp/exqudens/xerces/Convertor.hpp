#pragma once

#include <string>

#include "exqudens/xerces/export.hpp"

namespace exqudens::xerces {

  class EXQUDENS_XERCES_EXPORT Convertor {

    public:

      virtual std::string toJson(const std::string& value) = 0;

      virtual ~Convertor() = default;

  };

}
