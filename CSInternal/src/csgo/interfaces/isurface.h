#pragma once
#include "../../tools/memory.h"
#include "iglowmanager.h"

struct ISurface
{
	void DrawSetColor(int r, int g, int b, int a = 255)
	{
		memory::CallVmtFn<void>(this, 15, r, g, b, a);
	}

	void DrawFilledRect(int x1, int y1, int x2, int y2)
	{
		memory::CallVmtFn<void>(this, 16, x1, y1, x2, y2);
	}

	void DrawOutlinedRect(int x1, int y1, int x2, int y2)
	{
		memory::CallVmtFn<void>(this, 18, x1, y1, x2, y2);
	}

	void DrawLine(int x1, int y1, int x2, int y2)
	{
		memory::CallVmtFn<void>(this, 19, x1, y1, x2, y2);
	}
};


