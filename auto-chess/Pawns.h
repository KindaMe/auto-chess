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

	int maxHealth = 0;
	int health = 0;
	int maxMana = 0;
	int mana = 0;
	int damage = 0;
	int cost = 0;
	int tier = 1;

	bool recentlyDamaged = false;
	bool recentlyHealed = false;

public:
	virtual void attack(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard) = 0;
	virtual void ability(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard) = 0;
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
	int getMana()
	{
		return mana;
	}
	int getMaxMana()
	{
		return maxMana;
	}
	bool wereDamagedRecently()
	{
		return recentlyDamaged;
	}
	bool wereHealedRecently()
	{
		return recentlyHealed;
	}
	void mergeTier()
	{
		tier++;
		updateStats();
	}
	void recieveDamage(int damage)
	{
		health -= damage;
		recentlyDamaged = true;
	}
	void recieveHeal(bool canOverheal, int heal)
	{
		switch (canOverheal)
		{
		case true:
			health += heal;
			break;
		case false:
			if (health + heal > maxHealth)
			{
				health = maxHealth;
			}
			else
			{
				health += heal;
			}
			break;
		}
		recentlyHealed = true;
	}
	void recentlyReset()
	{
		recentlyDamaged = false;
		recentlyHealed = false;
	}
	void updateStats()
	{
		switch (tier)
		{
		case 1:

			maxHealth = baseHealth;
			health = maxHealth;
			maxMana = baseMana;
			mana = 0;
			damage = baseDamage;
			cost = baseCost;
			break;
		case 2:
			maxHealth = baseHealth * 2;
			health = maxHealth;
			maxMana = baseMana / 2;
			mana = 0;
			damage = baseDamage * 2;
			cost = baseCost * 3;
			break;
		case 3:
			maxHealth = baseHealth * 3;
			health = maxHealth;
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
	void attack(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		if (mana == maxMana)
		{
			ability(boardToAttack, attackingBoard);
		}
		else
		{
			int attackMaxIndex = boardToAttack.size();
			int attackIndex;

			attackIndex = rand() % attackMaxIndex;

			boardToAttack[attackIndex]->recieveDamage(damage);
			if (boardToAttack[attackIndex]->getHealth() <= 0)
			{
				boardToAttack.erase(boardToAttack.begin() + attackIndex);
			}

			if (mana + 10 > maxMana)
			{
				mana = maxMana;
				//ability(boardToAttack, attackingBoard);
			}
			else
			{
				mana += 10;
			}
		}
	}
	virtual void ability(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		std::cout << "casted ability debug";
		mana = 0;
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
	void attack(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		if (mana == maxMana)
		{
			ability(boardToAttack, attackingBoard);
		}
		else
		{
			int attackMaxIndex = boardToAttack.size();
			int attackIndex;

			attackIndex = rand() % attackMaxIndex;

			boardToAttack[attackIndex]->recieveDamage(damage);
			if (boardToAttack[attackIndex]->getHealth() <= 0)
			{
				boardToAttack.erase(boardToAttack.begin() + attackIndex);
			}

			if (mana + 10 > maxMana)
			{
				mana = maxMana;
				//ability(boardToAttack, attackingBoard);
			}
			else
			{
				mana += 10;
			}
		}
	}
	virtual void ability(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		mana = 0;

		boardToAttack[0]->recieveDamage(boardToAttack[0]->getHealth() * 0.1);
		boardToAttack[boardToAttack.size() - 1]->recieveDamage(boardToAttack[0]->getHealth() * 0.1);
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
	void attack(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		if (mana == maxMana)
		{
			ability(boardToAttack, attackingBoard);
		}
		else
		{
			int attackMaxIndex = boardToAttack.size();
			int attackIndex;

			attackIndex = rand() % attackMaxIndex;

			boardToAttack[attackIndex]->recieveDamage(damage);
			if (boardToAttack[attackIndex]->getHealth() <= 0)
			{
				boardToAttack.erase(boardToAttack.begin() + attackIndex);
			}

			if (mana + 10 > maxMana)
			{
				mana = maxMana;
				//ability(boardToAttack, attackingBoard);
			}
			else
			{
				mana += 10;
			}
		}
	}
	virtual void ability(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		mana = 0;
		int tempHeal = 0;

		for (int i = 0; i < boardToAttack.size(); i++)
		{
			boardToAttack[i]->recieveDamage(5);
			tempHeal += 5;
		}

		recieveHeal(true, tempHeal);
	}
};