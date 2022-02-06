#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "pawns.h"
#include <thread>
#include "color.h"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

const int benchMax = 9;
const int boardMax = 7;

const int shopMax = 5;
const int refreshCost = 2;

void inGame();
void shopping(int& goldPtr, std::vector<pawn*>& benchPtr, std::vector<pawn*>& shop);
void refreshShop(std::vector<pawn*>& shop);
void manageBoard(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr);
void mergeCheck(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr);
void mergePawns(std::vector<pawn*>& benchPtr, std::vector<pawn*>& boardPtr, std::vector<int> sameIndex);
void battleMenu(std::vector<pawn*>& boardPtr);
void printBoard(std::vector<pawn*>& playerBoard, std::vector<pawn*>& enemyBoard);
void battle(std::vector<pawn*> playerBoard, std::vector<pawn*> enemyBoard);

void timer(int seconds, std::string message);
void timer(int seconds);

int main()
{
	srand(time(NULL));

	inGame();

	system("pause>0");
}

void inGame()
{
	int gold = 50;
	std::vector<pawn*> shop;
	std::vector<pawn*> bench;
	std::vector<pawn*> board;

	char choice;

	do
	{
		system("cls");

		std::cout << "1 - Shop\n2 - Manage Board\n\nR - Ready up.";
		std::cout << "\n\n\nChoose: ";
		std::cin >> choice;

		switch (tolower(choice))
		{
		case '2':
			manageBoard(bench, board);
			mergeCheck(bench, board);
			break;
		case '1':
			shopping(gold, bench, shop);
			mergeCheck(bench, board);
			break;
		case 'r':
			std::cout << "Ready!";

			battleMenu(board);
			break;
		default:
			break;
		}
	} while (true);
}

