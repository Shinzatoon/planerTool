#pragma once

#include <stdio.h>
#include <windows.h>
#include "DataList.h"

//�t�@�C�������o���N���X
class Exporter
{
private:

public:
	void exportFile(LPSTR fileName,Dlist dataList);

};

Exporter* exporter();
