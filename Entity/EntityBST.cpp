#include "EntityBST.h"

EntityBST::EntityBST() {
	this->root = NULL;
	treeSize = 0;
}

EntityBST::~EntityBST() {
	delete this->root;
}

int EntityBST::size() {
	return treeSize;
}

void EntityBST::insert(EntityNode* node) {
	if (this->root == NULL) {
		root = node;
		treeSize++;
		return; 
	}
	
	else {
		EntityNode* temp = root;
		while (temp != NULL)
		{
			//found equal, duplicate
			if (node->name == temp->name) {
				delete node;
				std::cerr << "Attemp to insert duplicate key" << temp->name << std::endl;
				return;
			}

			//check left subtree
			else if (node->name < temp->name){
				if (temp->left) {
					temp = temp->left;
				}else {
					temp->left = node;
					node->parent = temp; //set parent
					treeSize++;
					return;}
			}

			//check right subtree
			else {
				if (temp->right) {
					temp = temp->right;
				} else {
					temp->right = node;
					node->parent = temp; //set parent
					treeSize++;
					return;}
			}


		} //end while
		 
	} //end else
}

void EntityBST::remove(EntityNode* node) {
	if (this->root == NULL) {
		std::cerr << "Attempt to remove in an empty tree!" << std::endl;
		return;
	}

	else if ( this->root->name == node->name)
	{
		EntityNode* succ = successor(root); //find its successor
		if (!succ) {
			if (root->left)
				root = root->left;
			else
				root = NULL;
		}

		else {
			if (succ->parent) {
				if (succ->right) {
					if (succ == succ->parent->left)
						succ->parent->left = succ->right;
					else if (succ == succ->parent->right)
						succ->parent->right = succ->right;
				}
				else {
					if (succ == succ->parent->left)
						succ->parent->left = NULL;
					else if (succ == succ->parent->right)
						succ->parent->right = NULL;
				}
			}

			succ->left = root->left;
			succ->right = root->right;
			this->root = succ;
		}

		delete node;
	}

	else {
		EntityNode* temp = root;
		while (temp != NULL)
		{
			//found equal, duplicate
			if (node->name == temp->name) {
				EntityNode* succ = successor(temp); //find its successor
				if (!succ) { //if successor does not exist
					if (node->parent)
					{
						if (node == node->parent->left) {
							node->parent->left = NULL;
						}
						else {
							node->parent->right = NULL;
						}
					}
					delete node;
					treeSize--;
					return;
				}
				if (succ->parent) {
					if (succ->right) {
						if (succ == succ->parent->left)
							succ->parent->left = succ->right;
						else if (succ == succ->parent->right)
							succ->parent->right = succ->right;
					}
					else {
						if (succ == succ->parent->left)
							succ->parent->left = NULL;
						else if (succ == succ->parent->right)
							succ->parent->right = NULL;
					}
				}

				if (node->parent) {
					succ->parent = node->parent;
					if (node == node->parent->left)
						node->parent->left = succ;
					else if (node == node->parent->right)
						node->parent->right = succ;
				}
				succ->left = node->left;
				succ->right = node->right;
				treeSize--;
				delete node;
				return;
			}

			//check left subtree
			else if (node->name < temp->name) {
				if (temp->left) {
					temp = temp->left;
				}
				else {
					return;
				}
			}

			//check right subtree
			else {
				if (temp->right) {
					temp = temp->right;
				}
				else{
					return;
				}
			}


		} //end while
		std::cerr << "Warning: Nothing was removed, request for removing non-existent name" << std::endl;
		return;
	} //end else
}

void EntityBST::remove(std::string removeID) {
	remove(find(removeID));
}

EntityNode* EntityBST::find(std::string findID) {
	if (this->root == NULL) {
		std::cerr << "Tree is empty!" << std::endl;
		return NULL;
	}

	else {
		EntityNode* temp = root;
		while (temp != NULL)
		{
			//found equal, return the node
			if ( findID == temp->name) {
				return temp;
			}

			//check left subtree
			else if ( findID < temp->name) {
				if (temp->left) {
					temp = temp->left;
				}
				else {
					return NULL;
				}
			}

			//check right subtree
			else {
				if (temp->right) {
					temp = temp->right;
				}
				else{
					return NULL;
				}
			}


		} //end while
		std::cerr << "ID not found in tree." << std::endl;
		return NULL;
	} //end else
}


EntityNode* EntityBST::successor(EntityNode* curr) {
	if (!curr->right) {
		return NULL;
	}
	else
		curr = curr->right;
	
	while (curr != NULL)
	{
		if (curr->left) {
			curr = curr->left;
		}
		else
			return curr;
	}
}

void EntityBST::printAll(EntityNode* node) {
	if (node->left)
		printAll(node->left);

	std::cout << node->name << " "; 

	if (node->right)
		printAll(node->right);
}

