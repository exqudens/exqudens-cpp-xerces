#pragma once

#include <vector>

#include <xercesc/dom/DOMNode.hpp>

#include "exqudens/xerces/export.hpp"

namespace exqudens::xerces {

  struct EXQUDENS_XERCES_EXPORT Unit {

    std::vector<size_t> indexPath;
    const xercesc::DOMNode* node;

  };

}
