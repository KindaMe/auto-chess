#pragma once

#include <iostream>
#include <string>
#include <iomanip>

class pawn
{
protected:
	int baseHealth = 0;
	int baseMana = 0;
	int baseDamage = 0;

	std::string name = "DEFAULT NAME";
	int health = 0;
	int mana = 0;
	int damage = 0;
	int cost = 0;
	int tier = 1;

public:
	virtual void attack(std::vector<pawn*>& boardToAttack)//= 0;
	{
		std::cout << name << " MASTER ATTACK.";
	}
	void getInfo()
	{
		std::cout << std::left << std::setw(15) << name << " Cost: " << std::setw(3) << cost << " Health: " << std::setw(6) << health << " Damage: " << std::setw(6) << damage << " Tier: " << std::setw(3) << tier << "\n";
	}
	int getCost()
	{
		return cost;
	}
	std::string getName()
	{
		return name;
	}
	int getTier()
	{
		return tier;
	}
	int getHealth()
	{
		return health;
	}
	void mergeTier()
	{
		tier++;
	}
	void recieveDamage(int damage)
	{
		health -= damage;
	}
};

class pawn1 : public pawn
{
public:
	pawn1()
	{
		name = "Ziutek";
		baseDamage = 5;
		damage = baseDamage;
		cost = 1;
		baseHealth = 100;
		health = baseHealth;
		baseMana = 100;
	}
	void attack(std::vector<pawn*>& boardToAttack)
	{
		int attackMaxIndex = boardToAttack.size();
		int attackIndex;

		attackIndex = rand() % attackMaxIndex;

		boardToAttack[attackIndex]->recieveDamage(damage);
		if (boardToAttack[attackIndex]->getHealth() <= 0)
		{
			boardToAttack.erase(boardToAttack.begin() + attackIndex);
		}
	}
};

class pawn2 : public pawn
{
public:
	pawn2()
	{
		name = "Jeremiasz";
		baseDamage = 10;
		damage = baseDamage;
		cost = 2;
		baseHealth = 80;
		health = baseHealth;
		baseMana = 60;
	}
	void attack(std::vector<pawn*>& boardToAttack)
	{
		/*std::cout << name << " CHILD ATTACK.\n";
		std::cout << damage << " CHILD DAMAGE.\n";*/

		int attackMaxIndex = boardToAttack.size();
		int attackIndex;

		attackIndex = rand() % attackMaxIndex;

		boardToAttack[attackIndex]->recieveDamage(damage);
		if (boardToAttack[attackIndex]->getHealth() <= 0)
		{
			boardToAttack.erase(boardToAttack.begin() + attackIndex);
		}
	}
};

class pawn3 : public pawn
{
public:
	pawn3()
	{
		name = "Marzena";
		baseDamage = 25;
		damage = baseDamage;
		cost = 3;
		baseHealth = 50;
		health = baseHealth;
		baseMana = 30;
	}
	void attack(std::vector<pawn*>& boardToAttack)
	{
		int attackMaxIndex = boardToAttack.size();
		int attackIndex;

		attackIndex = rand() % attackMaxIndex;

		boardToAttack[attackIndex]->recieveDamage(damage);
		if (boardToAttack[attackIndex]->getHealth() <= 0)
		{
			boardToAttack.erase(boardToAttack.begin() + attackIndex);
		}
	}
};