
#pragma once

#include <iostream>
#include <sstream>
#include <memory>

// #include "bintree.h"

#define AVLDEBUG
#define MAXDEPTH 30

namespace otusalg
{

template<typename T>
class AVLTreeNode : public std::enable_shared_from_this<AVLTreeNode<T>>
{
	int _cnt;
	T _data;

	std::shared_ptr<AVLTreeNode<T>> left;
	std::shared_ptr<AVLTreeNode<T>> right;
	std::shared_ptr<AVLTreeNode<T>> parent;


	int balance;

#ifdef AVLDEBUG
	static int sbcnt;
#endif

public: 

	// friend AVLTreeNode;

	AVLTreeNode(const T &it, std::shared_ptr<AVLTreeNode<T>> p) : parent(p), _data(it), balance(1), _cnt(1)
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << "   data " << _data << std::endl;
#endif
	}

	~AVLTreeNode() 
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << "   data " << _data << std::endl;
#endif
	}

	void setLeft(std::shared_ptr<AVLTreeNode<T>> pn)
	{
#ifdef AVLDEBUG
std::cout << "~ " << _data << " -> ";
if(pn != nullptr) std::cout << pn->_data;
else std::cout << "nullptr";
std::cout << "   " << __PRETTY_FUNCTION__ << std::endl;
#endif
		if(pn != nullptr)
		{
			pn->parent = this->shared_from_this();
		}

		left = pn;
	}


	void setRight(std::shared_ptr<AVLTreeNode<T>> pn)
	{
#ifdef AVLDEBUG
std::cout << "~ " << _data << " -> ";
if(pn != nullptr) std::cout << pn->_data;
else std::cout << "nullptr";
std::cout << "   " << __PRETTY_FUNCTION__ << std::endl;
#endif
		if(pn != nullptr)
		{
			pn->parent = this->shared_from_this();
		}

		right = pn;
	}


	const T &data() const
	{
		return _data;
	}


	void insert(const T &it, AVLTreeNode<T> **rootNode) 
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		if(it < _data)
		{
			if(left == nullptr)
			{
				left = std::make_shared<AVLTreeNode<T>>(it, this->shared_from_this());
				setBalance(rootNode);
			}
			else
			{
				left->insert(it, rootNode);
			}
		}
		else if(it > _data)
		{
			if(right == nullptr)
			{
				right = std::make_shared<AVLTreeNode<T>>(it, this->shared_from_this());
				setBalance(rootNode);
			}
			else
			{
				right->insert(it, rootNode);
			}
		}
		else // it == _data
		{
			_cnt++;
		}
	}


	bool remove(const T &it)
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		return false;
	}


	void setBalance(AVLTreeNode<T> **rootNode)
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;

sbcnt++;
if(sbcnt > MAXDEPTH)
	// throw "OVERFLOW";
	return;
#endif

		int res = 0;
		int l = 0;
		int r = 0;

		auto a = this->shared_from_this();
		std::shared_ptr<AVLTreeNode<T>> p;
		std::shared_ptr<AVLTreeNode<T>> b;
		std::shared_ptr<AVLTreeNode<T>> c;
		std::shared_ptr<AVLTreeNode<T>> M;
		std::shared_ptr<AVLTreeNode<T>> N;

		if(left != nullptr)
		{
			l = left->balance;
		}
		if(right != nullptr)
		{
			r = right->balance;
		}

		if((r - l) > 1)
		{ // Правая ветка тяжелее левой. Надо поворачивать налево.
			b = right;
			int br = 0;
			int bl = 0;
			if(b->right != nullptr) br = b->right->balance;
			if(b->left != nullptr) bl = b->left->balance;

			if(br < bl)
			{ // Большое левое вращение
#ifdef AVLDEBUG
std::cout << "setBalance 1 ((r - l) > 1) (br < bl)" << std::endl;
#endif
				c = b->left;
				M = c->left;
				N = c->right;
				if(parent != nullptr)
				{
					if(parent->left.get() == this)
						parent->setLeft(c);
					else
						parent->setRight(c);
				}
				else
				{
					c->parent = nullptr;
					*rootNode = c.get();
				}
				c->setLeft(this->shared_from_this());
				c->setRight(b);
				setRight(M);
				b->setLeft(N);

				if(right != nullptr) br = right->balance;
				else br = 0;
				if(left != nullptr) bl = left->balance;
				else bl = 0;
				balance = std::max(br, bl) + 1;
				if(b->left != nullptr) bl = b->left->balance;
				else bl = 0;
				if(b->right != nullptr) br = b->right->balance;
				else br = 0;
				b->balance = std::max(bl, br) + 1;
				c->balance = std::max(balance, b->balance) + 1;
				if(c->parent != nullptr) c->parent->setBalance(rootNode);
			}
			else
			{ // Малое левое вращение
#ifdef AVLDEBUG
std::cout << "setBalance 2 ((r - l) > 1) (br >= bl)" << std::endl;
#endif
				c = b->left;
				if(parent != nullptr)
				{
					if(parent->left.get() == this)
						parent->setLeft(b);
					else
						parent->setRight(b);
				}
				else
				{
					b->parent = nullptr;
					*rootNode = b.get();
				}
				setRight(c);
				b->setLeft(this->shared_from_this());

				if(right != nullptr) br = right->balance;
				else br = 0;
				if(left != nullptr) bl = left->balance;
				else bl = 0;
				balance = std::max(bl, br) + 1;
				if(b->right != nullptr) br = b->right->balance;
				else br = 0;
				b->balance = std::max(balance, br) + 1;
				if(b->parent != nullptr) b->parent->setBalance(rootNode);
			}
		}
		else if((r - l) < -1)
		{ // Левая ветка тяжелее правой. Надо поворачивать направо.
			b = left;
			int br = 0;
			int bl = 0;
			if(b->right != nullptr) br = b->right->balance;
			if(b->left != nullptr) bl = b->left->balance;

			if(bl < br)
			{ // Большое левое вращение
#ifdef AVLDEBUG
std::cout << "setBalance 3 ((r - l) < -1) (bl < br)" << std::endl;
#endif
				c = b->right;
				M = c->left;
				N = c->right;
				if(parent != nullptr)
				{
					if(parent->left.get() == this)
						parent->setLeft(c);
					else
						parent->setRight(c);
				}
				else
				{
					c->parent = nullptr;
					*rootNode = c.get();
				}
				c->setLeft(b);
				c->setRight(this->shared_from_this());
				setLeft(N);
				b->setRight(M);

				if(right != nullptr) br = right->balance;
				else br = 0;
				if(left != nullptr) bl = left->balance;
				else bl = 0;
				balance = std::max(br, bl) + 1;
				if(b->left != nullptr) bl = b->left->balance;
				else bl = 0;
				if(b->right != nullptr) br = b->right->balance;
				else br = 0;
				b->balance = std::max(bl, br) + 1;
				c->balance = std::max(balance, b->balance) + 1;
				if(c->parent != nullptr) c->parent->setBalance(rootNode);
			}
			else
			{ // Малое левое вращение
#ifdef AVLDEBUG
std::cout << "setBalance 4 ((r - l) < -1) (bl >= br)" << std::endl;
#endif
				c = b->right;
				if(parent != nullptr)
				{
					if(parent->left.get() == this)
						parent->setLeft(b);
					else
						parent->setRight(b);
				}
				else
				{
					b->parent = nullptr;
					*rootNode = b.get();
				}
				setLeft(c);
				b->setRight(this->shared_from_this());

				if(right != nullptr) br = right->balance;
				else br = 0;
				if(left != nullptr) bl = left->balance;
				else bl = 0;
				balance = std::max(bl, br) + 1;
				if(b->right != nullptr) br = b->right->balance;
				else br = 0;
				b->balance = std::max(balance, br) + 1;
				if(b->parent != nullptr) b->parent->setBalance(rootNode);
			}
		}
		else
		{ // Баласировать не нужно. Обновляем признаки балансировки.
			balance = std::max(r, l) + 1;
#ifdef AVLDEBUG
std::cout << "setBalance 5. data " << _data << " r=" << r << "; l=" << l << "; balance=" << balance << "\n";
#endif
			if(parent != nullptr)
				parent->setBalance(rootNode);
		}

