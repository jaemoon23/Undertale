#include "stdafx.h"
#include "PlayerInfo.h"



int PlayerInfo::hp = 20;
int PlayerInfo::maxHp = 20;
int PlayerInfo::ATK = 50;
int PlayerInfo::lv = 1;
int PlayerInfo::exp = 0;
int PlayerInfo::gold = 0;
int PlayerInfo::Moral = 0;

void PlayerInfo::PlusExp(int e)
{
	int pastLv = lv;
	exp += e;
	if (exp >= 99999)
	{
		lv = 20;
		maxHp = 99;
		exp = 99999;
		return;
	}
	else if (exp >= 50000)
	{
		lv = 19;
	}
	else if (exp >= 25000)
	{
		lv = 18;
	}
	else if (exp >= 15000)
	{
		lv = 17;
	}
	else if (exp >= 10000)
	{
		lv = 16;
	}
	else if (exp >= 7000)
	{
		lv = 15;
	}
	else if (exp >= 5000)
	{
		lv = 14;
	}
	else if (exp >= 3500)
	{
		lv = 13;
	}
	else if (exp >= 2500)
	{
		lv = 12;
	}
	else if (exp >= 1700)
	{
		lv = 11;
	}
	else if (exp >= 1200)
	{
		lv = 10;
	}
	else if (exp >= 800)
	{
		lv = 9;
	}
	else if (exp >= 500)
	{
		lv = 8;
	}
	else if (exp >= 300)
	{
		lv = 7;
	}
	else if (exp >= 200)
	{
		lv = 6;
	}
	else if (exp >= 120)
	{
		lv = 5;
	}
	else if (exp >= 70)
	{
		lv = 4;
	}
	else if (exp >= 30)
	{
		lv = 3;
	}
	else if (exp >= 10)
	{
		lv = 2;
	}
	else
	{
		lv = 1;
	}
	maxHp = 16 + 4 * lv;
	hp += (lv - pastLv) * 4;
}

void PlayerInfo::Heal(int h)
{
	hp += h;
	if (hp > maxHp)
	{
		hp = maxHp;
	}
}