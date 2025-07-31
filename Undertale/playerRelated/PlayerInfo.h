





#pragma once
class PlayerInfo
{
public:
	static int hp;
	static int maxHp;
	static int ATK;
	static int lv;
	static int exp;
	static int gold;
	static int Moral;

	static void PlusExp(int e);
	static void Heal(int h);
};

