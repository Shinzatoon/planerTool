#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//#include <WindowsX.h>
//#include <crtdbg.h>

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
	int m_objNum;
	bool m_initialized;
public:
	FileLoader();
	void load(LPSTR fileName);//ì«Ç›çûÇ›ä÷êî
	void release();
	Object* getObj() { return obj; };
	int objNum() { return m_objNum; }
	bool initialized() { return m_initialized; };
};

FileLoader* getFileLoader();
