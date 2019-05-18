#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

enum OBJ_TYPE
{
	T_PLAYER,
	T_WALL,
	T_ENEMY,
	T_STAR,
};

struct Object {
	int id;
	int objType;
	D3DXVECTOR2 position;
	float rotation;
};

class FileLoader
{
private:
	Object* obj;
	int _objNum;
	bool _initialized;//初期化された
	bool _untreated;//未処理状態
public:
	FileLoader();
	void load(LPSTR fileName);//読み込み関数
	void release();
	Object* getObj() { return obj; };
	int objNum() { return _objNum; }
	bool initialized() { return _initialized; }
	bool untreated() { return _untreated; }//未処理状態
	void processed() { _untreated = false; }

};

FileLoader* getFileLoader();
