#include <string>
#include <filesystem>
#include <iostream>
#include <format>

#include <gtest/gtest.h>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "TestUtils.hpp"

class OtherTests : public testing::Test {

  protected:

    void createFile(const std::filesystem::path& currentTestFile) {
      try {
        xercesc::XMLPlatformUtils::Initialize();

        xercesc::DOMImplementation* impl = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));
        xercesc::DOMDocument* doc = impl->createDocument(0, xercesc::XMLString::transcode("root"), 0);
        xercesc::DOMElement* root = doc->getDocumentElement();

        xercesc::DOMElement* rootName = doc->createElement(xercesc::XMLString::transcode("name"));
        rootName->setAttribute(xercesc::XMLString::transcode("type"), xercesc::XMLString::transcode("string"));
        xercesc::DOMText* rootNameValue = doc->createTextNode(xercesc::XMLString::transcode("Abc"));
        rootName->appendChild(rootNameValue);
        root->appendChild(rootName);

        xercesc::DOMElement* rootId = doc->createElement(xercesc::XMLString::transcode("id"));
        rootId->setAttribute(xercesc::XMLString::transcode("type"), xercesc::XMLString::transcode("int"));
        xercesc::DOMText* rootIdValue = doc->createTextNode(xercesc::XMLString::transcode("1"));
        rootId->appendChild(rootIdValue);
        root->appendChild(rootId);

        xercesc::DOMLSSerializer* serializer = ((xercesc::DOMImplementationLS*)impl)->createLSSerializer();
        xercesc::DOMLSOutput* output = ((xercesc::DOMImplementationLS*)impl)->createLSOutput();
        xercesc::DOMConfiguration* configuration = serializer->getDomConfig();
        configuration->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
        xercesc::XMLFormatTarget* target = new xercesc::LocalFileFormatTarget(currentTestFile.string().c_str());
        output->setByteStream(target);
        serializer->write(doc, output);
        delete target;
        output->release();
        serializer->release();
        doc->release();

        xercesc::XMLPlatformUtils::Terminate();
      } catch (const std::exception& e) {
        std::throw_with_nested(std::runtime_error(CALL_INFO()));
      }
    }

};

TEST_F(OtherTests, test1) {
  try {
    std::string currentTestName = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
    std::filesystem::path currentTestDir = std::filesystem::path("resources").append(currentTestName);
    std::filesystem::path currentTestFile = std::filesystem::path(currentTestDir).append("root.xml");

    if (std::filesystem::exists(currentTestFile)) {
      std::filesystem::remove(currentTestFile);
    }

    if (!std::filesystem::exists(currentTestDir)) {
      std::filesystem::create_directories(currentTestDir);
    }

    createFile(currentTestFile);

    xercesc::XMLPlatformUtils::Initialize();

    xercesc::DOMImplementation* impl = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("LS"));
    xercesc::DOMLSParser* parser = ((xercesc::DOMImplementationLS*)impl)->createLSParser(xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, 0);

    xercesc::DOMDocument* doc = parser->parseURI(currentTestFile.string().c_str());

    xercesc::DOMNodeList* list = doc->getElementsByTagName(xercesc::XMLString::transcode("root"));

    std::cout << std::format("list.length: '{}'", list->getLength()) << std::endl;

    parser->release();

    xercesc::XMLPlatformUtils::Terminate();
  } catch (const std::exception& e) {
    FAIL() << TestUtils::toString(e);
  }
}
