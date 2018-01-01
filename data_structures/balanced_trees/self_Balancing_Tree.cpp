/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */

int getHeight(node* root){
    if(root==NULL)  return -1;
    else return root->ht;
}

int updateHeight(node *root){
    if(root==NULL){
        return -1;
    }
    else{
        return(1 + max(getHeight(root->left), getHeight(root->right)));
    }
}

int getBalanceFactor(node* root){
    if(root==NULL){
        return 0;
    }
    else    return (getHeight(root->left) - getHeight(root->right));
}

// node* rotateLeft(node *root){
//     if(getBalanceFactor(root->left) == 1){
//         node* newRoot = root->left;
//         root->left = newRoot->right;
//         root->ht = updateHeight(root);
        
//         newRoot->right = root;
//         newRoot->ht = updateHeight(newRoot);
//         return newRoot;
//     }
//     else if(getBalanceFactor(root->right) == -1){
//         node* newNode = root->left;
//         root->left = newNode->right;
//         newNode->right = (root->left)->left;
//         newNode->ht = updateHeight(newNode);
//         (root->left)->left = newNode;
//         (root->left)->ht = updateHeight(root->left);
//         root->ht = updateHeight(root);
//         return rotateLeft(root);
//     }
//     return root;
// }

// node* rotateRight(node* root){
//     if(getBalanceFactor(root->right) == -1){
//         node* newRoot = root->right;
//         root->right = newRoot->left;
//         root->ht = updateHeight(root);
        
//         newRoot->left = root;
//         newRoot->ht = updateHeight(newRoot);
//         return newRoot;
//     }
//     else if(getBalanceFactor(root->right) == 1){
//         node* newNode = root->right;
//         root->right = newNode->left;
        
//         newNode->left = (root->right)->right;
//         newNode->ht = updateHeight(newNode);
        
//         (root->right)->right = newNode;
//         (root->right)->ht = updateHeight(root->right);
//         root->ht = updateHeight(root);
        
//         return rotateRight(root);
//     }
//     return root;
// }

node* rotateL(node* root){
    node* newRoot = root->right;
    root->right = newRoot->left;
    root->ht = updateHeight(root);
    
    newRoot->left = root;
    newRoot->ht = updateHeight(newRoot);
    
    return newRoot;
}

node* rotateR(node* root){
    node* newRoot = root->left;
    root->left = newRoot->right;
    root->ht = updateHeight(root);
    
    newRoot->right = root;
    newRoot->ht = updateHeight(newRoot);
    
    return newRoot;
}
node* insert(node* root, int val){
   if(root==NULL){
        node* newNode = new node;
        newNode->val = val;
        newNode->ht = updateHeight(newNode);
        return newNode;
    }
    if (val <= root->val){
        root->left = insert(root->left, val);
    }
    else{
        root->right = insert(root->right, val);
    }
    
    int balanceFactor = getBalanceFactor(root);
    
    if(balanceFactor > 1){
        //root = rotateLeft(root);
        if(getBalanceFactor(root->left)==1){
            root = rotateR(root);
        }
        else{
            root->left = rotateL(root->left);
            root = rotateR(root);
        }
    }
    else if(balanceFactor < -1){
        //root = rotateRight(root);
        if(getBalanceFactor(root->right)==-1){
            root = rotateL(root);
        }
        else{
            root->right = rotateR(root->right);
            root = rotateL(root);
        }
    }
    else{
        root->ht = updateHeight(root);
    }
    return root;
}
