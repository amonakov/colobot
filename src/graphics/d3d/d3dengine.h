// * This file is part of the COLOBOT source code
// * Copyright (C) 2001-2008, Daniel ROUX & EPSITEC SA, www.epsitec.ch
// *
// * This program is free software: you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * (at your option) any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this program. If not, see  http://www.gnu.org/licenses/.

// d3dengine.h

#pragma once


#include "math/point.h"
#include "common/struct.h"


class CD3DApplication;
class CInstanceManager;
class CObject;
class CLight;
class CText;
class CParticule;
class CWater;
class CCloud;
class CBlitz;
class CPlanet;
class CSound;
class CTerrain;


const int D3DMAXOBJECT		= 1200;
const int D3DMAXSHADOW		= 500;
const int D3DMAXGROUNDSPOT	= 100;


enum D3DTypeObj
{
	TYPENULL		= 0,		// object doesn't exist
	TYPETERRAIN		= 1,		// terrain
	TYPEFIX			= 2,		// fixed object
	TYPEVEHICULE		= 3,		// moving object
	TYPEDESCENDANT		= 4,		// part of a moving object
	TYPEQUARTZ		= 5,		// fixed object type quartz
	TYPEMETAL		= 6,		// fixed object type metal
};

enum D3DTypeTri
{
	D3DTYPE6T		= 1,		// triangles
	D3DTYPE6S		= 2,		// surfaces
};

enum D3DMaping
{
	D3DMAPPINGX		= 1,
	D3DMAPPINGY		= 2,
	D3DMAPPINGZ		= 3,
	D3DMAPPING1X	= 4,
	D3DMAPPING1Y	= 5,
	D3DMAPPING1Z	= 6,
};

enum D3DMouse
{
	D3DMOUSEHIDE	= 0,		// no mouse
	D3DMOUSENORM	= 1,
	D3DMOUSEWAIT	= 2,
	D3DMOUSEEDIT	= 3,
	D3DMOUSEHAND	= 4,
	D3DMOUSECROSS	= 5,
	D3DMOUSESHOW	= 6,
	D3DMOUSENO	= 7,
	D3DMOUSEMOVE	= 8,		// +
	D3DMOUSEMOVEH	= 9,		// -
	D3DMOUSEMOVEV	= 10,		// |
	D3DMOUSEMOVED	= 11,		// /
	D3DMOUSEMOVEI	= 12,		// \ //
	D3DMOUSESCROLLL	= 13,		// <<
	D3DMOUSESCROLLR	= 14,		// >>
	D3DMOUSESCROLLU	= 15,		// ^
	D3DMOUSESCROLLD	= 16,		// v
	D3DMOUSETARGET	= 17,
};

enum D3DShadowType
{
	D3DSHADOWNORM	= 0,
	D3DSHADOWWORM	= 1,
};


const int D3DSTATENORMAL	= 0;		// normal opaque materials
const int D3DSTATETTb		= (1<<0);	// the transparent texture (black = no)
const int D3DSTATETTw		= (1<<1);	// the transparent texture (white = no)
const int D3DSTATETD		= (1<<2);	// the transparent diffuse color
const int D3DSTATEWRAP		= (1<<3);	// texture wrappe
const int D3DSTATECLAMP		= (1<<4);	// texture borders with solid color
const int D3DSTATELIGHT		= (1<<5);	// light texture (ambient max)
const int D3DSTATEDUALb		= (1<<6);	// double black texturing
const int D3DSTATEDUALw		= (1<<7);	// double white texturing
const int D3DSTATEPART1		= (1<<8);	// part 1 (no change in. MOD!)
const int D3DSTATEPART2		= (1<<9);	// part 2
const int D3DSTATEPART3		= (1<<10);	// part 3
const int D3DSTATEPART4		= (1<<11);	// part 4
const int D3DSTATE2FACE		= (1<<12);	// double-sided face
const int D3DSTATEALPHA		= (1<<13);	// image using alpha channel
const int D3DSTATESECOND	= (1<<14);	// always use 2nd floor texturing
const int D3DSTATEFOG		= (1<<15);	// causes the fog
const int D3DSTATETCb		= (1<<16);	// the transparent color (black = no)
const int D3DSTATETCw		= (1<<17);	// the transparent color (white = no)


