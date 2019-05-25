// 循環・重連結リスト（ソース部）
#include <stdio.h>
#include <stdlib.h>
#include "DataList.h"

// 一つのノードを動的に生成
static Dnode* AllocDnode(void)
{
	return (Dnode*)calloc(1, sizeof(Dnode));
}

// ノードの各メンバに値を設定
static void SetDnode(Dnode* n, const Icon* x, Dnode* prev, Dnode* next)
{
	n->data = *x;		// データ
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// リストは空か
int Dlist::IsEmpty()
{
	return head->next == head;
}

// リストを初期化
void Dlist::Initialize()
{
	Dnode* dummyNode = AllocDnode(); // ダミーノードを生成
	head = crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// 着目ノードのデータを表示
void Dlist::PrintCurrent()
{
	if (IsEmpty()){}
		//printf("着目ノードがありません。");
	//else
		//PrintImage(&list->crnt->data);
}

// 着目ノードのデータを表示（改行付き）
void Dlist::PrintLnCurrent()
{
	PrintCurrent();
	putchar('\n');
}

// 関数compareによってxと一致すると判定されるノードを探索
Dnode* Dlist::Search(const Icon* x, int compare(const Icon* x, const Icon* y))
{
	Dnode* ptr = head->next;
	while (ptr != head)
	{
		if (compare(&ptr->data, x) == 0)
		{
			crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};

//着目ノードを先頭ヘッダにする
void Dlist::setHead()
{
	if (IsEmpty() || crnt == head->next)return;	// 既に先頭ヘッダである又は空
	
	crnt = head->next;//先頭ヘッダに合わせる
}

// リストのサイズを戻す
int Dlist::size()
{
	int listSize = 0;
	if (IsEmpty()) {
		return listSize;
	}
	else {
		//全オブジェクトの走査
		Dnode* ptr = head->next;//ポインタを先頭ヘッダに合わせる。
		while (ptr != head) {
			listSize++;
			ptr = ptr->next;	// 後続ノードに着目	
		}
	}
	return listSize;
}

// 全ノードのデータをリスト順に更新
void Dlist::update()
{
	if (IsEmpty()) {
		//何の処理も行いません。
		//puts("ノードがありません。");
	}
	else {
		//全オブジェクトの走査
		Dnode* ptr = head->next;//ポインタを先頭ヘッダに合わせる。
		while (ptr != head) {
			ptr->data.update();	//更新処理
			ptr = ptr->next;	// 後続ノードに着目	
		}
	}
};


// 全ノードのデータをリスト順に表示
void Dlist::Print()
{
	if (IsEmpty()){
		//puts("ノードがありません。");
	} else {
		//全オブジェクトの走査
		Dnode* ptr = head->next;//ポインタを先頭ヘッダに合わせる。
		while (ptr != head) {
			ptr->data.draw();	//実行したいこと
			ptr = ptr->next;	// 後続ノードに着目	
		}
	}
};


// 全ノードのデータをリストの逆順に表示
void Dlist::PrintReverse()
{
	if (IsEmpty()) {
		//puts("ノードがありません。");
	} else {
		Dnode* ptr = head->prev;
		//puts("【一覧表】");
		while (ptr != head) {
			//PrintLnImage(&ptr->data);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

bool Dlist::IsLast()
{
	if (IsEmpty() || crnt->next == head)
		return true;	// 最後のノードである
	return false;
}

// 着目ノードを一つ後方に進める
int Dlist::Next()
{
	if (IsEmpty() || crnt->next == head)
		return 0;	// 進めることはできない
	crnt = crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Dlist::Prev()
{
	if (IsEmpty() || crnt->prev == head)
		return 0;	// 戻すことはできない
	crnt = crnt->prev;
	return 1;
};


// pが指すノードの直後にノードを挿入
void Dlist::InsertAfter(Dnode* p, const Icon* x)
{
	Dnode* ptr = AllocDnode();
	Dnode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	crnt = ptr;

};

// 先頭にノードを挿入
void Dlist::InsertFront(const Icon* x)
{
	InsertAfter(head, x);
};

// 末尾にノードを挿入
void Dlist::InsertRear(const Icon* x)
{
	InsertAfter(head->prev, x);
};

// pが指すノードを削除
void Dlist::Remove(Dnode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
	if (crnt == head)
		crnt = head->next;
};

// 先頭ノードを削除
void Dlist::RemoveFront()
{
	if (!IsEmpty())
		Remove(head->next);
};

// 末尾ノードを削除
void Dlist::RemoveRear()
{
	if (!IsEmpty())
		Remove(head->prev);
};

// 着目ノードを削除
void Dlist::RemoveCurrent()
{
	if (crnt != head)
		Remove(crnt);
};

// 全ノードを削除
void Dlist::Clear()
{
	while (!IsEmpty())	// 空になるまで
		RemoveFront();	// 先頭ノードを削除
};

// 循環・重連結リストの後始末
void Dlist::Terminate()
{
	Clear();			// 全ノードを削除
	free(head);		// ダミーノードを削除
};
