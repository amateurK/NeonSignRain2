#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 文字列を描画するクラス
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Sprite2DPicture.h"
#include "CharacterManager.h"

namespace AK_Base {

	/// @brief 文字列を描画するクラス
	/// @note 文字の画像を連続して描画するので、ちょっと処理が重いかも...
	/// @note 傾けて表示などはしない（どうやってきれいに実装するんだ...）
	__declspec(align(16))
		class Sprite2DString :public Sprite2DPicture
	{
	public:
		/// @brief どこに揃えるか
		enum class Align {
			RIGHT,		// 右揃え
			CENTER,		// 中央揃え
			LEFT,		// 左揃え
		};



	protected:
		/// @brief 文字を監理するマネージャーへのポインタ
		CharacterManager* m_CharacterManager;

		/// @brief 表示する文字列(処理用)
		std::wstring m_String;
		/// @brief 表示する文字列(描画用)
		std::vector<Character*> m_CharaString;
		/// @brief 現在のフォントセット
		FontSet* m_FontSet;

		/// @brief 文字列に更新が入ったか
		bool m_IsUpdate;

		/// @brief 表示する座標（基準点の場所なので左上ではない）
		Point<int> m_Pos;

		/// @brief 文字列全体の横幅
		int m_StringWidth;

		/// @brief どこに揃えるか
		Align m_Alignment;

	public:

		/// @brief コンストラクタ
		/// @param game ゲーム本体へのポインタ
		/// @param pos 表示する座標（基準点の場所なので左上ではない）
		/// @param id 使用するフォントのID
		/// @param str 表示する文字列
		/// @param align どこに揃えるか
		Sprite2DString(
			BaseWindow* const game,
			Point<int> pos,
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::LEFT
		);
		/// @brief デストラクタ
		virtual ~Sprite2DString();

		/// @brief 更新
		virtual void Move() override;
		/// @brief 描画
		virtual void Render() override;

		/// @brief world行列を計算
		/// @return World行列
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