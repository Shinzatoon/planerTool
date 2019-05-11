#pragma once

#include <stdio.h>
#include <windows.h>

//ファイル書き出しクラス
class Exporter
{
private:

public:
	void exportFile(LPSTR fileName);

};

Exporter* exporter();
