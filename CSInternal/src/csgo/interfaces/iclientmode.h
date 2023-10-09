#pragma once
#include "../vector.h"
#include "../panel.h"

struct CBaseEntity;
struct CBasePlayer;

struct ViewSetup
{
	int			x;
	int			unscaledX;
	int			y;
	int			unscaledY;
	int			width;
	int			unscaledWidth;
	int			height;
	int			unscaledHeight;
	bool		ortho;
	float		orthoLeft;
	float		orthoTop;
	float		orthoRight;
	float		orthoBottom;
	std::byte	pad0[0x7C];
	float		fov;
	float		viewModelFOV;
	Vector3		origin;
	Vector3		view;
	float		nearZ;
	float		farZ;
	float		nearViewmodelZ;
	float		farViewmodelZ;
	float		aspectRatio;
	float		nearBlurDepth;
	float		nearFocusDepth;
	float		farFocusDepth;
	float		farBlurDepth;
	float		nearBlurRadius;
	float		farBlurRadius;
	float		doFQuality;
	int			motionBlurMode;
	float		shutterTime;
	Vector3		shutterOpenPosition;
	Vector3		shutterOpenAngles;
	Vector3		shutterClosePosition;
	Vector3		shutterCloseAngles;
	float		offCenterTop;
	float		offCenterBottom;
	float		offCenterLeft;
	float		offCenterRight;
	bool		offCenter : 1;
	bool		renderToSubrectOfLargerScreen : 1;
	bool		bloomAndToneMapping : 1;
	bool		depthOfField : 1;
	bool		HDRTarget : 1;
	bool		drawWorldNormal : 1;
	bool		cullFontFaces : 1;
	bool		cacheFullSceneState : 1;
	bool		CSMView : 1;
};

enum ButtonCode
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};

struct AnimationController;
struct AudioState;
struct UserCmd;

struct IClientMode
{
	virtual	~IClientMode() {}

	// Called before the HUD is initialized.
	virtual void InitViewport() = 0;

	// One time init when .dll is first loaded.
	virtual void Init() = 0;

	// Called when vgui is shutting down.
	virtual void VGui_Shutdown() = 0;

	// One time call when dll is shutting down
	virtual void Shutdown() = 0;

	// Called when switching from one IClientMode to another.
	// This can re-layout the view and such.
	// Note that Enable and Disable are called when the DLL initializes and shuts down.
	virtual void Enable() = 0;
	virtual void EnableWithRootPanel(VPANEL pRoot) = 0;

	// Called when it's about to go into another client mode.
	virtual void Disable() = 0;

	// Called when initializing or when the view changes.
	// This should move the viewport into the correct position.
	virtual void Layout(bool bForce = false) = 0;

	// Gets at the viewport, if there is one...
	virtual Panel* GetViewport() = 0;

	// Gets a panel hierarchically below the viewport by name like so "ASWHudInventoryMode/SuitAbilityPanel/ItemPanel1"...
	virtual Panel* GetPanelFromViewport(const char* pchNamePath) = 0;

	// Gets at the viewports vgui panel animation controller, if there is one...
	virtual AnimationController* GetViewportAnimationController() = 0;

	// called every time shared client dll/engine data gets changed,
	// and gives the cdll a chance to modify the data.
	virtual void ProcessInput(bool bActive) = 0;

	// The mode can choose to draw/not draw entities.
	virtual bool ShouldDrawDetailObjects() = 0;
	virtual bool ShouldDrawEntity(CBaseEntity* pEnt) = 0;
	virtual bool ShouldDrawLocalPlayer(CBasePlayer* pPlayer) = 0;
	virtual bool ShouldDrawParticles() = 0;

	// The mode can choose to not draw fog
	virtual bool ShouldDrawFog(void) = 0;

	virtual void OverrideView(ViewSetup* pSetup) = 0;
	virtual void OverrideAudioState(AudioState* pAudioState) = 0;
	virtual int	 KeyInput(int down, ButtonCode keynum, const char* pszCurrentBinding) = 0;
	virtual void StartMessageMode(int iMessageModeType) = 0;
	virtual Panel* GetMessagePanel() = 0;
	virtual void OverrideMouseInput(float* x, float* y) = 0;
	virtual bool CreateMove(float flInputSampleTime, UserCmd* cmd) = 0;

	virtual void LevelInit(const char* newmap) = 0;
	virtual void LevelShutdown(void) = 0;

	// Certain modes hide the view model
	virtual bool ShouldDrawViewModel(void) = 0;
	virtual bool ShouldDrawCrosshair(void) = 0;

	// Let mode override viewport for engine
	virtual void AdjustEngineViewport(int& x, int& y, int& width, int& height) = 0;

	// Called before rendering a view.
	virtual void PreRender(ViewSetup* pSetup) = 0;

	// Called after everything is rendered.
	virtual void PostRender(void) = 0;

	virtual void PostRenderVGui() = 0;

	virtual void ActivateInGameVGuiContext(Panel* pPanel) = 0;
	virtual void DeactivateInGameVGuiContext() = 0;
	virtual float GetViewModelFOV(void) = 0;

	virtual bool CanRecordDemo(char* errorMsg, int length) const = 0;

	virtual wchar_t* GetServerName(void) = 0;
	virtual void SetServerName(wchar_t* name) = 0;
	virtual wchar_t* GetMapName(void) = 0;
	virtual void SetMapName(wchar_t* name) = 0;

	virtual void	OnColorCorrectionWeightsReset(void) = 0;
	virtual float	GetColorCorrectionScale(void) const = 0;

	virtual int		HudElementKeyInput(int down, ButtonCode keynum, const char* pszCurrentBinding) = 0;

	virtual void	DoPostScreenSpaceEffects(const ViewSetup* pSetup) = 0;

	virtual void	UpdateCameraManUIState(int iType, int nOptionalParam, uint64_t xuid) = 0;
	virtual void	ScoreboardOff(void) = 0;
	virtual void	GraphPageChanged(void) = 0;

	// Called every frame.
	virtual void	Update() = 0;

	virtual void	SetBlurFade(float scale) = 0;
	virtual float	GetBlurFade(void) = 0;
};