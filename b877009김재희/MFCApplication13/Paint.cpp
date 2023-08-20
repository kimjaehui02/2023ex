#include "stdafx.h"
#include "Paint.h"


Paint::Paint()
{
}


Paint::~Paint()
{
}

Paint::Paint(CPoint point, int color, bool rect)
{
	this->Pos_S = point;
	this->ColorType = color;
	this->RectType = rect;
}

