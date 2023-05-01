#pragma once

#include <string>
#include <vector>

#include <xercesc/dom/DOM.hpp>
#include <json/json.h>

#include "exqudens/xerces/export.hpp"
#include "exqudens/xerces/Convertor.hpp"
#include "exqudens/xerces/Unit.hpp"

namespace exqudens::xerces {

  class EXQUDENS_XERCES_EXPORT XmlToJsonConvertor : public Convertor {

    public:

      std::string toJson(const std::string &value) override;

      ~XmlToJsonConvertor() override = default;

    private:

      Json::Value toJson(xercesc::DOMNode* node);

      std::vector<Unit> traverse(xercesc::DOMNode* xml);

      std::string toStdString(const XMLCh* value);

  };

}
