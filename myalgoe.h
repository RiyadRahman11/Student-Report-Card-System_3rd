
#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>mp;

struct Node {
    int info, priority;
    Node *link;
};

struct PriorityQueue {
    Node *start;

    PriorityQueue() {
        start = (Node *)malloc(sizeof(Node));
        start->link = NULL;
    }

    void insert(int item, int pr) {
        Node *New = (Node *)malloc(sizeof(Node));
        New->info = item;
        New->priority = pr;
        // pq is empty
        if (start->link == NULL) {
            start->link = New;
            New->link = NULL;
            return;
        }
        // before first node
        if (pr < start->link->priority) {
            New->link = start->link;
            start->link = New;
            return;
        } else {
            Node *ptr;
            ptr = start;
            while (ptr->link != NULL && pr >= ptr->link->priority) {
                ptr = ptr->link;
            }
            New->link = ptr->link;
            ptr->link = New;
        }
    }

    void Delete() {
        if (start->link == NULL) {
            cout << "Underflow" << endl;
            return;
        }

        Node* dlt = start->link;
        start->link = dlt->link;
        free(dlt);
    }
        Node* top() {
        if (start->link == NULL) {
            cout << "Priority Queue is empty" << endl;
            return NULL;
        } else {
            return start->link;
        }
    }
    bool isEmpty()
    {
         return (start->link==NULL);
    }

    void display() {
        Node *ptr = start->link;
        while (ptr != NULL) {
            cout << ptr->info << " " << ptr->priority << endl;
            ptr = ptr->link;
        }
        cout << endl;
    }
    int returnsize()
    {
         if (start->link == NULL) return 0;
        int count = 0;
        Node *ptr = start->link;
        count++;
        ptr = ptr->link;
         return count;
    }
    void clear() {
        Node *ptr = start->link;
        while (ptr != NULL) {
            Node *temp = ptr;
            ptr = ptr->link;
            free(temp);
        }
        start->link = NULL;
    }


};


struct BST {

    struct Node {
        int marks;
        int size;
        Node* left;
        Node* right;

        Node(int marks) : marks(marks), size(1), left(NULL), right(NULL) {}
    };

    Node* root;

    BST() : root(NULL) {}

    Node* createNode(int marks) {
        return new Node(marks);
    }

    void updateSize(Node* node) {
        if (node) {
            node->size = 1;
            if (node->left) node->size += node->left->size;
            if (node->right) node->size += node->right->size;
        }
    }

    Node* insertNode(Node* node, int marks) {
        if (!node) return createNode(marks);
        if (marks < node->marks) {
            node->left = insertNode(node->left, marks);
        } else {
            node->right = insertNode(node->right, marks);
        }
        updateSize(node);
        return node;
    }

    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);
            cout << "Marks: " << node->marks << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node* node) {
        if (node) {
            cout << "Marks: " << node->marks << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node* node) {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            cout << "Marks: " << node->marks << " ";
        }
    }

    int findRank(Node* node, int marks) {
        if (!node) return 0;
        if (mp[marks] >= 1) return mp[marks];
        if (marks < node->marks) {
            return findRank(node->left, marks);
        } else if (marks > node->marks) {
            int leftSize = node->left ? node->left->size : 0;
            int ans = 1 + leftSize + findRank(node->right, marks);
            mp[marks] = ans;
            return ans;
        } else {
            int ans = node->left ? node->left->size : 0;
            mp[marks] = ans;
            return ans;
        }
    }

    void display() {
        if (root) {
            printf("\nTraverse Tree INorder\n");
            inOrder(root);
            printf("\nTraverse Tree PREorder\n");
            preOrder(root);
            printf("\nTraverse Tree POSTorder\n");
            postOrder(root);
        } else {
            printf("\nBST IS NULL\n");
        }
    }

    Node* search(Node*& par, int marks) {
        Node* ptr = root;
        par = NULL;
        while (ptr != NULL && ptr->marks != marks) {
            par = ptr;
            if (marks > ptr->marks)
                ptr = ptr->right;
            else
                ptr = ptr->left;
        }
        return ptr;
    }

    void deleteNode(Node* par, Node* target) {
        if (par == NULL && target == NULL) {
            cout << "UNDERFLOW" << endl;
            return;
        } else if (target->left == NULL && target->right == NULL) {  // No child
            if (par == NULL)
                root = NULL;
            else if (target == par->left)
                par->left = NULL;
            else
                par->right = NULL;
        } else if (target->left != NULL && target->right == NULL) {  // only left child
            if (par == NULL)
                root = target->left;
            else {
                if (target == par->left)
                    par->left = target->left;
                else
                    par->right = target->left;
            }
        } else if (target->right != NULL && target->left == NULL) {  // only right child
            if (par == NULL) {
                root = target->right;
            } else {
                if (target == par->left)
                    par->left = target->right;
                else
                    par->right = target->right;
            }
        } else {  // two children
            Node* parptr = target;
            Node* ptr = target->right;
            while (ptr->left != NULL) {
                parptr = ptr;
                ptr = ptr->left;
            }
            if (parptr != target)
                parptr->left = ptr->right;
            else
                parptr->right = ptr->right;

            target->marks = ptr->marks;
            free(ptr);
        }
    }

    void Binsert(int marks) {
        root = insertNode(root, marks);
    }

    void Bdelete(int marks) {
        Node* par = NULL;
        Node* target = search(par, marks);
        if (target != NULL)
            deleteNode(par, target);
        else
            cout << "Item not found" << endl;
    }
     void clear() {
        root = nullptr;
    }

    int Brank(int marks) {
        int rank = findRank(root, marks) + 1;
        return rank;
    }
};
