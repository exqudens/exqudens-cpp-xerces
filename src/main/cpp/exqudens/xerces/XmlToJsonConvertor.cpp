#include "exqudens/xerces/XmlToJsonConvertor.hpp"
#include "exqudens/xerces/macros.hpp"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>

#include <queue>
#include <utility>
#include <stdexcept>
#include <iostream>

namespace exqudens::xerces {

  std::string XmlToJsonConvertor::toJson(const std::string& value) {
    try {
      std::string jsonContent = {};

      xercesc::XMLPlatformUtils::Initialize();
      xercesc::DOMImplementation* impl = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("LS"));
      xercesc::DOMLSInput* input = ((xercesc::DOMImplementationLS*)impl)->createLSInput();
      input->setStringData(xercesc::XMLString::transcode(value.c_str()));
      xercesc::DOMLSParser* parser = ((xercesc::DOMImplementationLS*)impl)->createLSParser(xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, nullptr);
      xercesc::DOMDocument* doc = parser->parse(input);

      Json::Value json = toJson(doc->getFirstChild());

      Json::StreamWriterBuilder wbuilder;
      //wbuilder["indentation"] = "\t";
      jsonContent = Json::writeString(wbuilder, json);

      input->release();
      parser->release();
      xercesc::XMLPlatformUtils::Terminate();

      return jsonContent;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

  Json::Value XmlToJsonConvertor::toJson(xercesc::DOMNode* node) {
    try {
      /*xercesc::DOMNode* parentNode = node->getParentNode();
      if (parentNode != nullptr) {
        std::cout << "parentNode: '" << toStdString(parentNode->getNodeName()) << "'" << std::endl;
      } else {
        std::cout << "parentNode: '" << "null" << "'" << std::endl;
      }*/

      /*std::string nodeName = toStdString(node->getChildNodes()->item(0)->getNodeName());
      json[nodeName] = {};*/

      //traverse(node->getFirstChild(), json);

      /*size_t s = node->getChildNodes()->getLength();
      std::cout << "s: '" << s << "'" << std::endl;*/

      /*xercesc::DOMNodeList* list = node->getChildNodes()->item(0)->getChildNodes()->item(0)->getChildNodes()->item(0)->getChildNodes();
      if (list != nullptr) {
        std::cout << "list: '" << list->getLength() << "'" << std::endl;
      } else {
        std::cout << "list: '" << "null" << "'" << std::endl;
      }*/

      std::vector<Unit> units = traverse(node);
      for (const Unit& unit : units) {
        std::string indexPath = "[";
        if (!unit.indexPath.empty()) {
          indexPath += std::to_string(unit.indexPath.at(0));
          for (size_t i = 1; i < unit.indexPath.size(); i++) {
            indexPath += ", ";
            indexPath += std::to_string(unit.indexPath.at(i));
          }
        }
        indexPath += "]";
        std::string value = {};
        if (unit.node->getNodeType() == xercesc::DOMNode::NodeType::TEXT_NODE) {
          value = toStdString(unit.node->getNodeValue());
        } else {
          value = toStdString(unit.node->getNodeName());
        }
        std::cout << CALL_INFO() + ": " << indexPath << ": '" << value << "'" << std::endl;
      }

      Json::Value json;
      return json;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

  std::vector<Unit> XmlToJsonConvertor::traverse(xercesc::DOMNode* xml) {
    try {
      std::vector<Unit> result = {};

      std::queue<Unit> queue = {};
      Unit root = {
          .indexPath = {0},
          .node = xml
      };
      queue.push(root);
      while (!queue.empty()) {
        Unit current = queue.front();
        std::vector<size_t> currentPath = current.indexPath;
        const xercesc::DOMNode* currentNode = current.node;
        result.emplace_back(current);
        for (size_t i = 0; i < currentNode->getChildNodes()->getLength(); i++) {
          std::vector<size_t> childPath = currentPath;
          childPath.emplace_back(i);
          xercesc::DOMNode* childNode = currentNode->getChildNodes()->item(i);
          Unit child = {
              .indexPath = childPath,
              .node = childNode
          };
          queue.push(child);
        }
        queue.pop();
      }

      return result;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

  std::string XmlToJsonConvertor::toStdString(const XMLCh* value) {
    try {
      const char* buffer = xercesc::XMLString::transcode(value);
      std::string result = std::string(buffer);
      return result;
    } catch (...) {
      std::throw_with_nested(std::runtime_error(CALL_INFO()));
    }
  }

}
