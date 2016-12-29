#ifndef MAP_HPP
#define MAP_HPP
//++++++++++++++++++++++++++++++++++ AVL TREE ++++++++++++++++++++++++++++++++++++++++//

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>

//Definition of the value that will
//be held in the in the Map
template<class Key_T, class Mapped_T>
using ValueType = std::pair <const Key_T, Mapped_T>;

//***** DECLARATION OF NODE *******//
template <class Key_T, class Mapped_T>
class Node
{
    public:
        //Parent of the current node
        Node * parent;

        //ValueType
        ValueType<Key_T, Mapped_T> pair;

        //Key and the Data for dictionary
        Mapped_T & data;
        const Key_T & key;

        //Left and right children
        Node * left;
        Node * right;

        //Pointer to be used for iteration
        Node * listPrevious;
        Node * listNext;

        unsigned char height;
        short int balanceFactor;

        //empty constructor
        Node()
            :height(0), left(0), right(0), parent(0), key(pair.first), data(pair.second)
        {
            //Empty
        }

        //constructor with key and value template type
        Node(Key_T key, Mapped_T item)
            : parent(0), pair(key, item), data(pair.second), key(pair.first),
            left(0), right(0), listPrevious(0), listNext(0), height(0), balanceFactor(0)
        {

        }

        //constructor with pair data type
        Node(ValueType <Key_T, Mapped_T> x)
            :parent(0), pair(x), data(pair.second), key(pair.first),
            left(0), right(0), listPrevious(0), listNext(0), height(0), balanceFactor(0)
        {

        }
};

//Pointer to the node
template<class Key_T, class Mapped_T>
using NodePtr = Node <Key_T, Mapped_T> *;

//****** END OF NODE DECLARATION ******//

//forward declaration of the Tree
template<class Key_T, class Mapped_T>
class Tree;

//Tree pointer
template<class Key_T, class Mapped_T>
using TreePtr = Tree<Key_T, Mapped_T> *;

//****** DECLARATION OF THE TREE BEGINS HERE *****//
template<class Key_T, class Mapped_T>
class Tree
{
    public:

        //forward declaration for the iterators
        struct Iterator;
        struct ConstIterator;
        struct ReverseIterator;

        //*** Beginning of Iterator definition ***//
        struct Iterator
        {
            NodePtr<Key_T, Mapped_T> inode;
            TreePtr<Key_T, Mapped_T> ptr;    //This is newly added.

            //no argument constructor
            Iterator()
            {
                inode = NULL;
            }

            //Iterator: that takes a node pointer and tree pointer
            Iterator(NodePtr<Key_T, Mapped_T> node, const TreePtr<Key_T, Mapped_T> tree)
                : ptr(tree)
            {
                inode = NULL;
                if (node != NULL)
                {
                    inode = node;
                }
            }

            //copy constructor for the iterator
            Iterator(const Iterator & copy)
            {
                inode = copy.inode;
                ptr = copy.ptr;
            }

            //overloaded operator equality
            bool operator==(const Iterator & itTwo)
            {
                return inode == itTwo.inode;
            }
            bool operator==(const ConstIterator & itTwo)
            {
                return inode == itTwo.inode;
            }

            //overloaded operator inequality
            bool operator!=(const Iterator & itTwo)
            {
                return !(inode == itTwo.inode);
            }
            bool operator!=(const ConstIterator & itTwo)
            {
                return !(inode == itTwo.inode);
            }

            //overloaded operator increment
            Iterator& operator++()
            {
                increment();
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator temp(*this);
                increment();
                return temp;
            }

            //overloaded operator decrement
            Iterator& operator--()
            {
                decrement();
                return *this;
            }
            Iterator operator--(int)
            {
                Iterator temp(*this);
                decrement();
                return temp;
            }

            //overloaded operator: pointer de-referencing
            ValueType<const Key_T, Mapped_T> & operator *() const
            {
                return inode->pair;
            }
            ValueType<const Key_T, Mapped_T> * operator->() const
            {
                return &(inode->pair);
            }

            void decrement();
            void increment();
        };

        //*** Beginning of CONST Iterator ***//
        struct ConstIterator
        {
            NodePtr <Key_T, Mapped_T> inode;
            const Tree<Key_T, Mapped_T> *ptr;

            //empty constructor
            ConstIterator()
            {
                inode = NULL;
            }

            //constructor that takes tree pointer and a node pointer
            ConstIterator(const NodePtr<Key_T, Mapped_T> & node, const Tree<Key_T, Mapped_T> *tree)
                : ptr(tree)
            {
                inode = NULL;
                if (node != NULL)
                    inode = node;
            }

