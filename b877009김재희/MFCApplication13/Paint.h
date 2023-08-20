#pragma once
#include "Shape.h"
class Paint :
	public Shape
{
private :

public:
	Paint();
	~Paint();

public :
	Paint(CPoint point, int color, bool rect);

	int ColorType = 0;

	bool RectType = true;

	int C_Num = 0;

};

