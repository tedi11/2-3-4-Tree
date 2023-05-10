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
        //children = {};
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
        //cout<<"FRUNZA"<<endl;
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

//    for (int i = 0; i < node->children.size(); i++)
//        traverse(node->children[i]);
//    for(int i = 0; i< node->keys.size(); i++)
//        cout<<node->keys[i]<<' ';
    //cout<<"NOD ";
    for(int i = 0; i< node->keys.size(); i++)
    {
        if (node->children.size() > 0)
            traverse(node->children[i]);
        cout<<node->keys[i]<<' ';
    }
    //cout<<node->keys[node->keys.size()]<<' ';

//
    if (node->children.size() > 1)
        traverse(node->children.back());

}
void split(Node* node, int key)
{
    if (node->parent == nullptr)
    {
        //cout<<"spart root\n";
//        Node* root2 = new Node();
//        root2->children.push_back(node);
//        node->parent = root2;

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
        //cout<<new_right->keys[0];

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
        //root2 = nullptr;
        //root2->children.erase(root2->children.begin() + root2->children.size()-1);
        //root2->parent = nullptr;
        //delete root2;
        //delete root;
        //Node* root = new Node();
        //root = root2;

        //cout<<"! ";
        //cout<<root->children.size();
    }
    else
    {
        //cout<<"spart nod\n";
        Node* parentt = node->parent;//catre 6 si 53
        int value = node->keys[2];//3
        int indexx = get_index(parentt, node);//0
        //cout<<value<<"!!";
        //Node* root2 = new Node();
        parentt->keys.push_back(value);//bag 3
        sort(parentt->keys.begin(), parentt->keys.end());
        Node* new_left = new Node();
        Node* new_right = new Node();

        //parentt->children.push_back(new_left);
        //parentt->children.push_back(new_right);

        new_left->keys.push_back(node->keys[0]);//1
        new_left->keys.push_back(node->keys[1]);//2
        new_right->keys.push_back(node->keys[3]);//4

        //cout<<new_right->keys[0];
        new_left->parent = parentt;
        new_right->parent = parentt;
        //if(value == 9)
        //cout<< parentt->children[4]->keys[0];
        //traverse(node);
        if(node->children.size() >= 5)
        {
            //for(int i = 0; i<indexx; i++)
            //new_left->children.push_back(node->children[i]);
            new_left->children.push_back(node->children[0]);
            new_left->children.push_back(node->children[1]);
            new_left->children.push_back(node->children[2]);
            //for(int j = indexx+1; j<node->children.size(); j++)
            //new_right->children.push_back(node->children[j]);
            new_right->children.push_back(node->children[3]);
            new_right->children.push_back(node->children[4]);
            node->children[0]->parent = new_left;
            node->children[1]->parent = new_left;
            node->children[2]->parent = new_left;
            node->children[3]->parent = new_right;
            node->children[4]->parent = new_right;
        }
        //cout<<indexx<<"!";
        //node = parentt;
        parentt->children.erase(parentt->children.begin() + indexx, parentt->children.begin()+indexx+1);
        parentt->children.insert(parentt->children.begin() + indexx, new_left);
        parentt->children.insert(parentt->children.begin() + indexx+1, new_right);

        //parentt->parent = nullptr;

        //delete node;

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
    //return false;
    //cout<<"!";

//    for(int i = node->children.size(); i++)
//        {for(int j = node->children[i].keys.size(); j++)
//            if(node->children[i].keys[j] == key)
//                return 1;
}

void insert(Node* node, int key)
{
    if(search( root,  key) == 1)
        return;
    Node* leaf = find_node(node, key);
    //for (int i = 0; i < leaf->keys.size(); i++)
    //cout << leaf->keys[i] << " ";
    //cout<<endl;
    //Node* leaf = root;
    if (leaf->size_f() < 3)
    {
        leaf->keys.push_back(key);
        sort(leaf->keys.begin(), leaf->keys.end());
    }
    else
    {
        leaf->keys.push_back(key);
        //cout<<"F"<<endl;
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
    //cout<<"!";
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
        //cout<<"!";
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
//        if (node->children.size() > 0)
//        {
//            int val = cauta_succesor(node->children[node->children.size()-1], key);
//            if (node->keys[node->keys.size()-1] < val && key > val)
//                return node->keys[i];
//            else
//                return val;
//        }
        if (key < node->keys[i] && node->children.size() == 0)
            return node->keys[i];
        //return -1;
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

void sterge(Node* node, int key)
{

Node* leaf = find_node(node, key);

if (!leaf || find(leaf->keys.begin(), leaf->keys.end(), key) == leaf->keys.end())
    return;

leaf->keys.erase(remove(leaf->keys.begin(), leaf->keys.end(), key), leaf->keys.end());

if (node == leaf && leaf->keys.empty())
{
    delete leaf;
    node = nullptr;
    return;
}

if (leaf->keys.size() >= 2)
    return;

Node* parent = leaf->parent;
int index = get_index(parent, leaf);
Node* left_sibling = index > 0 ? parent->children[index-1] : nullptr;
Node* right_sibling = index < parent->children.size()-1 ? parent->children[index+1] : nullptr;

if (left_sibling && left_sibling->keys.size() >= 2)
{
    int parent_key = parent->keys[index-1];
    int left_key = left_sibling->keys.back();
    left_sibling->keys.pop_back();
    parent->keys[index-1] = left_key;
    leaf->keys.push_back(parent_key);
    sort(leaf->keys.begin(), leaf->keys.end());
    return;
}

if (right_sibling && right_sibling->keys.size() >= 2)
{
    int parent_key = parent->keys[index];
    int right_key = right_sibling->keys.front();
    right_sibling->keys.erase(right_sibling->keys.begin());
    parent->keys[index] = right_key;
    leaf->keys.push_back(parent_key);
    sort(leaf->keys.begin(), leaf->keys.end());
    return;
}

if (left_sibling)
{
    left_sibling->keys.push_back(parent->keys[index-1]);
    for (int i = 0; i < leaf->keys.size(); i++)
        left_sibling->keys.push_back(leaf->keys[i]);
    parent->children.erase(parent->children.begin()+index);
    parent->keys.erase(parent->keys.begin()+index-1);
    delete leaf;
}
else if (right_sibling)
{
    leaf->keys.push_back(parent->keys[index]);
    for (int i = 0; i < right_sibling->keys.size(); i++)
        leaf->keys.push_back(right_sibling->keys[i]);
    parent->children.erase(parent->children.begin()+index+1);
    parent->keys.erase(parent->keys.begin()+index);
    delete right_sibling;
}

if (parent == node && parent->keys.empty())
{
    node = left_sibling ? left_sibling : leaf;
    node->parent = nullptr;
    delete parent;
}

if (parent)
    sterge(parent, key);
}

///delete
///predecesor daca nu am key in arbore
///succesor
///toate numerele din intervalul x-y

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
    //sterge(root, 8);
    //linii(root);
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
        cout<<"8 - Delete a key\n";
        cout<<"9 - Quit\n";
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
            int X;
            cout<<"What is the key to delete?\n";
            cin>>X;
            sterge(root, X);
            break;
        }
        case 9:
        {
            system("CLS");
            k = 0;
            break;
        }
        default:
            break;
        }
    }

