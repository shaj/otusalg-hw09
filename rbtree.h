
#pragma once

#include <iostream>
#include <sstream>
#include <memory>

// #include "bintree.h"

// #define RBTDEBUG
#define MAXDEPTH 30

namespace otusalg
{

template<typename T>
class RBTreeNode : public std::enable_shared_from_this<RBTreeNode<T>>
{
	int _cnt;
	T _data;

	std::shared_ptr<RBTreeNode<T>> left;
	std::shared_ptr<RBTreeNode<T>> right;
	std::weak_ptr<RBTreeNode<T>> parent;


	bool colorRed;

#ifdef RBTDEBUG
	static int sbcnt;
#endif

	void _updateParent(std::shared_ptr<RBTreeNode<T>> &newChild, std::shared_ptr<RBTreeNode<T>> &rootNode)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__;
if(newChild == nullptr) std::cout << "   nullptr";
else std::cout << "   " << newChild->_data;
std::cout << std::endl;
#endif
		if(auto spt = parent.lock())
		{ // Есть родитель
			if(spt->left.get() == this)
				spt->setLeft(newChild);
			else
				spt->setRight(newChild);
		}
		else
		{ // Единственный узел в дереве
#ifdef RBTDEBUG
std::cout << "   new ROOT" << std::endl;
#endif
			rootNode = newChild;
			newChild->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
		}
	}


public: 


