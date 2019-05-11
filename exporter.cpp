#include "exporter.h"
Exporter g_exporter;
void Exporter::exportFile(LPSTR fileName)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "wt");



	fclose(fp);
}

Exporter* exporter() { return &g_exporter; }	