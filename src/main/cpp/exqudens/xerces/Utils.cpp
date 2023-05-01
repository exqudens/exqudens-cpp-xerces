#include "exqudens/xerces/Utils.hpp"
#include "exqudens/xerces/macros.hpp"

#include <algorithm>
#include <stdexcept>

namespace exqudens::xerces {

  std::vector<std::string> Utils::toStringVector(const std::exception& exception, std::vector<std::string> previous) {
    try {
      previous.emplace_back(exception.what());
      std::rethrow_if_nested(exception);
      return previous;
    } catch (const std::exception& e) {
      return toStringVector(e, previous);
    } catch (...) {
      if (previous.empty()) {
        previous.emplace_back(CALL_INFO() + ": Empty stack!");
      }
      return previous;
    }
  }

  std::vector<std::string> Utils::toStackTrace(const std::exception& exception) {
    try {
      std::vector<std::string> elements = toStringVector(exception);
      if (elements.size() > 1) {
        std::ranges::reverse(elements);
      }
      return elements;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

  std::string Utils::toString(const std::exception& e) {
    try {
      std::vector<std::string> stackTrace = toStackTrace(e);
      std::ostringstream out;
      for (size_t i = 0; i < stackTrace.size(); i++) {
        out << stackTrace[i];
        if (i < stackTrace.size() - 1) {
          out << std::endl;
        }
      }
      return out.str();
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

  std::map<std::string, std::vector<std::string>> Utils::toMap(
      const std::set<std::string>& options,
      const std::set<std::string>& oneValueKeywords,
      const std::set<std::string>& multyValueKeywords,
      const std::vector<std::string>& arguments
  ) {
    try {
      std::map<std::string, std::vector<std::string>> map = {};
      for (const std::string& option : options) {
        if (!option.empty()) {
          map[option] = {"false"};
        }
      }
      std::string key = {};
      for (const std::string& argument : arguments) {
        if (oneValueKeywords.contains(argument) || multyValueKeywords.contains(argument)) {
          if (!argument.empty()) {
            key = argument;
          }
        } else if (options.contains(argument)) {
          if (!argument.empty()) {
            map[argument] = {"true"};
          }
        } else {
          if (!key.empty()) {
            if (!map.contains(key)) {
              map[key] = {};
            }
            map[key].emplace_back(argument);
          }
        }
      }
      return map;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

}