//    insert(copill, 330);
    //insert(copill, 200);
    //copill->parent = root;
    //root->children.push_back(copill);
//    insert(root, 1);
//    insert(root, 6);
//    insert(root, 7);
//    insert(root, 2);
//    insert(root, 3);
//    insert(root, 52);
//    insert(root, 53);
//    insert(root, 54);
//    insert(root, 4);
//    insert(root, 5);
//
//    insert(root, 8);
//
//
//
//
//    insert(root, 22);
//    insert(root, 42);
//    insert(root, 9);
//////////
//
//    insert(root, 55);
//    insert(root, 23);
//    insert(root, 867);
//    insert(root, 1234);
//    insert(root, 233);
//    insert(root, 234);
//    insert(root, 56);
//    insert(root, 57);
//    insert(root, 43);
//    insert(root, 25);
//    insert(root, 26);
//    insert(root, 44);
//    insert(root, 45);
//    insert(root, 46);
//    insert(root, 47);
//    insert(root, 48);
//    insert(root, 49);
    //for (int i = 40; i <= 55; i++)
    //cout<<i<<' '<<search(root, i)<<endl;
    //cout<<root->children[1]->children[1];
    //for (int i = 0; i < root->keys.size(); i++)
//    cout << root->keys[i] << " ";
    //cout << root->keys[0] << " ";
    //cout << root->keys[1] << " ";
    //cout << root->keys[2] << " ";
    //insert(root, 40);
