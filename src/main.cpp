#include <iostream>
#include <string>

#include "GalaxyWnd.hpp"

/* TODO: delete inimplemented sign if finished <04-04-23, nikl> */
std::string helpstr() {
  return "default:						open in qt-window "
         "window (CURRENTLY UNIMPLEMENTED!)\n"
         "-f								"
         "	open in Fullscreen mode\n"
         "-l [width] [height]	open in legacy SDL-Window\n";
}

std::string unknownCmd(const char *original_cmd) {
  return "Unknown Argumand '" + std::string(original_cmd) +
         "', type -h for help";
}

int main(int argc, char **argv) {
  try {
    if (argv[1]) {
      const char *arg = argv[1];
      switch (arg[0]) {
      case '-':
        switch (arg[1]) {
        case 'f': {
          GalaxyWnd wndMain;
          wndMain.InitFullscreen(35000.0,
                                 "Rendering a Galaxy with Density Waves");
          wndMain.MainLoop();
        } break;
        case 'l': {
          GalaxyWnd wndMain;
          if (argv[2] && argv[3]) {
            const char *width = argv[2], *height = argv[3];
            wndMain.Init(atoi(width), atoi(height), 35000,
                         "Rendering a Galaxy with Density Waves");
          } else
            wndMain.Init(1600, 1000, 35000.0,
                         "Rendering a Galaxy with Density Waves");
          wndMain.MainLoop();
          break;
        }
        case 'h':
          std::cout << helpstr() << std::endl;
          break;
        default:
          std::cout << unknownCmd(arg) << std::endl;
        }
        break;
      default:
        std::cout << helpstr() << std::endl;
      }
    } else
      std::cout << helpstr() << std::endl;
  } catch (std::exception &exc) {
    std::cout << "Fatal error: " << exc.what() << std::endl;
  } catch (...) {
    std::cout << "Fatal error: unexpected exception" << std::endl;
  }

  return 0;
}