struct D3DTriangle
{
	D3DVERTEX2		triangle[3];
	D3DMATERIAL7	material;
	int				state;
	char			texName1[20];
	char			texName2[20];
};


struct D3DObjLevel6
{
	int				totalPossible;
	int				totalUsed;
	D3DMATERIAL7	material;
	int				state;
	D3DTypeTri		type;		// D3DTYPE6x
	D3DVERTEX2		vertex[1];
};

struct D3DObjLevel5
{
	int				totalPossible;
	int				totalUsed;
	int				reserve;
	D3DObjLevel6*	table[1];
};

struct D3DObjLevel4
{
	int				totalPossible;
	int				totalUsed;
	float			min, max;
	D3DObjLevel5*	table[1];
};

struct D3DObjLevel3
{
	int				totalPossible;
	int				totalUsed;
	int				objRank;
	D3DObjLevel4*	table[1];
};

struct D3DObjLevel2
{
	int				totalPossible;
	int				totalUsed;
	char			texName1[20];
	char			texName2[20];
	D3DObjLevel3*	table[1];
};

struct D3DObjLevel1
{
	int				totalPossible;
	int				totalUsed;
	D3DObjLevel2*	table[1];
};


struct D3DObject
{
	char		bUsed;			// true -> object exists
	char		bVisible;		// true -> visible object
	char		bDrawWorld;		// true -> shape behind the interface
	char		bDrawFront;		// true -> shape before the interface
	int		totalTriangle;		// number of triangles used
	D3DTypeObj	type;			// type of the object (TYPE*)
	D3DMATRIX	transform;		// transformation matrix
	float		distance;		// distance point of view - original
	D3DVECTOR	bboxMin;		// bounding box of the object
	D3DVECTOR	bboxMax;		// (the origin 0, 0, 0 is always included)
	float		radius;			// radius of the sphere at the origin
	int		shadowRank;		// rank of the associated shadow
	float		transparency;		// transparency of the object (0 .. 1)
};

struct D3DShadow
{
	char		bUsed;			// true -> object exists
	char		bHide;			// true -> invisible shadow (object carried by ex.)
	int		objRank;		// rank of the object
	D3DShadowType 	type;			// type of shadow
	D3DVECTOR	pos;			// position for the shadow
	D3DVECTOR	normal;			// normal terrain
	float		angle;			// angle of the shadow
	float		radius;			// radius of the shadow
	float		intensity;		// intensity of the shadow
	float		height;			// height from the ground
};

struct D3DGroundSpot
{
	char		bUsed;			// true -> object exists
	D3DCOLORVALUE	color;			// color of the shadow
	float		min, max;		// altitudes min / max
	float		smooth;			// transition area
	D3DVECTOR	pos;			// position for the shadow
	float		radius;			// radius of the shadow
	D3DVECTOR	drawPos;		// drawn to position the shade
	float		drawRadius;		// radius of the shadow drawn
};

struct D3DGroundMark
{
	char		bUsed;			// true -> object exists
	char		bDraw;			// true -> drawn mark
	int		phase;			// 1 = increase, 2 = fixed, 3 = decrease
	float		delay[3];		// time for 3 phases
	float		fix;			// fixed time
	D3DVECTOR	pos;			// position for marks
	float		radius;			// radius of marks
	float		intensity;		// color intensity
	D3DVECTOR	drawPos;		// drawn in position marks
	float		drawRadius;		// radius marks drawn
	float		drawIntensity;		// current drawn
	int		dx, dy;			// dimensions table
	char*		table;			// pointer to the table
};



class CD3DEngine
{
public:
	CD3DEngine(CInstanceManager *iMan, CD3DApplication *app);
	~CD3DEngine();

	void		SetD3DDevice(LPDIRECT3DDEVICE7 device);
	LPDIRECT3DDEVICE7 RetD3DDevice();

	void		SetTerrain(CTerrain* terrain);

	bool		WriteProfile();

	void		SetPause(bool bPause);
	bool		RetPause();

	void		SetMovieLock(bool bLock);
	bool		RetMovieLock();

	void		SetShowStat(bool bShow);
	bool		RetShowStat();

	void		SetRenderEnable(bool bEnable);

