#include "fileLoader.h"

FileLoader fileLoader;

FileLoader::FileLoader()
{
	_objNum = 0;
	_initialized = false;
}

void FileLoader::load(LPSTR fileName)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "rt");

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