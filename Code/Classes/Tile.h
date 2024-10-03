#pragma once
#include "Figure.h"

class Tile
{
private:
	Figure* figureOnTile = nullptr;

public:

	Figure* GetFigure() const {
		return figureOnTile;
	};

	void SetFigure(Figure *figureOnTile_) {
		figureOnTile = figureOnTile_;
	};


};

