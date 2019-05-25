#include "fileLoader.h"
#include "main.h"

FileLoader fileLoader;

FileLoader::FileLoader()
{
	// できれば、このファイル名をデフォルトとするのではなく、
	// stageディレクトリを調べて、stage/stage[空き番].txtを設定したい
	// 追加処理
	// stageディレクトリ探査
	// 空き番stage.txtテキストファイルへのパスの設定
	_snprintf_s(currentFile,1024,"%s","stage/defaultSaveData.txt");

	_objNum = 0;
	_initialized = false;
}

void FileLoader::load(LPSTR fileName)
{
	//文字情報の解析
	char* p;
	char* txt;
	char record[255];
	//下記２点が見つからなかったらエラー報告の上、読み込まない。
	p = strstr(fileName,"stage\\");//「stage/」文字位置を検索
	txt = strstr(fileName,".txt");//「stage/」文字位置を検索

	//追加処理
	//上記の結果からエラー報告をここに追加

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
	if(onButton == IDNO)return;

	_snprintf_s(currentFile,1024,"%s",record);
	FILE* fp = NULL;
	fopen_s(&fp, currentFile, "rt");

	char key[255] = { 0 };

	if (_initialized)
	{
		delete[] obj;
	}

	while (!feof(fp) || strcmp(key,"num") == 0)
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//オブジェクト数を読み込む
		if (strcmp(key, "num") == 0)
		{
			_objNum = 0;
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
	//バグ
	//ファイルを読み込み、アプリケーションを閉じた時に出たバグ
	//deleteで、メモリの解放処理を行ったが、何かが問題でエラーを吐く
	//恐らく動的確保の繰り返しの中で、間違った確保をしている？
	//動的確保の正しいやり方をもっと調べる必要ありnew,deleteで。
	//エラー表記では、obj = new Objectでエラーが出ている模様
}

FileLoader* getFileLoader()
{
	return &fileLoader;
}