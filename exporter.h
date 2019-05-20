#pragma once

#include <stdio.h>
#include <windows.h>
#include "DataList.h"

//ファイル書き出しクラス
class Exporter
{
private:

public:
	void exportFile(LPSTR fileName,Dlist dataList);

};

Exporter* exporter();
