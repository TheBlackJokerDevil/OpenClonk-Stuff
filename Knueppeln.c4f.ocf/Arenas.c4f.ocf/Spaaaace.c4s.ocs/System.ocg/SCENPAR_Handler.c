

global func CheckScenarioParameters()
{
	if(SCENPAR_ChampSelection == 2)
		CreateObject(Rule_RandomChamp, 0, 0, -1);
		
	if(SCENPAR_ChampSelection == 3)
		CreateObject(Rule_ChampRotation, 0, 0, -1);
		
	if(SCENPAR_IncreasedManaReg == 2)
		CreateObject(Rule_FastMana, 0, 0, -1);
}

global func RelaunchCount()
{
	return SCENPAR_Relaunchs;
}