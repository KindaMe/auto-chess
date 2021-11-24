#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iomanip>

const int benchMax = 9;
const int boardMax = 7;

const int shopMax = 5;
const int refreshCost = 2;

class pawn
{
protected:
	std::string name = "DEFAULT NAME";
	int health = 0;
	int damage = 0;
	int cost = 0;
	int tier = 1;

public:
	virtual void attack()//= 0;
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
	void mergeTier()
	{
		tier++;
	}
};

class pawn1 : public pawn
{
public:
	pawn1()
	{
		name = "Ziutek";
		damage = 5;
		cost = 1;
		health = 100;
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
		name = "Jeremiasz";
		damage = 10;
		cost = 2;
		health = 80;
	}
	void attack()
	{
		std::cout << name << " CHILD ATTACK.\n";
		std::cout << damage << " CHILD DAMAGE.\n";
	}
};

class pawn3 : public pawn
{
public:
	pawn3()
	{
		name = "Marzena";
		damage = 25;
		cost = 3;
		health = 50;
	}
	void attack()
	{
		std::cout << name << " CHILD ATTACK.\n";
		std::cout << damage << " CHILD DAMAGE.\n";
	}
};

void inGame();
void shopping(int& goldPtr, std::vector<pawn*>& benchPtr, std::vector<pawn*>& shop);
void refreshShop(std::vector<pawn*>& shop);
void manageBoard(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr);
void mergeCheck(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr);
void mergePawns(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr, std::vector<int> sameIndex);

int main()
{
	srand(time(NULL));

	inGame();

	system("pause>0");
}

void inGame()
{
	int gold = 25;
	std::vector<pawn*> shop;
	std::vector<pawn*> bench;
	std::vector<pawn*> board;

	char choice;

	do
	{
		system("cls");

		std::cout << "1 - Manage Board\n2 - Shop\n\nR - Ready up.";
		std::cout << "\n\n\nChoose: ";
		std::cin >> choice;

		switch (tolower(choice))
		{
		case '1':
			manageBoard(bench, board);
			mergeCheck(bench, board);
			break;
		case '2':
			shopping(gold, bench, shop);
			mergeCheck(bench, board);
			break;
		case 'r':
			std::cout << "Ready!";
			std::cin.ignore();
			std::cin.clear();
			std::cin.get();
			break;
		default:
			break;
		}
	} while (true);

	for (int i = 0; i < board.size(); i++)
	{
		board[i]->attack();
	}
}

void shopping(int& goldPtr, std::vector<pawn*>& benchPtr, std::vector<pawn*>& shop)
{
	do
	{
		system("cls");

		std::cout << "Shop [" << shop.size() << "/" << shopMax << "]: " << "\n\n";
		for (int i = 0; i < shop.size(); i++)
		{
			std::cout << i + 1 << " - ";
			shop[i]->getInfo();
		}
		std::cout << "\nR - Refresh (" << refreshCost << " gold) " << "\n\n";

		std::cout << "\nBench [" << benchPtr.size() << "/" << benchMax << "]: " << "\n\n";

		for (int i = 0; i < benchPtr.size(); i++)
		{
			std::cout << i + 1 << " - ";
			benchPtr[i]->getInfo();
		}

		std::cout << "\n\nGold: " << goldPtr << "\n\n";

		char choice;

		std::cout << "(X - Exit)";
		std::cout << "\nChoose pawn to buy: ";
		std::cin >> choice;

		if (isalnum(choice) && (choice - '0' - 1) >= 0 && (choice - '0' - 1) < shop.size())
		{
			if (goldPtr - shop[choice - '0' - 1]->getCost() >= 0 && benchPtr.size() < benchMax)
			{
				goldPtr -= shop[choice - '0' - 1]->getCost();
				benchPtr.push_back(shop[choice - '0' - 1]);
				shop.erase((shop.begin() + (choice - '0' - 1)));
			}
		}
		else if (tolower(choice) == 'r')
		{
			if (goldPtr - refreshCost >= 0)
			{
				goldPtr -= refreshCost;
				refreshShop(shop);
			}
		}
		else if (tolower(choice == 'x'))
		{
			return;
		}
	} while (true);
}

void refreshShop(std::vector<pawn*>& shop)
{
	shop.clear();

	for (int i = 0; i < shopMax; i++)
	{
		switch (rand() % 3)
		{
		case 0:
			shop.push_back(new pawn1);
			break;
		case 1:
			shop.push_back(new pawn2);
			break;
		case 2:
			shop.push_back(new pawn3);
			break;
		}
	}
}

