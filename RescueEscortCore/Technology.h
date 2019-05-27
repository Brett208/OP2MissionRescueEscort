#pragma once

#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

void SetMultipleResearchedTechs(int playerNum, std::vector<TechID>& completedResearch);
void SetMultipleResearchedTechs(int playerNum, std::vector<int>& completedResearch);

void SetResearchedTech();
void SetRescueConvoyResearchedTech();
void SetEvacuationConvoyResearchedTech();
void SetEnemyResearchedTech();

void SetResearchedTech()
{
	SetRescueConvoyResearchedTech();
	SetEvacuationConvoyResearchedTech();
	SetEnemyResearchedTech();
}

void SetMultipleResearchedTechs(int playerNum, std::vector<TechID>& completedResearch)
{
	for (TechID techID : completedResearch)
	{
		Player[playerNum].MarkResearchComplete(techID);
	}
}

void SetMultipleResearchedTechs(int playerNum, std::vector<int>& completedResearch)
{
	for (int techID : completedResearch)
	{
		Player[playerNum].MarkResearchComplete(techID);
	}
}

std::vector<int> sharedTech{
	//05052, // Garage
	2701, // Astronomy
	2702, // Boptronics
	2703, // Chemistry
	2704, // Planetary Sciences
	2705, // Social Sciences
	3401, // Cybernetic Teleoperation
	3406, // Environmental Psychology
	3301, // Emergency Response Systems
	8307, // Multitainment Console Upgrade
	5305, // DIRT Procedural Review
	3303, // Health Maintenance
	3402, // High-Temperature Superconductivity
	3405, // Metallogeny
	3302, // Metals Reclamation
	3304, // Offspring Enhancement
	3305, // Research Training Programs
	3201, // Seismology
	3202, // Vulcanology
	3306, // Leisure Studies
	3851, // Mobile Weapons Platform
	5110, // Rare Ore Processing
	5201, // Advanced Combat Chassis
	5111, // Independent Turret Power Systems
	5317, // Reinforced Vehicle Construction
	5508, // Electromagnetic Pulsing
	5307, // Automated Diagnostic Examinations
	7102, // Explosive Charges
	8306, // Enhanced Defensive Fortifications
	8309, // Reinforced Panther Construction
	10303, // Advanced Armoring Systems
};

std::vector<int> edenTech{
	3407, // Large-Scale Optical Resonators
	5506, // Directional Magnetic Fields
	7403, // Increased Capacitance Circuitry
	8503, // Acid Weaponry
	10102, // Artificial Lightning
	7211, // Extended-Range Projectile Launcher (Eden)
	10305, // Grenade Loading Mechanism (Eden)
	12101 // Heat Dissipation Systems (Eden)
};

std::vector<int> plymouthTech{
	2706, // Cryptology
	2707, // Vehicle Encryption Patch
	5601, // Heat Dissipation Systems (Plymouth)
	8203, // High-Powered Explosives
	5116, // Legged Robots
	5202, // Dissipating Adhesives
	3408, // Focused Microwave Projection
	7103, // Multiple Mine Projectile System
	5599, // Rocket Propulsion
	7212, //Extended-Range Projectile Launcher (Plymouth)
	10306 //Grenade Loading Mechanism (Plymouth)
};

void SetRescueConvoyResearchedTech()
{
	std::vector<int> tech
	{
		TechID::techAdvancedVehiclePowerPlant,
		TechID::techScoutClassDriveTrainRefit
	};

	tech.insert(std::end(tech), std::begin(sharedTech), std::end(sharedTech));

	if (Player[Player0].IsEden()) {
		tech.insert(std::end(tech), std::begin(edenTech), std::end(edenTech));
	}
	else {
		tech.insert(std::end(tech), std::begin(plymouthTech), std::end(plymouthTech));
	}

	if (Player[Player0].Difficulty() == PlayerDifficulty::DiffEasy)
	{
		//researchedTech.push_back(8320); //Reduced Foam Evaporation	
	}

	SetMultipleResearchedTechs(Player0, tech);
}

void SetEvacuationConvoyResearchedTech()
{
	std::vector<int> tech(sharedTech);

	if (Player[Player1].IsEden()) {
		tech.insert(std::end(tech), std::begin(edenTech), std::end(edenTech));
	}
	else {
		tech.insert(std::end(tech), std::begin(plymouthTech), std::end(plymouthTech));
	}

	SetMultipleResearchedTechs(Player1, tech);
}

void SetEnemyResearchedTech()
{
	std::vector<int> tech(sharedTech);

	tech.insert(std::end(tech), std::begin(edenTech), std::end(edenTech));

	SetMultipleResearchedTechs(Player2, tech);
}