	HRESULT		OneTimeSceneInit();
	HRESULT		InitDeviceObjects();
	HRESULT		DeleteDeviceObjects();
	HRESULT		RestoreSurfaces();
	HRESULT		Render();
	HRESULT		FrameMove(float rTime);
	void		StepSimul(float rTime);
	HRESULT		FinalCleanup();
	void		AddStatisticTriangle(int nb);
	int			RetStatisticTriangle();
	void		SetHiliteRank(int *rankList);
	bool		GetHilite(Math::Point &p1, Math::Point &p2);
	bool		GetSpriteCoord(int &x, int &y);
	void		SetInfoText(int line, char* text);
	char*		RetInfoText(int line);
	LRESULT		MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void		FirstExecuteAdapt(bool bFirst);
	int			GetVidMemTotal();
	bool		IsVideo8MB();
	bool		IsVideo32MB();

	bool		EnumDevices(char *bufDevices, int lenDevices, char *bufModes, int lenModes, int &totalDevices, int &selectDevices, int &totalModes, int &selectModes);
	bool		RetFullScreen();
	bool		ChangeDevice(char *device, char *mode, bool bFull);

	D3DMATRIX*	RetMatView();
	D3DMATRIX*	RetMatLeftView();
	D3DMATRIX*	RetMatRightView();

	void		TimeInit();
	void		TimeEnterGel();
	void		TimeExitGel();
	float		TimeGet();

	int			RetRestCreate();
	int			CreateObject();
	void		FlushObject();
	bool		DeleteObject(int objRank);
	bool		SetDrawWorld(int objRank, bool bDraw);
	bool		SetDrawFront(int objRank, bool bDraw);
	bool		AddTriangle(int objRank, D3DVERTEX2* vertex, int nb, const D3DMATERIAL7 &mat, int state, char* texName1, char* texName2, float min, float max, bool bGlobalUpdate);
	bool		AddSurface(int objRank, D3DVERTEX2* vertex, int nb, const D3DMATERIAL7 &mat, int state, char* texName1, char* texName2, float min, float max, bool bGlobalUpdate);
	bool		AddQuick(int objRank, D3DObjLevel6* buffer, char* texName1, char* texName2, float min, float max, bool bGlobalUpdate);
	D3DObjLevel6* SearchTriangle(int objRank, const D3DMATERIAL7 &mat, int state, char* texName1, char* texName2, float min, float max);
	void		ChangeLOD();
	bool		ChangeSecondTexture(int objRank, char* texName2);
	int			RetTotalTriangles(int objRank);
	int			GetTriangles(int objRank, float min, float max, D3DTriangle* buffer, int size, float percent);
	bool		GetBBox(int objRank, D3DVECTOR &min, D3DVECTOR &max);
	bool		ChangeTextureMapping(int objRank, const D3DMATERIAL7 &mat, int state, char* texName1, char* texName2, float min, float max, D3DMaping mode, float au, float bu, float av, float bv);
	bool		TrackTextureMapping(int objRank, const D3DMATERIAL7 &mat, int state, char* texName1, char* texName2, float min, float max, D3DMaping mode, float pos, float factor, float tl, float ts, float tt);
	bool		SetObjectTransform(int objRank, const D3DMATRIX &transform);
	bool		GetObjectTransform(int objRank, D3DMATRIX &transform);
	bool		SetObjectType(int objRank, D3DTypeObj type);
	D3DTypeObj	RetObjectType(int objRank);
	bool		SetObjectTransparency(int objRank, float value);

	bool		ShadowCreate(int objRank);
	void		ShadowDelete(int objRank);
	bool		SetObjectShadowHide(int objRank, bool bHide);
	bool		SetObjectShadowType(int objRank, D3DShadowType type);
	bool		SetObjectShadowPos(int objRank, const D3DVECTOR &pos);
	bool		SetObjectShadowNormal(int objRank, const D3DVECTOR &n);
	bool		SetObjectShadowAngle(int objRank, float angle);
	bool		SetObjectShadowRadius(int objRank, float radius);
	bool		SetObjectShadowIntensity(int objRank, float intensity);
	bool		SetObjectShadowHeight(int objRank, float h);
	float		RetObjectShadowRadius(int objRank);

	void		GroundSpotFlush();
	int			GroundSpotCreate();
	void		GroundSpotDelete(int rank);
	bool		SetObjectGroundSpotPos(int rank, const D3DVECTOR &pos);
	bool		SetObjectGroundSpotRadius(int rank, float radius);
	bool		SetObjectGroundSpotColor(int rank, D3DCOLORVALUE color);
	bool		SetObjectGroundSpotMinMax(int rank, float min, float max);
	bool		SetObjectGroundSpotSmooth(int rank, float smooth);

