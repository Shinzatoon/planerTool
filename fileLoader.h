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

#define DIRECTORY_PASS "stage/"

struct Object {
	int id;
	int objType;
	D3DXVECTOR2 position;
	float rotation;
};

class FileLoader
{
private:
	char currentFile[1024];
	Object* obj;
	int _objNum;
	bool _initialized;//���������ꂽ
	bool _untreated;//���������
public:
	FileLoader();
	void load(LPSTR fileName);//�ǂݍ��݊֐�
	void release();
	Object* getObj() { return obj; };
	int objNum() { return _objNum; }
	bool initialized() { return _initialized; }
	bool untreated() { return _untreated; }//���������
	void processed() { _untreated = false; }
	char* getCurrentFile() { return currentFile; }
};

FileLoader* getFileLoader();
