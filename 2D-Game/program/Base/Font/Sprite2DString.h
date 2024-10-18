#pragma once
#include "Sprite2DPicture.h"
#include "CharacterManager.h"

namespace AK_Base {

	// 文字列を描画するクラス
	// 傾けて表示はしない（処理が増えるので）
	// 文字の画像を連続して描画するので、ちょっと処理が重いかも...
	__declspec(align(16))
		class Sprite2DString :public Sprite2DPicture
	{
	public:
		enum class Align {	// どこに揃えるか
			RIGHT,		// 右揃え
			CENTER,		// 中央揃え
			LEFT,		// 左揃え
		};

	protected:
		// マネージャーへのポインタ
		CharacterManager* m_CharacterManager;

		std::wstring m_String;			// 表示する文字列(処理用)
		std::vector<Character*> m_CharaString;	// 表示する文字列(描画用)
		FontSet* m_FontSet;			// 現在のフォントセット

		bool m_IsUpdate;			// 文字列に更新が入ったか

		Point<int> m_Pos;		// 表示する座標（基準点の場所なので左上ではない）

		int m_StringWidth;		// 文字列全体の横幅
		Align m_Alignment;

	public:

		Sprite2DString(
			BaseWindow* const game,
			Point<int> pos,
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::LEFT
		);
		virtual ~Sprite2DString();

		virtual void Move() override;
		virtual void Render() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;

		// セッター
		void SetString(std::wstring str);
		void SetFont(int id);
		void SetPos(Point<int> pos) { m_Pos = pos; }
		void SetAlignment(Align align) { m_Alignment = align; }



		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Sprite2DString));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}