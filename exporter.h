#pragma once

#include <stdio.h>
#include <windows.h>

//�t�@�C�������o���N���X
class Exporter
{
private:

public:
	void exportFile(LPSTR fileName);

};

Exporter* exporter();
