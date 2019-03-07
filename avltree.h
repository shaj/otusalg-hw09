
#pragma once

#include <iostream>
#include <memory>

#include "bintree.h"

namespace otusalg
{

template<typename T>
class AVLTreeNode : public BinTreeNode<T>
{
	using BT = BinTreeNode<T>;

protected:

	int balance;

public: 

	AVLTreeNode(const T &it, std::shared_ptr<BinTreeNode<T>> p) : BinTreeNode<T>(it, p), balance(0) 
	{
		// При любом добавлении узла вызываем балансировку
		setBalance();
	}

	~AVLTreeNode() {}

	void insert(const T &it) override
	{
		if(it < BT::_data)
		{
			if(BT::left == nullptr)
				BT::left = std::make_shared<AVLTreeNode<T>>(it, this->shared_from_this());
			else
				BT::left->insert(it);
		}
		else
		{
			if(BT::right == nullptr)
				BT::right = std::make_shared<AVLTreeNode<T>>(it, this->shared_from_this());
			else
				BT::right->insert(it);
		}
	}

	
	void setBalance()
	{
		int res = 0;
		int l = 0;
		int r = 0;

		if(BT::left != nullptr)
		{
			l = static_cast<AVLTreeNode<T>*>(BT::left.get())->balance;
		}
		if(BT::right != nullptr)
		{
			r = static_cast<AVLTreeNode<T>*>(BT::right.get())->balance;
		}

		// if((r - l) > 1)
		// {
		// 	// Балансировка
		// 	if(static_cast<std::shared_ptr<AVLTreeNode<T>>>(BT::right->right)->balance < 
		// 		static_cast<std::shared_ptr<AVLTreeNode<T>>>(BT::right->left)->balance)
		// 		BT::bl_rotate();
		// 	else
		// 		BT::l_rotate();
		// }
		// else if((r - l) < -1)
		// {
		// 	// Балансировка
		// 	if(static_cast<std::shared_ptr<AVLTreeNode<T>>>(BT::left->left)->balance < 
		// 		static_cast<std::shared_ptr<AVLTreeNode<T>>>(BT::left->right)->balance)
		// 		BT::br_rotate();
		// 	else
		// 		BT::r_rotate();
		// }

		balance = std::max(r, l) + 1;

		// if(BT::parent != nullptr)
		// 	static_cast<std::shared_ptr<AVLTreeNode<T>>>(BT::parent)->setBalance();
	}

};



template<typename T>
class AVLTree : public BinTree<T>
{
	using BT = BinTree<T>;
public:

	AVLTree() : BinTree<T>() {}

	~AVLTree() {}

	void insert(const T &it) override
	{
		if(BT::rootNode == nullptr)
			BT::rootNode = std::make_shared<AVLTreeNode<T>>(it, nullptr);
		else
			BT::rootNode->insert(it);
	}
};


} // namespace otusalg