	RBTreeNode(const T &it, std::shared_ptr<RBTreeNode<T>> p) : 
		parent(p), 
		_data(it), 
		colorRed(true),   // Узел всегда вставляем красным
		_cnt(1)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << "   data " << _data << std::endl;
#endif
	}

	~RBTreeNode() 
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << "   data " << _data << std::endl;
#endif
	}

	void setLeft(std::shared_ptr<RBTreeNode<T>> const &pn)
	{
#ifdef RBTDEBUG
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


	void setRight(std::shared_ptr<RBTreeNode<T>> const &pn)
	{
#ifdef RBTDEBUG
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



	std::shared_ptr<RBTreeNode<T>> find(const T &it)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
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


	void insert(const T &it, std::shared_ptr<RBTreeNode<T>> &rootNode) 
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		if(it < _data)
		{
			if(left == nullptr)
			{
				left = std::make_shared<RBTreeNode<T>>(it, this->shared_from_this());
				if(colorRed)
					left->setBalance(rootNode);
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
				right = std::make_shared<RBTreeNode<T>>(it, this->shared_from_this());
				if(colorRed)
					right->setBalance(rootNode);
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


	void remove(const T &it, std::shared_ptr<RBTreeNode<T>> &rootNode)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif

		if(_data == it)
		{
			if(_cnt > 1)
			{
				_cnt--;
			}
			else
			{
				if((left == nullptr) && (right == nullptr))
				{ // Узел является листом. Просто удаляем себя.
					if(auto p = parent.lock())
					{
#ifdef RBTDEBUG
std::cout << "   ~~~ remove 1" << std::endl;
#endif
						_updateParent(left, rootNode);
						p->setBalance(rootNode);
					}
					else
					{ // Последний узел
#ifdef RBTDEBUG
std::cout << "   ~~~ remove 2" << std::endl;
#endif
						rootNode = nullptr;
					}

				}
				else if(left != nullptr)
				{ // Поиск узла слева для замены
					auto a = this->shared_from_this();
					auto spt = left->right;
					if(spt == nullptr)
					{ // Подставляем левый узел вместо себя
#ifdef RBTDEBUG
std::cout << "   ~~~ remove 3" << std::endl;
#endif
						_updateParent(left, rootNode);
						left->setRight(right);
						left->setBalance(rootNode);
					}
					else
					{
#ifdef RBTDEBUG
std::cout << "   ~~~ remove 4" << std::endl;
#endif
						while(spt->right != nullptr)
							spt = spt->right;
						auto p = spt->parent.lock();
						auto L = spt->left;
						_updateParent(spt, rootNode);
						spt->setLeft(left);
						spt->setRight(right);
						p->setRight(L);
						p->setBalance(rootNode);
					}
				}
				else
				{ // Поиск узла справа для замены
					auto a = this->shared_from_this();
					auto spt = right->left;
					if(spt == nullptr)
					{ // Подставляем правый узел вместо себя
#ifdef RBTDEBUG
std::cout << "   ~~~ remove 5" << std::endl;
#endif
						_updateParent(right, rootNode);
						// right->setLeft(left);
						right->setBalance(rootNode);
					}
					else
					{
#ifdef RBTDEBUG
std::cout << "   ~~~ remove 6" << std::endl;
#endif
						while(spt->left != nullptr)
							spt = spt->left;
						auto p = spt->parent.lock();
						auto R = spt->right;
						_updateParent(spt, rootNode);
						spt->setRight(right);
						// spt->setLeft(left);
						p->setLeft(R);
						p->setBalance(rootNode);
					}
				}
			}
		}
		else
		{ // Поиск узла
			auto n = this->find(it);
			if(n != nullptr)
				n->remove(it, rootNode);
		}				
	}


	void setBalance(std::shared_ptr<RBTreeNode<T>> &rootNode)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << "   data " << _data << std::endl;

sbcnt++;
if(sbcnt > MAXDEPTH)
	throw;
	// return;
#endif

		auto a = this->shared_from_this();
		std::shared_ptr<RBTreeNode<T>> p;   // Родитель
		std::shared_ptr<RBTreeNode<T>> g;   // Дед
		std::shared_ptr<RBTreeNode<T>> u;   // Дядя
		std::shared_ptr<RBTreeNode<T>> gg;  // Родитель деда
		std::shared_ptr<RBTreeNode<T>> M;
		std::shared_ptr<RBTreeNode<T>> N;

		if(p = parent.lock())
		{ // Есть родитель
			if(g = p->parent.lock())
			{ // Есть дед
				if( // Где тут правый / левый - не понятно
			}
		}


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
#ifdef RBTDEBUG
std::cout << "setBalance 1 ((r - l) > 1) (br < bl)" << std::endl;
#endif
				c = b->left;
				M = c->left;
				N = c->right;
				if(auto spt = parent.lock())
				{
					if(spt->left.get() == this)
						spt->setLeft(c);
					else
						spt->setRight(c);
				}
				else
				{
					c->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
					rootNode = c;
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
				if(auto spt = c->parent.lock()) 
					spt->setBalance(rootNode);
			}
			else
			{ // Малое левое вращение
#ifdef RBTDEBUG
std::cout << "setBalance 2 ((r - l) > 1) (br >= bl)" << std::endl;
#endif
				c = b->left;
				if(auto spt = parent.lock())
				{
					if(spt->left.get() == this)
						spt->setLeft(b);
					else
						spt->setRight(b);
				}
				else
				{
					b->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
					rootNode = b;
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
				if(auto spt = b->parent.lock()) 
					spt->setBalance(rootNode);
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
			{ // Большое правое вращение
#ifdef RBTDEBUG
std::cout << "setBalance 3 ((r - l) < -1) (bl < br)" << std::endl;
#endif
				c = b->right;
				M = c->left;
				N = c->right;
				if(auto spt = parent.lock())
				{
					if(spt->left.get() == this)
						spt->setLeft(c);
					else
						spt->setRight(c);
				}
				else
				{
					c->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
					rootNode = c;
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
				if(auto spt = c->parent.lock()) 
					spt->setBalance(rootNode);
			}
			else
			{ // Малое правое вращение
#ifdef RBTDEBUG
std::cout << "setBalance 4 ((r - l) < -1) (bl >= br)" << std::endl;
#endif
				c = b->right;
				if(auto spt = parent.lock())
				{
					if(spt->left.get() == this)
						spt->setLeft(b);
					else
						spt->setRight(b);
				}
				else
				{
					b->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
					rootNode = b;
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
				if(auto spt = b->parent.lock()) 
					spt->setBalance(rootNode);
			}
		}
		else
		{ // Баласировать не нужно. Обновляем признаки балансировки.
			balance = std::max(r, l) + 1;
#ifdef RBTDEBUG
std::cout << "setBalance 5. data " << _data << " r=" << r << "; l=" << l << "; balance=" << balance << "\n";
#endif
			if(auto spt = parent.lock()) 
				spt->setBalance(rootNode);
		}

#ifdef RBTDEBUG
std::cout << "node data  " << _data;
std::cout << "  left->balance=";
if(left != nullptr) std::cout << left->balance;
else std::cout << "nullptr";
std::cout << "; right->balance=";
if(right != nullptr) std::cout << right->balance;
else std::cout << "nullptr";
std::cout << ";   parent=";
if(auto spt = parent.lock())
	std::cout << spt->_data;
else std::cout << "nullptr";
std::cout << std::endl;


sbcnt--;
#endif
	}


	std::string fullName()
	{
		std::stringstream name;
		name << _data;
		name << "\\ncnt " << _cnt << "\\n" << balance;
		return name.str();
	}

	void print(std::ostream &os)
	{

#ifdef RBTDEBUG
sbcnt++;
if(sbcnt > MAXDEPTH)
	throw;
	// return;
#endif


		os << "\"" << _data << "\" [label=\"" << fullName() << "\""
		if(colorRed) os << ",color=indianred1";
		os << "]\n";
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
#ifdef RBTDEBUG
sbcnt--;
#endif
	}

};



template<typename T>
class RBTree
{

	std::shared_ptr<RBTreeNode<T>> rootNode;

public:

	RBTree() 
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	}

	~RBTree() 
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	}


	void insert(const T &it)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__;
if(rootNode != nullptr) std::cout << "   root node data  " << rootNode->data();
std::cout << std::endl;
#endif

		if(rootNode == nullptr)
		{
			rootNode = std::make_shared<RBTreeNode<T>>(it, nullptr);
			rootNode->colorRed = false;   // Корневой узел просто перекрашиваем в черный
		}
		else
			rootNode->insert(it, rootNode);
	}


	void remove(const T &it)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif

		if(rootNode != nullptr) 
			rootNode->remove(it, rootNode);

	}


	std::shared_ptr<RBTreeNode<T>> find(const T &it)
	{
#ifdef RBTDEBUG
std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif

		return rootNode->find(it);
	}


	void print(std::ostream &os)
	{
		os << "digraph G {\nnode [style=filled,color=honeydew4]\n";
		rootNode->print(os);
		os << "}\n";
	}

};



#ifdef RBTDEBUG
template<typename T>
int RBTreeNode<T>::sbcnt = 0;
#endif


} // namespace otusalg

