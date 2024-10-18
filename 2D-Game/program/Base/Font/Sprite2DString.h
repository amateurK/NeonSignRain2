#pragma once
#include "Sprite2DPicture.h"
#include "CharacterManager.h"

namespace AK_Base {

	// �������`�悷��N���X
	// �X���ĕ\���͂��Ȃ��i������������̂Łj
	// �����̉摜��A�����ĕ`�悷��̂ŁA������Ə������d������...
	__declspec(align(16))
		class Sprite2DString :public Sprite2DPicture
	{
	public:
		enum class Align {	// �ǂ��ɑ����邩
			RIGHT,		// �E����
			CENTER,		// ��������
			LEFT,		// ������
		};

	protected:
		// �}�l�[�W���[�ւ̃|�C���^
		CharacterManager* m_CharacterManager;

		std::wstring m_String;			// �\�����镶����(�����p)
		std::vector<Character*> m_CharaString;	// �\�����镶����(�`��p)
		FontSet* m_FontSet;			// ���݂̃t�H���g�Z�b�g

		bool m_IsUpdate;			// ������ɍX�V����������

		Point<int> m_Pos;		// �\��������W�i��_�̏ꏊ�Ȃ̂ō���ł͂Ȃ��j

		int m_StringWidth;		// ������S�̂̉���
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

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;

		// �Z�b�^�[
		void SetString(std::wstring str);
		void SetFont(int id);
		void SetPos(Point<int> pos) { m_Pos = pos; }
		void SetAlignment(Align align) { m_Alignment = align; }



		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Sprite2DString));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}