void shopping(int& goldPtr, std::vector<pawn*>& benchPtr, std::vector<pawn*>& shop)
{
	char mode = 'b';
	char choice;

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

		std::cout << "Switch mode - S / Refresh shop - R\nOr ";
		(mode == 'b') ? std::cout << "choose pawn to buy: " : std::cout << "choose pawn to sell: ";

		std::cin >> choice;

		if (isdigit(choice) && (choice - '0' - 1) >= 0)
		{
			if (mode == 'b' && (choice - '0' - 1) < shop.size())
			{
				if (goldPtr - shop[choice - '0' - 1]->getCost() >= 0 && benchPtr.size() < benchMax)
				{
					goldPtr -= shop[choice - '0' - 1]->getCost();
					benchPtr.push_back(shop[choice - '0' - 1]);
					shop.erase((shop.begin() + (choice - '0' - 1)));
				}
			}
			else if (mode == 's' && (choice - '0' - 1) < benchPtr.size())
			{
				goldPtr += benchPtr[choice - '0' - 1]->getCost();
				delete benchPtr[choice - '0' - 1];
				benchPtr.erase((benchPtr.begin() + (choice - '0' - 1)));
			}
		}
		else if (tolower(choice) == 's')
		{
			(mode == 'b') ? mode = 's' : mode = 'b';
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

			if (isdigit(choice) && (choice - '0' - 1) >= 0 && (choice - '0' - 1) < benchPtr.size())
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

			if (isdigit(choice) && (choice - '0' - 1) >= 0 && (choice - '0' - 1) < boardPtr.size())
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
					sameIndex.push_back(i);

					if (sameIndex.size() == 3)
					{
						mergePawns(benchPtr, boardPtr, sameIndex);

						merged = true;
						goto restartOnMerge;
					}
				}
				else if (i >= benchPtr.size() && boardPtr[i - benchPtr.size()]->getName() == tempPawn->getName() && boardPtr[i - benchPtr.size()]->getTier() == tempPawn->getTier() && i != h)
				{
					sameIndex.push_back(i);

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

void battleMenu(std::vector<pawn*>& boardPtr)
{
	/////enemy placeholder
	std::vector<pawn*> EnemyBoardDebug;
	std::vector<pawn*> EnemyBenchEmptyDebug;

	for (int i = 0; i < boardMax; i++)
	{
		switch (rand() % 3)
		{
		case 0:
			EnemyBoardDebug.push_back(new pawn1);
			break;
		case 1:
			EnemyBoardDebug.push_back(new pawn2);
			break;
		case 2:
			EnemyBoardDebug.push_back(new pawn3);
			break;
		}
	}
	mergeCheck(EnemyBenchEmptyDebug, EnemyBoardDebug);
	/////

	printBoard(boardPtr, EnemyBoardDebug);

	std::cout << "\n\nBattle begins in:\n";
	timer(5, "Fight!");

	battle(boardPtr, EnemyBoardDebug);
	for (int i = 0; i < boardPtr.size(); i++)//reset stats
	{
		boardPtr[i]->updateStats();
	}

	std::cout << "\nEnd of battle.\n";

	timer(5);
}

void printBoard(std::vector<pawn*>& playerBoard, std::vector<pawn*>& enemyBoard)
{
	system("cls");

	std::cout << "Your pawns";
	std::cout << "\n" << std::string(boardMax * 15, '-') << "\n";

	for (int i = 0; i < playerBoard.size(); i++)
	{
		std::string temp = "Mana: " + std::to_string(playerBoard[i]->getMana()) + "/" + std::to_string(playerBoard[i]->getMaxMana());

		if (playerBoard[i]->getMana() == playerBoard[i]->getMaxMana())
		{
			std::cout << std::left << std::setw(15) << dye::blue(temp);
		}
		else
		{
			std::cout << std::left << std::setw(15) << temp;
		}
	}

	std::cout << "\n";

	for (int i = 0; i < playerBoard.size(); i++)
	{
		std::string temp = "Health: " + std::to_string(playerBoard[i]->getHealth());

		if (playerBoard[i]->wereDamagedRecently())
		{
			std::cout << std::left << std::setw(15) << dye::red(temp);
		}
		else if (playerBoard[i]->wereHealedRecently())
		{
			std::cout << std::left << std::setw(15) << dye::green(temp);
		}
		else
		{
			std::cout << std::left << std::setw(15) << temp;
		}
	}

	std::cout << "\n";

	for (int i = 0; i < playerBoard.size(); i++)
	{
		std::string temp = "Tier: " + std::to_string(playerBoard[i]->getTier());
		std::cout << std::left << std::setw(15) << temp;
	}

	std::cout << "\n\n";

	for (int i = 0; i < playerBoard.size(); i++)
	{
		std::cout << std::left << std::setw(15) << dye::black_on_white(playerBoard[i]->getName());
	}

	std::cout << "\n" << std::string(boardMax * 15, '-') << "\n";

	for (int i = 0; i < enemyBoard.size(); i++)
	{
		std::cout << std::left << std::setw(15) << dye::black_on_white(enemyBoard[i]->getName());
	}

	std::cout << "\n\n";

	for (int i = 0; i < enemyBoard.size(); i++)
	{
		std::string temp = "Tier: " + std::to_string(enemyBoard[i]->getTier());
		std::cout << std::left << std::setw(15) << temp;
	}

	std::cout << "\n";

	for (int i = 0; i < enemyBoard.size(); i++)
	{
		std::string temp = "Health: " + std::to_string(enemyBoard[i]->getHealth());

		if (enemyBoard[i]->wereDamagedRecently())
		{
			std::cout << std::left << std::setw(15) << dye::red(temp);
		}
		else if (enemyBoard[i]->wereHealedRecently())
		{
			std::cout << std::left << std::setw(15) << dye::green(temp);
		}
		else
		{
			std::cout << std::left << std::setw(15) << temp;
		}
	}

	std::cout << "\n";

	for (int i = 0; i < enemyBoard.size(); i++)
	{
		std::string temp = "Mana: " + std::to_string(enemyBoard[i]->getMana()) + "/" + std::to_string(enemyBoard[i]->getMaxMana());

		if (enemyBoard[i]->getMana() == enemyBoard[i]->getMaxMana())
		{
			std::cout << std::left << std::setw(15) << dye::blue(temp);
		}
		else
		{
			std::cout << std::left << std::setw(15) << temp;
		}
	}

	std::cout << "\n" << std::string(boardMax * 15, '-') << "\n";
	std::cout << "Enemy pawns\n";
}

void battle(std::vector<pawn*> playerBoard, std::vector<pawn*> enemyBoard)
{
	int counter;

	while (true)
	{
		//make it so team with less pawns starts

		if (enemyBoard.size() > playerBoard.size())
		{
			counter = enemyBoard.size();
		}
		else
		{
			counter = playerBoard.size();
		}

		for (int i = 0; i < counter; i++)
		{
			if (enemyBoard.size() == 0)
			{
				printBoard(playerBoard, enemyBoard);
				std::cout << "\nYou won!\n";
				return;
			}
			else if (playerBoard.size() == 0)
			{
				printBoard(playerBoard, enemyBoard);
				std::cout << "\nYou lost.\n";
				return;
			}
			else
			{
				if (i < playerBoard.size())
				{
					playerBoard[i]->attack(enemyBoard, playerBoard);

					printBoard(playerBoard, enemyBoard);
					std::cout << "\n\n" << i << " " << playerBoard[i]->getName() << " attacked!" << "\n";

					sleep_for(2s);
				}

				//reset 'recently' flags
				for (int i = 0; i < enemyBoard.size(); i++)
				{
					enemyBoard[i]->recentlyReset();
				}
				for (int i = 0; i < playerBoard.size(); i++)
				{
					playerBoard[i]->recentlyReset();
				}

				if (i < enemyBoard.size())
				{
					enemyBoard[i]->attack(playerBoard, enemyBoard);

					printBoard(playerBoard, enemyBoard);
					std::cout << "\n\n" << i << " " << enemyBoard[i]->getName() << " attacked!" << "\n";

					sleep_for(2s);
				}

				//reset 'recently' flags
				for (int i = 0; i < playerBoard.size(); i++)
				{
					playerBoard[i]->recentlyReset();
				}
				for (int i = 0; i < enemyBoard.size(); i++)
				{
					enemyBoard[i]->recentlyReset();
				}
			}
		}
	}
}

void timer(int seconds, std::string message)
{
	for (int i = seconds; i > 0; i--)
	{
		std::cout << i << " \r";
		sleep_for(1s);
	}
	std::cout << message << "\r\n";
	sleep_for(1s);
}

void timer(int seconds)
{
	for (int i = seconds; i > 0; i--)
	{
		std::cout << i << " \r";
		sleep_for(1s);
	}
	std::cout << "  \r\n";
}