#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <exception>

#include "exqudens/xerces/export.hpp"

namespace exqudens::xerces {

  class EXQUDENS_XERCES_EXPORT Utils {

    public:

      static std::vector<std::string> toStringVector(
          const std::exception& exception,
          std::vector<std::string> previous = {}
      );

      static std::vector<std::string> toStackTrace(
          const std::exception& exception
      );

      static std::string toString(
          const std::exception& e
      );

      static std::map<std::string, std::vector<std::string>> toMap(
          const std::set<std::string>& options,
          const std::set<std::string>& oneValueKeywords,
          const std::set<std::string>& multyValueKeywords,
          const std::vector<std::string>& arguments
      );

  };

}
