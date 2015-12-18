#include <iostream>
#include <stdio.h>

/*
有一些bug，删除根节点会出现一点错误，
导致节点丢失，暂时没想到解决的办法。。
*/
using namespace std;
template <class T>
#define LEFT 0
#define RIGHT 1
//构造函数生成节点
class BinaryNode {
public:
    BinaryNode<T> *left;
    BinaryNode<T> *right;
    BinaryNode<T> *parent;
    int pos;//默认在父节点的左子树
    T key;
    int nums;
    BinaryNode(T _key) {
        left=NULL;
        right=NULL;
        parent=NULL;
        key=_key;
        nums=1;
        pos=LEFT;
    }
    //连接另一个树
    BinaryNode(BinaryNode<T>*left,BinaryNode<T>*right,BinaryNode<T>*parent,T _key) {
        left=NULL;
        right=NULL;
        parent=NULL;
        key=_key;
        nums=1;
        pos=LEFT;
    }
};
//insert
template<class T>
void Insert(BinaryNode<T> *&root,T data,BinaryNode<T> * parent=NULL,int pos=LEFT) {
    BinaryNode<T>* binaryNode= new BinaryNode<T>(data);
    if(root==NULL) {
        binaryNode->parent=parent;
        binaryNode->pos=pos;
        root=binaryNode;
        return;
    }
    if(data>root->key) {
        Insert(root->right,data,root,RIGHT);
    } else if(data<root->key) {
        Insert(root->left,data,root,LEFT);
    } else {
        root->nums++;
        delete binaryNode;
    }
}
//print tree
template<class T>
void PrintTree(BinaryNode<T>* binaryNode) {
    if(binaryNode==NULL)
        return ;
    PrintTree(binaryNode->left);
    if(binaryNode->parent==NULL)
        printf("root:\n");
    printf("Num:%d Cot:%d\n",binaryNode->key,binaryNode->nums);
    PrintTree(binaryNode->right);
}
//print binaryNode
template<class T>
void PrintBinaryNode(BinaryNode<T>* binaryNode) {
    if(binaryNode==NULL) {
        printf("Error:binaryNode is NULL!\n");
        return ;
    }
    printf("Num:%d Cot:%d\n",binaryNode->key,binaryNode->nums);
}
//search
template<class T>
BinaryNode<T>* SearchElement(BinaryNode<T> *&binaryNode,T data) {
    if(binaryNode==NULL) {
        printf("No found!\n");
        return NULL;
    }
    if(binaryNode->key==data) {
            printf("Found!\n");
        return binaryNode;
    } else if(data<binaryNode->key) {
        return SearchElement(binaryNode->left,data);
    } else {
        return SearchElement(binaryNode->right,data);
    }
}
//delete binartNode
template<class T>
void Delete(BinaryNode<T>* &root,T data) {
    BinaryNode<T>* binaryNode;
    binaryNode=SearchElement(root,data);
    if(binaryNode==NULL) {
        printf("No found!\n");
        return ;
    }
    BinaryNode<T>* parent=binaryNode->parent;
    if(parent==NULL&&binaryNode->left==NULL&&binaryNode->right==NULL){
        root=NULL;
        delete binaryNode;
        return ;
    }
//    if(parent==NULL){
////        binaryNode->right->left=binaryNode->left;
////        binaryNode->right->parent=NULL;
////        binaryNode->left->parent=binaryNode->right;
////        root=binaryNode->right;
//BinaryNode<T>* maxBinaryNode=MaxBinaryNode(binaryNode->left);
//if(maxBinaryNode==NULL){
//
//}
//maxBinaryNode->left=binaryNode->left;
//maxBinaryNode->right=binaryNode->right;
//maxBinaryNode->parent=NULL;
//maxBinaryNode
//Delete(root,maxBinaryNode);
//        return ;
//    }
    if(binaryNode->left==NULL&&binaryNode->right==NULL) {
            if(binaryNode->pos){
                parent->right=NULL;
            }else{
                parent->left=NULL;
            }
        delete binaryNode;
    }else if(binaryNode->left==NULL&&binaryNode->right!=NULL){
        if(binaryNode->pos){
                parent->right=binaryNode->right;
            }else{
                parent->left=binaryNode->right;
            }
            binaryNode->right->parent=parent;
            delete binaryNode;
    }else if(binaryNode->left!=NULL&&binaryNode->right==NULL){
        if(binaryNode->pos){
                parent->right=binaryNode->left;
            }else{
                parent->left=binaryNode->left;
            }
            binaryNode->left->parent=parent;
            binaryNode->left->pos=RIGHT;
            delete binaryNode;
    }else{
        if(binaryNode->pos){
                parent->right=binaryNode->right;
                binaryNode->right->left=binaryNode->left;
                binaryNode->right->parent=parent;
                binaryNode->left->parent=binaryNode->right;
            }else{
                parent->left=binaryNode->left;
                binaryNode->left->right=binaryNode->right;
                binaryNode->right->parent=binaryNode->left;
                binaryNode->left->parent=parent;
            }
            delete binaryNode;
    }
}

template <class T>
BinaryNode<T>* MaxBinaryNode(BinaryNode<T>* root) {
    if(root==NULL) {
        printf("No MaxNode!\n");
        return NULL;
    }
    if(root->right==NULL) {
        return root;
    }
    return MaxBinaryNode(root->right);
}

int main() {
    BinaryNode<int>* binaryNode=NULL;
    BinaryNode<int>* root=NULL;
    Insert(root,6);
    Insert(root,10);
    Insert(root,7);
    Insert(root,11);
    Insert(root,5);

    PrintTree(root);
//    puts("");
//    binaryNode=SearchElement(root,5);
//    PrintBinaryNode(binaryNode);
//    binaryNode=MaxBinaryNode(root);
//    printf("%d\n",binaryNode->key);
    Delete(root,10);
//    Delete(root,6);
//    binaryNode=SearchElement(root,5);
//    PrintBinaryNode(binaryNode);
PrintTree(root);
    return 0;
}
