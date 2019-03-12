
#pragma once

#include <iostream>
#include <memory>


namespace otusalg
{


template<typename T>
class BinTreeNode : public std::enable_shared_from_this<BinTreeNode<T>>
{
protected:

	T _data;

public:

	// friend BinTreeNode;

	std::shared_ptr<BinTreeNode<T>> left;
	std::shared_ptr<BinTreeNode<T>> right;
	std::shared_ptr<BinTreeNode<T>> parent;



	BinTreeNode(const T &it, std::shared_ptr<BinTreeNode> p) : parent(p), _data(it)
	{
	}


	~BinTreeNode() {}


	void setLeft(std::shared_ptr<BinTreeNode<T>> pn)
	{
		if(pn != nullptr)
		{
			pn->parent = this->shared_from_this();
		}

		left = pn;
	}


	void setRight(std::shared_ptr<BinTreeNode<T>> pn)
	{
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
		std::shared_ptr<BinTreeNode<T>> p;
		std::shared_ptr<BinTreeNode<T>> b;
		std::shared_ptr<BinTreeNode<T>> c;
		std::shared_ptr<BinTreeNode<T>> M;
		std::shared_ptr<BinTreeNode<T>> N;

		p = this->parent;
		b = right;
		if(b != nullptr)
			c = b->left;
		else
			c = nullptr;
	
		if(c != nullptr)
		{
			M = c->left;
			N = c->right;
		}
		else
		{
			M = nullptr;
			N = nullptr;
		}

		if(p != nullptr)
		{
			if(p->left.get() == this)
				p->setLeft(c);
			else
				p->setRight(c);
		}

		if(c != nullptr)
		{
			c->setLeft(this->shared_from_this());
			c->setRight(b);
		}

		this->setRight(M);
		if(b != nullptr)
		{
			b->setLeft(N);
		}
	}


	void br_rotate()
	{
		std::shared_ptr<BinTreeNode<T>> p;
		std::shared_ptr<BinTreeNode<T>> b;
		std::shared_ptr<BinTreeNode<T>> c;
		std::shared_ptr<BinTreeNode<T>> M;
		std::shared_ptr<BinTreeNode<T>> N;

		p = this->parent;
		b = left;
		if(b != nullptr)
			c = b->right;
		else
			c = nullptr;

		if(c != nullptr)
		{
			M = c->left;
			N = c->right;
		}
		else
		{
			M = nullptr;
			N = nullptr;
		}

		if(p != nullptr)
		{
			if(p->left.get() == this)
				p->setLeft(c);
			else
				p->setRight(c);
		}

		if(c != nullptr)
		{
			c->setLeft(b);
			c->setRight(this->shared_from_this());
		}

		left = N;
		if(b != nullptr)
			b->setRight(M);
	}

	
	void l_rotate()
	{
		std::shared_ptr<BinTreeNode<T>> p;
		std::shared_ptr<BinTreeNode<T>> b;
		std::shared_ptr<BinTreeNode<T>> C;

		p = this->parent;
		b = right;
		if(b != nullptr)
			C = b->left;

		if(p != nullptr)
		{
			if(p->left.get() == this)
				p->setLeft(b);
			else
				p->setRight(b);
		}

		if(b != nullptr)
			b->setLeft(this->shared_from_this());
		right = C;
	}


	void r_rotate()
	{
		std::shared_ptr<BinTreeNode<T>> p;
		std::shared_ptr<BinTreeNode<T>> b;
		std::shared_ptr<BinTreeNode<T>> C;

		p = this->parent;
		b = left;
		if(b != nullptr)
			C = b->right;

		if(p != nullptr)
		{
			if(p->left.get() == this)
				p->setLeft(b);
			else
				p->setRight(b);
		}

		if(p != nullptr)
		{
			if(p->left.get() == this)
				p->setLeft(b);
			else
				p->setRight(b);
		}

		if(b != nullptr)
			b->setRight(this->shared_from_this());
		left = C;
	}


	void print(std::ostream &os)
	{
		os << "\"" << _data << "\"\n";
		if(left != nullptr)
		{
			os << "\"" << _data << "\" -> \"" << left->data() << "\" [label=\"L\"]\n";
			left->print(os);
		}
		if(right != nullptr)
		{
			os << "\"" << _data << "\" -> \"" << right->data() << "\" [label=\"R\"]\n";
			right->print(os);
		}
	}

};


template<typename T>
class BinTree
{

protected:

	std::shared_ptr<BinTreeNode<T>> rootNode;

public:

	BinTree() {}
	~BinTree() {}

	virtual void insert(const T &it)
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
		os << "digraph G {\n";
		rootNode->print(os);
		os << "}\n";
	}

};


} // namespace otusalg

