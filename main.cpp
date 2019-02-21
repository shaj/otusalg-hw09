
#include <iostream>
#include <vector>
#include <chrono>

#include "generators.h"
#include "bintree.h"

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

	std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	otusalg::BinTree<int> bt;

	for(const auto &it: v)
		bt.insert(it);

	bt.print(std::cout);

	return 0;
}

