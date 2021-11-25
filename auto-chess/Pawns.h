#pragma once

#include <iostream>
#include <string>
#include <iomanip>

class pawn
{
protected:
	std::string name = "DEFAULT NAME";
	int baseHealth = 0;
	int baseMana = 0;
	int baseDamage = 0;
	int baseCost = 0;

	int health = 0;
	int maxMana = 0;
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
		std::cout << std::left << std::setw(15) << name << " Cost: " << std::setw(3) << cost << " Damage: " << std::setw(6) << damage << " Health: " << std::setw(6) << health << " Mana: " << std::setw(5) << maxMana << " Tier: " << std::setw(3) << tier << "\n";
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
		updateStats();
	}
	void recieveDamage(int damage)
	{
		health -= damage;
	}
	void updateStats()
	{
		switch (tier)
		{
		case 1:
			health = baseHealth;
			maxMana = baseMana;
			mana = 0;
			damage = baseDamage;
			cost = baseCost;

			break;
		case 2:
			health = baseHealth * 2;
			maxMana = baseMana / 2;
			mana = 0;
			damage = baseDamage * 2;
			cost = baseCost * 3;

			break;
		case 3:
			health = baseHealth * 3;
			maxMana = baseMana / 3;
			mana = 0;
			damage = baseDamage * 3;
			cost = baseCost * 9;
			break;
		}
	}
};

class pawn1 : public pawn
{
public:
	pawn1()
	{
		name = "Ziutek";
		baseHealth = 100;
		baseMana = 100;
		baseDamage = 5;
		baseCost = 1;
		updateStats();
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
		baseHealth = 80;
		baseMana = 60;
		baseDamage = 10;
		baseCost = 2;
		updateStats();
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

class pawn3 : public pawn
{
public:
	pawn3()
	{
		name = "Marzena";
		baseHealth = 50;
		baseMana = 30;
		baseDamage = 25;
		baseCost = 3;
		updateStats();
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