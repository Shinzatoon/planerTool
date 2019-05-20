#pragma once
// 循環・重連結リスト(ヘッダ部)
#include "main.h"
#include "icon.h"

// ノード
typedef struct __node {
	Icon	data;				// データ
	struct __node *prev;		// 先行ノードへのポインタ
	struct __node *next;		// 後続ノードへのポインタ
}Dnode;


// 循環・重連結リスト
class Dlist {

public:
	Dnode * head;				// 先頭ダミーノードへのポインタ
	Dnode *crnt;				// 着目ノードへのポインタ

	//リストは空か
	int IsEmpty();

	// リストを初期化
	void Initialize();

	// 着目ノードのデータを表示
	void PrintCurrent();

	// 着目ノードのデータを表示（改行付き）
	void PrintLnCurrent();

	// 関数compareによってxと一致すると判定されるノードを探索
	Dnode* Search(const Icon* x, int compare(const Icon* x, const Icon* y));

	//着目ノードを先頭ヘッダにする
	void setHead();

	// リストのサイズを戻す
	int size();

	// 全ノードのデータをリスト順に更新
	void update();

	// 全ノードのデータをリスト順に表示
	void Print();

	// 全ノードのデータをリスの逆順に表示
	void PrintReverse();

	// 着目ノードを一つ後方に進める
	int Next();

	// 着目ノードを一つ前方に戻す
	int Prev();

	// pが指すノードの直後にノードを挿入
	void InsertAfter(Dnode* p, const Icon* x);

	// 先頭にノードを挿入
	void InsertFront(const Icon* x);

	// 末尾にノードを挿入
	void InsertRear(const Icon* x);

	// pが指すノードを削除
	void Remove(Dnode* p);

	// 先頭ノードを削除
	void RemoveFront();

	// 末尾ノードを削除
	void RemoveRear();

	// 着目ノードを削除
	void RemoveCurrent();

	// 全ノードを削除
	void Clear();

	// 循環・重連結リストの後始末
	void Terminate();
};
