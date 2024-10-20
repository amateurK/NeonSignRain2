#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 乱数生成用クラス
// インスタンスを生成することない
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/// @brief 乱数生成用クラス
class Random {
public:

	/// @brief 乱数を生成 範囲: [min, max]
	/// @param min 最小値
	/// @param max 最大値
	/// @return 生成された乱数
	static int GetRandom(int min = INT_MIN, int max = INT_MAX) {
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

};
