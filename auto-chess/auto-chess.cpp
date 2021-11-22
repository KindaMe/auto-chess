#include <iostream>
#include <vector>
#include <stdlib.h>

class pawn
{
protected:
	std::string name = "DEFAULT NAME";
	int damage = 0;
	int cost = 0;

public:
	virtual void attack()
	{
		std::cout << name << " MASTER ATTACK.";
	}
	void getInfo()
	{
		std::cout << name << " Damage: " << damage << " Cost: " << cost << "\n";
	}
	int getCost()
	{
		return cost;
	}
};

class pawn1 : public pawn
{
public:
	pawn1()
	{
		name = "PAWN 1";
		damage = 5;
		cost = 1;
	}
	void attack()
	{
		std::cout << name << " CHILD ATTACK.\n";
		std::cout << damage << " CHILD DAMAGE.\n";
	}
};

class pawn2 : public pawn
{
public:
	pawn2()
	{
		name = "PAWN 2";
		damage = 10;
		cost = 2;
	}
	void attack()
	{
		std::cout << name << " CHILD ATTACK.\n";
		std::cout << damage << " CHILD DAMAGE.\n";
	}
};

void shopping(int& moneyPtr, std::vector<pawn*>& inventoryPtr);
void inGame();

int main()
{
	srand(time(NULL));

	inGame();

	system("pause>0");
}

void shopping(int& moneyPtr, std::vector<pawn*>& inventoryPtr)
{
	std::vector<pawn*> shop;

	const int shopSize = 5;

	const int refreshCost = 2;
	bool refresh = false;

	do
	{
		refresh = false;
		shop.clear();

		for (int i = 0; i < shopSize; i++)
		{
			switch (rand() % 2)
			{
			case 0:
				shop.push_back(new pawn1);
				break;
			case 1:
				shop.push_back(new pawn2);
				break;
			}
		}

		do
		{
			system("cls");

			std::cout << "Shop: \n\n";
			for (int i = 0; i < shop.size(); i++)
			{
				std::cout << i + 1 << " - ";
				shop[i]->getInfo();
			}
			std::cout << "\nR - Refresh (" << refreshCost << " gold) " << "\n\n";

			std::cout << "\nInventory: \n\n";

			for (int i = 0; i < inventoryPtr.size(); i++)
			{
				inventoryPtr[i]->getInfo();
			}

			std::cout << "\n\nBalance: " << moneyPtr << "\n\n";

			char choice;

			std::cout << "Choose pawn to buy: ";
			std::cin >> choice;

			if (isalnum(choice) && (choice - '0' - 1) >= 0 && (choice - '0' - 1) < shop.size())
			{
				if (moneyPtr - shop[choice - '0' - 1]->getCost() >= 0)
				{
					moneyPtr -= shop[choice - '0' - 1]->getCost();
					inventoryPtr.push_back(shop[choice - '0' - 1]);
					shop.erase((shop.begin() + (choice - '0' - 1)));
				}
			}
			else if (tolower(choice) == 'r')
			{
				if (moneyPtr - refreshCost >= 0)
				{
					refresh = true;
					moneyPtr -= refreshCost;
				}
			}
		} while (refresh == false);
	} while (refresh == true);
}

void inGame()
{
	int money = 25;
	std::vector<pawn*> shop;
	std::vector<pawn*> inventory;

	shopping(money, inventory);

	for (int i = 0; i < inventory.size(); i++)
	{
		inventory[i]->attack();
	}
}

//virtual functions