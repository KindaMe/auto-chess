#include <iostream>
#include <vector>

class pawn
{
protected:
	std::string name = "DEFAULT NAME";
	int damage = 0;
public:
	virtual void ability()
	{
		std::cout << name << " MASTER ABILITY.";
	}
};

class pawn1 : public pawn
{
public:
	pawn1()
	{
		name = "PAWN 1";
		damage = 5;
	}
	void ability()
	{
		std::cout << name << " CHILD ABILITY.\n";
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
	}
	void ability()
	{
		std::cout << name << " CHILD ABILITY.\n";
		std::cout << damage << " CHILD DAMAGE.\n";
	}
};

int main()
{
	std::vector<pawn*> pawnsPtrs;

	pawn* pawn1Ptr;
	pawn1 p1;
	pawn1Ptr = &p1;

	pawnsPtrs.push_back(pawn1Ptr);

	pawnsPtrs[0]->ability();

	system("pause>0");
}