#ifdef AVLDEBUG
std::cout << "node data  " << _data;
std::cout << "  left->balance=";
if(left != nullptr) std::cout << left->balance;
else std::cout << "nullptr";
std::cout << "; right->balance=";
if(right != nullptr) std::cout << right->balance;
else std::cout << "nullptr";
std::cout << ";   parent=";
if(parent != nullptr) std::cout << parent->_data;
else std::cout << "nullptr";
std::cout << std::endl;


sbcnt--;
#endif
	}


	std::string fullName()
	{
		std::stringstream name;
		name << _data << "\\nparent  ";
		if(parent != nullptr) name << parent->_data;
		name << "\\n" << balance;
		return name.str();
	}

	void print(std::ostream &os)
	{

#ifdef AVLDEBUG
sbcnt++;
if(sbcnt > MAXDEPTH)
	// throw "OVERFLOW";
	return;
#endif


		os << "\"" << _data << "\" [label=\"" << fullName() << "\"]\n";
		if(left != nullptr)
		{
			os << "\"" << _data << "\" -> \"" << left->_data << "\" [label=\"L\"]\n";
			left->print(os);
		}
		if(right != nullptr)
		{
			os << "\"" << _data << "\" -> \"" << right->_data << "\" [label=\"R\"]\n";
			right->print(os);
		}
#ifdef AVLDEBUG
sbcnt--;
#endif
	}

};



template<typename T>
class AVLTree
{

	std::shared_ptr<AVLTreeNode<T>> rootNode;

public:

	AVLTree() 
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	}

	~AVLTree() 
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	}


	void insert(const T &it)
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__;
if(rootNode != nullptr) std::cout << "   root node data  " << rootNode->data();
std::cout << std::endl;
#endif
		if(rootNode == nullptr)
			rootNode = std::make_shared<AVLTreeNode<T>>(it, nullptr);
		else
		{
			AVLTreeNode<T> *newRoot = rootNode.get();
			rootNode->insert(it, &newRoot);
			if(newRoot != rootNode.get())
			{
#ifdef AVLDEBUG
std::cout << "!!! change root node !!! was " << rootNode.get() << " new " << newRoot;
std::cout << "   " << rootNode->data() << " -> " << newRoot->data() << std::endl;
#endif
				rootNode.reset(newRoot);
			}
		}
	}


	void remove(const T &it)
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		if(rootNode != nullptr)
			if(rootNode->remove(it))
			{
				rootNode.reset();
			}
	}


	std::shared_ptr<AVLTreeNode<T>> find(const T &it)
	{
#ifdef AVLDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		return rootNode->find(it);
	}


	void print(std::ostream &os)
	{
		os << "digraph G {\n";
		rootNode->print(os);
		os << "}\n";
	}

};



#ifdef AVLDEBUG
template<typename T>
int AVLTreeNode<T>::sbcnt = 0;
#endif


} // namespace otusalg