            ConstIterator(const ConstIterator & iter)
            {
                inode = iter.inode;
                ptr = iter.ptr;
            }

            //operator overloading equality
            bool operator==(const Iterator & itTwo)
            {
                return inode == itTwo.inode;
            }
            bool operator==(const ConstIterator & itTwo)
            {
                return inode == itTwo.inode;
            }

            //operator overloading inequality
            bool operator!=(const Iterator & itTwo)
            {
                return !(inode == itTwo.inode);
            }

            bool operator!=(const ConstIterator & itTwo)
            {
                return !(inode == itTwo.inode);
            }

            //operator overloading increment
            ConstIterator& operator++()
            {
                increment();
                return *this;
            }
            ConstIterator operator++(int)
            {
                ConstIterator temp(*this);
                increment();
                return temp;
            }

            //operator overloading decrement
            ConstIterator& operator--()
            {
                decrement();
                return *this;
            }
            ConstIterator operator--(int)
            {
                ConstIterator temp(*this);
                decrement();
                return temp;
            }
            const ValueType<const Key_T, Mapped_T> & operator *() const
            {
                return inode->pair;
            }
            const ValueType<const Key_T, Mapped_T> * operator-> () const
            {
                return &(inode->pair);
            }

            void increment();
            void decrement();
        };
        //*** END OF CONST ITERATOR ***//

        struct ReverseIterator
        {
            NodePtr <Key_T, Mapped_T> inode;
            TreePtr<Key_T, Mapped_T> ptr;

            //empty constructor
            ReverseIterator()
            {
                inode = NULL;
            }

            //constructor that takes a node and tree
            ReverseIterator(NodePtr<Key_T, Mapped_T> node, const TreePtr<Key_T, Mapped_T> tree)
                : ptr(tree)
            {
                inode = NULL;
                if (node != NULL)
                {
                    inode = node;
                }
            }
            //copy constructor
            ReverseIterator(const ReverseIterator & copy)
            {
                inode = copy.inode;
                ptr = copy.ptr;
            }

            //overloaded operator equality
            bool operator==(const ReverseIterator & itTwo)
            {
                return inode == itTwo.inode;
            }

            //overloaded operator inequality
            bool operator!=(const ReverseIterator & itTwo)
            {
                return !(inode == itTwo.inode);
            }

            //overloaded operator increment
            ReverseIterator& operator++()
            {
                increment();
                return *this;
            }
            ReverseIterator operator++(int)
            {
                ReverseIterator temp(*this);
                increment();
                return *this;
            }

            //overloaded operator decrement
            ReverseIterator& operator--()
            {
                decrement();
                return *this;
            }
            ReverseIterator operator--(int)
            {
                ReverseIterator temp(*this);
                decrement();
                return temp;
            }

            //overloaded pointer de-referencing
            ValueType<const Key_T, Mapped_T> & operator *() const
            {
                return inode->pair;
            }
            ValueType<const Key_T, Mapped_T> * operator->() const
            {
                return &(inode->pair);
            }

            void increment();
            void decrement();
        };

        //declarations for all the iterators
        Iterator begin();
        Iterator end();
        const ConstIterator begin() const;
        const ConstIterator end() const;
        ReverseIterator rbegin();
        ReverseIterator rend();

        //forward declarations for the at functions
        Mapped_T & at(const Key_T & key);
        const Mapped_T & at(const Key_T &) const;

        //forward declaration for the tree constructor
        Tree<Key_T, Mapped_T>();

        //copy constructor
        Tree<Key_T, Mapped_T>(const Tree<Key_T, Mapped_T> & otherTree);

        bool empty() const
        {
            return treeRoot == NULL;
        }

        size_t sizeR() const
        {
            return size;
        }

        //search function declaration along with helper functions
        bool search(const Key_T & key) const;
        NodePtr<Key_T, Mapped_T> helper_search(const Key_T & key)
        {
            return hSearch(key);
        }
        NodePtr<Key_T, Mapped_T> helper_search(const Key_T & key) const
        {
            return hSearch(key);
        }

        NodePtr <Key_T, Mapped_T> insert(const Key_T &, const Mapped_T &);
        void remove(const Key_T & key)
        {
            remove_node(key);
        }

        void display_min_max()
        {
            std::cout << min_val(treeRoot)->data << std::endl;
            std::cout << max_val(treeRoot)->data << std::endl;
        }

        void clear()
        {
            helper_dest();
            treeRoot = NULL;
            size = 0;
        }

        Tree<Key_T, Mapped_T> & operator=(const Tree &);
        ~Tree<Key_T, Mapped_T>();

    private:
        //root of the tree
        NodePtr<Key_T, Mapped_T> treeRoot;
        size_t size;

