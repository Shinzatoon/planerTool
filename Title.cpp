#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"
#include"input.h"
#include "CircDblLinkedList.h"

Image back;
Image back1;
Image back2;
Image back3;	//後で配列にしよう！！
Dlist objList;


bool checkin = false;

VECTOR2 cursorMoveAmount;//移動量 
VECTOR2 recordCursor; //クリックしたときのマウス座標
VECTOR2 recordIcon; //クリックしたときのアイコン座標


bool onDrag = false;//ドラッグされているか
bool onDrag2 = false;//ドラッグされているか


bool oncursor(Image);

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0,WINDOW_WIDTH, WINDOW_HEIGHT);
	InitImage(&back1, getTexture(textureLoaderNS::ENEMY_ICON), 100, 160, 100, 100);
	InitImage(&back2, getTexture(textureLoaderNS::PLAYER_ICON), 100, 320, 100, 100);
	InitImage(&back3, getTexture(textureLoaderNS::STAR_ICON), 100, 480, 100, 100);
	
	Initialize(&objList);//リストの初期化

	InsertAfter(&objList, objList.crnt, new Image());//新しいImage構造体を追加する 登録　new
	InitImage(&objList.crnt->data, getTexture(textureLoaderNS::ENEMY_ICON), 100, 160, 100, 100);//現在さしているノードを初期化
	
};
void updateTitle() {

	moveControl(&back1);

	moveControl(&back2);
	//if (getMouseLButton())
	//{//左クリックが押されているとき
	//	if (oncursor(back1)) 
	//	{//カーソルがアイコン上にあるとき
	//		if (!onDrag)
	//		{//何かをドラッグしていなければ
	//			//そのアイコンをドラッグする
	//			recordCursor = VECTOR2(getMouseX(), getMouseY());//クリックした瞬間のカーソル位置を保存
	//			recordIcon = (VECTOR2)back1.position;//クリックした瞬間のアイコン位置を保存
	//			onDrag = true;//ドラッグ状態にする
	//		}
	//	}
	//	//setPosition(&back1, back1.position.x += (float)getMouseRawX(), back1.position.y += (float)getMouseRawY());
	//	//setPosition(&back1, (float)getMouseRawX(), (float)getMouseRawY());
	//}
	//else if (onDrag)
	//{//左クリックが離されていて、ドラッグ状態であったならば
	//	onDrag = false;//ドラッグ状態をOFFにする
	//}

	//if (onDrag)
	//{//ドラッグ状態のとき移動
	//	cursorMoveAmount = VECTOR2(getMouseX(), getMouseY()) - recordCursor;//カーソル移動量
	//	VECTOR2 virtualPos = recordIcon + cursorMoveAmount;//仮の表示位置
	//	setPosition(&back1, virtualPos.x, virtualPos.y);
	//}
	

	


};
void drawTitle() {
	DrawImage(&back);
	DrawImage(&back1);
	DrawImage(&back2);
	DrawImage(&back3);


	DrawImage(&objList.crnt->data);//現在さしているノードを描画する

};
void printTitle() {
	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());
	if (getMouseLButton())
	{
		printTextDX(getDebugFont(), "mouseX:", 500, 0, getMouseRawX());
		printTextDX(getDebugFont(), "mouseY:", 500, 20, getMouseRawY());

	}
	if (oncursor(back1))
	{
		printTextDX(getDebugFont(), "挿入った", 500, 0);
	}
	if (oncursor(back2))
	{
		printTextDX(getDebugFont(), "挿入った", 500, 0);
	}
	if (oncursor(back3))
	{
		printTextDX(getDebugFont(), "挿入った", 500, 0);
	}
};
bool oncursor(Image img)
{
	if (img.position.x < getMouseX() && img.position.x + img.height > getMouseX() &&
		img.position.y < getMouseY() && img.position.y + img.width > getMouseY())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Image a[1];
Image *Target;

void moveControl(Image *img)
{
	if (getMouseLButton())
	{//左クリックが押されているとき
		if (oncursor(*img))
		{//カーソルがアイコン上にあるとき
			if (!onDrag)
			{//何かをドラッグしていなければ
				//そのアイコンをドラッグする
				Target = img;

				recordCursor = VECTOR2(getMouseX(), getMouseY());//クリックした瞬間のカーソル位置を保存
				recordIcon = (VECTOR2)Target->position;//クリックした瞬間のアイコン位置を保存
				onDrag = true;//ドラッグ状態にする
			}
		}
		//setPosition(&back1, back1.position.x += (float)getMouseRawX(), back1.position.y += (float)getMouseRawY());
		//setPosition(&back1, (float)getMouseRawX(), (float)getMouseRawY());
	}
	else if (onDrag)
	{//左クリックが離されていて、ドラッグ状態であったならば
		onDrag = false;//ドラッグ状態をOFFにする
		Target = NULL;
	}

	if (onDrag && Target != NULL)
	{//ドラッグ状態のとき移動
		cursorMoveAmount = VECTOR2(getMouseX(), getMouseY()) - recordCursor;//カーソル移動量
		VECTOR2 virtualPos = recordIcon + cursorMoveAmount;//仮の表示位置
		setPosition(Target, virtualPos.x, virtualPos.y);
	}
}

////mallocサンプル
//int main()
//{
//	int i;
//	int *heep;
//	heep = (int*)malloc(sizeof(int) * 10);
//
//	if (heep == NULL)
//		exit(0);
//
//	for (i = 0; i < 10; i++)
//	{
//		heep[i] = i;
//	}
//	printf("%d\n", heep[5]);
//
//	free(heep);
//
//	return 0;
//}

void unInitializeTitle() {};