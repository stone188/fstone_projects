#ifndef BST_H
#define BST_H
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <deque>

#define MARKER "NULL"
#define MAXROLLBACK 5

using namespace std;

template<class T>
class BST{
	public:
		BST(string fileName);
		~BST();
		
		void insert(T value);
		void deleteTree(TreeNode<T>* node);
		void makeSerializedString(TreeNode<T> *node, ostringstream& serial_stream);
		void serialize();
		void deserialize();
		void snapshot();
		void popSnap();
		void clearSnap();
		void rollback();
		bool remove(int ID);
		T* search(int ID);
		TreeNode<T>* contains(int ID);
		TreeNode<T>* getMax();
		TreeNode<T>* getSuccessor(TreeNode<T>* d);
		
		TreeNode<T>* root;
		
		string fileName;
		deque<string> recovery;
};

template<class T>
BST<T>::BST(string fileName){
	this->fileName = fileName;
	root = NULL;
}

template<class T>
BST<T>::~BST(){
	deleteTree();
	root = NULL;
}

template<class T>
TreeNode<T>* BST<T>::getMax(){
	TreeNode<T>* current = root;
	
	if(root == NULL){
		return NULL;
	}
	
	while(current->right != NULL){
		current = current->right;
	}
	return &(current->key);
}

template<class T>
void BST<T>::insert(T value){
	TreeNode<T>* node = new TreeNode<T>(value);
	
	if(root == NULL){
		root = node;
	}
	
	else{
		TreeNode<T>* current = root;
		TreeNode<T>* parent;
		
		while(true){
			parent = current;
			
			if(value < current->key){
				current = current->left;
				if(current == NULL){
					parent->left = node;
					break;
				}
			}
			
			else{
				current = current->right;
				if(current == NULL){
					parent->right = node;
					break;
				}
			}
			
		}
	}
}

template<class T>
TreeNode<T>* BST<T>::contains(int ID){
	if(root == NULL){
		return NULL;
	}
	
	else{
		TreeNode<T>* current = root;
		
		while(current != NULL || current->key != ID){
			if(current->key > ID){
				current = current->left;
			}
			
			if(current->key < ID){
				current = current->right;
			}
			
			if(current->key == ID){
				return current;
			}
			
			if(current == NULL){
				return NULL;
			}
			
		}
	}
}

template<class T>
T* BST<T>::search(int ID){
	TreeNode<T>* result = contains(ID);
	if(result == NULL){
		return NULL;
	}
	else{
		return &result->key;
	}
}

template<class T>
bool BST<T>::remove(int ID){
	if(root == NULL){
		return false;
	}
	
	else{
		TreeNode<T>* current = root;
		TreeNode<T>* parent = current;
		bool isLeft = true;
		
		while(current->key != ID){
			parent = current;
			
			if(current->key > ID){
				isLeft = true;
				current = current->left;
			}
			
			else{
				isLeft = false;
				current = current->right;
			}
			
			if(current == NULL){
				return false;
			}
		}
		if(current->left == NULL && current->right == NULL){
			if(current == root){
				root = NULL;
			}
			
			else if(isLeft){
				parent->left = NULL;
			}
			
			else{
				parent->right = NULL;
			}
		}
		
		else if(current->right == NULL){
			if(current == root){
				root = current->left;
			}
			
			else if(isLeft){
				parent->left = current->left;
			}
			
			else{
				parent->right = current->left;
			}
		}
		
		else if(current->left == NULL){
			if(current == root){
				root = current->right;
			}
			
			else if(isLeft){
				parent->right = current->right;
			}
			
			else{
				parent->left = current->right;
			}
		}
		
		else{
			TreeNode<T>* successor = getSuccessor(current);
			
			if(current == root){
				root = successor;
			}
			
			else if(isLeft){
				parent->left = successor;
			}
			
			else{
				parent->right = successor;
			}
			successor->left = current->left;
		}
		return true;
	}
}

template<class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d){
	TreeNode<T>* sp = d;
	TreeNode<T>* successor = d;
	TreeNode<T>* current = d->right;
	
	while(current != NULL){
		sp = successor;
		successor = current;
		current = current->left;
	}
	
	if(successor != d->right){
		sp->left = successor->right;
		successor->right = d->right;
	}
	delete(d);
	return successor;
}

template<class T>
void BST<T>::deleteTree(TreeNode<T>* node){
	if(node == NULL){
		return;
	}
	
	deleteTree(node->left);
	deleteTree(node->right);
	delete(node);
}

template<class T>
void BST<T>::makeSerializedString(TreeNode<T> *node, ostringstream& serialStream){
	if(node == NULL) {
        serialStream << MARKER << '\n';
        return;
    }
    makeSerializedString(node->left, serialStream);
    serialStream << node->key.ToString();
    makeSerializedString(node->right, serialStream);
}

template<class T>
void BST<T>::serialize(){
	ofstream outFile (fileName);
    ostringstream outStream;
    makeSerializedString(root, outStream);
    outFile << outStream.str();
	outFile.close();
}

template<class T>
void BST<T>::deserialize(){
	string textLine;
	
    delete root;
    root = NULL;
	
    ifstream inFile(fileName);
    while (getline(inFile, textLine)){
		if(textLine != MARKER){
            insert(T(textLine));
		}
    } 
    inFile.close();
}

template<class T>
void BST<T>::snapshot(){
	if(recovery.size() >= MAXROLLBACK){
		recovery.pop_back();
	}
	
	ostringstream s;
	makeSerializedString(root, s);
	recovery.push_front(s.str());
}

template<class T>
void BST<T>::popSnap(){
	if(!recovery.empty()){
		recovery.pop_front();
	}
}

template<class T>
void BST<T>::rollback(){
	string retrieve;
	
	if(recovery.empty()){
		return;
	}
	
	retrieve = recovery.front();
	ofstream outFile(fileName);
	outFile << retrieve;
	outFile.close();
	
	recovery.pop_front();
	deserialize();
}

#endif