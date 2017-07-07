/**
	Knüppeln.c4s

	@author KKenny / Thow
*/



func Initialize()
{
	CreateObject(Goal_LastManStanding);
	CreateObject(Rule_KillLogs);

	CheckScenarioParameters();
	InitClouds();
	ActivateMedalRule();
	// Gather statistics.
	InitStatistics(STATS_Type_All);
}

func InitClouds()
{
	for(var i = 0; i < 8; i++)
	{
		var cloud = CreateObject(DecoCloud, Random(LandscapeWidth() + 400) - 200, Random(LandscapeHeight()), -1);
		cloud->SetClrModulation(RGBa(255, 128, 0, 40));
		cloud->SetXDir(RandomX(1, 3));
	}
}

func GetItemCratePos()
{
	return [100 + Random(LandscapeWidth() - 200), 50];
}

func InitializePlayer(int plr, int iX, int iY, object pBase, int iTeam)
{
	//SpawnPlayer(plr);
   	SetPlayerZoomByViewRange(plr, 700, 0, PLRZOOM_Direct);
   	//SetPlayerZoomByViewRange(plr, 700, 0, PLRZOOM_Direct);
	return;
}

func SpawnPlayer(int plr, prev_clonk)
{
	var clonk = GetCrew(plr);
	clonk->CreateContents(Sword);
	clonk->SetMagicEnergy(50);
	ScheduleCall(clonk, "SelectChampion", 15, 0);
	//clonk->ChooseMenu();
}

global func GetRandomSpawn()
{
	var spawns = [[80,190],[250,230],[360,230],[510,230],[660,230],[940,190]];
	var rand = Random(GetLength(spawns));
	return spawns[rand];
}

func OnClonkEnteredRelaunch(object clonk, int plr)
{	
	SpawnPlayer(plr);
}

func OnClonkLeftRelaunch(object clonk)
{
	var pos = GetRandomSpawn();
	clonk->SetPosition(pos[0],pos[1]);
	clonk->SpawnProtection();
	return;
}

func KillsToRelaunch() { return 0; }


