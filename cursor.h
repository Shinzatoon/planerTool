#pragma once

#include "main.h"
#include "icon.h"

class Cursor
{
private:

public:
	bool onDrag;//�h���b�O�Ԃ��ǂ���
	VECTOR2 position;
	VECTOR2 recordPos;
	VECTOR2 recordIconPos;
	VECTOR2 moveAmount;


	Cursor();

	void update();

	void drag(Icon* icon);
};