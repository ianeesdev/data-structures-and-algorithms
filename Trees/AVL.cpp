#include<iostream>
#include <queue>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

struct BST {
    int id;
    BST *right = NULL, *left = NULL;
};

BST *root = NULL, *current = NULL;


int height(BST *p) {
    if (p == NULL) {
        return -1;
    }
    int Lheight = height(p -> left);
    int Rheight = height(p -> right);
    return (max(Lheight, Rheight) + 1);
}

int getBF(BST *p) {
    if (p == NULL) {
        return -1;
    }
    else {
        return (height(p -> left) - height(p -> right));
    }
}

BST *rightRotate(BST *p) {
    BST *q = p -> left;
    BST *k = q -> right;

    q -> right = p;
    p -> left = k;
    return q;
}

BST *leftRotate(BST *q) {
    BST *p = q -> right;
    BST *s = p -> left;

    p -> left = q;
    q -> right = s;
    return p;
}

BST *insert(BST *r, BST *current) {
    if (r == NULL) {
        r = current;
        return r;
    }
    else if (current -> id < r -> id) {
        r -> left = insert(r -> left, current);
    }
    else if (current -> id > r -> id) {
        r -> right = insert(r -> right, current);
    }

    int bf = getBF(r);
    if (bf > 1 && current -> id < r -> left -> id) {
        return rightRotate(r);
    }
    else if (bf < -1 && current -> id > r -> right -> id) {
        return leftRotate(r);
    }
    else if (bf > 1 && current -> id > r -> left -> id) {
        r -> left = leftRotate(r -> left);
        return rightRotate(r);
    }
    else if (bf < -1 && current -> id < r -> right -> id) {
        r -> right = rightRotate(r -> right);
        return leftRotate(r);
    }
    return r;
}


void insertion() {
    current = new BST;
    cout << "\nEnter a value: ";
    cin >> current -> id;
    root = insert(root, current);
}

void PreOrder(BST *p) {
    if (p != NULL) {
        cout << p -> id << endl;
        PreOrder(p -> left);
        PreOrder(p -> right);
    }
}


BST *balencingTree(BST *r) {
    int bf = getBF(r);
    if (bf == 2 && (getBF(r -> left) >= 0)) {
        return rightRotate(r);
    }
    else if (bf == -2 && (getBF(r -> right) <= 0)) {
        return leftRotate(r);
    }
    else if (bf == 2 && (getBF(r -> left) == -1)) {
        r -> left = leftRotate(r -> left);
        return rightRotate(r);
    }
    else if (bf == -2 && (getBF(r -> right) == 1)) {
        r -> right = rightRotate(r -> right);
        return leftRotate(r);
    }
    return r;
}


void deletion(int x) {
    BST *p = root, *k = NULL;
    while (p -> id != x) {
        k = p;
        if (x > p -> id) {
            p = p -> right;
        }
        else {
            p = p -> left;
        }
        if (p == NULL) break;
    }
    if (p != NULL) {
        if (p -> right == NULL && p -> left == NULL) {
            if (k -> right == p) {
                delete p;
                k -> right = NULL;
            }
            else {
                delete p;
                k -> left = NULL;
            }
        }
        else if (p -> right == NULL || p -> left == NULL) {
            if (p -> left == NULL) {
                if (k -> right == p && p -> right != NULL) {
                    k -> right = p -> right;
                    delete p;
                }
                else if (k -> left == p && p -> right != NULL) {
                    k -> left = p -> right;
                    delete p;
                }
            }
            else {
                if (k -> left == p && p -> left != NULL) {
                    k -> left = p -> left;
                    delete p;
                }
                else if (k -> right == p && p -> left != NULL) {
                    k -> right = p -> left;
                    delete p;
                }
            }
        }
        else {
            BST *q = p -> right, *d = NULL;
            while (q -> left != NULL) {
                d = q;
                q = q -> left;
            }
            p -> id = q -> id;
            if (q -> right == NULL) {
                if (d != NULL) {
                    delete q;
                    d -> left = NULL;
                }
                else {
                    p -> right = NULL;
                    delete q;
                }
            }
            else if (q -> right != NULL) {
                if (d != NULL) {
                    d -> left = q -> right;
                    delete q;
                }
                else {
                    p -> right = q -> right;
                    delete q;
                }
            }
            else {
                if (p -> right != NULL) {
                    d -> left = NULL;
                    delete q;
                }
                else {
                    p -> right = NULL;
                    delete q;
                }
            }
        }
        root = balencingTree(root);
        root -> left = balencingTree(root -> left);
        root -> right = balencingTree(root -> right);
        cout << "\nSuccessful!\n";
    }
    else cout << "\nValue not found!\n";
}

int main() {
    int x;
    do {
        cout << "\n\t\t\tA V L - T R E E\n";
        cout << "\nEnter 1 to insert \nEnter 2 to delete \nEnter 3 to display "
                "\nEnter 0 to QUIT--> ";
        cin >> x;
        switch (x) {
            case 0:
                break;
            case 1:
                insertion();
                cout << "\nSuccessful!\n";
                break;
            case 2:
                int z;
                cout << endl;
                PreOrder(root);
                cout << endl;
                cout << "\nEnter a value to delete: ";
                cin >> z;
                deletion(z);
                break;
            case 3:
                PreOrder(root);
                break;
        }
    } while(x != 0);
}