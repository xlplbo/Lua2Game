#include <iostream>
#include "Core.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (!g_Core.Initialize())
	{
		g_Core.Uninitialize();
		return 0;
	}
	std::cout << "Start game!!!" << std::endl;
	while (g_bRunning)
	{
		g_bRunning = g_Core.Breathe();
	}
	std::cout << "Game over!!!" << std::endl;
	g_Core.Uninitialize();
	return 1;
}