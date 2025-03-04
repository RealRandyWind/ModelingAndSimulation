// SimulatingCollidingGalaxies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace NDev;
using namespace NDev::Types;

using namespace ModelingAndSimulation;

FReturn main()
{
	using FBarnesHut = Method::TBarnesHut<4>;
	
	auto Window = FWindow::Default();
	
	FBarnesHut BarnsHut;
	TData<FBarnesHut::FPoint> Result;
	
	BarnsHut.OnVisualizeResult = [&Window](auto &_Result) {
		FWindow::Display(_Result.Descriptor(), Window);
		Sleep(1000 / 60);
	};
	BarnsHut.UseDefaultParameters();
	BarnsHut.Initialize();
	BarnsHut.Start(Result);

	return FWindow::Wait();
}