	int			GroundMarkCreate(D3DVECTOR pos, float radius, float delay1, float delay2, float delay3, int dx, int dy, char* table);
	bool		GroundMarkDelete(int rank);

	void		Update();
	
	void		SetViewParams(const D3DVECTOR &vEyePt, const D3DVECTOR &vLookatPt, const D3DVECTOR &vUpVec, FLOAT fEyeDistance);

	bool		FreeTexture(char* name);
	bool		LoadTexture(char* name, int stage=0);
	bool		LoadAllTexture();

	void		SetLimitLOD(int rank, float limit);
	float		RetLimitLOD(int rank, bool bLast=false);

	void		SetTerrainVision(float vision);

	void		SetGroundSpot(bool bMode);
	bool		RetGroundSpot();
	void		SetShadow(bool bMode);
	bool		RetShadow();
	void		SetDirty(bool bMode);
	bool		RetDirty();
	void		SetFog(bool bMode);
	bool		RetFog();
	bool		RetStateColor();

	void		SetSecondTexture(int texNum);
	int			RetSecondTexture();

	void		SetRankView(int rank);
	int			RetRankView();

	void		SetDrawWorld(bool bDraw);
	void		SetDrawFront(bool bDraw);

	void		SetAmbiantColor(D3DCOLOR color, int rank=0);
	D3DCOLOR	RetAmbiantColor(int rank=0);

	void		SetWaterAddColor(D3DCOLORVALUE color);
	D3DCOLORVALUE RetWaterAddColor();

	void		SetFogColor(D3DCOLOR color, int rank=0);
	D3DCOLOR	RetFogColor(int rank=0);

	void		SetDeepView(float length, int rank=0, bool bRef=false);
	float		RetDeepView(int rank=0);

	void		SetFogStart(float start, int rank=0);
	float		RetFogStart(int rank=0);

	void		SetBackground(char *name, D3DCOLOR up=0, D3DCOLOR down=0, D3DCOLOR cloudUp=0, D3DCOLOR cloudDown=0, bool bFull=false, bool bQuarter=false);
	void		RetBackground(char *name, D3DCOLOR &up, D3DCOLOR &down, D3DCOLOR &cloudUp, D3DCOLOR &cloudDown, bool &bFull, bool &bQuarter);
	void		SetFrontsizeName(char *name);
	void		SetOverFront(bool bFront);
	void		SetOverColor(D3DCOLOR color=0, int mode=D3DSTATETCb);

	void		SetParticuleDensity(float value);
	float		RetParticuleDensity();
	float		ParticuleAdapt(float factor);

	void		SetClippingDistance(float value);
	float		RetClippingDistance();

	void		SetObjectDetail(float value);
	float		RetObjectDetail();

	void		SetGadgetQuantity(float value);
	float		RetGadgetQuantity();

	void		SetTextureQuality(int value);
	int			RetTextureQuality();

	void		SetTotoMode(bool bPresent);
	bool		RetTotoMode();

	void		SetLensMode(bool bPresent);
	bool		RetLensMode();

	void		SetWaterMode(bool bPresent);
	bool		RetWaterMode();

	void		SetBlitzMode(bool bPresent);
	bool		RetBlitzMode();

	void		SetSkyMode(bool bPresent);
	bool		RetSkyMode();

	void		SetBackForce(bool bPresent);
	bool		RetBackForce();

	void		SetPlanetMode(bool bPresent);
	bool		RetPlanetMode();

	void		SetLightMode(bool bPresent);
	bool		RetLightMode();

	void		SetEditIndentMode(bool bAuto);
	bool		RetEditIndentMode();

	void		SetEditIndentValue(int value);
	int			RetEditIndentValue();

	void		SetSpeed(float speed);
	float		RetSpeed();

	void		SetTracePrecision(float factor);
	float		RetTracePrecision();

	void		SetFocus(float focus);
	float		RetFocus();
	D3DVECTOR	RetEyePt();
	D3DVECTOR	RetLookatPt();
	float		RetEyeDirH();
	float		RetEyeDirV();
	POINT		RetDim();
	void		UpdateMatProj();

