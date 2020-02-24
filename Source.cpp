#include<iostream>
using namespace std;

class Container
{
public:

	virtual void insert(int value) = 0;

	virtual bool exists(int value) = 0;

	virtual void print() = 0;

	virtual void remove(int value) = 0;

	virtual ~Container();

};
Container::~Container() { }

class SimpleTree : public Container
{
protected:
	int R;
	struct el
	{
		int value;
		shared_ptr<el> left;
		shared_ptr<el> right;
		shared_ptr<el> parent;
	};
	shared_ptr<el> root;
public:
	SimpleTree()
	{
		root = NULL;
		R = 0;
	}
	void insert(int value)
	{
		R += 1;
		if (R == 1)
		{
			root = create(value);
		}
		else
		{
			shared_ptr<el> s = create(value);
			insert(root, s);
		}
	}
	void print()

	{

		print_tree(root);

	}

	bool exists(int value)

	{
		shared_ptr<el> c = create(value);

		shared_ptr<el> k = find(root, c);


		if (k != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void remove(int value)
	{
		shared_ptr<el> c = create(value);

		shared_ptr<el> k = find(root, c);

		shared_ptr<el> t = LAST_ELEMENT(k->right);


		DELETE(k, t);
	}

	void DELETE(shared_ptr<el> k, shared_ptr<el> t)
	{
		if (k->right != NULL)
		{
			k->right->parent = k->parent;
			if (k->parent->right == k)
			{
				k->parent->right = k->right;
			}
			else
			{
				k->parent->left = k->right;
			}
			if (k->left != NULL)
			{
				if (k->right->left == NULL)
				{
					k->left->parent = k->right;
					k->right->left = k->left;
				}
				else
				{
					k->left->parent = t;
					t->left = k->left;
				}
			}
		}
		else
		{
			k->left->parent = k->parent;
			if (k->parent->right == k)
			{
				k->parent->right = k->left;
			}
			else
			{
				k->parent->left = k->left;
			}
		}
	}

	shared_ptr<el> LAST_ELEMENT(shared_ptr<el> p)

	{
		if (p != NULL)
		{

			if (p->left != NULL)

			{

				return LAST_ELEMENT(p->left);
			}
			else
			{
				return(p);
			}
		}
		else
		{
			return (p->parent);
		}
	};
	
	shared_ptr<el> create(int a)
	{
		shared_ptr<el> s = make_shared<el>();
		s->value = a;
		s->left = NULL;
		s->right = NULL;
		s->parent = NULL;
		return s;
	};
	void insert(shared_ptr<el> root, shared_ptr<el> s)
	{
		if (root->value >= s->value)
		{
			if (root->left == NULL)
			{
				root->left = s;
				s->parent = root;
			}
			else
			{
				insert(root->left, s);
			}
		}
		else
		{
			if (root->right == NULL)
			{
				root->right = s;
				s->parent = root;
			}
			else
			{
				insert(root->right, s);
			}
		}
	}
	void print_tree(shared_ptr<el> root)
	{

		cout << root->value << endl;
		if (root->left != NULL)
		{
			print_tree(root->left);
		}
		if (root->right != NULL)
		{
			print_tree(root->right);
		}
	}
	shared_ptr<el> find(shared_ptr<el> root, shared_ptr<el> c)
	{
		if (root->value == c->value)
		{
			return root;
		}
		if (root->value < c->value)
		{
			if (root->right != 0)
			{
				return find(root->right, c);
			}
			else
			{
				return NULL;
			}
		}
		if (root->value > c->value)
		{
			if (root->right != 0)
			{
				return find(root->left, c);
			}
			else
			{
				return NULL;
			}
		}
		return NULL;
	};
};
int main()
{
	Container* c = new SimpleTree();
	for (int i = 1; i < 10; i++)
		c->insert(i*i);
	cout << "List after creation: " << endl;
	c->print();
	if (c->exists(25))
		cout << "Search for value 25: found" << endl;
	if (!c->exists(111))
		cout << "Search for value 111: not found" << endl;
	c->remove(25);
	cout << "List after deletion of the element:" << endl;
	c->print();
	delete c;
	system("pause");
	return 0;
}

