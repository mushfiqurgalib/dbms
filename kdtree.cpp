#include<bits/stdc++.h>
using namespace std;

int k=2;
typedef unsigned int udef;
struct Node
{
    vector<int>point;
    Node *left,*right;
};

struct Node *newnode(int arr[])
{
    struct Node *temp=new Node;

    for(int i=0;i<k;i++)
        temp->point.push_back(arr[i]);
        temp->left=NULL;
        temp->right=NULL;
        return temp;
};

Node *insertTree(Node *root,int point[],udef depth){
    if(root==NULL)
        return newnode(point);

    udef cd=depth%k;
    if(point[cd]<(root->point[cd]))
        root->left=insertTree(root->left,point,depth+1);
    else
        root->right=insertTree(root->right,point,depth+1);
    return root;
}
Node *insert(Node *root,int points[])
{
 return insertTree(root,points,0);
}
bool arepointsame(vector<int> point1,int point2[])
{
    for(int i=0;i<k;i++)
    {
        if(point1[i]!=point2[i])
            return false;
        return true;
    }
}

bool searchtree(Node* root,int point[],udef depth)
{
    if(root==NULL)
        return false;
    if(arepointsame(root->point,point))
        return true;

        udef cd=depth%k;
        if(point[cd]< root->point[cd])
            return searchtree(root->left,point,depth+1);
        return searchtree(root->right,point,depth+1);
}
bool findnode(Node *root,int point[])
{
    return searchtree(root,point,0);
}

void printtree(const string& prefix,const Node* node,bool isLeft)
{
    if(node!=NULL)
    {
        cout<<prefix;

        cout<<(isLeft?"|---" : "|___");

        cout<<"(";

        for(int j=0;j<k-1;j++)
            cout<<node->point[j]<<"," ;
        cout<< node->point[k-1]<< ")\n";

        printtree(prefix+(isLeft?"|   " : "   "),node->left,true);
        printtree(prefix+(isLeft?"|   " : "   "),node->right,false);
    }
}

void printtree(const Node* node)
{
    printtree("",node,false);
}

bool isInRange(Node* node, Node* rangeNode1, Node* rangeNode2)
{
    for(int i=0;i<k;i++){
        int low = min(rangeNode1->point[i], rangeNode2->point[i]);
        int high = max(rangeNode1->point[i], rangeNode2->point[i]);
        if(node->point[i] < low or node->point[i] > high)
            return false;
    }
    return true;
}


void range_search_helper(Node *current, Node *node1, Node *node2, udef depth)
{
    int current_level = depth % k;
    int low = min(node1->point[current_level], node2->point[current_level]);
    int high = max(node1->point[current_level], node2->point[current_level]);
    if(isInRange(current, node1, node2)){
        for(int i=0;i<k;i++){
            cout<< current->point[i]<< " ";
        }
        cout<< endl;
    }
    if(current->point[current_level] >= low and current->point[current_level] <= high){
        if(current->right != NULL)
            range_search_helper(current->right, node1, node2, depth+1);
        if(current->left != NULL)
            range_search_helper(current->left, node1, node2, depth+1);
    }
    else if(current->point[current_level] < low){
        if(current->right != NULL)
            range_search_helper(current->right, node1, node2, depth+1);
    }
    if(current->point[current_level] > high){
        if(current->left != NULL)
            range_search_helper(current->left, node1, node2, depth+1);
    }
}

int main()
{
    struct Node *root=NULL;
    int numnode=0;
    cout<<"Enter your data dimension"<<endl;
    cin>>k;

    while(1)
    {
        if(root==NULL)

            cout<<"Tree is empty"<<endl;


        cout<<"Choose an operation:\n 0.Insert default point\n 1.Insert a point \n 2.Find a point \n 3.print \n 4.Ranged Search \n 5.Exit \n";

        int type;
        cin>>type;
        if(type==0)
        {
            int points[][k]= {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                {9, 1}, {2, 7}, {10, 19}
            };
            int n=sizeof(points)/sizeof(points[0]);
            for(int i=0; i<n; i++)
                root=insert(root,points[i]);
                cout<<points[0][0];

        }
        else if(type==1)
        {
            cout<<"Enter a k-d point:";
            int point[k];
            for(int j=0;j<k;j++)
            {
                cin>>point[j];
            }
            root=insert(root,point);
            numnode++;
        }

        else if(type==2)
        {


            cout<<"Enter a k-d point :";
            int point[k];
            for(int j=0;j<k;j++)
                cin>>point[j];
            cout<<"( ";
            for(int j=0;j<k-1;j++)
                cout<<point[j]<<",";
            cout<<point[k-1]<<")is";
            (findnode(root,point))?cout<<"found"<<endl : cout<<"Not found"<<endl;
        }
        else if(type==3)
        {
            printtree(root);
        }

        else if(type==4)
        {


            cout<<"Enter 2 k-d points : ";
            int point1[k],point2[k];

                for(int j=0;j<k;j++)
                {
                    cin>>point1[j];
                }
             for(int j=0;j<k;j++)
                {
                    cin>>point2[j];
                }

          /*  cout<<"Points are ";
            for(int i=0;i<2;i++)
            {
                cout<<"(";
                for(int j=0;j<k;j++)
                {
                    cout<<point[i][j]<<",";
                }
                cout<<")";
                cout<<endl;
            }*/
               struct Node *node1=newnode( point1);
               struct Node *node2=newnode( point2);
              range_search_helper(root,node1,node2,0);

            //ranged(root,point,0);
        }

        else break;
    }
    return 0;
}
