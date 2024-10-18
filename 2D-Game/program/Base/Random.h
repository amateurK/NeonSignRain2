#pragma once

// ���������p�N���X
// �C���X�^���X�𐶐����邱�ƂȂ�
class Random {
public:

	// �����𐶐� �͈�: [min, max]
	static int GetRandom(int min = INT_MIN, int max = INT_MAX) {
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

};
