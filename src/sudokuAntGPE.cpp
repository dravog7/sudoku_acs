#include "sudokuAntGPE.h"
#include <iostream>

void sudokuAntGPE::globalPheromoneEvap(int valuesPerCell){
    for (int i = 0; i < numCells; i++){
        for (int j = 0; j < valuesPerCell; j++){
            pher[i][j] *= (1.0f - bestEvap);
        }
    }
}

bool sudokuAntGPE::Solve(const Board& puzzle, float maxTime )
{
	solutionTimer.Reset();
	int iter = 0;
	bool solved = false;
	bestPher = 0.0f;
	int curBestAnt = 0;
	InitPheromone( puzzle.CellCount(), puzzle.GetNumUnits() );
	while (!solved)
	{
		// start each ant on a different square
		std::uniform_int_distribution<int> dist(0, puzzle.CellCount()-1);
		for (auto a : antList)
		{
			a->InitSolution(puzzle, dist(randGen));
		}
		// fill cells one at a time
		for (int i = 0; i < puzzle.CellCount(); i++)
		{
			// step each ant in turn
			for (auto a : antList)
			{
				a->StepSolution();
			}
		}
		// update pheromone
		int iBest = 0;
		int bestVal = 0;
		for (unsigned int i = 0; i < antList.size(); i++)
		{
			if (antList[i]->NumCellsFilled() > bestVal)
			{
				bestVal = antList[i]->NumCellsFilled();
				iBest = i;
			}
		}
		float pherToAdd = PherAdd(bestVal);

		if (pherToAdd > bestPher)
		{
			// new best
			bestSol.Copy(antList[iBest]->GetSolution());
			bestPher = pherToAdd;
			curBestAnt = bestVal;
			if (bestVal == numCells)
			{
				solved = true;
				solTime = solutionTimer.Elapsed();
			}
		}
		globalPheromoneEvap(puzzle.GetNumUnits());
		UpdatePheromone();
		//bestPher *= (1.0f - bestEvap);
        
		++iter;
		// check timer every 100 iterations
		if ((iter % 100) == 0)
		{
			float elapsed = solutionTimer.Elapsed();
			if ( elapsed > maxTime)
			{
				break;
			}
		}
	}
	ClearPheromone();
	return solved;
	
}

