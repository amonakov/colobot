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

// autoconvert.h

#pragma once


#include "object/auto/auto.h"
#include "common/misc.h"


class CInstanceManager;
class CD3DEngine;
class CParticule;
class CTerrain;
class CCamera;
class CObject;



enum AutoConvertPhase
{
	ACP_STOP		= 1,
	ACP_WAIT		= 2,
	ACP_CLOSE		= 3,	// close the cover
	ACP_ROTATE		= 4,	// turn the cover
	ACP_OPEN		= 5,	// opens the cover
};



class CAutoConvert : public CAuto
{
public:
	CAutoConvert(CInstanceManager* iMan, CObject* object);
	~CAutoConvert();

	void		DeleteObject(bool bAll=false);

	void		Init();
	bool		EventProcess(const Event &event);
	Error		RetError();
	bool		Abort();

	bool		CreateInterface(bool bSelect);

	bool		Write(char *line);
	bool		Read(char *line);

protected:
	CObject*	SearchStone(ObjectType type);
	bool		SearchVehicle();
	void		CreateMetal();

protected:
	AutoConvertPhase	m_phase;
	float				m_progress;
	float				m_speed;
	float				m_timeVirus;
	float				m_lastParticule;
	bool				m_bResetDelete;
	bool				m_bSoundClose;
	int					m_soundChannel;
};

