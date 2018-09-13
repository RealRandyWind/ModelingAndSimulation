// ModelingAndSimulation.cpp : Defines the entry point for the console application.
//

#include "Configurations.h"
#include "NDevTypes.h"

namespace ModelingAndSimulation
{
	using namespace NDev::Types;

	class ModelingAndSimulation_Exports CModelingAndSimulation final
	{
	public:
		~CModelingAndSimulation();

		static CModelingAndSimulation* Instance();


	private:
		CModelingAndSimulation();

		static CModelingAndSimulation* _Instance;


	};

}