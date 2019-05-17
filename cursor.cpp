
#include "cursor.h"
#include "input.h"

Cursor::Cursor()
{
	onDrag = false;
	target = NULL;
	position.x = (float)getMouseX();
	position.y = (float)getMouseY();

}

void Cursor::update()
{

	position.x = (float)getMouseX();
	position.y = (float)getMouseY();
}

void Cursor::setTarget(Icon* icon)
{
	target = icon;//ドラッグ対象をセットする。
}

void Cursor::drag()
{
	if (target == NULL)return;//選択対象がなければリターン
	if (getMouseLButton())
	{//左クリックが押されているとき
		if (target->onCursor(position))
		{//カーソルがアイコン上にあるとき
			if (!onDrag)
			{//何かをドラッグしていなければ
			 //そのアイコンをドラッグする
				recordPos = VECTOR2((float)getMouseX(), (float)getMouseY());//クリックした瞬間のカーソル位置を保存
				recordIconPos = target->getPos();//クリックした瞬間のアイコン位置を保存
				onDrag = true;//ドラッグ状態にする
			}
		}
	}
	else if (onDrag)
	{//左クリックが離されていて、ドラッグ状態であったならば
		onDrag = false;//ドラッグ状態をOFFにする
		target = NULL;//ターゲットを手放す。
	}
	if (onDrag)
	{//ドラッグ状態のとき移動
		moveAmount = VECTOR2((float)getMouseX(), (float)getMouseY()) - recordPos;//カーソル移動量
		VECTOR2 virtualPos = recordIconPos + moveAmount;//仮の表示位置	
		target->setPos(virtualPos);
	}
}