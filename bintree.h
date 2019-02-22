
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


	std::shared_ptr<BinTreeNode<T>> find(const T &it)
	{
		if(_data == it)
			return this->shared_from_this();
		if(it < _data)
		{
			if(left != nullptr)
				return left->find(it);
			else
				return nullptr;
		}
		else
		{
			if(right != nullptr)
				return right->find(it);
			else
				return nullptr;
		}
	}


	void bl_rotate()
	{
		auto b = right;
		auto c = right->left;
		auto M = c->left;
		auto N = c->right;

		if(parent->left == this)
		{
			parent->left = c;
		}
		else
		{
			parent->right = c;
		}

		c->left = this->shared_from_this();
		c->right = b;

		right = M;
		b->left = N;
	}


	void br_rotate()
	{
		auto b = left;
		auto c = left->right;
		auto M = c->left;
		auto N = c->right;

		if(parent->left == this)
		{
			parent->left = c;
		}
		else
		{
			parent->right = c;
		}

		c->left = b;
		c->right = this->shared_from_this();

		left = N;
		b->right = M;
	}

	
	void l_rotate()
	{
		auto b = right;
		auto C = b->left;

		if(parent->left == this)
			parent->left = b;
		else
			parent->right = b;

		b->left = this->shared_from_this();
		right = C;
	}


	void r_rotate()
	{
		auto b = left;
		auto C = b->right;

		if(parent->left == this)
			parent->left = b;
		else
			parent->right = b;

		b->right = this->shared_from_this();
		left = C;
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

	std::shared_ptr<BinTreeNode<T>> find(const T &it)
	{
		
		return rootNode->find(it);
	}


	void print(std::ostream &os)
	{
		os << "BinTree:\n";
		rootNode->print(os);
	}

};


} // namespace otusalg