        //*** HELPER FUNCTIONS *****
        //update height after insert and remove
        void adjust_height_insert(NodePtr<Key_T, Mapped_T> &);
        void adjust_height_remove(NodePtr<Key_T, Mapped_T> &);

        //helper function copy
        void helper_copy_const(const Tree<Key_T, Mapped_T> &);

        //helper function when the tree is destroyed
        void helper_dest();

        //post order traversal
        void post_order_traversal(NodePtr<Key_T, Mapped_T>);

        //balance factor
        short int balance_factor(const NodePtr<Key_T, Mapped_T> &) const;

        short int height(const NodePtr<Key_T, Mapped_T> &) const;

        void get_balance_factor(NodePtr<Key_T, Mapped_T> &);

        //what is the height of the current node
        void get_height(const NodePtr<Key_T, Mapped_T> &) const;

        //left rotation
        void left_rotation(NodePtr<Key_T, Mapped_T>);

        //right rotation
        void right_rotation(NodePtr<Key_T, Mapped_T>);

        //left-right rotation
        void left_right_rotation(NodePtr<Key_T, Mapped_T> &);

        //right-left rotation
        void right_left_rotation(NodePtr<Key_T, Mapped_T> &);

        void preform_rotation(NodePtr<Key_T, Mapped_T> &);
        void preform_remove(NodePtr<Key_T, Mapped_T> &);

        NodePtr<Key_T, Mapped_T> min_val(const NodePtr<Key_T, Mapped_T> &) const;
        NodePtr<Key_T, Mapped_T> max_val(const NodePtr<Key_T, Mapped_T> &) const;


        NodePtr<Key_T, Mapped_T> get_successor(NodePtr<Key_T, Mapped_T>);
        NodePtr<Key_T, Mapped_T> get_predecessor(NodePtr<Key_T, Mapped_T>);

        //helper search functions
        NodePtr<Key_T, Mapped_T> hSearch(const Key_T &) const;
        NodePtr<Key_T, Mapped_T> hSearch(const Key_T &);

        void remove_node(const Key_T &);
};

//**** END OF TREE DECLARATIONS *****//

//**** IMPLEMENT OF FUNCTIONS STARTS HERE ****//
//implementation for the default constructor
template<class Key_T, class Mapped_T>
Tree<Key_T, Mapped_T>::Tree()
    : treeRoot(0), size(0)
{
    //empty constructor
}

//COPY CONSTRUCTOR
template<class Key_T, class Mapped_T>
Tree<Key_T, Mapped_T>::Tree(const Tree<Key_T, Mapped_T> & original)
{
	helper_copy_const(original);
}

//DESTRUCTOR
template<class Key_T, class Mapped_T>
Tree<Key_T, Mapped_T>::~Tree()
{
	helper_dest();
}

//OPERATOR OVERLOADED: equality
template<class Key_T, class Mapped_T>
Tree<Key_T, Mapped_T> & Tree<Key_T, Mapped_T>::operator = (const Tree<Key_T, Mapped_T> & original)
{
    //helper destructor
	helper_dest();
	helper_copy_const(original);
	return *this;
}

//HELPER FUNCTION: Copy Constructor
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::helper_copy_const(const Tree<Key_T, Mapped_T> & original)
{
	Tree<Key_T, Mapped_T>::ConstIterator x = original.begin();
	for (; x != original.end(); ++x)
    {
        insert(x->first, x->second);
    }
}

//HELPER FUNCTION: Destructor
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::helper_dest()
{
	post_order_traversal(treeRoot);
}

//HELPER FUNCTION: Post Order Traversal
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::post_order_traversal(NodePtr<Key_T, Mapped_T> root)
{
	if (root == NULL)
    {
		return;
	}
	else
	{
		post_order_traversal(root->left);
		post_order_traversal(root->right);
		delete root;
	}
}

//*** SEARCH FUNCTION ****//
template<class Key_T, class Mapped_T>
bool Tree<Key_T, Mapped_T>::search(const Key_T & key) const
{
	NodePtr<Key_T, Mapped_T> nodePtr = treeRoot;
	bool found = false;
	while (!found && nodePtr != 0)
    {
		if (key < nodePtr->key)
		{
		    nodePtr = nodePtr->left;
		}
		else if (nodePtr->key < key)
        {
            nodePtr = nodePtr->right;
        }
		else
        {
            found = true;
        }
	}
	return found;
}

