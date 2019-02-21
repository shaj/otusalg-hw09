
#pragma once

#include <iostream>
#include <memory>


namespace otusalg
{


template<typename T>
class BinTreeNode : public std::enable_shared_from_this<BinTreeNode<T>>
{

	T _data;

public:
	std::shared_ptr<BinTreeNode<T>> left;
	std::shared_ptr<BinTreeNode<T>> right;
	std::weak_ptr<BinTreeNode<T>> parent;

	BinTreeNode(const T &it, std::shared_ptr<BinTreeNode> p) : parent(p), _data(it)
	{
	}


	~BinTreeNode() {}


	void insert(const T &it)
	{
		if(it < _data)
		{
			if(left == nullptr)
				left = std::make_shared<BinTreeNode<T>>(it, this->shared_from_this());
			else
				left->insert(it);
		}
		else
		{
			if(right == nullptr)
				right = std::make_shared<BinTreeNode<T>>(it, this->shared_from_this());
			else
				right->insert(it);
		}
	}


	bool remove(const T &it)
	{
		return false;
	}


	void print(std::ostream &os)
	{
		os << "   node: " << _data << "\n";
		if(left != nullptr)
			left->print(os);
		if(right != nullptr)
			right->print(os);
	}

};


template<typename T>
class BinTree
{

	std::shared_ptr<BinTreeNode<T>> rootNode;

public:

	BinTree() {}
	~BinTree() {}

	void insert(const T &it)
	{
		if(rootNode == nullptr)
			rootNode = std::make_shared<BinTreeNode<T>>(it, nullptr);
		else
			rootNode->insert(it);
	}

	void remove(const T &it)
	{
		if(rootNode != nullptr)
			if(rootNode->remove(it))
				rootNode.reset();
	}

	// std::iterator<BinTree<T>> find(const T &it)
	// {
	// }

	void print(std::ostream &os)
	{
		os << "BinTree:\n";
		rootNode->print(os);
	}

};


} // namespace otusalg

