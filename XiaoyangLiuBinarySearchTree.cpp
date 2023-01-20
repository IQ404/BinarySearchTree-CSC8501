#include <iostream>
#include <vector>

class BinarySearchTree
{
public:

	BinarySearchTree() {}
	~BinarySearchTree() { terminate_tree(); }

	void insert_integer(const int inserting_value)
	{
		//insert_integer(root, inserting_value);
		insert_integer(&root, inserting_value);
	}

	void print_tree() const  // print to std::cout
	{
		if (root)
		{
			print_tree(root);
		}
		else
		{
			std::cout << "The tree has no element (root == nullptr).\n";
		}
	}

	void terminate_tree()
	{
		terminate_tree(root);
	}

	const std::vector<int>& most_common_integers()
	{
		mode.clear();
		if (root)
		{
			max_count = root->count;
			most_common_integers(root);
		}
		return mode;
	}

	const int* largest_integer()  // return nullptr if no element at all
	{
		if (!(root))
		{
			return nullptr;
		}
		largest = largest_integer(root)->value;
		return &largest;
	}

	const int* smallest_integer()  // return nullptr if no element at all
	{
		if (!(root))
		{
			return nullptr;
		}
		smallest = smallest_integer(root)->value;
		return &smallest;
	}

	const int* sum_of_all_integers()  // return nullptr if no element at all
	{
		if (root)
		{
			sum = 0;
			sum_all_integers(root);
			return &sum;
		}
		return nullptr;
	}

	bool has(const int& i) const
	{
		return has(i, root);
	}

	bool is_empty() const
	{
		if (root)
		{
			return false;
		}
		return true;
	}

	void remove(const int& removing_value, const int& count)  // you can even use negative number to add more existing item(s)
	{
		remove(removing_value, count, root);
	}

private:

	struct node
	{
		int value;
		int count = 1;
		node* left;
		node* right;

		node(int v, node* l = nullptr, node* r = nullptr)
			: value{ v }, left{ l }, right{ r }
		{}
	};

	node* root = nullptr;
	int max_count;
	std::vector<int> mode;
	int largest;
	int smallest;
	int sum;

	/*void insert_integer(node*& tree, const int& inserting_value)
	{
		if (!(tree))
		{
			tree = new node(inserting_value);
		}
		else if (tree->value > inserting_value)
		{
			insert_integer(tree->left, inserting_value);
		}
		else if (tree->value < inserting_value)
		{
			insert_integer(tree->right, inserting_value);
		}
		else
		{
			tree->count += 1;
		}
	}*/

	void insert_integer(node** tree, const int& inserting_value)
	{
		if (!(*tree))
		{
			*tree = new node(inserting_value);
		}
		else if ((*tree)->value > inserting_value)
		{
			insert_integer(&((*tree)->left), inserting_value);
		}
		else if ((*tree)->value < inserting_value)
		{
			insert_integer(&((*tree)->right), inserting_value);
		}
		else
		{
			(*tree)->count += 1;
		}
	}

	void print_tree(node* tree) const
	{
		if (tree->left)
		{
			print_tree(tree->left);
		}
		for (int i = 0; i < tree->count; i++)
		{
			std::cout << tree->value << std::endl;
		}
		if (tree->right)
		{
			print_tree(tree->right);
		}
	}

	void terminate_tree(node*& tree)
	{
		if (tree)
		{
			terminate_tree(tree->left);
			terminate_tree(tree->right);
			delete tree;
			tree = nullptr;
		}
	}

	void most_common_integers(node* tree)
	{
		if (tree->left)
		{
			most_common_integers(tree->left);
		}

		if (tree->count == max_count)
		{
			mode.push_back(tree->value);
		}
		if (tree->count > max_count)
		{
			mode.clear();
			mode.push_back(tree->value);
			max_count = tree->count;
		}

		if (tree->right)
		{
			most_common_integers(tree->right);
		}
	}

	node* largest_integer(node* tree) const
	{
		if (!(tree) || !(tree->right))
		{
			return tree;
		}
		return largest_integer(tree->right);
	}

	node* smallest_integer(node* tree) const
	{
		if (!(tree) || !(tree->left))
		{
			return tree;
		}
		return smallest_integer(tree->left);
	}

	void sum_all_integers(node* tree)
	{
		if (tree->left)
		{
			sum_all_integers(tree->left);
		}
		for (int i = 0; i < tree->count; i++)
		{
			sum += tree->value;
		}
		if (tree->right)
		{
			sum_all_integers(tree->right);
		}
	}

	bool has(const int& searching_value, node* tree) const
	{
		if (!tree)
		{
			return false;
		}
		if (searching_value < tree->value)
		{
			return has(searching_value, tree->left);
		}
		if (searching_value > tree->value)
		{
			return has(searching_value, tree->right);
		}
		return true;
	}

	void remove(const int& removing_value, const int& count, node*& tree)
	{
		if (!tree)
		{
			return;
		}
		if (removing_value < tree->value)
		{
			remove(removing_value, count, tree->left);
		}
		else if (removing_value > tree->value)
		{
			remove(removing_value, count, tree->right);
		}
		else if (tree->count > count)
		{
			tree->count -= count;
		}
		else if ((tree->left) && (tree->right))  // double-children cases
		{
			node* n = smallest_integer(tree->right);
			tree->value = n->value;
			tree->count = n->count;
			remove(tree->value, tree->count, tree->right);  // local minimum deletion
		}
		else  // this block accounts for both of the local minimum deletion and the single-child cases and the no-child cases
		{
			node* n = tree;
			tree = (tree->right) ? (tree->right) : (tree->left);
			delete n;
		}
	}

};

int main()
{
	using bst = BinarySearchTree;
	using namespace std;

	bst t;
	// Try t's member functions here :)
}