	void		ApplyChange();

	void		FlushPressKey();
	void		ResetKey();
	void		SetKey(int keyRank, int option, int key);
	int			RetKey(int keyRank, int option);

	void		SetJoystick(bool bEnable);
	bool		RetJoystick();

	void		SetDebugMode(bool bMode);
	bool		RetDebugMode();
	bool		RetSetupMode();

	bool		IsVisiblePoint(const D3DVECTOR &pos);

	int			DetectObject(Math::Point mouse);
	void		SetState(int state, D3DCOLOR color=0xffffffff);
	void		SetTexture(char *name, int stage=0);
	void		SetMaterial(const D3DMATERIAL7 &mat);

	void		MoveMousePos(Math::Point pos);
	void		SetMousePos(Math::Point pos);
	Math::Point		RetMousePos();
	void		SetMouseType(D3DMouse type);
	D3DMouse	RetMouseType();
	void		SetMouseHide(bool bHide);
	bool		RetMouseHide();
	void		SetNiceMouse(bool bNice);
	bool		RetNiceMouse();
	bool		RetNiceMouseCap();

	CText*		RetText();

	bool		ChangeColor(char *name, D3DCOLORVALUE colorRef1, D3DCOLORVALUE colorNew1, D3DCOLORVALUE colorRef2, D3DCOLORVALUE colorNew2, float tolerance1, float tolerance2, Math::Point ts, Math::Point ti, Math::Point *pExclu=0, float shift=0.0f, bool bHSV=false);
	bool		OpenImage(char *name);
	bool		CopyImage();
	bool		LoadImage();
	bool		ScrollImage(int dx, int dy);
	bool		SetDot(int x, int y, D3DCOLORVALUE color);
	bool		CloseImage();
	bool		WriteScreenShot(char *filename, int width, int height);
	bool		GetRenderDC(HDC &hDC);
	bool		ReleaseRenderDC(HDC &hDC);
	PBITMAPINFO	CreateBitmapInfoStruct(HBITMAP hBmp);
	bool		CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);

protected:
	void		MemSpace1(D3DObjLevel1 *&p, int nb);
	void		MemSpace2(D3DObjLevel2 *&p, int nb);
	void		MemSpace3(D3DObjLevel3 *&p, int nb);
	void		MemSpace4(D3DObjLevel4 *&p, int nb);
	void		MemSpace5(D3DObjLevel5 *&p, int nb);
	void		MemSpace6(D3DObjLevel6 *&p, int nb);

	D3DObjLevel2* AddLevel1(D3DObjLevel1 *&p1, char* texName1, char* texName2);
	D3DObjLevel3* AddLevel2(D3DObjLevel2 *&p2, int objRank);
	D3DObjLevel4* AddLevel3(D3DObjLevel3 *&p3, float min, float max);
	D3DObjLevel5* AddLevel4(D3DObjLevel4 *&p4, int reserve);
	D3DObjLevel6* AddLevel5(D3DObjLevel5 *&p5, D3DTypeTri type, const D3DMATERIAL7 &mat, int state, int nb);

	bool		IsVisible(int objRank);
	bool		DetectBBox(int objRank, Math::Point mouse);
	bool		DetectTriangle(Math::Point mouse, D3DVERTEX2 *triangle, int objRank, float &dist);
	bool		TransformPoint(D3DVECTOR &p2D, int objRank, D3DVECTOR p3D);
	void		ComputeDistance();
	void		UpdateGeometry();
	void		RenderGroundSpot();
	void		DrawShadow();
	void		DrawBackground();
	void		DrawBackgroundGradient(D3DCOLOR up, D3DCOLOR down);
	void		DrawBackgroundImageQuarter(Math::Point p1, Math::Point p2, char *name);
	void		DrawBackgroundImage();
	void		DrawPlanet();
	void		DrawFrontsize();
	void		DrawOverColor();
	bool		GetBBox2D(int objRank, Math::Point &min, Math::Point &max);
	void		DrawHilite();
	void		DrawMouse();
	void		DrawSprite(Math::Point pos, Math::Point dim, int icon);

