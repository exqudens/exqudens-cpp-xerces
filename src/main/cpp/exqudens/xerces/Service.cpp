#include "exqudens/xerces/Service.hpp"
#include "exqudens/xerces/XmlToJsonConvertor.hpp"
#include "exqudens/xerces/Utils.hpp"
#include "exqudens/xerces/macros.hpp"

#include <map>
#include <utility>
#include <stdexcept>

namespace exqudens::xerces {

  Service::Service(
      std::vector<std::string> commandLineArguments
  ):
      commandLineArguments(std::move(commandLineArguments))
  {
  }

  void Service::run() {
    try {
      std::string inputFileKey = "--input-file";
      std::string outputFileKey = "--output-file";

      std::map<std::string, std::vector<std::string>> map = Utils::toMap(
          {},
          {inputFileKey, outputFileKey},
          {},
          commandLineArguments
      );

      XmlToJsonConvertor xmlToJsonConvertor = {};
      Convertor* convertor = &xmlToJsonConvertor;

      std::string xml = "";
      std::string json = convertor->toJson(xml);
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

}