//*** AT FUNCTION ***//
template<class Key_T, class Mapped_T>
Mapped_T & Tree<Key_T, Mapped_T>::at(const Key_T & key)
{
	NodePtr<Key_T, Mapped_T> temp = hSearch(key);
	if (temp == NULL)
    {
        throw std::out_of_range("not in range");
    }
	return temp->data;
}
template<class Key_T, class Mapped_T>
const Mapped_T & Tree<Key_T, Mapped_T>::at(const Key_T & key) const
{
	NodePtr<Key_T, Mapped_T> temp = hSearch(key);
	if (temp == NULL)
    {
        throw std::out_of_range("not in range");
    }
	return temp->data;
}

//*** INSERT FUNCTION ***//
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::insert(const Key_T & key, const Mapped_T & item)
{
	NodePtr<Key_T, Mapped_T> locationPtr = treeRoot, parent = 0;
	bool found = false;

	while (!found && locationPtr != 0)
    {
		parent = locationPtr;
		if (key < locationPtr->key)
		{
		    locationPtr = locationPtr->left;
		}
		else if (locationPtr->key < key)
        {
            locationPtr = locationPtr->right;
        }
		else
        {
            found = true;
        }
	}
	if (found)
    {
		remove_node(locationPtr->key);
		insert(key, item);
	}

	if (!found)
    {
		locationPtr = new Node<Key_T, Mapped_T>(key, item);
        //empty tree
		if (parent == 0)
		{
			treeRoot = locationPtr;
        }
		else if (key < parent->key)
        {
            parent->left = locationPtr;
        }
		else
        {
            parent->right = locationPtr;
        }

		locationPtr->parent = parent;
		adjust_height_insert(locationPtr);

		if (NodePtr<Key_T, Mapped_T> successor = get_successor(locationPtr))
        {
			locationPtr->listNext = successor;
			successor->listPrevious = locationPtr;
		}
		if (NodePtr<Key_T, Mapped_T> predecessor = get_predecessor(locationPtr))
		{
			locationPtr->listPrevious = predecessor;
			predecessor->listNext = locationPtr;
		}

		++size;
		return locationPtr;
	}
	return NULL;
}

//HELPER FUNCTION: update height of the tree after insertion
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::adjust_height_insert(NodePtr<Key_T, Mapped_T> & insertedPtr)
{
	NodePtr<Key_T, Mapped_T> child = insertedPtr;
	while (child->parent != 0)
    {

		get_height(child);
		get_balance_factor(child);
		this->preform_rotation(child);
		child = child->parent;
	}
	if (child->parent == 0)
    {
		get_height(child);
		get_balance_factor(child);
		preform_rotation(child);
	}
}

//HELPER FUNCTION: re-adjust height of the tree after a remove
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::adjust_height_remove(NodePtr<Key_T, Mapped_T> & insertedPtr)
{
	NodePtr<Key_T, Mapped_T> child = insertedPtr;
	if (child != NULL)
    {
		while (child->parent != 0)
		{
			get_height(child);
			get_balance_factor(child);
			preform_remove(child);
			child = child->parent;
		}
		if (child->parent == 0)
        {
			get_height(child);
			get_balance_factor(child);
			preform_remove(child);
		}
	}
}

//HELPER FUNCTION: what is the balance factor, needed to readjust the height of the
//tree
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::get_balance_factor(NodePtr<Key_T, Mapped_T> & node)
{
	node->balanceFactor = balance_factor(node);
}
template<class Key_T, class Mapped_T>
short int Tree<Key_T, Mapped_T>::balance_factor(const NodePtr<Key_T, Mapped_T> & p) const
{
	return height(p->left) - height(p->right);
}

//HELPER FUNCTION: calculate the hight of a sub_tree
template<class Key_T, class Mapped_T>
short int Tree<Key_T, Mapped_T>::height(const NodePtr<Key_T, Mapped_T> & p) const
{
	return p ? p->height : -1;
}

//HELPER FUNCTION: calculate the height of the tree
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::get_height(const NodePtr<Key_T, Mapped_T> & node) const
{
	node->height = std::max(height(node->right), height(node->left)) + 1;
}

//HELPER FUNCTION: left rotation
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::left_rotation(NodePtr<Key_T, Mapped_T> node)
{
	NodePtr<Key_T, Mapped_T> tempNode = node->right;
	tempNode->parent = node->parent;
	if (node->parent != NULL) {
		if (node == node->parent->left)
			node->parent->left = tempNode;
		else if (node == node->parent->right)
			node->parent->right = tempNode;
	}

	node->parent = tempNode;
	node->right = tempNode->left;

	if (tempNode->left != NULL)
    {
        tempNode->left->parent = node;
    }

	tempNode->left = node;

	get_height(node);
	get_balance_factor(node);

	get_height(tempNode);
	get_balance_factor(tempNode);

	if (tempNode->parent == NULL)
    {
        this->treeRoot = tempNode;
    }
}

