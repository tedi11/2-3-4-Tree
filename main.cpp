#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

ifstream f("abce.in");
ofstream g("abce.out");

struct Node
{
    vector<int> keys;
    vector<Node*> children;
    Node* parent;

    Node()
    {
        parent = nullptr;
    }

    bool is_leaf()
    {
        return children.size() == 0;
    }

    bool is_full()
    {
        return keys.size() >= 3;
    }
    int size_f()
    {
        return keys.size();
    }
};

Node* find_node(Node* node, int key)
{
    if (node->is_leaf())
    {
        return node;
    }

    for (int i = 0; i < node->keys.size(); i++)
    {
        if (key < node->keys[i])
            return find_node(node->children[i], key);
        if (i == node->keys.size() - 1)
            return find_node(node->children[i+1], key);
    }
}

int get_index(Node* parent, Node* child)
{
    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i] == child)
        {
            return i;
        }
    }
}
Node* root = new Node();

void traverse(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    for(int i = 0; i< node->keys.size(); i++)
    {
        if (node->children.size() > 0)
            traverse(node->children[i]);
        cout<<node->keys[i]<<' ';
    }

    if (node->children.size() > 1)
        traverse(node->children.back());

}
void split(Node* node, int key)
{
    if (node->parent == nullptr)
    {

        int value = node->keys[2];
        Node* root2 = new Node();
        root2->keys.push_back(value);

        Node* new_leftt = new Node();
        Node* new_rightt = new Node();

        root2->children.push_back(new_leftt);
        root2->children.push_back(new_rightt);

        new_leftt->keys.push_back(node->keys[0]);
        new_leftt->keys.push_back(node->keys[1]);
        new_rightt->keys.push_back(node->keys[3]);

        new_leftt->parent = root2;
        new_rightt->parent = root2;
        if(node->children.size() >= 5)
        {
            new_leftt->children.push_back(node->children[0]);

            new_leftt->children.push_back(node->children[1]);
            new_leftt->children.push_back(node->children[2]);
            new_rightt->children.push_back(node->children[3]);
            new_rightt->children.push_back(node->children[4]);
            node->children[0]->parent = new_leftt;
            node->children[1]->parent = new_leftt;
            node->children[2]->parent = new_leftt;
            node->children[3]->parent = new_rightt;
            node->children[4]->parent = new_rightt;
        }


        root = root2;

    }
    else
    {

        Node* parentt = node->parent;
        int value = node->keys[2];
        int indexx = get_index(parentt, node);

        parentt->keys.push_back(value);
        sort(parentt->keys.begin(), parentt->keys.end());
        Node* new_left = new Node();
        Node* new_right = new Node();

        new_left->keys.push_back(node->keys[0]);
        new_left->keys.push_back(node->keys[1]);
        new_right->keys.push_back(node->keys[3]);

        new_left->parent = parentt;
        new_right->parent = parentt;

        if(node->children.size() >= 5)
        {

            new_left->children.push_back(node->children[0]);
            new_left->children.push_back(node->children[1]);
            new_left->children.push_back(node->children[2]);

            new_right->children.push_back(node->children[3]);
            new_right->children.push_back(node->children[4]);
            node->children[0]->parent = new_left;
            node->children[1]->parent = new_left;
            node->children[2]->parent = new_left;
            node->children[3]->parent = new_right;
            node->children[4]->parent = new_right;
        }

        parentt->children.erase(parentt->children.begin() + indexx, parentt->children.begin()+indexx+1);
        parentt->children.insert(parentt->children.begin() + indexx, new_left);
        parentt->children.insert(parentt->children.begin() + indexx+1, new_right);

        if (parentt->size_f() > 3)
        {
            split(parentt, -1);
        }
    }
}

bool search(Node* node, int key)
{
    for(int i = 0; i < node->keys.size(); i++)
    {
        if(key == node->keys[i])
            return true;
        if(node->children.size() > i)
            if(key < node->keys[i])
                return search(node->children[i],key);
    }
    if(node->children.size() > 0)
        return search(node->children[node->children.size()-1],key);

}

void insert(Node* node, int key)
{
    if(search( root,  key) == 1)
        return;
    Node* leaf = find_node(node, key);

    if (leaf->size_f() < 3)
    {
        leaf->keys.push_back(key);
        sort(leaf->keys.begin(), leaf->keys.end());
    }
    else
    {
        leaf->keys.push_back(key);

        sort(leaf->keys.begin(), leaf->keys.end());
        split(leaf, key);
    }
}
void linii(Node* nod)
{
    for(int i = 0; i <nod->keys.size(); i++)
        cout<<nod->keys[i]<<' ';
    cout<<endl;
    for(int i = 0; i <nod->children.size(); i++)
        linii(nod->children[i]);
}

