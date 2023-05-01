#include "TestApplication.hpp"
#include "TestConfiguration.hpp"
#include "OtherTests.hpp"
#include "exqudens/xerces/UtilsTests.hpp"
#include "exqudens/xerces/ConvertorTests.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <string>
#include <utility>
#include <iostream>

int TestApplication::run(int* argc, char** argv) {
  std::pair<int, std::string> result = TestConfiguration::setExecutableFile(argv[0]);
  int status = result.first;
  std::string error = result.second;
  if (status != EXIT_SUCCESS) {
    std::cerr << error << std::endl;
    return status;
  }
  testing::InitGoogleMock(argc, argv);
  testing::InitGoogleTest(argc, argv);
  status = RUN_ALL_TESTS();
  return status;
}