protected:
	CInstanceManager* m_iMan;
	CD3DApplication* m_app;
	LPDIRECT3DDEVICE7 m_pD3DDevice;
	CText*			m_text;
	CLight*			m_light;
	CParticule*		m_particule;
	CWater*			m_water;
	CCloud*			m_cloud;
	CBlitz*			m_blitz;
	CPlanet*		m_planet;
	CSound*			m_sound;
	CTerrain*		m_terrain;

	int				m_blackSrcBlend[2];
	int				m_blackDestBlend[2];
	int				m_whiteSrcBlend[2];
	int				m_whiteDestBlend[2];
	int				m_diffuseSrcBlend[2];
	int				m_diffuseDestBlend[2];
	int				m_alphaSrcBlend[2];
	int				m_alphaDestBlend[2];

	D3DMATRIX		m_matProj;
	D3DMATRIX		m_matLeftView;
	D3DMATRIX		m_matRightView;
	D3DMATRIX		m_matView;
	float			m_focus;

	D3DMATRIX		m_matWorldInterface;
	D3DMATRIX		m_matProjInterface;
	D3DMATRIX		m_matViewInterface;

	DWORD			m_baseTime;
	DWORD			m_stopTime;
	float			m_absTime;
	float			m_lastTime;
	float			m_speed;
	bool			m_bPause;
	bool			m_bRender;
	bool			m_bMovieLock;

	POINT			m_dim;
	POINT			m_lastDim;
	D3DObjLevel1*	m_objectPointer;
	int				m_objectParamTotal;
	D3DObject*		m_objectParam;
	int				m_shadowTotal;
	D3DShadow*		m_shadow;
	D3DGroundSpot*	m_groundSpot;
	D3DGroundMark	m_groundMark;
	D3DVECTOR		m_eyePt;
	D3DVECTOR		m_lookatPt;
	float			m_eyeDirH;
	float			m_eyeDirV;
	int				m_rankView;
	D3DCOLOR		m_ambiantColor[2];
	D3DCOLOR		m_backColor[2];
	D3DCOLOR		m_fogColor[2];
	float			m_deepView[2];
	float			m_fogStart[2];
	D3DCOLORVALUE	m_waterAddColor;
	int				m_statisticTriangle;
	bool			m_bUpdateGeometry;
	char			m_infoText[10][200];
	int				m_alphaMode;
	bool			m_bStateColor;
	bool			m_bForceStateColor;
	bool			m_bGroundSpot;
	bool			m_bShadow;
	bool			m_bDirty;
	bool			m_bFog;
	bool			m_bFirstGroundSpot;
	int				m_secondTexNum;
	char			m_backgroundName[50];
	D3DCOLOR		m_backgroundColorUp;
	D3DCOLOR		m_backgroundColorDown;
	D3DCOLOR		m_backgroundCloudUp;
	D3DCOLOR		m_backgroundCloudDown;
	bool			m_bBackgroundFull;
	bool			m_bBackgroundQuarter;
	bool			m_bOverFront;
	D3DCOLOR		m_overColor;
	int				m_overMode;
	char			m_frontsizeName[50];
	bool			m_bDrawWorld;
	bool			m_bDrawFront;
	float			m_limitLOD[2];
	float			m_particuleDensity;
	float			m_clippingDistance;
	float			m_lastClippingDistance;
	float			m_objectDetail;
	float			m_lastObjectDetail;
	float			m_terrainVision;
	float			m_gadgetQuantity;
	int				m_textureQuality;
	bool			m_bTotoMode;
	bool			m_bLensMode;
	bool			m_bWaterMode;
	bool			m_bSkyMode;
	bool			m_bBackForce;
	bool			m_bPlanetMode;
	bool			m_bLightMode;
	bool			m_bEditIndentMode;
	int				m_editIndentValue;
	float			m_tracePrecision;

	int				m_hiliteRank[100];
	bool			m_bHilite;
	Math::Point			m_hiliteP1;
	Math::Point			m_hiliteP2;

	int				m_lastState;
	D3DCOLOR		m_lastColor;
	char			m_lastTexture[2][50];
	D3DMATERIAL7	m_lastMaterial;

	Math::Point			m_mousePos;
	D3DMouse		m_mouseType;
	bool			m_bMouseHide;
	bool			m_bNiceMouse;

	LPDIRECTDRAWSURFACE7 m_imageSurface;
	DDSURFACEDESC2	m_imageDDSD;
	WORD*			m_imageCopy;
	int				m_imageDX;
	int				m_imageDY;
};


