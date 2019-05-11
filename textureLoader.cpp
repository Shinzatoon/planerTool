#include "TextureLoader.h"

TextureLoader textureLoader;//インスタンス(実体)

TextureLoader* getTextureLoader()
{
	return &textureLoader;
}
LPDIRECT3DTEXTURE9* getTexture(int i)
{
	return textureLoader.getTexture(i);
}

TextureLoader::TextureLoader()
{
	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/backGround2.jpg" };
	textureName[textureLoaderNS::ENEMY_ICON] = { "TEXTURE/enemyIcon.png" };
	textureName[textureLoaderNS::PLAYER_ICON] = { "TEXTURE/playerIcon.png" };
	textureName[textureLoaderNS::STAR_ICON] = { "TEXTURE/starIcon.png" };
	textureName[textureLoaderNS::EXPORT_ICON] = { "TEXTURE/exportButton.png" };
	textureName[textureLoaderNS::BUTTON_FRAME] = { "TEXTURE/buttonFrame.png" };
}


TextureLoader::~TextureLoader()
{
	release();
}


void TextureLoader::load(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			textureName[i],		// ファイルの名前
			&g_pD3DTexture[i]);	// 読み込むメモリー
	}
}

void TextureLoader::release()
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++) {
		if (g_pD3DTexture[i] != NULL)
		{// テクスチャの開放
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}