//HELPER FUNCTION: right rotation
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::right_rotation(NodePtr<Key_T, Mapped_T> node)
{
	NodePtr<Key_T, Mapped_T> tempNode = node->left;
	tempNode->parent = node->parent;
	if (node->parent != NULL)
    {
		if (node == node->parent->left)
		{
		    node->parent->left = tempNode;
		}
		else if (node == node->parent->right)
        {
            node->parent->right = tempNode;
        }
	}

	node->parent = tempNode;
	node->left = tempNode->right;

	if (tempNode->right != NULL)
    {
        tempNode->right->parent = node;
    }
	tempNode->right = node;
	get_height(node);
	get_balance_factor(node);

	get_height(tempNode);
	get_balance_factor(tempNode);

	if (tempNode->parent == NULL)
    {
        this->treeRoot = tempNode;
    }
}

//HELPER FUNCTION: left_right rotation
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::left_right_rotation(NodePtr<Key_T, Mapped_T> & node)
{
	left_rotation(node->left);
	right_rotation(node);
}

//HELPER FUNCTION: right_left rotation
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::right_left_rotation(NodePtr<Key_T, Mapped_T> & node)
{
	right_rotation(node->right);
	left_rotation(node);
}

//HELPER FUNCTION: decides which type of rotation is needed
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::preform_rotation(NodePtr<Key_T, Mapped_T> & node)
{
	NodePtr<Key_T, Mapped_T> temp = NULL;
	if (node->balanceFactor == 2)
    {
		temp = node->left;
		if (temp->balanceFactor == 1)
		{
			right_rotation(node);
		}
		if (temp->balanceFactor == -1)
		{
			left_right_rotation(node);
		}
	}
	if (node->balanceFactor == -2)
	{
		temp = node->right;
		if (temp->balanceFactor == 1)
		{
			right_left_rotation(node);
		}

		if (temp->balanceFactor == -1)
		{
			left_rotation(node);
		}
	}
}

//HELPER FUNCTION: re-adjust the tree after removing a node
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::preform_remove(NodePtr<Key_T, Mapped_T> & node)
{
	NodePtr<Key_T, Mapped_T> temp = NULL;

	if (node->balanceFactor == 2)
    {
		temp = node->left;

		if (temp->balanceFactor == 1 || temp->balanceFactor == 0)
        {
			right_rotation(node);
		}

		else if (temp->balanceFactor == -1)
        {
			left_right_rotation(node);
		}
	}

	if (node->balanceFactor == -2)
    {
		temp = node->right;
		if (temp->balanceFactor == 1)
		{
			right_left_rotation(node);
		}

		else if (temp->balanceFactor == -1 || temp->balanceFactor == 0)
        {
			left_rotation(node);
		}
	}
}

//HELPER FUNCTION: get the minimum value
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::min_val(const NodePtr<Key_T, Mapped_T> & subTreeRoot) const
{
	if (subTreeRoot == NULL)
    {
        return NULL;
    }

	NodePtr<Key_T, Mapped_T> current = subTreeRoot;
	while (current->left != NULL)
    {
		current = current->left;
	}

	return current;
}

//HELPER FUNCTION: get the maximum value
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::max_val(const NodePtr<Key_T, Mapped_T> & subTreeRoot) const
{
	if (subTreeRoot == NULL)
    {
        return NULL;
    }

	NodePtr<Key_T, Mapped_T> current = subTreeRoot;
	while (current->right != NULL)
    {
		current = current->right;
	}

	return current;
}

//HELPER FUNCTION: in-order Successor
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::get_successor(NodePtr<Key_T, Mapped_T> node)
{
    //if it has a right child
    if (node->right != NULL)
    {
        return min_val(node->right);
    }

	NodePtr<Key_T, Mapped_T> p = node->parent;
	while (p != NULL && node == p->right)
    {
		node = p;
		p = node->parent;
	}

	return p;
}

//HELPER FUNCTION: in-order predecessor
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::get_predecessor(NodePtr<Key_T, Mapped_T> node)
{
    //if it has a left child
	if (node->left != NULL)
    {
        return max_val(node->left);
    }


	NodePtr<Key_T, Mapped_T> p = node->parent;
	while (p != NULL && node == p->left)
    {
		node = p;
		p = node->parent;
	}

	return p;
}

//HELPER FUNCTION: search function
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::hSearch(const Key_T & key)
{
	NodePtr<Key_T, Mapped_T> nodePtr = treeRoot;
	bool found = false;

	while (!found && nodePtr != 0)
    {
		if (key < nodePtr->key)
		{
		    nodePtr = nodePtr->left;
		}
		else if (nodePtr->key < key)
        {
            nodePtr = nodePtr->right;
        }
		else
        {
            found = true;
        }
	}
	if (found)
    {
        return nodePtr;
    }
	return NULL;
}

