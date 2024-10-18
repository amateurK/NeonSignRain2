#pragma once

namespace AK_Base {

	// �V���O���g�����N���X
	// �V���O���g���ɂ������N���X��public�p�����Ďg���Ă�
	// ���͂����Ɠ����Ă��邩�������̂Ŏg���ĂȂ�
	template<class T> class Singleton
	{
	protected:
		Singleton() {};

	private:
		// �I�u�W�F�N�g������j�~
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

		// �C���X�^���X���쐬
		// �p�����ꂽ�N���X�̃R���X�g���N�^���Ăяo��
		static T* CreateInstance() {
			return reinterpret_cast<T*> (this);
		}

	public:
		// �C���X�^���X���擾
		// 2��ڈȍ~��Create����Ȃ�
		static T& GetInstance() {
			static std::unique_ptr<T> SingletonObj(CreateInstance());
			return *SingletonObj;
		}

	};
}
