
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>

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



void split(std::vector<std::string> &v, std::string str, std::string delim)
{
	std::string word = "";
	for (int i = 0; i < str.size(); i++)
	{
		if (delim.find(str[i]) == std::string::npos)
		{
			word += str[i];
		}
		else if (word.size() > 0)
		{
			v.push_back(word);
			word = "";
		}
	}
	if (word.size() > 0)
		v.push_back(word);
}



std::vector<std::string> parseDataset(char* name)
{
	std::fstream in(name);
	std::string line;
	std::vector<std::string> result;
	if (in.is_open())
	{
		while (std::getline(in, line))
			split(result, line, " .,<>@-=():_';\"");
	}
	in.close();
	return result;
}





int main(int argc, char const *argv[])
{

	// {
	// 	std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		
	// 	otusalg::BinTree<int> bt;

	// 	for(const auto &it: v)
	// 		bt.insert(it);

	// 	bt.print(std::cout);

	// }

	// {
	// 	std::vector<int> v {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};

	// 	otusalg::BinTree<int> bt;

	// 	for(const auto &it: v)
	// 		bt.insert(it);

	// 	bt.print(std::cout);



	// 	auto a = bt.find(11);
	// 	a->bl_rotate();
	// 	a->br_rotate();
	// 	a->l_rotate();
	// 	a->r_rotate();

	// 	if(bt.find(0) == nullptr) std::cout << "Not found 0\n";
	// 	else std::cout << "Found 0\n";

	// 	if(bt.find(5) == nullptr) std::cout << "Not found 5\n";
	// 	else std::cout << "Found 5\n";

	// 	if(bt.find(10) == nullptr) std::cout << "Not found 10\n";
	// 	else std::cout << "Found 10\n";

	// 	if(bt.find(20) == nullptr) std::cout << "Not found 20\n";
	// 	else std::cout << "Found 20\n";

	// 	bt.print(std::cout);
	// }


	// {
	// 	std::cout << "\n\nAVL Tree\n\n";

	// 	std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
		
	// 	otusalg::AVLTree<int> bt;

	// 	for(const auto &it: v)
	// 	{
	// 		std::cout << "Insert " << it << std::endl;
	// 		bt.insert(it);
	// 	}

	// 	bt.print(std::cout);
	// }


	// {
	// 	std::cout << "\n\nAVL Tree\n\n";

	// 	std::vector<int> v {
	// 		8,
	// 		2, 6, 14,
	// 		1, 3, 13, 15, 16,
	// 		9, 10, 11, 12,
	// 		4, 5,

	// 		11, 12, 14, 17, 17, 19, 20, 19
	// 	};
		
	// 	otusalg::AVLTree<int> bt;

	// 	for(const auto &it: v)
	// 	{
	// 		std::cout << "Insert " << it << std::endl;
	// 		bt.insert(it);
	// 	}

	// 	bt.print(std::cout);

	// 	bt.remove(13);

	// 	bt.print(std::cout);

	// 	bt.remove(11);
	// 	bt.remove(12);
	// 	bt.remove(16);

	// 	bt.print(std::cout);
	// }



	// {
	// 	std::cout << "\n\nAVL Tree\n\n";

	// 	otusalg::AVLTree<int> bt;

	// 	std::srand(std::time(nullptr));
	
	// 	for(int i=300; i>0; i--)
	// 	{
	// 		bt.insert(std::rand() % 500);
	// 	}

	// 	bt.print(std::cout);

	// 	for(int i=1000; i>0; i--)
	// 	{
	// 		bt.remove(std::rand() % 500);
	// 	}

	// 	bt.print(std::cout);
	// }


	// {
	// 	std::cout << "\n\nAVL Tree string\n\n";

	// 	std::vector<std::string> v {
	// 		"A", 
	// 		"B",
	// 		"C",
	// 		"D",
	// 		"E",
	// 		"F",
	// 		"G",
	// 		"H",
	// 		"I",
	// 		"J",
	// 		"K",
	// 		"L",
	// 		"M",
	// 		"N",
	// 		"O",
	// 		"P",
	// 		"Q"
	// 	};
		
	// 	otusalg::AVLTree<std::string> bt;

	// 	for(const auto &it: v)
	// 	{
	// 		std::cout << "Insert " << it << std::endl;
	// 		bt.insert(it);
	// 	}

	// 	bt.print(std::cout);
	// }


	{
		std::cout << "\n\nAVL Tree string\n\n";
		// auto v = parseDataset("wiki.test");
		auto v = parseDataset("wiki.train");
		otusalg::AVLTree<std::string> bt;
		for(const auto &it: v)
		{
			bt.insert(it);
		}

		bt.print(std::cout);
	}


	return 0;
}

