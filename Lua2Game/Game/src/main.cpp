#include "Core.h"

int main(int argc, char* argv[])
{
	if (!g_Core.Initialize())
	{
		g_Core.Uninitialize();
		return 0;
	}
	bool bRunning = true;
	while (bRunning)
	{
		bRunning = g_Core.Breathe();
	}

	g_Core.Uninitialize();
	return 1;
}