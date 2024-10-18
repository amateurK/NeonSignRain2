#pragma once

namespace AK_Base {

	// �V���O���g�����N���X
	// public�p�����Ďg���Ă�
	// �{���ɑj�~�ł��Ă��邩�͕s��...
	template<class T> class Singleton
	{
	private:
		// �C���X�^���X��ێ����Ă����ϐ�
		// unique_ptr<T>���ƃ_���H
		static T* SingletonObj;

	protected:
		// �f�t�H���g�R���X�g���N�^
		// 2��ڈȍ~�̓��b�Z�[�W�{�b�N�X���o��i�G���[���ł邩���j
		// �������e�N���X�Ƃ��Ĉ����Ă�C���[�W
		explicit Singleton() {
			if (SingletonObj != nullptr) {
				MessageBox(nullptr, L"FAILED : Singleton::SingletonObj()\ninstance already created", L"Error", MB_OK);
			}
			// reinterpret_cast<type>() :()���̃|�C���^�𖳗����type�̌^�ɕύX����
			SingletonObj = reinterpret_cast<T*>(this);
		};

		virtual ~Singleton() {
			SingletonObj = nullptr;
		}
		
		// ������j�~
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;
		
	public:
		// �C���X�^���X���擾
		static inline T& GetInstance() {
			if (SingletonObj == nullptr) {
				MessageBox(nullptr, L"FAILED : Singleton::GetInstance()\nNo instance created", L"Error", MB_OK);
			}
			return *SingletonObj;
		}

	};

	template<class T> T* Singleton<T>::SingletonObj = nullptr;
}
