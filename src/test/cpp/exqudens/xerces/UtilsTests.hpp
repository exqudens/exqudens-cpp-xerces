#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <exception>
#include <iostream>
#include <format>

#include <gtest/gtest.h>

#include "TestUtils.hpp"
#include "exqudens/xerces/Utils.hpp"

namespace exqudens::xerces {

  class UtilsTests : public testing::Test {};

  TEST_F(UtilsTests, test1) {
    try {
      std::map<std::string, std::vector<std::string>> expected = {
          {"--help", {"true"}},
          {"--file", {"xml/1.xml"}},
          {"--files", {"xml/2.xml", "xml/3.xml"}}
      };
      std::map<std::string, std::vector<std::string>> actual = Utils::toMap(
          {"--help"},
          {"--file"},
          {"--files"},
          {"--help", "--file", "xml/1.xml", "--files", "xml/2.xml", "xml/3.xml"}
      );
      ASSERT_EQ(expected, actual);
    } catch (const std::exception& e) {
      FAIL() << TestUtils::toString(e);
    }
  }

}
