#include "fileLoader.h"
#include "main.h"

FileLoader fileLoader;

FileLoader::FileLoader()
{
	// �ł���΁A���̃t�@�C�������f�t�H���g�Ƃ���̂ł͂Ȃ��A
	// stage�f�B���N�g���𒲂ׂāAstage/stage[�󂫔�].txt��ݒ肵����
	// �ǉ�����
	// stage�f�B���N�g���T��
	// �󂫔�stage.txt�e�L�X�g�t�@�C���ւ̃p�X�̐ݒ�
	_snprintf_s(currentFile,1024,"%s","stage/defaultSaveData.txt");

	_objNum = 0;
	_initialized = false;
}

void FileLoader::load(LPSTR fileName)
{
	//�������̉��
	char* p;
	char* txt;
	char record[255];
	//���L�Q�_��������Ȃ�������G���[�񍐂̏�A�ǂݍ��܂Ȃ��B
	p = strstr(fileName,"stage\\");//�ustage/�v�����ʒu������
	txt = strstr(fileName,".txt");//�ustage/�v�����ʒu������

	//�ǉ�����
	//��L�̌��ʂ���G���[�񍐂������ɒǉ�

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
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�I�u�W�F�N�g����ǂݍ���
		if (strcmp(key, "num") == 0)
		{
			_objNum = 0;
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
	//�o�O
	//�t�@�C����ǂݍ��݁A�A�v���P�[�V������������ɏo���o�O
	//delete�ŁA�������̉���������s�������A���������ŃG���[��f��
	//���炭���I�m�ۂ̌J��Ԃ��̒��ŁA�Ԉ�����m�ۂ����Ă���H
	//���I�m�ۂ̐����������������ƒ��ׂ�K�v����new,delete�ŁB
	//�G���[�\�L�ł́Aobj = new Object�ŃG���[���o�Ă���͗l
}

FileLoader* getFileLoader()
{
	return &fileLoader;
}