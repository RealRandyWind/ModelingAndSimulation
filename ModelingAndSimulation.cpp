// ModelingAndSimulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ModelingAndSimulation.h"

using namespace ModelingAndSimulation;

CModelingAndSimulation* CModelingAndSimulation::_Instance = NullPtr;

CModelingAndSimulation::CModelingAndSimulation()
{

}

CModelingAndSimulation::~CModelingAndSimulation()
{

}

CModelingAndSimulation* CModelingAndSimulation::Instance()
{
	if (!_Instance) { _Instance = new CModelingAndSimulation(); }
	return _Instance;
}