//    Node* op = new Node();
//    root->children.push_back(op);
//    op->parent = root;
//
//    insert(op, 5);
//    insert(op, 6);

    //cout<<op->keys.size()<<'\n';
    //cout<<root->children[0]->keys.size();
    //cout<<op->parent->keys.size()<<endl;
//    insert(op, 7);
//    insert(op, 8);
    //insert(op, 9);

    //cout<<op->keys.size()<<'\n';
    //cout<<op->children->keys.size();

//        Node* opq = new Node();
//    root->children.push_back(opq);
//    opq->keys.push_back(230);
    //cout<<root->children[2]->keys[0]<<' ';
    //cout<<root->children[2]->keys[1]<<' ';
    //cout<<root->children[2]->keys[2]<<' ';

    //cout<<root->keys.size();
    //cout<<root->children.size();
//
    //for (int i = 0; i < root->keys.size(); i++)
    //cout << root->keys[i] << endl;

    //traverse(root);
    //cout<<endl;
    //linii(root);
    //cout<<search(root, 3);

    //insert(root, 20);
    //insert(root, 25);
    //insert(root, 30);
    //cout<<root->keys[2];
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

struct nod
{
    vector<int> keys;
    vector<nod*> copil;
    nod* parinte;

    nod()
    {
        parinte = nullptr;
    }

    bool frunza()
    {
        return copil.empty();
    }

    bool plin()
    {
        return keys.size() == 3;
    }
    void nodNou(nod*, int);
};

nod* cauta_pozitie(nod* nod, int key) {
    if (nod->frunza()) {
        return nod;
    }

    for (int i = 0; i < nod->keys.size(); i++) {
        if (key < nod->keys[i] || i == nod->keys.size() - 1) {
            return cauta_pozitie(nod->copil[i], key);
        }
    }
}

int get_index(nod* parinte, nod* copil) {
    for (int i = 0; i < parinte->copil.size(); i++) {
        if (parinte->copil[i] == copil) {
            return i;
        }
    }
}

nod* root = new nod();

void split(nod* nod1, int key){
    if(nod1->parinte == nullptr){
        root = new nod;
        nod1->keys.push_back(key);
        sort(nod1->keys.begin(), nod1->keys.end());
        root->keys.push_back(nod1->keys[2]);
        int val = nod1->keys.back();
        nod1->keys.pop_back();
        nod1->keys.pop_back();
        nod1->keys.push_back(val)
        root->copil.push_back(nod1);
        nod1->parinte = root;
    }

    nod* parinte = nod1->parinte;
    int index = get_index(parinte, nod1);

    parinte->keys.insert(parinte->keys.begin() + index, key);

    nod* stanga = new nod();
    stanga->keys.push_back(nod1->keys[0]);
    stanga->copil.push_back(nod1->copil[0]);
    stanga->copil.push_back(nod1->copil[1]);
    stanga->parinte = parinte;

    nod* dreapta = new nod();
    dreapta->keys.push_back(nod1->keys[2]);
    dreapta->copil.push_back(nod1->copil[2]);
    dreapta->copil.push_back(nod1->copil[3]);
    dreapta->parinte = parinte;

    parinte->copil.erase(parinte->copil.begin() + index);
    parinte->copil.insert(parinte->copil.begin() + index, dreapta);
    parinte->copil.insert(parinte->copil.begin() + index, stanga);

    //delete nod1;

    if (parinte->plin()) {
        split(parinte, parinte->keys[1]);
    }
}

void insert(nod* nod1, int key) {
    nod* frunza = cauta_pozitie(nod1, key);

    if (!frunza->plin()) {
        frunza->keys.push_back(key);
        sort(frunza->keys.begin(), frunza->keys.end());
    } else {
        split(frunza, key);
    }
}

void stergeNod(nod* nod1,int key)
{
    return;
}

bool aparitie(nod* nod1, int key) {
    nod* frunza = cauta_pozitie(nod1, key);

    for (int i = 0; i < frunza->keys.size(); i++) {
        if (key == frunza->keys[i]) {
            return true;
        }
    }
    return false;
}


int main()
{

    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    //insert(root, 50);
    //insert(root, 25);
    //nodNou(root->copil[0], 50);
    //cout<<aparitie(root, 300);
   //cout<<root->copil[0]->keys[0];
    cout<<root->keys[0];
    cout<<root->keys[1];
    cout<<root->keys[2];
//    cout<<root->keys[1];
//    cout<<root->keys[2];
//    cout<<root->keys[3];
}

*/
///TODO:
///insert
///delete
///verifica aparitie
///afisare
