#pragma once

namespace AK_Base {

	// シングルトン化クラス
	// public継承して使ってね
	// 本当に阻止できているかは不明...
	template<class T> class Singleton
	{
	private:
		// インスタンスを保持しておく変数
		// unique_ptr<T>だとダメ？
		static T* SingletonObj;

	protected:
		// デフォルトコンストラクタ
		// 2回目以降はメッセージボックスが出る（エラーもでるかも）
		// 無理やり親クラスとして扱ってるイメージ
		explicit Singleton() {
			if (SingletonObj != nullptr) {
				MessageBox(nullptr, L"FAILED : Singleton::SingletonObj()\ninstance already created", L"Error", MB_OK);
			}
			// reinterpret_cast<type>() :()内のポインタを無理やりtypeの型に変更する
			SingletonObj = reinterpret_cast<T*>(this);
		};

		virtual ~Singleton() {
			SingletonObj = nullptr;
		}
		
		// 複製を阻止
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;
		
	public:
		// インスタンスを取得
		static inline T& GetInstance() {
			if (SingletonObj == nullptr) {
				MessageBox(nullptr, L"FAILED : Singleton::GetInstance()\nNo instance created", L"Error", MB_OK);
			}
			return *SingletonObj;
		}

	};

	template<class T> T* Singleton<T>::SingletonObj = nullptr;
}
