#include "fileLoader.h"
#include "main.h"

FileLoader fileLoader;

FileLoader::FileLoader()
{
	_snprintf_s(currentFile,1024,"%s","defaultSaveData");
	_objNum = 0;
	_initialized = false;
}

void FileLoader::load(LPSTR fileName)
{
	//文字情報の解析
	char* p;
	char* txt;
	char record[255];
	p = strstr(fileName,"stage\\");//「stage/」文字位置を検索
	txt = strstr(fileName,".txt");//「stage/」文字位置を検索
	int i = 0;
	while (p != txt)
	{
		record[i] = *p;
		i++; p++;
	}
	record[i] = '\0';
	_snprintf_s(record, 255, "%s%s", record, ".txt");

	const int BUF_SIZE = 1024;
	char buffer[BUF_SIZE];
	int onButton;
	_snprintf_s(buffer, BUF_SIZE, "%s%s%s",
		"ファイルパス[",
		record,
		"]を読み込みます。よろしいですか？");
	onButton = MessageBox(getHWnd(), buffer, "ロードファイルの確認", MB_YESNO | MB_ICONWARNING);
	if (onButton == IDNO)return;

	_snprintf_s(currentFile,1024,"%s",record);
	FILE* fp = NULL;
	fopen_s(&fp, currentFile, "rt");

	char key[255] = { 0 };

	if (_initialized)
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
			_objNum;
			fscanf_s(fp, "%d", &_objNum);
			obj = new Object[_objNum];//オブジェクトを用意する。
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
	_initialized = true;
	_untreated = true;
}

void FileLoader::release()
{
	delete[] obj;
}

FileLoader* getFileLoader()
{
	return &fileLoader;
}