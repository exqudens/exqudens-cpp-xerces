#pragma once

#include <string>
#include <vector>

#include "exqudens/xerces/export.hpp"

namespace exqudens::xerces {

  class EXQUDENS_XERCES_EXPORT Service {

    private:

      std::vector<std::string> commandLineArguments;

    public:

      explicit Service(std::vector<std::string> commandLineArguments);

      void run();

  };

}
