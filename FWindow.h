#pragma once

#include "NDevTypes.h"

namespace ModelingAndSimulation
{
	using namespace NDev::Types;

	struct FWindow
	{ 
		static FWindow *Display(FPointer PtrData, FSize Size, FSize SizeOf, FWindow *PtrWindow = NullPtr);

	};


}


