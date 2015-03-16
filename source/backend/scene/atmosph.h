//******************************************************************************
///
/// @file backend/scene/atmosph.h
///
/// This module contains all defines, typedefs, and prototypes for
/// `atmosph.cpp`.
///
/// @copyright
/// @parblock
///
/// Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
/// Copyright 1991-2015 Persistence of Vision Raytracer Pty. Ltd.
///
/// POV-Ray is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as
/// published by the Free Software Foundation, either version 3 of the
/// License, or (at your option) any later version.
///
/// POV-Ray is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
///
/// You should have received a copy of the GNU Affero General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// ----------------------------------------------------------------------------
///
/// POV-Ray is based on the popular DKB raytracer version 2.12.
/// DKBTrace was originally written by David K. Buck.
/// DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
///
/// @endparblock
///
//******************************************************************************

#ifndef ATMOSPH_H
#define ATMOSPH_H

#include "core/material/pigment.h"

namespace pov
{

/*****************************************************************************
* Global preprocessor defines
******************************************************************************/

/* Define fog types. DMF */

#define ORIG_FOG    1
#define GROUND_MIST 2
#define FOG_TYPES   2

/*****************************************************************************
* Global typedefs
******************************************************************************/

typedef struct Fog_Struct FOG;
typedef struct Rainbow_Struct RAINBOW;
typedef struct Skysphere_Struct SKYSPHERE;

struct TurbulenceWarp; // full declaration in core/material/warp.h

struct Fog_Struct
{
    Fog_Struct() : Turb(NULL), Next(NULL) {}
    ~Fog_Struct() { if (Turb) POV_FREE(Turb); }
    int Type;
    DBL Distance;
    DBL Alt;
    DBL Offset;
    TransColour colour; // may have a filter/transmit component
    Vector3d Up;
    TurbulenceWarp *Turb;
    SNGL Turb_Depth;
    FOG *Next;
};

struct Rainbow_Struct
{
    Rainbow_Struct() : Pigment(NULL), Next(NULL) {}
    ~Rainbow_Struct() { if (Pigment) delete Pigment; }
    DBL Distance;
    DBL Jitter;
    DBL Angle, Width;
    DBL Arc_Angle, Falloff_Angle, Falloff_Width;
    Vector3d Antisolar_Vector;
    Vector3d Up_Vector, Right_Vector;
    PIGMENT *Pigment;
    RAINBOW *Next;
};

struct Skysphere_Struct
{
    Skysphere_Struct() : Trans(NULL) {}
    ~Skysphere_Struct() { for (vector<PIGMENT*>::iterator i = Pigments.begin(); i != Pigments.end(); ++ i) delete *i; if (Trans) POV_FREE(Trans); }
    MathColour        Emission; ///< Brightness adjustment.
    vector<PIGMENT *> Pigments; ///< Pigment(s) to use.
    TRANSFORM *       Trans;    ///< Skysphere transformation.
};

/*****************************************************************************
* Global functions
******************************************************************************/

FOG *Create_Fog (void);
FOG *Copy_Fog (const FOG *Fog);
void Destroy_Fog (FOG *Fog);

RAINBOW *Create_Rainbow (void);
RAINBOW *Copy_Rainbow (const RAINBOW *Rainbow);
void Destroy_Rainbow (RAINBOW *Rainbow);

SKYSPHERE *Create_Skysphere (void);
SKYSPHERE *Copy_Skysphere (const SKYSPHERE *Skysphere);
void Destroy_Skysphere (SKYSPHERE *Skysphere);
void Scale_Skysphere (SKYSPHERE *Skysphere, const Vector3d& Vector);
void Rotate_Skysphere (SKYSPHERE *Skysphere, const Vector3d& Vector);
void Translate_Skysphere (SKYSPHERE *Skysphere, const Vector3d& Vector);
void Transform_Skysphere (SKYSPHERE *Skysphere, const TRANSFORM *Trans);

}

#endif
