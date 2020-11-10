#pragma once
#include <vector>
#include <random>
#include "sudokuantsystem.h"


class sudokuAntGPE : public SudokuAntSystem
{
	void globalPheromoneEvap(int valuesPerCell);
public:
	sudokuAntGPE(int numAnts, float q0, float rho, float pher0, float bestEvap) : 
	SudokuAntSystem(numAnts, q0, rho, pher0, bestEvap)
	{
	}
	virtual bool Solve(const Board& puzzle, float maxTime );
};