int cauta_sus_stanga(Node* node, int key)
{
    if(node->parent != nullptr)
        for(int i = node->parent->keys.size()-1; i >= 0 ; i--)
            if(node->parent->keys[i] < key)
                return node->parent->keys[i];
    return cauta_sus_stanga(node->parent, key);

}
int cauta_dreapta(Node* node)
{
    if(node->children.size() == 0)
        return(node->keys[node->keys.size()-1]);
    cauta_dreapta(node->children[node->children.size()-1]);
}
int precedent(Node* node, int key)
{
    int indexx;
    for(int i = 0; i < node->keys.size(); i++)
        if (node->keys[i] == key)
            indexx = i;
    //cout<<indexx;
    if(node->children.size() > indexx) ///daca am copii
    {
        return cauta_dreapta(node->children[indexx]);
    }
    if(node->children.size() == 0 && indexx > 0)///daca nu am copii, dar e un key mai mic in nod
    {
        return node->keys[indexx-1];
    }
    if(node->children.size() == 0 && indexx == 0)
        return cauta_sus_stanga(node, key);
}


int cauta_precedent(Node* node, int key)
{

    for(int i = 0; i < node->keys.size(); i++)
    {
        if(key == node->keys[i])
            return precedent(node, key);
        if(node->children.size() > i)
            if(key < node->keys[i])
                return cauta_precedent(node->children[i],key);
    }
    if(node->children.size() > 0)
        return cauta_precedent(node->children[node->children.size()-1],key);
}

int cauta_succesor(Node* node, int key)
{
    for(int i = 0; i < node->keys.size(); i++)
    {
        if (key < node->keys[i] && node->children.size() > 0)
        {
            int val = cauta_succesor(node->children[i], key);
            if (node->keys[i] < val)
                return node->keys[i];
            else
                return val;
        }

        if (key < node->keys[i] && node->children.size() == 0)
            return node->keys[i];
    }
    if (node->children.size() > 0)
    {
        int val = cauta_succesor(node->children[node->children.size()-1], key);
        if ( key < val)
            return val;
    }
    return 99999;
}

void interval(int x, int y, Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    for(int i = 0; i< node->keys.size(); i++)
    {
        if (node->children.size() > 0)
            interval(x, y, node->children[i]);
        if(node->keys[i] >= x && node->keys[i] <= y)
            cout<<node->keys[i]<<' ';
    }

    if (node->children.size() > 1)
        interval(x, y, node->children.back());

}

void bac()
{
    cout<<"Type 0 to go back\n";
    int bac;
    cin>>bac;
}

int main()
{
    insert(root, 1);
    insert(root, 2);
    insert(root, 4);
    insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 6);
    insert(root, 8);

    bool k = true;
    while(k)
    {

        system("CLS");
        cout<<"-MENIU-\n";
        cout<<"1 - Insert\n";
        cout<<"2 - Show on lines\n";
        cout<<"3 - Search a number\n";
        cout<<"4 - Predecesor\n";
        cout<<"5 - Succesor\n";
        cout<<"6 - [x,y]\n";
        cout<<"7 - Inorder\n";
        cout<<"8 - Quit\n";
        int c;
        cin>>c;
        switch(c)
        {
        case 1:
        {
            system("CLS");
            int X;
            cout<<"What is the number?\n";
            cin>>X;
            insert(root, X);
            break;
        }
        case 2:
        {
            system("CLS");
            linii(root);
            bac();
            break;
        }
        case 3:
        {
            system("CLS");
            cout<<"What is the number?\n";
            int X;
            cin>>X;
            cout<<search(root, X);
            break;
        }
        case 4:
        {
            system("CLS");
            cout<<"Dati un numar\n";
            int X;
            cin>>X;
            cout<<"Predecesorul este: ";
            cout<<cauta_precedent(root, X)<<endl;
            bac();
            break;
        }
        case 5:
        {
            system("CLS");
            cout<<"Dati un numar: ";
            int X;
            cin>>X;
            if(cauta_succesor(root, X) == 99999)
            {
                system("CLS");
                cout<<"Numarul dat este mai mare sau egal cu numarul din secventa!\n";
            }
            else
            {
                cout<<"\Succesorul este: ";
                cout<<cauta_succesor(root, X)<<endl;
            }
            bac();
            break;
        }
        case 6:
        {
            system("CLS");
            cout<<"Dati doua numere\n";
            int X, Y;
            cin>>X>>Y;
            interval(X,Y, root);
            cout<<endl;
            bac();
            break;
        }
        case 7:
        {
            system("CLS");
            traverse(root);
            cout<<endl<<endl;
            bac();
            break;
        }
        case 8:
        {
            system("CLS");
            k = 0;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}