//HELPER FUNCTION: search function doesn't modify the tree
template<class Key_T, class Mapped_T>
NodePtr<Key_T, Mapped_T> Tree<Key_T, Mapped_T>::hSearch(const Key_T & key) const
{
	NodePtr<Key_T, Mapped_T> nodePtr = treeRoot;
	bool found = false;

	while (!found && nodePtr != 0)
    {
        //search left
		if (key < nodePtr->key)
		{
		    nodePtr = nodePtr->left;
		}
		else if (nodePtr->key < key)
        {
            nodePtr = nodePtr->right;
        }
		else
        {
            found = true;
        }
	}
	if (found)
    {
        return nodePtr;
    }
	return NULL;
}

//REMOVE: the node with the given key
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::remove_node(const Key_T & key)
{
	NodePtr<Key_T, Mapped_T> sub_tree_node = NULL;

	//node to be deleted
	NodePtr<Key_T, Mapped_T> to_delete = NULL;

	if (NodePtr<Key_T, Mapped_T> node = hSearch(key))
    {
		to_delete = node;
		if (node->left != NULL && node->right != NULL)
        {
            //in order successor
			NodePtr<Key_T, Mapped_T> nodeSucc = get_successor(node);

			//create a new node with the successor value
			NodePtr<Key_T, Mapped_T> newNode = new Node<Key_T, Mapped_T>(nodeSucc->pair);

			//Copy everything for the old node into the new node
			newNode->height = node->height;
			newNode->balanceFactor = node->balanceFactor;
			newNode->parent = node->parent;
			newNode->right = node->right;
			newNode->left = node->left;
			newNode->listPrevious = node->listPrevious;
			newNode->listNext = node->listNext;

			//point to the newly created node
			node->listPrevious->listNext = newNode;
			node->listNext->listPrevious = newNode;

			//Set children's parent
			node->right->parent = newNode;
			node->left->parent = newNode;

			//it is the root of the tree
			if (node->parent == NULL)
            {
                treeRoot = newNode;
            }

			//it is not the root of the tree
			if (node->parent != NULL)
            {
				if (node == node->parent->right)
				{
					node->parent->right = newNode;
				}
				if (node == node->parent->left)
				{
					node->parent->left = newNode;
				}
			}

			//discard the old node
			delete node;

			//set the successor
			to_delete = nodeSucc;
		}

		//reassign children based on whether or not it has 1 or 0 children
		sub_tree_node = to_delete->left;
		if (sub_tree_node == NULL)
        {
			sub_tree_node = to_delete->right;
		}

		//is the node to be deleted is root?
		if (to_delete->parent == NULL)
        {
			treeRoot = sub_tree_node;
		}

		//The node to be deleted, which child is it?
		else if (to_delete->parent->left == to_delete)
        {
			to_delete->parent->left = sub_tree_node;
		}
		else
		{
			to_delete->parent->right = sub_tree_node;
		}

		//Set the parent to the node's parent pointer
		if (sub_tree_node != NULL)
        {
			sub_tree_node->parent = to_delete->parent;
		}

		//re-adjust the height after a node is removed
		adjust_height_remove(to_delete->parent);
		{
			if (to_delete->listPrevious != NULL)
				(to_delete->listPrevious)->listNext = (to_delete->listNext);
			if (to_delete->listNext != NULL)
				(to_delete->listNext)->listPrevious = (to_delete->listPrevious);
		}
		--size;
		delete to_delete;
	}
}

//**** IMPLEMENTATION FOR ITERATORS STARTS HERE *****//

//Iterator: begin
template<class Key_T, class Mapped_T>
typename Tree<Key_T, Mapped_T>::Iterator Tree<Key_T, Mapped_T>::begin()
{
	return Iterator(min_val(treeRoot), this);
}

//Iterator: end
template<class Key_T, class Mapped_T>
typename Tree<Key_T, Mapped_T>::Iterator Tree<Key_T, Mapped_T>::end()
{
	return Iterator(NULL, this);
}

//Iterator: increment
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::Iterator::increment() {
	if (inode != NULL)
    {
        inode = inode->listNext;
	}
}

//Iterator: decrement
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::Iterator::decrement()
{
	if (inode != NULL)
    {
		inode = inode->listPrevious;
	}

	if (inode == NULL)
	{
		inode = ptr->max_val(ptr->treeRoot);
	}
}

//Const Iterator: begin
template<class Key_T, class Mapped_T>
const typename Tree<Key_T, Mapped_T>::ConstIterator Tree<Key_T, Mapped_T>::begin() const
{
	return ConstIterator(min_val(treeRoot), this);
}

