#include "fileLoader.h"

FileLoader fileLoader;

FileLoader::FileLoader()
{
	m_objNum = 0;
	m_initialized = false;
}

void FileLoader::load(LPSTR fileName)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "rt");

	char key[255] = { 0 };

	if (m_initialized)
	{
		delete[] obj;
	}

	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//オブジェクト数を読み込む
		if (strcmp(key, "objnum") == 0)
		{
			m_objNum;
			fscanf_s(fp, "%d", &m_objNum);
			obj = new Object[m_objNum];//オブジェクトを用意する。
		}
	}

	fseek(fp, SEEK_SET, 0);//ファイルシーク位置を先頭にリセット
	Object o;//格納用
	int count = 0;
	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//オブジェクト情報を読み込む
		if (strcmp(key, "obj") == 0)
		{
			fscanf_s(fp, "%d %d %f %f %f",	&o.id,&o.objType,&o.position.x,&o.position.y,&o.rotation);
			obj[count] = o;
			count++;
		}
	}
	fclose(fp);
	m_initialized = true;
}

void FileLoader::release()
{
	delete[] obj;
}

FileLoader* getFileLoader()
{
	return &fileLoader;
}