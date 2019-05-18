#pragma once

#include "main.h"
#include <stdarg.h>

enum InitializeMethod{
	DEFAULT,
	ANIME,
	COLOR,
};

typedef struct {
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffer = NULL;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DTEXTURE9*		textureArray = NULL;		// 切替テクスチャへのポインタ
	int listNum = 0;
	D3DXCOLOR color[4]; // 画像の頂点カラー
	D3DXVECTOR3 position; // 画像の位置
	float width; // 幅
	float height; // 高さ
	float angle;
	bool playAnime; // アニメーション再生フラグ
	int	g_nCountAnime; // アニメーションカウント(更新フレーム数の保存)
	int	g_nPatternAnime;	// アニメーションパターンナンバー
	int ANIME_TIME; // アニメーション時間(フレーム数)
	int ANIME_PATTERN; // アニメーションパターン数
	int DIVIDE_U; // テクスチャU方向[横/x方向]分割数 
	int DIVIDE_V; // テクスチャV方向[縦/y方向]分割数
	bool renderFlag; // 描画フラグ
}Image;

// image: 初期化するImage構造体
// texture: Imageに使用するテクスチャポインタ
// x:画面上で配置するx位置
// y:画面上で配置するy位置
// width:Imageオブジェクトの幅
// height:Imageオブジェクトの高さ
void InitImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height);


// image: 初期化するImage構造体
// texture: Imageに使用するテクスチャポインタ
// x:画面上で配置するx位置
// y:画面上で配置するy位置
// width:Imageオブジェクトの幅
// height:Imageオブジェクトの高さ
// color:ポリゴンの頂点カラー
void InitImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height, D3DXCOLOR color);

// アニメーション付きImageの初期化
// image: 初期化するImage構造体
// texture: Imageに使用するテクスチャポインタ
// x:画面上で配置するx位置
// y:画面上で配置するy位置
// width:Imageオブジェクトの幅
// height:Imageオブジェクトの高さ
// time:１アニメーションあたりのフレーム数
// pattern:アニメーションのパターン数
// divide_u:横[U]方向の分割数
// divide_v:横[V]方向の分割数
void InitAnimeImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height,
	int time, int pattern, int divide_u, int divide_v);

void UninitImage(Image* image);
void DrawImage(Image* image);

// Imageのテクスチャ位置をセットする
void SetTexture(Image* image);
void SetTexture(Image* image, float ratioU, float ratioV);


// Imageの位置を変更する
void setPosition(Image* image, float _x, float _y);
// Imageのサイズを変更する
void setSize(Image* image, float _width, float _height);
// Imageの回転を変更する
void setAngle(Image* image, float _angle);
// Imageのカラーを変更する
void SetColorImage(Image* image, D3DXCOLOR color);
// ImageのUV座標を変更する
void SetTexture(Image* image, float ratioU, float ratioV);
// Imageのテクスチャリストをセットする
// ※必ずarg_numと可変引数の数を同じにすること！！
// ※デフォルトテクスチャは引数０番目へ指定する
void setTextureList(Image* image,int arg_num, LPDIRECT3DTEXTURE9 texture, ...);
// Imageのテクスチャを変更する
void changeTexture(Image* image, int listNo);
// Imageの頂点を作成する
HRESULT MakeVertex(Image* image, LPDIRECT3DDEVICE9 pDevice);