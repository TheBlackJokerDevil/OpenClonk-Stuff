/**
	Spaaaaace.c4s

	@author 
*/

func Initialize()
{
	SetSkyParallax(0, 30, 30);
	AddEffect("Spaaaace", nil, 1, 2);
	
	CreateObject(Goal_LastManStanding);
	CreateObject(Rule_KillLogs);
	CheckScenarioParameters();
	
	CreateEnvironment();
	
	// Active the medal rule if loaded.
	ActivateMedalRule();
	// Gather statistics.
	InitStatistics(STATS_Type_All);
}

func CreateEnvironment()
{
	var o = CreateObjectAbove(GravityThing, 173, 694);
	o->CreatePartner();
	o.partner->SetPosition(o->GetX(), o->GetY() - 50);
	
	o = CreateObjectAbove(GravityThing, 733, 695);
	o->CreatePartner();
	o.partner->SetPosition(o->GetX(), o->GetY() - 50);
	
	o = CreateObjectAbove(GravityThing, 427, 518);
	o->CreatePartner();
	o.partner->SetPosition(o->GetX() + 125, o->GetY());
	
	o = CreateObjectAbove(GravityThing, 425, 711);
	o->CreatePartner();
	o.partner->SetPosition(o->GetX() + 125, o->GetY());
	
	o = CreateObjectAbove(GravityThing, 710, 610);
	o->CreatePartner();
	o.partner->SetPosition(685, 550);
}

func InitializePlayer(int plr, int iX, int iY, object pBase, int iTeam)
{
	//SpawnPlayer(plr);
   	SetPlayerZoomByViewRange(plr, 700, 0, PLRZOOM_Direct);
   	SetPlayerZoomByViewRange(plr, 700, 0, PLRZOOM_Direct);
	return;
}

func GetItemCratePos()
{
	for (var i = 0; i < 100; i++)
	{
		var pos = [200 + Random(LandscapeWidth() - 400), 10 + Random(LandscapeHeight() - 450)];
		
		if(GBackSolid(pos[0], pos[1]))
			continue;
		
		return pos;
	}
}

global func FxSpaaaaceTimer(object target, proplist effect, int time)
{
	for(var o in FindObjects(Find_NoContainer()))
	{
		if(!o)
			continue;
		
		if(o->GetY() < -20)
		{
			o->RemoveObject();
			continue;
		}
	
		if(o->GetProcedure() == "FLOAT")
			continue;
		
		if(o->GetMaterial() != Material("FlatTunnel"))
			o->SetYDir(o->GetYDir(100) - 31, 100);
		
	}
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
	var spawns = [[490,605],[395,500],[585,500],[340,685],[625,685],[835,595]];
	var rand = Random(GetLength(spawns));
	return spawns[rand];
}

// see https://github.com/openclonk/openclonk/commit/c2f1d47f6301fa4488f1f479a419c7ae47a4eaf0
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