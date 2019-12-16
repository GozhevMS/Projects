#include<iostream>
#include<fstream>

using namespace std;

struct node//��������� ����
{
	int key;
	int height;
	node* left;
	node* right;
	node(int k) {key = k; left = right = NULL; height = 1;}//�����������
};

int height(node* root)//������ ������
{
	return root?root->height:0;
}

int bfactor(node* p)//�������� ����� ������� �����������
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)//����������� ������ ���������� ���������+1
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p)//������ �������
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q)//����� �������
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p)//������������
{
	fixheight(p);
	if( bfactor(p)==2 )//������� ����� �������
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )//������� ������ �������
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* insertNode(node* root, int k)//������� ����
{
	if(!root) return new node(k);
	if( k<root->key )
		root->left = insertNode(root->left,k);
	else
		root->right = insertNode(root->right,k);
	return balance(root);
}

node* findmin(node* r)//����� ������������ �������� � ������
{
	return r->left?findmin(r->left):r;
}

node* removemin(node* r)//�������� ������������ �������� � ������
{
	if(r->left==0)
		return r->right;
	r->left = removemin(r->left);
	return balance(r);
}

node* removeNode(node* root, int k)//�������� ����
{
	if(!root) return 0;
	if(k < root->key)
		root->left = removeNode(root->left, k);
	else if( k > root->key )
		root->right = removeNode(root->right, k);
	else
	{
		node* q = root->left;
		node* r = root->right;
		delete root;
		if(!r) return q;
		node* minNode = findmin(r);
		minNode->right = removemin(r);
		minNode->left = q;
		return balance(minNode);
	}
	return balance(root);
}
node* removeTree(node* root)
{
    if((root->left==NULL)&&(root->right=NULL))
    {
        delete root;
        return NULL;
    }
    else
    {
        if(!root->left)
            root->left=removeTree(root->left);
        if(!root->right)
            root->right=removeTree(root->right);
        delete root;
        return NULL;
    }
}
//---------------------------------����� �� �����������-----------------------------------------\\

void printTree(node *x){
   if (x != NULL){
      printTree(x->left);
      cout<<x->key<<' ';
      printTree(x->right);
   }
}
//------------------------------------����� � ������--------------------------------------------\\

void levelOrderPrint(node *root) {
    if (root == NULL) {return;}
    node *q[1024];
	for(int i = 0; i < 100; i++)
        q[i] = NULL;
    int first = 0;
    int last = 0;
    q[0] = root;

    while (q[first]!=NULL)
    {
        node* temp = q[first];
        cout << temp->key << " ";
        if ( temp->left != NULL ){
            last++;
            q[last] = temp->left;
        }
        if ( temp->right != NULL ){
            last++;
            q[last] = temp->right;
        }
        if(q[first+1])
            if(q[first]->key > q[first+1]->key) cout<<endl;
        first++;
   }
}

int main()
{
    node *z = new node(0);
    char filename[]= "numbers";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "failed to open " <<filename <<endl;
    } else
    {
        int k;
        file>>k;
        z->key = k;
        while(true)
        {
            file>>k;
            if (file.eof()) break;
            z=insertNode(z, k);
        }
    }
    file.close();

    //z=removeNode(z, 43);
    //z=removeNode(z, 39);
    //z=removeNode(z, 25);
    printTree(z);
    cout<<endl<<endl;
    levelOrderPrint(z);
    cout<<endl<<endl;
    z->left->right=removeTree(z->left->right);
    levelOrderPrint(z);
    z=insertNode(z, 23);
    z=insertNode(z, 25);
    z=insertNode(z, 28);
    cout<<endl<<endl;
    levelOrderPrint(z);

    return 0;
}