//Const Iterator: end
template<class Key_T, class Mapped_T>
const typename Tree<Key_T, Mapped_T>::ConstIterator Tree<Key_T, Mapped_T>::end() const
{
	return ConstIterator(NULL, this);
}

//Const Iterator: increment
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::ConstIterator::increment() {
	if (inode != NULL) {
		inode = inode->listNext;
	}
}

//Const Iterator: decrement
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::ConstIterator::decrement()
{
	if (inode != NULL)
    {
		inode = inode->listPrevious;
	}
	if (inode == NULL)
    {
		inode = ptr->max_val(ptr->treeRoot);
	}
}

//Reverse Iterator: begin
template<class Key_T, class Mapped_T>
typename Tree<Key_T, Mapped_T>::ReverseIterator Tree<Key_T, Mapped_T>::rbegin()
{
	return ReverseIterator(max_val(treeRoot), this);
}

//Reverse Iterator: end
template<class Key_T, class Mapped_T>
typename Tree<Key_T, Mapped_T>::ReverseIterator Tree<Key_T, Mapped_T>::rend()
{
	return ReverseIterator(NULL, this);
}

//Reverse Iterator: increment operator
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::ReverseIterator::increment()
{
	if (inode != NULL)
        {
		inode = inode->listPrevious;
	}
}

//Reverse Iterator: decrement operator
template<class Key_T, class Mapped_T>
void Tree<Key_T, Mapped_T>::ReverseIterator::decrement()
{
	if (inode != NULL)
    {
		inode = inode->listNext;
	}
	if (inode == NULL)
	{
		inode = ptr->min_val(ptr->treeRoot);
	}
}

//Operator overloaded: equality
template <class Key_T, class Mapped_T>
bool operator==(const Tree<Key_T, Mapped_T> & x, const Tree<Key_T, Mapped_T> & y)
{
	typename Tree<Key_T, Mapped_T>::ConstIterator first = x.begin();
	typename Tree<Key_T, Mapped_T>::ConstIterator second = y.begin();
	if (x.sizeR() != y.sizeR())
		return false;
	for (; first != x.end() || second != y.end(); ++first, ++second) {
		if (!(first->first == second->first) || !(first->second == second->second))
			return false;
	}
	return true;
}

//Operator overloaded: inequality
template <class Key_T, class Mapped_T>
bool operator!=(const Tree<Key_T, Mapped_T> & x, const Tree<Key_T, Mapped_T> & y)
{
	return !(x == y);
}

//Operator overloaded: less-than
template <class Key_T, class Mapped_T>
bool operator<(const Tree<Key_T, Mapped_T> & x, const Tree<Key_T, Mapped_T> & y)
{
	return x.sizeR()<y.sizeR();
}

//*** END OF ITERATOR IMPLEMENTATION ***//

//+++++++++++++++++++++++++++++ END AVL TREE +++++++++++++++++++++++++++++++++++++++++//

namespace cs540
{
    //class declaration
	template<class Key_T, class Mapped_T>
	class Map;

	//equality operator
	template<class Key_T, class Mapped_T>
	bool operator==(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);

	//less-than operator
	template<class Key_T, class Mapped_T>
	bool operator<(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);

	//inequality operator
	template<class Key_T, class Mapped_T>
	bool operator!=(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);

	//equality operator
	template<class Key_T, class Mapped_T>
	bool operator==(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);

	//*** Start of the Map Class ***//
	template<class Key_T, class Mapped_T>
	class Map
	{
	    private:
            Tree<Key_T, Mapped_T> tree;
            friend bool operator== <>(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);
            friend bool operator< <>(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);
            friend bool operator!= <>(const Map<Key_T, Mapped_T> &, const Map<Key_T, Mapped_T> &);

        public:

            //declarations for the iterators
            using Iterator = typename Tree<Key_T, Mapped_T>::Iterator;
            using ConstIterator = typename Tree<Key_T, Mapped_T>::ConstIterator;
            using ReverseIterator = typename Tree<Key_T, Mapped_T>::ReverseIterator;

            //empty constructor
            Map <Key_T, Mapped_T>()
            {
                //empty
            }

            //copy constructor
            Map <Key_T, Mapped_T>(const Map<Key_T, Mapped_T> &original)
            {
                tree = original.tree;
            }

            //assignment operator
            Map<Key_T, Mapped_T> & operator=(const Map & original)
            {
                clear();
                tree = original.tree;
                return *this;
            }

            //constructor when a list of initializer is given
            Map <Key_T, Mapped_T>(std::initializer_list<std::pair<const Key_T, Mapped_T>> list)
            {
                for (auto x : list)
                {
                    insert(x);
                }
            }

