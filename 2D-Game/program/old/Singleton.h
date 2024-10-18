#pragma once

namespace AK_Base {

	// シングルトン化クラス
	// シングルトンにしたいクラスにpublic継承して使ってね
	// 今はちゃんと動いているか怪しいので使ってない
	template<class T> class Singleton
	{
	protected:
		Singleton() {};

	private:
		// オブジェクト生成を阻止
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

		// インスタンスを作成
		// 継承されたクラスのコンストラクタを呼び出す
		static T* CreateInstance() {
			return reinterpret_cast<T*> (this);
		}

	public:
		// インスタンスを取得
		// 2回目以降はCreateされない
		static T& GetInstance() {
			static std::unique_ptr<T> SingletonObj(CreateInstance());
			return *SingletonObj;
		}

	};
}
