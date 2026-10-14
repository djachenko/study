#pragma once

#include <functional>

using namespace std;

template<class Key, class Value, class Comp = less<Key>>
class SplayMap {
private:
	Comp comp;
	unsigned long p_size;

	typedef pair<Key, Value> Entry;

	struct Node {
		Node *left;
		Node *right;
		Node *parent;

		Entry entry;

		explicit Node(const Entry& init) 
			: left(nullptr), right(nullptr), parent(nullptr), entry(init) { }

		~Node() {
			if (left != nullptr) {
				delete left;
			}

			if (right != nullptr) {
				delete right;
			}

			if (parent != nullptr) {
				delete parent;
			}
		}
	};
	
	Node *root;

	void leftRotate(Node *x) {
		Node *y = x->right;
		
		if (nullptr != y) {
			x->right = y->left;

			if (nullptr != y->left) {
				y->left->parent = x;
			}

			y->parent = x->parent;
		}

		if (x == root) {
			root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}

		if (nullptr != y) {
			y->left = x;
		}

		x->parent = y;
	}

	void rightRotate(Node *x) {
		Node *y = x->left;

		if (nullptr != y) {
			x->left = y->right;
		
			if (nullptr != y->right) {
				y->right->parent = x;
			}
			
			y->parent = x->parent;
		}

		if (x == root) {
			root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}

		if (nullptr != y) {
			y->right = x;
		}

		x->parent = y;
	}

	void splay(Node *x) {
		while (x != root) 
		{
			if (x->parent == root)//Zig
			{
				if (x->parent->left == x) 
				{
					rightRotate(x->parent);
				}
				else 
				{
					leftRotate(x->parent);
				}
			}
			else if (x->parent->left == x && x->parent->parent->left == x->parent) {
				rightRotate(x->parent->parent);//Zig-Zig
				rightRotate(x->parent);
			}
			else if (x->parent->right == x && x->parent->parent->right == x->parent) {
				leftRotate(x->parent->parent);//Zig-Zig
				leftRotate(x->parent);
			}
			else if (x->parent->left == x && x->parent->parent->right == x->parent) {
				rightRotate(x->parent);//Zig-Zag
				leftRotate(x->parent);
			}
			else {
				leftRotate(x->parent);//Zig-Zag
				rightRotate(x->parent);
			}
		}
	}

	void replace(Node *u, Node *v) {
		if (u == root) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}

		if (nullptr != v) {
			v->parent = u->parent;
		}
	}

	static Node* subtree_minimum(Node *u) {
		if (nullptr != u) {
			while (nullptr != u->left) {
				u = u->left;
			}
		}

		return u;
	}

	static Node* subtree_maximum(Node *u) {
		if (nullptr == u) {
			while (nullptr != u->right) {
				u = u->right;
			}
		}

		return u;
	}
public:
	class Iterator : public iterator<bidirectional_iterator_tag, Key> {
	private:
		friend class SplayMap;
		Node *current;
	public:

		Iterator()
			:Iterator(subtree_minimum(root)) {}

		explicit Iterator(Node *const node)
			:current(node) {}

		Iterator(const Iterator &other)
			:current(other.current) {}

		Iterator &operator=(const Iterator &other) {
			current = other.current;

			return *this;
		}

		Entry &operator*() {
			return current->entry;
		}

		Entry *operator->() {
			return &(current->entry);
		}

		Iterator &operator++() {
			if (current != nullptr) {
				if (current->right != nullptr) {
					current = subtree_minimum(current->right);
				}
				else {
					while (current == current->parent->right) {
						current = current->parent;

						if (current == nullptr) {
							break;
						}
					}
				}
			}
			
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret = *this;

			if (current != nullptr) {
				if (current->left != nullptr) {
					current = subtree_maximum(current->left);
				}
				else if (nullptr != current->parent) {
					while (current == current->parent->left) {
						current = current->parent;

						if (current == nullptr) {
							break;
						}
					}
				}
			}

			return ret;
		}

		Iterator &operator--() {
			if (current != nullptr) {
				if (current->left != nullptr) {
					current = subtree_maximum(current->left);
				}
				else {
					while (current == current->parent->left) {
						current = current->parent;

						if (current == nullptr) {
							break;
						}
					}
				}
			}
			else {
				current = subtree_maximum(root);
			}

			return *this;
		}

		Iterator &operator--(int) {
			Iterator ret = *this;

			if (current != nullptr) {
				if (current->left != nullptr) {
					current = subtree_maximum(current->left);
				}
				else {
					while (current == current->parent->left) {
						current = current->parent;

						if (current == nullptr) {
							break;
						}
					}
				}
			}
			else {
				current = subtree_maximum(root);
			}

			return ret;
		}

		friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
			return lhs.current == rhs.current;
		}

		friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
			return !(lhs == rhs);
		}
	};

	SplayMap() 
		: p_size(0), root(nullptr) { }

	pair<Iterator, bool> insert(const Entry &entry) {
		auto findResult = find(entry.first);

		if (findResult != end()) {
			return std::make_pair(findResult, false);
		}

		Node *z = root;
		Node *p = nullptr;

		auto key = entry.first;

		while (nullptr != z) {
			p = z;

			if (comp(z->entry.first, key)) {
				z = z->right;
			}
			else {
				z = z->left;
			}
		}

		z = new Node(entry);

		z->parent = p;

		if (nullptr == p) {
			root = z;
		}
		else if (comp(p->entry.first, z->entry.first)) {
			p->right = z;
		}
		else {
			p->left = z;
		}

		splay(z);

		p_size++;

		return std::make_pair(Iterator(z), true);
	}
	
	Iterator insert(Iterator position, const Entry &entry) {
		auto searchResult = find(entry.first);

		if (searchResult != end()) {
			return searchResult;
		}

		auto previous = position++;

		Node *currentNode = position.current;
		Node *rightNode = currentNode->right;

		if (previous->first < entry.first && 
			position->first < entry.first && 
			nullptr == rightNode) {
			auto newNode = new Node(entry);

			newNode->parent = position.current;
			position.current->right = newNode;

			return Iterator(newNode);
		}
		
		auto insertResult = insert(entry);

		return insertResult.first;
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (; first != last; first++) {
			insert(*first);
		}
	}

	Iterator find(const Key &key) {
		Node *z = root;
		
		while (z) {
			auto entrykey = z->entry.first;

			if (comp(entrykey, key)) {
				z = z->right;
			}
			else if (comp(key, entrykey)) {
				z = z->left;
			}
			else {
				splay(z);

				return Iterator(z);
			}
		}

		return end();
	}

	Iterator begin() {
		return Iterator(subtree_minimum(root));
	}
	Iterator end() {
		return Iterator(nullptr);
	}

	void erase(const Key &key) {
		Node *z = find(key);

		if (nullptr == z) {
			return;
		}

		splay(z);

		if (nullptr == z->left) {
			replace(z, z->right);
		}
		else if (nullptr == z->right) {
			replace(z, z->left);
		}
		else {
			Node *y = subtree_minimum(z->right);

			if (y->parent != z) {
				replace(y, y->right);
			
				y->right = z->right;
				y->right->parent = y;
			}

			replace(z, y);
			
			y->left = z->left;
			y->left->parent = y;
		}

		delete z;
		p_size--;
	}

	const Key& minimum() {
		return subtree_minimum(root)->key;
	}

	const Key& maximum() {
		return subtree_maximum(root)->key;
	}

	bool empty() const {
		return 0 == size();
	}

	unsigned long size() const {
		return p_size;
	}
};