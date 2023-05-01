#include "exqudens/xerces/Application.hpp"
#include "exqudens/xerces/macros.hpp"
#include "exqudens/xerces/Service.hpp"
#include "exqudens/xerces/Utils.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

namespace exqudens::xerces {

  int Application::run(int argc, char** argv) noexcept {
    try {
      std::vector<std::string> commandLineArguments = {};
      for (int i = 0; i < argc; i++) {
        commandLineArguments.emplace_back(std::string(argv[i]));
      }
      Service service(commandLineArguments);
      service.run();
      return EXIT_SUCCESS;
    } catch (const std::exception& e) {
      std::cerr << Utils::toString(e) << std::endl;
      return EXIT_FAILURE;
    } catch (...) {
      std::cerr << CALL_INFO() + ": Unknown error!" << std::endl;
      return EXIT_FAILURE;
    }
  }

}
