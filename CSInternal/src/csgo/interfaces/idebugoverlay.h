#pragma once
#include "../vector.h"
#include "iglowmanager.h"

struct IDebugOverlay
{
	virtual void AddEntityTextOverlay(int entityIndex, int lineOffset, float duration, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void AddBoxOverlay(const Vector3& origin, const Vector3& min, const Vector3& max, const Vector3& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void AddSphereOverlay(const Vector3& origin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float duration) = 0;
	virtual void AddTriangleOverlay(const Vector3& p1, const Vector3& p2, const Vector3& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void AddLineOverlay(const Vector3& origin, const Vector3& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
	virtual void AddTextOverlay(const Vector3& origin, float duration, const char* fmt, ...) = 0;
	virtual void AddTextOverlay(const Vector3& origin, int lineOffset, float duration, const char* fmt, ...) = 0;
	virtual void AddScreenTextOverlay(float x, float y, float duration, int r, int g, int b, int a, const char* text) = 0;
	virtual void AddSweptBoxOverlay(const Vector3& start, const Vector3& end, const Vector3& min, const Vector3& max, const Vector3& angles, int r, int g, int b, int a, float duration) = 0;
	virtual void AddGridOverlay(const Vector3& origin) = 0;
	virtual void AddCoordFrameOverlay(const CMatrix3x4& frame, float scale, int colorTable[3][3] = nullptr) = 0;
	virtual int ScreenPosition(const Vector3& worldPosition, Vector3& screen) = 0;
	virtual int ScreenPosition(float flXPos, float flYPos, Vector3& vecScreen) = 0;
	virtual void* GetFirst() = 0;
	virtual void* GetNext(void* pCurrent) = 0;
	virtual void ClearDeadOverlays() = 0;
	virtual void ClearAllOverlays() = 0;
	virtual void AddTextOverlayRGB(const Vector3& vecOrigin, int iLineOffset, float flDuration, float r, float g, float b, float a, const char* fmt, ...) = 0;
	virtual void AddTextOverlayRGB(const Vector3& vecOrigin, int iLineOffset, float flDuration, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void AddLineOverlayAlpha(const Vector3& vecOrigin, const Vector3& dest, int r, int g, int b, int a, bool bNoDepthTest, float flDuration) = 0;
	virtual void AddBoxOverlay2(const Vector3& vecOrigin, const Vector3& vecAbsMin, const Vector3& vecAbsMax, const Vector3& angOrientation, const Color& faceColor, const Color& edgeColor, float flDuration) = 0;
	virtual void AddLineOverlay(const Vector3& vecOrigin, const Vector3& vecDest, int r, int g, int b, int a, float flThickness, float flDuration) = 0;
	virtual void PurgeTextOverlays() = 0;
	virtual void AddCapsuleOverlay(const Vector3& vecAbsMin, const Vector3& vecAbsMax, const float& flRadius, int r, int g, int b, int a, float flDuration) = 0;
	virtual void DrawPill(Vector3& vecAbsMin, Vector3& vecAbsMax, float flRadius, int r, int g, int b, int a, float flDuration) = 0;
};