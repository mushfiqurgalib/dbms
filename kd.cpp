#include<bits/stdc++.h>

using namespace std;

int k = 2;
typedef unsigned int uInt;

struct Node
{
	vector<int>point;
	Node *left, *right;
};

struct Node* newNode(int arr[])
{
	struct Node* temp = new Node;

	for (int i=0; i<k; i++)
        temp->point.push_back(arr[i]);
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

Node *insertInTree(Node *root, int point[], uInt depth)
{
	if (root == NULL)
        return newNode(point);

	uInt cd = depth % k;

	if (point[cd] < (root->point[cd]))
		root->left = insertInTree(root->left, point, depth + 1);
	else
		root->right = insertInTree(root->right, point, depth + 1);

	return root;
}

Node* insert(Node *root, int point[])
{
	return insertInTree(root, point, 0);
}

bool arePointsSame(vector <int> point1, int point2[])
{
	for (int i = 0; i < k; ++i)
		if (point1[i] != point2[i])
			return false;

	return true;
}

bool searchInTree(Node* root, int point[], uInt depth)
{
	if (root == NULL)
		return false;
	if (arePointsSame(root->point, point))
		return true;

	uInt cd = depth % k;

	if (point[cd] < root->point[cd])
		return searchInTree(root->left, point, depth + 1);

	return searchInTree(root->right, point, depth + 1);
}

bool Find(Node* root, int point[])
{
	return searchInTree(root, point, 0);
}

void printTree(const string& prefix, const Node* node, bool isLeft)
{
    if( node != NULL )
    {
        cout << prefix;

        cout << (isLeft ? "|---" : "|___" );

        cout << "( ";
        for(int j=0; j<k-1; j++)
            cout << node->point[j] << ", ";
        cout << node->point[k-1] << " )\n";

        printTree( prefix + (isLeft ? "|     " : "      "), node->left, true);
        printTree( prefix + (isLeft ? "|     " : "      "), node->right, false);
    }
}

void printTree(const Node* node)
{
    printTree("", node, false);
}

int main()
{
	struct Node *root = NULL;
	int numNodes = 0;
	cout << "Enter Your Data Dimension: ";
    cin >> k;
	while(1)
    {
        if(root == NULL) cout << "The tree is Empty. Please insert some points.\n";
        cout << "Choose an operation:\n  0. Insert default points\n  1. Insert a point\n  2. Find a point\n  3. Pretty print k-d Tree \n  4. Find range of Points\n  5. Exit\n";
        int type;
        cin >> type;
        if(type == 0)
        {
            int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                       {9, 1}, {2, 7}, {10, 19}};
            int n = sizeof(points)/sizeof(points[0]);
            for (int i=0; i<n; i++)
               root = insert(root, points[i]);
        }

        else if(type == 1)
        {
            cout << "Enter a k-dimension point : ";
            int point[k];
            for(int j=0; j<k; j++)
                cin >> point[j];
            root = insert(root, point);
            numNodes++;
        }

        else if(type == 2)
        {
            cout << "Enter a k-dimension point : ";
            int point[k];
            for(int j=0; j<k; j++)
                cin >> point[j];
            cout << "( ";
            for(int j=0; j<k-1; j++)
                cout << point[j] << ", ";
            cout << point[k-1] << " ) is ";
            (Find(root, point))? cout << "Found\n": cout << "Not Found\n";
        }

        else if(type == 3)
        {
            printTree(root);
        }

        else if(type == 4)
        {
            //do something
        }

        else break;
    }

	return 0;
}