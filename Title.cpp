#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include "textureLoader.h"
#include "input.h"
#include "DataList.h"
#include "fileLoader.h"
#include "exporter.h"
#include "icon.h"
#include "cursor.h"

Image back;
Image back1;
Image back2;
Image back3;	//後で配列にしよう！！

Icon playerIcon;

Icon exportButton;
Cursor cursor;
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
	
	playerIcon.initialize(PLAYER_ICON);

	objList.Initialize();//リストの初期化

	exportButton.initialize(EXPORT_ICON);
};

void updateTitle() {

	cursor.update();//カーソルの更新

	exportButton.update();
	
	bool onCreateIcon = false;
	Icon obj;//新たに作成するオブジェクトの初期化用
	if (getMouseLTrigger())
	{// 左クリックされた時
		if (playerIcon.onCursor(cursor.position))
		{// カーソルがプレイヤーアイコン上にあった場合
			obj.initialize(PLAYER_ICON,playerIcon.getPos());//新たに作成するオブジェクトの初期化
			objList.InsertAfter(objList.crnt, &obj);//オブジェクトの生成(リストへ登録)
			onCreateIcon = true;
			cursor.setTarget(&objList.crnt->data);//カーソルの選択対象としてセットする。
		}
		
		//リストの全走査


	}


	//選択対象オブジェクトがあればドラッグを行う。
	cursor.drag();

};

void drawTitle() {
	
	DrawImage(&back);
	DrawImage(&back1);
	DrawImage(&back2);
	DrawImage(&back3);

	playerIcon.draw();
	objList.Print();//リスト内を全て描画する

	exportButton.draw();

};

void printTitle() {

	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());


	//プロパティの表示
	if (getMouseLButton())
	{
		if (oncursor(back2))
		{
			printTextDX(getDebugFont(), "■ プレイヤー", 1230, 60);
			printTextDX(getDebugFont(), "高さ:", 1300, 80, back2.height);
			printTextDX(getDebugFont(), "幅　:", 1300, 100, back2.width);
			if (!onDrag)
			{
			}
		}
	}


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

	//ドラッグしたファイル内情報を表示
	if (getFileLoader()->initialized())
	{
		printTextDX(getDebugFont(), "id", 0, WINDOW_HEIGHT / 2 - 20);
		printTextDX(getDebugFont(), ":objType", 100, WINDOW_HEIGHT / 2 -20);
		printTextDX(getDebugFont(), ":x", 200, WINDOW_HEIGHT / 2 -20);
		printTextDX(getDebugFont(), ":y", 300, WINDOW_HEIGHT / 2 -20);
		printTextDX(getDebugFont(), ":rot", 400, WINDOW_HEIGHT / 2 -20);
		int objNum = getFileLoader()->objNum();
		Object* o = getFileLoader()->getObj();
		for (int i = 0;i < objNum; i++)
		{
			printTextDX(getDebugFont(), "", 0, WINDOW_HEIGHT / 2 + (i * 20), o[i].id);
			printTextDX(getDebugFont(), ":", 100, WINDOW_HEIGHT / 2 + (i * 20), o[i].objType);
			printTextDX(getDebugFont(), ":", 200, WINDOW_HEIGHT / 2 + (i * 20), o[i].position.x);
			printTextDX(getDebugFont(), ":", 300, WINDOW_HEIGHT / 2 + (i * 20), o[i].position.y);
			printTextDX(getDebugFont(), ":", 400, WINDOW_HEIGHT / 2 + (i * 20), o[i].rotation);
		}
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
bool on(Image img)
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

				recordCursor = VECTOR2((float)getMouseX(), (float)getMouseY());//クリックした瞬間のカーソル位置を保存
				recordIcon = (VECTOR2)Target->position;//クリックした瞬間のアイコン位置を保存
				onDrag = true;//ドラッグ状態にする
			}
		}
	}
	else if (onDrag)
	{//左クリックが離されていて、ドラッグ状態であったならば
		onDrag = false;//ドラッグ状態をOFFにする
		Target = NULL;
	}

	if (onDrag && Target != NULL)
	{//ドラッグ状態のとき移動
		cursorMoveAmount = VECTOR2((float)getMouseX(), (float)getMouseY()) - recordCursor;//カーソル移動量
		VECTOR2 virtualPos = recordIcon + cursorMoveAmount;//仮の表示位置
		setPosition(Target, virtualPos.x, virtualPos.y);
	}

}

void unInitializeTitle() 
{
	objList.Terminate();
};