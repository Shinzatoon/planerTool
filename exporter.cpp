#include "main.h"
#include "exporter.h"
Exporter g_exporter;
void Exporter::exportFile(LPSTR fileName,Dlist dataList)
{
	if (dataList.IsEmpty())
	{
		MessageBox(getHWnd(),
			"�f�[�^�����݂��Ȃ��̂ŁA�����o�����Ƃ��ł��܂���B",
			"�G�N�X�|�[�g���s",
			MB_OK | MB_ICONWARNING);
		return;
	}
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "wt");

	//�I�u�W�F�N�g�̐��������o��
	fprintf_s(fp, "objNum %d\n", dataList.size());

	bool complete = false;
	dataList.setHead();//���X�g��擪�ɂ���
	while (!complete)
	{//�f�[�^�̃��X�g���Ō�ɂȂ�܂ő�����
		fprintf_s(fp, "obj %05d %d %.2f %.2f %.2f\n",
			dataList.crnt->data.getID(),
			dataList.crnt->data.getType(),
			dataList.crnt->data.getLeft(),
			dataList.crnt->data.getRight(),
			dataList.crnt->data.getAngle()
			);
		
		if (dataList.Next() == 0)
		{//���̃��X�g�f�[�^���Ȃ����
			complete = true;
		}
	}
	fclose(fp);
	MessageBox(getHWnd(),
		"�t�@�C���̏����o�����s���܂����B",
		"�G�N�X�|�[�g����",
		MB_OK | MB_ICONWARNING);
}

Exporter* exporter() { return &g_exporter; }	