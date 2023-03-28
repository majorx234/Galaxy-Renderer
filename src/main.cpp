#include <iostream>

#include "GalaxyWnd.hpp"

int main(int argc, char** argv)
{
	try
	{
		GalaxyWnd wndMain;
		wndMain.InitFullscreen(35000.0, "Rendering a Galaxy with Density Waves");
		wndMain.MainLoop();
	}
	catch (std::exception& exc)
	{
		std::cout << "Fatal error: " << exc.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Fatal error: unexpected exception" << std::endl;
	}

	return 0;
}
