#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �������`�悷��N���X
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Sprite2DPicture.h"
#include "CharacterManager.h"

namespace AK_Base {

	/// @brief �������`�悷��N���X
	/// @note �����̉摜��A�����ĕ`�悷��̂ŁA������Ə������d������...
	/// @note �X���ĕ\���Ȃǂ͂��Ȃ��i�ǂ�����Ă��ꂢ�Ɏ��������...�j
	__declspec(align(16))
		class Sprite2DString :public Sprite2DPicture
	{
	public:
		/// @brief �ǂ��ɑ����邩
		enum class Align {
			RIGHT,		// �E����
			CENTER,		// ��������
			LEFT,		// ������
		};



	protected:
		/// @brief �������ė�����}�l�[�W���[�ւ̃|�C���^
		CharacterManager* m_CharacterManager;

		/// @brief �\�����镶����(�����p)
		std::wstring m_String;
		/// @brief �\�����镶����(�`��p)
		std::vector<Character*> m_CharaString;
		/// @brief ���݂̃t�H���g�Z�b�g
		FontSet* m_FontSet;

		/// @brief ������ɍX�V����������
		bool m_IsUpdate;

		/// @brief �\��������W�i��_�̏ꏊ�Ȃ̂ō���ł͂Ȃ��j
		Point<int> m_Pos;

		/// @brief ������S�̂̉���
		int m_StringWidth;

		/// @brief �ǂ��ɑ����邩
		Align m_Alignment;

	public:

		/// @brief �R���X�g���N�^
		/// @param game �Q�[���{�̂ւ̃|�C���^
		/// @param pos �\��������W�i��_�̏ꏊ�Ȃ̂ō���ł͂Ȃ��j
		/// @param id �g�p����t�H���g��ID
		/// @param str �\�����镶����
		/// @param align �ǂ��ɑ����邩
		Sprite2DString(
			BaseWindow* const game,
			Point<int> pos,
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::LEFT
		);
		/// @brief �f�X�g���N�^
		virtual ~Sprite2DString();

		/// @brief �X�V
		virtual void Move() override;
		/// @brief �`��
		virtual void Render() override;

		/// @brief world�s����v�Z
		/// @return World�s��
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