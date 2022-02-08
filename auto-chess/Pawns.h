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

	bool isDead = false;

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
	int getMaxHealth()
	{
		return maxHealth;
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
	bool getIsDead()
	{
		return isDead;
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

		if (health <= 0)
		{
			isDead = true;
			health = 0;
		}
	}
	void recieveHeal(bool canOverheal, int heal)
	{
		switch (canOverheal)
		{
		case true:
			health += heal;
			break;
		case false:
			if (health >= maxHealth)
			{
				return;
			}
			else if (health + heal > maxHealth)
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
		isDead = false;
	}
};

class pawn1 : public pawn
{
public:
	pawn1()
	{
		name = "Thanasis";
		baseHealth = 100;
		baseMana = 50;
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

		int lowestHpIndex = 0;

		for (int i = 0; i < boardToAttack.size(); i++)
		{
			if (boardToAttack[lowestHpIndex]->getHealth() > boardToAttack[i]->getHealth())
			{
				lowestHpIndex = i;
			}
		}

		boardToAttack[lowestHpIndex]->recieveDamage(9999);
	}
};

class pawn2 : public pawn
{
public:
	pawn2()
	{
		name = "Korina";
		baseHealth = 80;
		baseMana = 40;
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
		name = "Agapios";
		baseHealth = 50;
		baseMana = 60;
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

class pawn4 : public pawn
{
public:
	pawn4()
	{
		name = "Ermis";
		baseHealth = 70;
		baseMana = 0;
		baseDamage = 10;
		baseCost = 2;
		updateStats();
	}
	void attack(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		bool woundedAllies = false;

		for (int i = 0; i < attackingBoard.size(); i++)
		{
			if (attackingBoard[i]->getHealth() < attackingBoard[i]->getMaxHealth())
			{
				woundedAllies = true;
				break;
			}
		}
		if (woundedAllies == true)
		{
			for (int i = 0; i < attackingBoard.size(); i++)
			{
				ability(boardToAttack, attackingBoard);
			}
		}
		else
		{
			int attackMaxIndex = boardToAttack.size();
			int attackIndex;

			attackIndex = rand() % attackMaxIndex;

			boardToAttack[attackIndex]->recieveDamage(damage);
		}
	}
	virtual void ability(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
	{
		for (int i = 0; i < attackingBoard.size(); i++)
		{
			attackingBoard[i]->recieveHeal(false, damage);
		}
	}
};

//quick template
//class xxxxxx : public pawn
//{
//public:
//	xxxxxx()
//	{
//		name = "xxxxxx";
//		baseHealth = xxxxxx;
//		baseMana = xxxxxx;
//		baseDamage = xxxxxx;
//		baseCost = xxxxxx;
//		updateStats();
//	}
//	void attack(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
//	{
//		if (mana == maxMana)
//		{
//			ability(boardToAttack, attackingBoard);
//		}
//		else
//		{
//			int attackMaxIndex = boardToAttack.size();
//			int attackIndex;
//
//			attackIndex = rand() % attackMaxIndex;
//
//			boardToAttack[attackIndex]->recieveDamage(damage);
//
//			if (mana + 10 > maxMana)
//			{
//				mana = maxMana;
//			}
//			else
//			{
//				mana += 10;
//			}
//		}
//	}
//	virtual void ability(std::vector<pawn*>& boardToAttack, std::vector<pawn*>& attackingBoard)
//	{
//		mana = 0;
//	}
//};