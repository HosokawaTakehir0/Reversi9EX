#pragma once
#include "../include/reversi/reversiUtil.h"


//石のおけるところをbitBoardで出力
bitBoard isPut(bitBoard &player, bitBoard &opp) {
	bitBoard tmp, canPut, blank;
	blank = (~(player | opp))&maskValid;

	//左探索
	tmp = opp & (player << 1);
	tmp |= opp & (tmp << 1); tmp |= opp & (tmp << 1); tmp |= opp & (tmp << 1);
	tmp |= opp & (tmp << 1); tmp |= opp & (tmp << 1); tmp |= opp & (tmp << 1);
	canPut = blank & (tmp << 1);

	//右探索
	tmp = opp & (player >> 1);
	tmp |= opp & (tmp >> 1); tmp |= opp & (tmp >> 1); tmp |= opp & (tmp >> 1);
	tmp |= opp & (tmp >> 1); tmp |= opp & (tmp >> 1); tmp |= opp & (tmp >> 1);
	canPut |= blank & (tmp >> 1);

	//上探索
	tmp = opp & (player << 11);
	tmp |= opp & (tmp << 11); tmp |= opp & (tmp << 11); tmp |= opp & (tmp << 11);
	tmp |= opp & (tmp << 11); tmp |= opp & (tmp << 11); tmp |= opp & (tmp << 11);
	canPut |= blank & (tmp << 11);

	//下探索
	tmp = opp & (player >> 11);
	tmp |= opp & (tmp >> 11); tmp |= opp & (tmp >> 11); tmp |= opp & (tmp >> 11);
	tmp |= opp & (tmp >> 11); tmp |= opp & (tmp >> 11); tmp |= opp & (tmp >> 11);
	canPut |= blank & (tmp >> 11);

	//右上探索
	tmp = opp & (player << 10);
	tmp |= opp & (tmp << 10); tmp |= opp & (tmp << 10); tmp |= opp & (tmp << 10);
	tmp |= opp & (tmp << 10); tmp |= opp & (tmp << 10); tmp |= opp & (tmp << 10);
	canPut |= blank & (tmp << 10);
	//左下探索
	tmp = opp & (player >> 10);
	tmp |= opp & (tmp >> 10); tmp |= opp & (tmp >> 10); tmp |= opp & (tmp >> 10);
	tmp |= opp & (tmp >> 10); tmp |= opp & (tmp >> 10); tmp |= opp & (tmp >> 10);
	canPut |= blank & (tmp >> 10);
	//左上探索
	tmp = opp & (player << 12);
	tmp |= opp & (tmp << 12); tmp |= opp & (tmp << 12); tmp |= opp & (tmp << 12);
	tmp |= opp & (tmp << 12); tmp |= opp & (tmp << 12); tmp |= opp & (tmp << 12);
	canPut |= blank & (tmp << 12);
	//左下探索
	tmp = opp & (player >> 12);
	tmp |= opp & (tmp >> 12); tmp |= opp & (tmp >> 12); tmp |= opp & (tmp >> 12);
	tmp |= opp & (tmp >> 12); tmp |= opp & (tmp >> 12); tmp |= opp & (tmp >> 12);
	canPut |= blank & (tmp >> 12);

	return canPut;
}

//石を置く
void doPut(int point, bitBoard &player, bitBoard &opp) {
	int poi;
	player.set(point);
	for (poi = point + 1;; poi += 1) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi -= 1) {
			player.set(poi); opp.reset(poi);
		}
	}

	for (poi = point - 1;; poi -= 1) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi += 1) {
			player.set(poi); opp.reset(poi);
		}
	}


	for (poi = point + 11;; poi += 11) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi -= 11) {
			player.set(poi); opp.reset(poi);
		}
	}

	for (poi = point - 11;; poi -= 11) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi += 11) {
			player.set(poi); opp.reset(poi);
		}
	}

	for (poi = point + 12;; poi += 12) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi -= 12) {
			player.set(poi); opp.reset(poi);
		}
	}

	for (poi = point - 12;; poi -= 12) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi += 12) {
			player.set(poi); opp.reset(poi);
		}
	}

	for (poi = point + 10;; poi += 10) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi -= 10) {
			player.set(poi); opp.reset(poi);
		}
	}

	for (poi = point - 10;; poi -= 10) {
		if (!opp.test(poi))break;
	}
	if (player.test(poi)) {
		for (; poi != point; poi += 10) {
			player.set(poi); opp.reset(poi);
		}
	}
}

//石の置けるところをbitFlagの立つindexに変換
std::vector<int> getFlag(bitBoard &canPut) {
	std::vector<int> put;
	int i = 12;
	int cnt = canPut.count();
	for (; i < 20; ++i) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i < 108; i += 11) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i > 100; --i) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i > 23; i -= 11) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	if (cnt == 0)return put;

	for (; i < 30; ++i) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i < 96; i += 11) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i > 90; --i) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i > 35; i -= 11) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	if (cnt == 0)return put;

	for (; i < 40; ++i) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i < 84; i += 11) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i > 80; --i) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}
	for (; i >= 47; i -= 11) {
		if (canPut.test(i)) { put.push_back(i); --cnt; }
	}

	return put;
}

//11*11盤面のうち有効な9*9の転置
inline void trans9in11(bitBoard &x)
{
	bitBoard t = mask50 & (x ^ (x >> 50));
	x ^= (t ^ (t << 50));
	t = mask20 & (x ^ (x >> 20));
	x ^= (t ^ (t << 20));
	t = mask10 & (x ^ (x >> 10));
	x ^= (t ^ (t << 10));

	t = mask40 & (x ^ (x >> 40));
	x ^= (t ^ (t << 40));
	t = mask30 & (x ^ (x >> 30));
	x ^= (t ^ (t << 30));
}

//11*11盤面の上下反転
inline void flip11(bitBoard &x) {

	bitBoard t = mask66 & (x ^ (x << 66));
	x ^= (t ^ (t >> 66));
	t = mask33 & (x ^ (x << 33));
	x ^= (t ^ (t >> 33));
	t = mask11 & (x ^ (x << 11));
	x ^= (t ^ (t >> 11));

}

//盤面の90度回転
void rotate90degClock(bitBoard &x) {
	flip11(x);
	trans9in11(x);
}