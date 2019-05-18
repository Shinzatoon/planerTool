#pragma once

#include "main.h"
#include "icon.h"

class Cursor
{
private:

public:
	bool onDrag;//ドラッグ態かどうか
	VECTOR2 position;
	VECTOR2 recordPos;//クリックしたときのマウス座標
	VECTOR2 recordIconPos;//クリックしたときのアイコン座標
	VECTOR2 moveAmount;//移動量 
	Icon* target;
	bool onCreateIcon;//アイコン生成中
	Cursor();

	void update();

	void selectTarget(Icon* icon);

	void drag();
	
	void setTarget(Icon* icon);
};