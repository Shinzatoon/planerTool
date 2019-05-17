#pragma once

#include "main.h"
#include "icon.h"

class Cursor
{
private:

public:
	bool onDrag;//ƒhƒ‰ƒbƒO‘Ô‚©‚Ç‚¤‚©
	VECTOR2 position;
	VECTOR2 recordPos;
	VECTOR2 recordIconPos;
	VECTOR2 moveAmount;
	Icon* target;


	Cursor();

	void update();

	void drag();
	
	void setTarget(Icon* icon);
};