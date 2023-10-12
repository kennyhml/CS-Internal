#pragma once
#include "../../tools/memory.h"
#include "iglowmanager.h"

typedef unsigned long HFont;

enum FontDrawType
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,		// custom generated font - never fall back to asian compatibility mode
	FONTFLAG_BITMAP = 0x800,		// compiled bitmap font - no fallbacks
};



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

	void DrawSetTextFont(HFont font)
	{
		memory::CallVmtFn<void>(this, 23, font);
	}

	void DrawSetTextColor(int r, int g, int b, int a)
	{
		memory::CallVmtFn<void>(this, 25, r, g, b, a);
	}

	void DrawSetTextPos(int x, int y)
	{
		memory::CallVmtFn<void>(this, 26, x, y);
	}

	void DrawPrintText(const wchar_t* text, int length, FontDrawType drawType = FONT_DRAW_DEFAULT)
	{
		memory::CallVmtFn<void>(this, 28, text, length, drawType);
	}

	HFont CreateFont_()
	{
		return memory::CallVmtFn<HFont>(this, 71);
	}

	void SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		memory::CallVmtFn<void>(this, 72, font, windowsFontName, tall, weight, blur, scanlines, flags, NULL, NULL);
	}

	void GetTextSize(HFont font, const wchar_t* text, int& wideOut, int& tallOut)
	{
		memory::CallVmtFn<void, HFont, const wchar_t*, int&, int&>(this, 79, font, text, wideOut, tallOut);
	}


};


