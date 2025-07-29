#pragma once

#define DEF_DEV

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Test,
	Intro,
	Title,
	test,
	Map1,
	Map2,
	MapTool,
	Game,
	Battle,
	Dev1,
	Dev2,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};

enum class ButtonState
{
	None,
	Fight,
	Act,
	Item,
	Mercy,
	ChooseFight,
	ChooseAct,
	ChooseItem,
	ChooseMercy
};

enum class BulletPattern
{
	Normal,
	Rotate,
	Homing,
	Arrow,
	Split
};