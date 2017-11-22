#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

template<class T>
class TreeNode{
	public:
		TreeNode();
		~TreeNode<T>();
		TreeNode(T k);
		
		TreeNode<T>* left;
		TreeNode<T>* right;
		
		T key;
};

template<class T>
TreeNode<T>::TreeNode(){
	left = NULL;
	right = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T k){
	left = NULL;
	right = NULL;
	key = k;
}

template<class T>
TreeNode<T>::~TreeNode(){
	if(left != NULL){
		left = NULL;
	}
	if(right != NULL){
		right = NULL;
	}
}

#endif