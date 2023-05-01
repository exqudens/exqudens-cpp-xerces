#pragma once

#include <string>
#include <exception>

#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "exqudens/xerces/XmlToJsonConvertor.hpp"

#include <xercesc/util/PlatformUtils.hpp>

namespace exqudens::xerces {

  class ConvertorTests : public testing::Test {};

  TEST_F(ConvertorTests, test1) {
    try {
      std::string xml = "<root id=\"1\" name=\"aaa\">\nbbb\n<name>ccc</name>\nddd\n</root>";

      XmlToJsonConvertor xmlToJsonConvertor = {};
      Convertor* convertor = &xmlToJsonConvertor;

      std::string expected = "{\"root\": 1}";
      std::string json = convertor->toJson(xml);

      std::cout << std::format("xml: '{}'", xml) << std::endl;
      std::cout << std::format("json: '{}'", json) << std::endl;
    } catch (const std::exception& e) {
      FAIL() << TestUtils::toString(e);
    }
  }

  TEST_F(ConvertorTests, test2) {
    try {
      std::string xml = "<root><id>1</id><name>Aaa<sub>Bbb</sub>Ccc</name></root>";

      XmlToJsonConvertor xmlToJsonConvertor = {};
      Convertor* convertor = &xmlToJsonConvertor;

      std::string expected = "{\"root\": 1}";
      std::string json = convertor->toJson(xml);

      std::cout << std::format("xml: '{}'", xml) << std::endl;
      std::cout << std::format("json: '{}'", json) << std::endl;
    } catch (const std::exception& e) {
      FAIL() << TestUtils::toString(e);
    }
  }

  TEST_F(ConvertorTests, test3) {
    try {
      std::string xml = "<root><id>1</id><name>Abc</name></root>";

      XmlToJsonConvertor xmlToJsonConvertor = {};
      Convertor* convertor = &xmlToJsonConvertor;

      std::string expected = "{\"root\": 1}";
      std::string json = convertor->toJson(xml);

      std::cout << std::format("xml: '{}'", xml) << std::endl;
      std::cout << std::format("json: '{}'", json) << std::endl;
    } catch (const std::exception& e) {
      FAIL() << TestUtils::toString(e);
    }
  }

}