void manageBoard(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr)
{
	char choice;
	bool mode = false;

	do
	{
		system("cls");

		std::cout << "Board [" << boardPtr.size() << "/" << boardMax << "]: " << "\n\n";

		for (int i = 0; i < boardPtr.size(); i++)
		{
			std::cout << i + 1 << " - ";
			boardPtr[i]->getInfo();
		}

		std::cout << "\nBench [" << benchPtr.size() << "/" << benchMax << "]: " << "\n\n";

		for (int i = 0; i < benchPtr.size(); i++)
		{
			std::cout << i + 1 << " - ";
			benchPtr[i]->getInfo();
		}

		if (mode == false)
		{
			std::cout << "\n(S - Switch mode / X - Exit)";
			std::cout << "\nAdd to board: ";
			std::cin >> choice;

			if (isalnum(choice) && (choice - '0' - 1) >= 0 && (choice - '0' - 1) < benchPtr.size())
			{
				if (boardPtr.size() < boardMax)
				{
					boardPtr.push_back(benchPtr[choice - '0' - 1]);
					benchPtr.erase((benchPtr.begin() + (choice - '0' - 1)));
				}
			}
			else if (tolower(choice) == 's')
			{
				mode = true;
			}
			else if (tolower(choice == 'x'))
			{
				return;
			}
		}
		else if (mode == true)
		{
			std::cout << "\n(S - Switch mode / X - Exit)";
			std::cout << "\nRemove from board: ";
			std::cin >> choice;

			if (isalnum(choice) && (choice - '0' - 1) >= 0 && (choice - '0' - 1) < boardPtr.size())
			{
				if (benchPtr.size() < benchMax)
				{
					benchPtr.push_back(boardPtr[choice - '0' - 1]);
					boardPtr.erase((boardPtr.begin() + (choice - '0' - 1)));
				}
			}
			else if (tolower(choice) == 's')
			{
				mode = false;
			}
			else if (tolower(choice == 'x'))
			{
				return;
			}
		}
	} while (true);
}

void mergeCheck(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr)
{
	std::vector<int> sameIndex;
	pawn* tempPawn = NULL;
	bool merged = false;

	do
	{
		merged = false;

		for (int h = 0; h < benchPtr.size() + boardPtr.size(); h++)
		{
			sameIndex.clear();
			sameIndex.push_back(h);

			if (h < benchPtr.size())
			{
				tempPawn = benchPtr[h];
			}
			else if (h >= benchPtr.size())
			{
				tempPawn = boardPtr[h - benchPtr.size()];
			}

			for (int i = 0; i < benchPtr.size() + boardPtr.size(); i++)
			{
				if (i < benchPtr.size() && benchPtr[i]->getName() == tempPawn->getName() && benchPtr[i]->getTier() == tempPawn->getTier() && i != h)
				{
					//std::cout << "\nbench//";
					sameIndex.push_back(i);
					//benchPtr[i]->getInfo();

					if (sameIndex.size() == 3)
					{
						mergePawns(benchPtr, boardPtr, sameIndex);

						merged = true;
						goto restartOnMerge;
					}
				}
				else if (i >= benchPtr.size() && boardPtr[i - benchPtr.size()]->getName() == tempPawn->getName() && boardPtr[i - benchPtr.size()]->getTier() == tempPawn->getTier() && i != h)
				{
					//std::cout << "\nboard//";
					sameIndex.push_back(i);
					//boardPtr[i - benchPtr.size()]->getInfo();

					if (sameIndex.size() == 3)
					{
						mergePawns(benchPtr, boardPtr, sameIndex);

						merged = true;
						goto restartOnMerge;
					}
				}
			}
		}
	restartOnMerge: {}
	} while (merged == true);

	/*std::cin.ignore();
	std::cin.clear();
	std::cin.get();*/
}

void mergePawns(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr, std::vector<int> sameIndex)
{
	for (int i = 2; i >= 0; i--)
	{
		if (i != 0)
		{
			if (sameIndex[i] >= benchPtr.size())
			{
				boardPtr.erase(boardPtr.begin() + (sameIndex[i] - benchPtr.size()));
			}
			else if (sameIndex[i] < benchPtr.size())
			{
				benchPtr.erase(benchPtr.begin() + sameIndex[i]);
			}
		}
		else if (i == 0)
		{
			if (sameIndex[i] >= benchPtr.size())
			{
				boardPtr[sameIndex[i] - benchPtr.size()]->mergeTier();
			}
			else if (sameIndex[i] < benchPtr.size())
			{
				benchPtr[sameIndex[i]]->mergeTier();
			}
		}
	}
}