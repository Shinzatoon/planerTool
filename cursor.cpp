
#include "cursor.h"
#include "input.h"

Cursor::Cursor()
{
	onDrag = false;

	position.x = (float)getMouseX();
	position.y = (float)getMouseY();

}

void Cursor::update()
{

	position.x = (float)getMouseX();
	position.y = (float)getMouseY();
}

void Cursor::drag(Icon* icon)
{
	if (getMouseLButton())
	{//左クリックが押されているとき
		if (icon->onCursor(position))
		{//カーソルがアイコン上にあるとき
			if (!onDrag)
			{//何かをドラッグしていなければ
			 //そのアイコンをドラッグする
				recordPos = VECTOR2((float)getMouseX(), (float)getMouseY());//クリックした瞬間のカーソル位置を保存
				recordIconPos = icon->getPos();//クリックした瞬間のアイコン位置を保存
				onDrag = true;//ドラッグ状態にする
			}
		}
		//setPosition(&back1, back1.position.x += (float)getMouseRawX(), back1.position.y += (float)getMouseRawY());
		//setPosition(&back1, (float)getMouseRawX(), (float)getMouseRawY());
	}
	else if (onDrag)
	{//左クリックが離されていて、ドラッグ状態であったならば
		onDrag = false;//ドラッグ状態をOFFにする
	}

	if (onDrag)
	{//ドラッグ状態のとき移動
		moveAmount = VECTOR2((float)getMouseX(), (float)getMouseY()) - recordPos;//カーソル移動量
		VECTOR2 virtualPos = recordIconPos + moveAmount;//仮の表示位置
		
		icon->setPos(virtualPos);
		}
}
