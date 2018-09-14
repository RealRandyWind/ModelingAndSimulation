// SimulatingCollidingGalaxies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace NDev;
using namespace NDev::Types;

using namespace ModelingAndSimulation;

FReturn main()
{
	auto Window = FWindow::Default();
	TUniform<FReal> Distribution;
	TSequence<TPoint4D<FReal>> Vertices(3, true);
	for (auto &Vertex : Vertices) { Distribution(Vertex.Point); }
	FWindow::Display(Vertices.Descriptor(), Window);

	return FWindow::Wait();
}

