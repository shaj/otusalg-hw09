
#pragma once

#include <iostream>
#include <sstream>
#include <memory>

// #include "bintree.h"

#define RBTDEBUG
#define MAXDEPTH 30

namespace otusalg
{

template<typename T>
class RBTreeNode : public std::enable_shared_from_this<RBTreeNode<T>>
{
	bool colorRed;
	int _cnt;
	T _data;

	std::shared_ptr<RBTreeNode<T>> left;
	std::shared_ptr<RBTreeNode<T>> right;
	std::weak_ptr<RBTreeNode<T>> parent;

#ifdef RBTDEBUG
	static int sbcnt;
#endif

public: 


	RBTreeNode(const T &it, std::shared_ptr<RBTreeNode<T>> p, bool red = true) : 
		parent(p), 
		_data(it), 
		colorRed(red),   // Узел всегда вставляем красным
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

sbcnt++;
if(sbcnt > MAXDEPTH)
	throw;
	// return;
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
#ifdef RBTDEBUG
sbcnt--;
#endif
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
				auto M = this->shared_from_this();   // Удаляемый узел
				if((left != nullptr) && (right != nullptr))
				{
					M = left->right;
					if(M != nullptr)
					{
						while(M->right != nullptr)
							M = M->right;
						_data = M->_data;
					}
					else
					{
						M = right->left;
						if(M != nullptr)
						{
							while(M->left != nullptr)
								M = m->left;
							_data = M->_data;
						}
						else
						{
							M = this->shared_from_this();
						}
					}
				}

				// Здесь найден удаляемый узел.
				// Начинаем удаление

				if(M->colorRed)
				{
					if((M->left == nullptr) && (M->right == nullptr))
					{
						if(auto spt = M->parent.lock())
						{
							if(spt->left == M)
								spt->left = nullptr;
							else
								spt->right = nullptr;
						}
						else
						{
							rootNode = nullptr;
						}
					}
					else if(M->left != nullptr)
					{
						auto C = M->left;
						_updateParent(C, rootNode);
					}
					else
					{
						auto C = M->right;
						_updateParent(C, rootNode);
					}
				}
				else
				{ // M черный
					std::shared_ptr<RBTreeNode> C;
					if(M->left != nullptr)
						C = M->left;
					else
						C = M->right;
					if(C->colorRed)
					{
						_updateParent(C, rootNode);
						c->colorRed = false;
					}
					else
					{ // Сложный случай: М и С черные.

					}
				}




		}
		else
		{ // Поиск узла
			throw;
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
		std::shared_ptr<RBTreeNode<T>> N;

		if(p = parent.lock())
		{ // Есть родитель
			if(g = p->parent.lock())
			{ // Есть дед
				if(g->left == p) 
					u = g->right;
				else
					u = g->left;
				if((u != nullptr) && (p->colorRed && u->colorRed))
				{ // Случай 3 (https://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D1%91%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE#%D0%92%D1%81%D1%82%D0%B0%D0%B2%D0%BA%D0%B0)
#ifdef RBTDEBUG
std::cout << "Случай 3" << std::endl;
#endif
					g->colorRed = true;
					p->colorRed = false;
					u->colorRed = false;
#ifdef RBTDEBUG
std::cout << p->_data << " color ";
if(p->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
std::cout << g->_data << " color ";
if(g->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
std::cout << u->_data << " color ";
if(u->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
#endif
					g->setBalance(rootNode);
				}
				else if(p->colorRed)
				{ 
					if((p->right == a) && (g->left == p))
					{ // Случай 4
#ifdef RBTDEBUG
std::cout << "Случай 4 левый" << std::endl;
#endif
						N = a->left;
						g->setLeft(a);
						a->setLeft(p);
						p->setRight(N);

						a = p;
						p = this->shared_from_this();
					}
					else if((p->left.get() == this) && (g->right == p))
					{ // Случай 4
#ifdef RBTDEBUG
std::cout << "Случай 4 правый" << std::endl;
#endif
						N = a->right;
						g->setRight(a);
						a->setRight(p);
						p->setLeft(N);

						a = p;
						p = this->shared_from_this();
					}

					if(p->colorRed && ((u == nullptr) || !u->colorRed))
					{ // Случай 5
						if(p->left == a)
						{
#ifdef RBTDEBUG
std::cout << "Случай 5 левый" << std::endl;
#endif
							N = p->right;
							if(auto gg = g->parent.lock())
							{
								if(gg->left == g)
									gg->setLeft(p);
								else
									gg->setRight(p);
							}
							else
							{
								rootNode = p;
								p->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
							}
							p->setRight(g);
							g->setLeft(N);							
							p->colorRed = false;
							g->colorRed = true;							
#ifdef RBTDEBUG
std::cout << p->_data << " color ";
if(p->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
std::cout << g->_data << " color ";
if(g->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
#endif
						}
						else
						{
#ifdef RBTDEBUG
std::cout << "Случай 5 правый" << std::endl;
#endif
							N = p->left;
							if(auto gg = g->parent.lock())
							{
								if(gg->left == g)
									gg->setLeft(p);
								else
									gg->setRight(p);
							}
							else
							{
								rootNode = p;
								p->parent = std::weak_ptr<RBTreeNode<T>>(); // Pointing to nothing
							}
							p->setLeft(g);
							g->setRight(N);
							p->colorRed = false;
							g->colorRed = true;							
#ifdef RBTDEBUG
std::cout << p->_data << " color ";
if(p->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
std::cout << g->_data << " color ";
if(g->colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
#endif
						}
					}
				}
			} 
		}
		else
		{ // Случай 1
			colorRed = false;
#ifdef RBTDEBUG
std::cout << _data << " color ";
if(colorRed) std::cout << "RED";
else std::cout << "BLACK";
std::cout << "\n";
#endif
		}

#ifdef RBTDEBUG
std::cout << "node data  " << _data;
std::cout << "   color ";
if(colorRed) std::cout << "RED";
else std::cout << "BLACK";
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
		name << "\\ncnt " << _cnt;
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


		os << "\"" << _data << "\" [label=\"" << fullName() << "\"";
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
			rootNode = std::make_shared<RBTreeNode<T>>(it, nullptr, false);
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
		{
			auto n = rootNode->find(it);
			if(n != nullptr)
				n->remove(it, rootNode);
		}

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

