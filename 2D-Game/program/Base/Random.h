#pragma once

// 乱数生成用クラス
// インスタンスを生成することない
class Random {
public:

	// 乱数を生成 範囲: [min, max]
	static int GetRandom(int min = INT_MIN, int max = INT_MAX) {
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

};