            //get the size of the tree
            size_t size() const
            {
                return tree.sizeR();
            }

            //check if the tree is empty
            bool empty() const
            {
                return tree.empty();
            }

            //*** DEFINITON OF ITERATOR FUNCTIONS *****
            Iterator begin();
            Iterator end();
            ConstIterator begin() const;
            ConstIterator end() const;
            ReverseIterator rbegin();
            ReverseIterator rend();

            //*** function declarations ****//
            Iterator find(const Key_T &);
            ConstIterator find(const Key_T &) const;
            Mapped_T &at(const Key_T &);
            template <typename IT_T>
            void insert(IT_T range_beg, IT_T range_end);
            void erase(Iterator pos);
            void erase(const Key_T &);
            void clear();
            const Mapped_T &at(const Key_T &) const;
            Mapped_T & operator[] (const Key_T &);
            std::pair<typename Map <Key_T, Mapped_T>::Iterator, bool> insert(const ValueType<const Key_T, Mapped_T> & pair);
            //end of function declarations


	};

	//*** end of map class ***//

	//**** IMPLEMENATION OF FUNCTIONS STARTS HERE *****//
	template<class Key_T, class Mapped_T>
	std::pair<typename Map <Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>::insert(const ValueType<const Key_T, Mapped_T> & pair)
	{
		NodePtr <Key_T, Mapped_T> tmp = tree.helper_search(pair.first);
		if (tmp)
        {
            return std::pair<Iterator, bool>(Iterator(tmp, &tree), false);
        }
		tmp = tree.insert(pair.first, pair.second);
		return std::pair<Iterator, bool>(Iterator(tmp, &tree), true);
	}

	template<class Key_T, class Mapped_T>
	template<typename IT_T>
	void Map<Key_T, Mapped_T>::insert(IT_T range_beg, IT_T range_end)
	{
		for (; range_beg != range_end; ++range_beg)
        {
			tree.insert(range_beg->first, range_beg->second);
		}
	}

	//erase the given key
	template<class Key_T, class Mapped_T>
	void Map<Key_T, Mapped_T>::erase(const Key_T & key)
    {
		tree.remove(key);
	}
	template<class Key_T, class Mapped_T>
	void Map<Key_T, Mapped_T>::erase(const Iterator pos)
	{
		Key_T temp = pos.inode->pair.first;
		tree.remove(temp);
	}

	//delete the entire tree
	template<class Key_T, class Mapped_T>
	void Map<Key_T, Mapped_T>::clear()
	{
		tree.clear();
	}

	//at function
	template<class Key_T, class Mapped_T>
	Mapped_T & Map<Key_T, Mapped_T>::at(const Key_T & key)
	{
		return tree.at(key);
	}
	template<class Key_T, class Mapped_T>
	const Mapped_T & Map<Key_T, Mapped_T>::at(const Key_T & key) const
	{
		return tree.at(key);
	}

	//find function
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::find(const Key_T & key)
	{
		return Map<Key_T, Mapped_T>::Iterator(tree.helper_search(key), &tree);
	}
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(const Key_T & key) const
	{
		return Map<Key_T, Mapped_T>::ConstIterator(tree.helper_search(key), &tree);
	}

	template<class Key_T, class Mapped_T>
	Mapped_T & Map<Key_T, Mapped_T>::operator[](const Key_T & key)
	{
		NodePtr<Key_T, Mapped_T> temp;
		if ((temp = tree.helper_search(key)))
        {
			return temp->data;
		}
		temp = tree.insert(key, Mapped_T());
		return temp->data;
	}

    //iterator implementation
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::begin()
	{
		return tree.begin();
	}
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::end()
	{
		return tree.end();
	}

	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::begin() const {
		return tree.begin();
	}
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::end() const
	{
		return tree.end();
	}
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rbegin()
	{
		return tree.rbegin();
	}
	template<class Key_T, class Mapped_T>
	typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rend()
	{
		return tree.rend();
	}

	//*** GLOBAL COMPARSION FUNCTIONS *****//
	template<class Key_T, class Mapped_T>
	bool operator==(const Map<Key_T, Mapped_T> & x, const Map<Key_T, Mapped_T> & y)
	{
		return x.tree == y.tree;
	}
	template<class Key_T, class Mapped_T>
	bool operator!=(const Map<Key_T, Mapped_T> & x, const Map<Key_T, Mapped_T> & y)
	{
		return x.tree != y.tree;
	}
	template <class Key_T, class Mapped_T>
	bool operator<(const Map<Key_T, Mapped_T> & x, const Map<Key_T, Mapped_T> & y)
	{
		return x.tree<y.tree;
	}
}

#endif
