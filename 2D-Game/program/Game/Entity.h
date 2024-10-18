#pragma once
#include "Camera\\SpriteByCamara.h"

namespace AK_Game {

	// Player��Enemy�̋��ʕ���
	__declspec(align(16))
		class Entity : public Camera::SpriteByCamera
	{
	protected:

		// ���݂̃p�����[�^�[
		Point<float> m_Pos;		// ���W
		Point<float> m_Speed;	// ���݂̈ړ����x
		int m_HP;				// �̗́i���S�����͊e���Łj
		float m_DamageMultiply;	// �e�Ȃǂ̃_���[�W��Z�l
		uint32_t m_Times;		// ����Ă���Move()�����s������

		Point<float> m_TargetOffset;	// �_���ׂ��ꏊ�ւ̃I�t�Z�b�g

		// �r�b�g�}�b�v����؂蔲��������
		uint8_t m_MaptipNumber;	// �\������}�b�v�`�b�v�i���o�[
		uint8_t m_MaptipTime;	// ���[�v�����Ɏg�p
		bool m_IsFlip;	// ���]���ĕ\�����邩



	public:
		// �R���X�g���N�^
		Entity(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource
		);
		virtual ~Entity();

		virtual void Move() override;
		virtual void Render() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() = 0;
		// UVMatrix�s����v�Z
		virtual DirectX::XMMATRIX CalcUVMatrix() override;

		// �_���[�W���󂯂��Ƃ��̏����i�f�t�H���g�ł͉������Ȃ��j
		virtual void TakeDamage(int damage) {};

		// �_���ׂ��ꏊ��Ԃ�
		virtual Point<float> GetTargetPos();


		// �Z�b�^�[
		void SetPos(Point<float> pos) { m_Pos = pos; }
		void SetHP(int hp) { m_HP = hp; }
		void MultiplyHP(float multi) { m_HP = (int)((float)m_HP * multi); }
		void MultiplyATK(float multi) { m_DamageMultiply *= multi; }

		// �Q�b�^�[
		Point<float> GetPos() { return m_Pos; }
		Point<float> GetSpeed() { return m_Speed; }
		int GetHP() { return m_HP; }


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Entity));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	protected:
		// �A�j���[�V�������[�v��������
		void LoopAnim(uint8_t begin, uint8_t end, uint8_t interval);


	};
}