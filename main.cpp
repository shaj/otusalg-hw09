
#include <iostream>
#include <vector>
#include <chrono>

#include "generators.h"
#include "bintree.h"
#include "avltree.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	// typedef typename TimeT::rep type;
	using type = typename TimeT::rep;

	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
							(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};



int main(int argc, char const *argv[])
{

	{
		std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		
		otusalg::BinTree<int> bt;

		for(const auto &it: v)
			bt.insert(it);

		bt.print(std::cout);

	}

	{
		std::vector<int> v {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};

		otusalg::BinTree<int> bt;

		for(const auto &it: v)
			bt.insert(it);

		bt.print(std::cout);



		auto a = bt.find(11);
		a->bl_rotate();
		a->br_rotate();
		a->l_rotate();
		a->r_rotate();

		if(bt.find(0) == nullptr) std::cout << "Not found 0\n";
		else std::cout << "Found 0\n";

		if(bt.find(5) == nullptr) std::cout << "Not found 5\n";
		else std::cout << "Found 5\n";

		if(bt.find(10) == nullptr) std::cout << "Not found 10\n";
		else std::cout << "Found 10\n";

		if(bt.find(20) == nullptr) std::cout << "Not found 20\n";
		else std::cout << "Found 20\n";

		bt.print(std::cout);
	}


	{
		std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		
		otusalg::AVLTree<int> bt;

		for(const auto &it: v)
			bt.insert(it);

		std::cout << "\n\nAVL Tree\n\n";
		bt.print(std::cout);
	}


	return 0;
}

