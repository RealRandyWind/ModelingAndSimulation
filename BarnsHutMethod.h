#pragma once

#include "NDev.h"
#include "NDevSimulation.h"

namespace ModelingAndSimulation
{
	namespace Method
	{
		using namespace NDev;
		using namespace NDev::Types;

		template<FSize SizePoint>
		struct TBarnesHut : public TSimulation<SizePoint>
		{
			using FSimulation = TSimulation<SizePoint>;
			
			struct FParameters
			{
				typename FSimulation::FPoint Delta;
				FReal Mean, SD, Alpha;
				FSize NEntities;
			};

			struct FState
			{
				TSequence<typename FSimulation::FPoint> Entities;
			};

			FParameters Parameters;
			FState State;
		
			FVoid UseDefaultParameters()
			{
				Parameters.Delta = 0.01;
				Parameters.Mean = 0;
				Parameters.SD = 1;
				Parameters.NEntities = 10000;
			}
		
		protected:
			virtual FVoid _Initialize() override
			{
				TNormal<FReal> Distribution;
				Distribution.Parameters(Parameters.Mean, Parameters.SD);
				State.Entities.Reserve(Parameters.NEntities, true);
				for (auto &Entity : State.Entities)
				{
					Distribution(Entity);
				}
			}

			virtual FVoid _Step(TSequence<typename FSimulation::FPoint> &Result, typename FSimulation::FOnVisualize OnVisualize) override
			{
				if (OnVisualize) { _Result(Result);  OnVisualize(Result); }

				this->Stop();
			}

			virtual FVoid _Result(TSequence<typename FSimulation::FPoint> &Result) override
			{
				Result.Data(State.Entities.Descriptor());
			}


		};
	}



}
