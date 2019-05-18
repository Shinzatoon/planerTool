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
Icon icon[ICON_NUM];



Cursor cursor;
Dlist objList;
bool checkin = false;

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0,WINDOW_WIDTH, WINDOW_HEIGHT);
	
	//アイコンの初期化
	for (int i = 0; i < ICON_NUM;i++)
	{
		icon[i].initialize(i);
	}
	objList.Initialize();//リストの初期化
};


void updateTitle() {

	Icon obj;//新たに作成するオブジェクトの初期化用
	if (getFileLoader()->untreated())
	{//ファイルが読み込まれて、未処理状態になった場合
		objList.Clear();//全ノードを削除
		int objNum = getFileLoader()->objNum();
		Object* o = getFileLoader()->getObj();
		for (int i = 0; i < objNum; i++)
		{//読み込んだファイルの情報に従って、リストを追加していく。
			obj.initialize(
				o[i].objType,
				VECTOR2(
					o[i].position.x+icon[EDITER_AREA].getLeft(),
					o[i].position.y+icon[EDITER_AREA].getTop()),
				o[i].id,
				o[i].rotation
			);//新たに作成するオブジェクトの初期化
			objList.InsertAfter(objList.crnt, &obj);//オブジェクトの生成(リストへ登録)
		}
		getFileLoader()->processed();//処理を完了状態にする
	}

	cursor.update();//カーソルの更新
	for (int i = 0; i < ICON_NUM; i++) {
		icon[i].update();//アイコンの更新
	}
	
	if (getMouseLTrigger())
	{// 左クリックされた時
		if (cursor.onCreateIcon==false)
		for (int i = 0; i < ICON_NUM; i++)
		{
			if (!icon[i].canDuplicate)continue;//複製可能アイコンの場合
			int id;//固有番号の設定
			if (objList.IsEmpty()) {id = 0;}
			else {//objList.Search()//IDの最大値を探索する。
				//とりあえずは、着目ノードのIDの次の番号を代入
				id = objList.crnt->prev->data.getID() + 1;}
			if (icon[i].onCursor())
			{// カーソルがプレイヤーアイコン上にあった場合
				obj.initialize(i,
					icon[i].getPos(),
					id, 
					0
				);//新たに作成するオブジェクトの初期化
				objList.InsertAfter(objList.crnt, &obj);//オブジェクトの生成(リストへ登録)
				cursor.onCreateIcon = true;
				cursor.setTarget(&objList.crnt->data);//カーソルの選択対象としてセットする。
			}
		}
	}

	objList.update();



	if (getMouseLRelease())
	{//左クリックが離されたとき
		if (cursor.onCreateIcon)//オブジェクトを生成していた場合
		{
			if (cursor.target == NULL)
			{//カーソルのターゲットがNULLでない場合
				objList.RemoveCurrent();
			}
			else {//カーソルのターゲットがNULLでない場合
				if (icon[EDITER_AREA].getLeft() > cursor.target->getLeft() ||
					icon[EDITER_AREA].getRight() < cursor.target->getRight() ||
					icon[EDITER_AREA].getTop() > cursor.target->getTop() ||
					icon[EDITER_AREA].getBottom() < cursor.target->getBottom())
				{//生成したオブジェクトがエリア内でない場合
					objList.RemoveCurrent();
				}
			}
			cursor.onCreateIcon = false;//生成状態を解除
		}
	}


	//選択対象オブジェクトがあればドラッグを行う。
	cursor.drag();

};

void drawTitle() {

	DrawImage(&back);//背景の描画
	for (int i = 0; i < ICON_NUM; i++) {
		icon[i].draw();
	}
	objList.Print();//リスト内を全て描画する
};

void printTitle() {

	printTextDX(getDebugFont(), "Title", 0, 0);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 20, getMouseY());

	//プロパティの表示
	if (cursor.target == NULL) {
		printTextDX(getDebugFont(), "■ オブジェクトを選択してください。", 1230, 60);
		printTextDX(getDebugFont(), "高さ:", 1300, 80);
		printTextDX(getDebugFont(), "幅　:", 1300, 100);
	}
	else if(cursor.target->onCursor())
	{
		printTextDX(getDebugFont(), "■ プレイヤー", 1230, 60);
		printTextDX(getDebugFont(), "高さ:", 1300, 80, cursor.target->getHeight());
		printTextDX(getDebugFont(), "幅　:", 1300, 100, cursor.target->getWidth());
	}

	//マウス左ボタントリガー
	if (getMouseLTrigger()){
		printTextDX(getDebugFont(), "MouseLButton[Trigger]:true", 500, 0);
	}else{
		printTextDX(getDebugFont(), "MouseLButton[Trigger]:false", 500, 0);}
	//マウス左ボタンリリース
	if (getMouseLRelease()){
		printTextDX(getDebugFont(), "MouseLButton[Release]:true", 500, 20);
	}else{
		printTextDX(getDebugFont(), "MouseLButton[Release]:false", 500, 20);}



	for (int i = 0; i < ICON_NUM; i++)
	{
		if (icon[i].onCursor())
		{
			printTextDX(getDebugFont(), "挿入った", 200, 0);
		}
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

void unInitializeTitle() 
{
	UninitImage(&back);
	objList.Terminate();
};