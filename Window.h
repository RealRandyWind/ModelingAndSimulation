#pragma once

#include "NDevTypes.h"
#include "NDevDefinitions.h"
#include "NDevPoint.h"
#include "NDevMathAliases.h"

namespace ModelingAndSimulation
{
	using namespace NDev::Types;

	struct FWindow
	{ 
		FReal LookSpeed, MoveSpeed, FieldOfView, AspectRatio, Near, Far;
		FSize Width, Height, X, Y;
		FBoolean bFullScreen, bWait, bPerspective;
		FString Title, Style, Simulation;
		NDev::TColor<FReal> Color;
		NDev::TPoint3D<FReal> LookAt, Position, Up;
		FReturn _ErrorNo;
		FPointer _State;

		static FWindow Default();

		static FWindow& Display(const NDev::FDescriptor &, FWindow &);

		FVoid Update(const NDev::FDescriptor &, FWindow &);

		static FReturn Wait();

		static FPointer _Application;
		static char** _Arguments;
		static int _ArgumentCount;
	};


}


