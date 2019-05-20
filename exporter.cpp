#include "main.h"
#include "exporter.h"
Exporter g_exporter;
void Exporter::exportFile(LPSTR fileName,Dlist dataList)
{
	if (dataList.IsEmpty())
	{
		MessageBox(getHWnd(),
			"データが存在しないので、書き出すことができません。",
			"エクスポート失敗",
			MB_OK | MB_ICONWARNING);
		return;
	}
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "wt");

	//オブジェクトの数を書き出す
	fprintf_s(fp, "objNum %d\n", dataList.size());

	bool complete = false;
	dataList.setHead();//リストを先頭にする
	while (!complete)
	{//データのリストが最後になるまで続ける
		fprintf_s(fp, "obj %05d %d %.2f %.2f %.2f\n",
			dataList.crnt->data.getID(),
			dataList.crnt->data.getType(),
			dataList.crnt->data.getLeft(),
			dataList.crnt->data.getRight(),
			dataList.crnt->data.getAngle()
			);
		
		if (dataList.Next() == 0)
		{//次のリストデータがなければ
			complete = true;
		}
	}
	fclose(fp);
	MessageBox(getHWnd(),
		"ファイルの書き出しを行いました。",
		"エクスポート完了",
		MB_OK | MB_ICONWARNING);
}

Exporter* exporter() { return &g_exporter; }	