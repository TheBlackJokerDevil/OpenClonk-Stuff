/**
	EarthWallManager
	Insert description here

	@author 
*/

local ManaCost = 35;

local stones;
local MaxHP = 100;
local HP = 100;
local Size_x = 80;
local Size_y = 80;

local SpellRange = 100;

local bar;
local team;

func Initialize()
{
	AddEffect("SlowHeal", this, 1, 15, this);
	AddEffect("CheckWipf", this, 1, 5, this);
}

func FxCheckWipfTimer()
{
	if(!bar)
		return;

	if(CheckWipf())
	{
		var rgba = SplitRGBaValue(GetTeamColor(team));
		bar->SetBarColor(RGBa(rgba.R, rgba.G, rgba.B, 255));
	}
	else
	{
		bar->SetBarColor(RGB(100, 100, 100));
	}
}

func CheckWipf()
{
	if(FindObject(Find_ID(Goal_BombRun.ballID), Find_Distance((Size_x + Size_y) + 50)))
	{
		return true;
	}
	
	return false;
}

func FxSlowHealTimer()
{
	if(bar && HP < MaxHP)
	{
		HP++;
		bar->SetValue(HP);
	}
}

func CreateWall(int teamid, int size_x, int size_y, int hp)
{
	if(hp)
	{
		MaxHP = hp;
		HP = hp;
	}
	if(size_x)
		Size_x = size_x;
	
	if(size_y)
		Size_y = size_y;
	
	if(bar)
		bar->RemoveObject();

	team = teamid;
		
	if(stones != nil)
	{
		Destroy();
	}
	
	var offset = {
		x = 0,
		y = - Size_y - 30,
	};
	bar = CreateProgressBar(GUI_SimpleProgressBar, MaxHP, HP, nil, -1, offset);
	
	stones = CreateArray(360/10);
	
	for(var i = 0; i < 360; i+=8)
	{
		var stone = CreateObject(PortalStone, Cos(i, Size_x), Sin(i, Size_y), -1);
		var clr = GetTeamColor(teamid);
		var rgba = SplitRGBaValue(clr);
		stone->SetClrModulation(RGBa(rgba.R, rgba.G, rgba.B, 100));
		
		stones[i] = stone;
		if(stone)
			stone->SetMaster(this);
	}
	
	//AddEffect("Remove", this, 20, Dur, this);
}

func GotDamage(int dmg, int plr)
{
	if(GetEffect(Format("DamageCD%d", plr), this))
		return;
		
	if(GetPlayerTeam(plr) == team)
		return;
	
	if(!CheckWipf())
		return;

	HP = HP - dmg;
	
	if(HP <= 0)
		ScheduleCall(this, "Destroy", 1);
	
	bar->SetValue(HP);
	
	if(this)
		AddEffect(Format("DamageCD%d", plr), this, 20, 6);
}

func Destroy()
{
	for(var s in stones)
	{
		if(s)
			s->RemoveObject();
	}
	Sound("Fire::BlastLiquid2");
	
	if(bar)
		bar->RemoveObject();
}

func FxRemoveStop(object target, proplist effect, int reason, bool temporary)
{
	if(temporary)
		return;
	
	Destroy();
}
