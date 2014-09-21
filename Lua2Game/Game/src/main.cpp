#include <iostream>
#include "Core.h"

int main(int argc, char* argv[])
{
	if (!g_Core.Initialize())
	{
		g_Core.Uninitialize();
		return 0;
	}
	printf("-----------------Start game!!!-----------------\n");
	while (1)
	{
		if (!g_Core.Breathe())
			break;
	}
	printf("-----------------Game over!!!------------------\n");
	g_Core.Uninitialize();

//	system("PAUSE");
	return 1;
}
