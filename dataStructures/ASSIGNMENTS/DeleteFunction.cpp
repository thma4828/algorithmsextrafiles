void deleteAndReplaceMinRight(TreeNode *root, int key){
    TreeNode *newNode;
    TreeNode *temp;
    TreeNode *node2;
    TreeNode *node3;
    if(root != NULL){
        if(root->key == key){
            newNode = root;
            newNode = newNode->right;
            while(newNode->left != NULL){
                newNode = newNode->left;
            }
            newNode->parent->left = NULL;
            newNode->parent = NULL;
            newNode->left = root->left;
            newNode->right = root->right;
            root->right->parent = newNode;
            root->left->parent = newNode;
        }else{
            temp = root;
            bool found = false;
            while(!found){
                if(temp->key < key){
                    temp = temp->right;
                }
                else if(temp->key > key){
                    temp = temp->left;
                }
                else if(temp->key == key){
                    found = true;
                }
            }
            if(root->key < key){
                node2 = temp;
                node2 = node2->right;
                while(node2->left != NULL){
                    node2 = node2->left;
                }
                node3 = node2->parent;
                temp->parent->right = node2;
                node2->parent = temp->parent;
                temp->left->parent = node2;
                temp->right->parent = node2;
                node2->left = temp->left;
                node2->right = temp->right;
                node3->left = NULL;
            }else if(root->key > key){
                node2 = temp;
                node2 = node2->right;
                while(node2->left != NULL){
                    node2 = node2->left;
                }
                node3 = node2->parent;
                temp->parent->left = node2;
                node2->parent = temp->parent;
                temp->left->parent = node2;
                node2->left = temp->left;
                node3->left = NULL;
            }

        }
    }
}
