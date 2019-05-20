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
	//�������̉��
	char* p;
	char* txt;
	char record[255];
	p = strstr(fileName,"stage\\");//�ustage/�v�����ʒu������
	txt = strstr(fileName,".txt");//�ustage/�v�����ʒu������
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
		"�t�@�C���p�X[",
		record,
		"]��ǂݍ��݂܂��B��낵���ł����H");
	onButton = MessageBox(getHWnd(), buffer, "���[�h�t�@�C���̊m�F", MB_YESNO | MB_ICONWARNING);
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
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�I�u�W�F�N�g����ǂݍ���
		if (strcmp(key, "objnum") == 0)
		{
			_objNum;
			fscanf_s(fp, "%d", &_objNum);
			obj = new Object[_objNum];//�I�u�W�F�N�g��p�ӂ���B
		}
	}

	fseek(fp, SEEK_SET, 0);//�t�@�C���V�[�N�ʒu��擪�Ƀ��Z�b�g
	Object o;//�i�[�p
	int count = 0;
	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�I�u�W�F�N�g����ǂݍ���
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