#include <iostream>

using namespace std;

const int nullptr = 0;

struct Node {
    int label;
    int conto;

    Node *left;
    Node *right;

    explicit Node(int n):label(n), conto(0), left(nullptr), right(nullptr) {}
} *root = nullptr;

void Insert(Node *tree, int val) {
    Node *NewNode = new Node(val);

    Node *actual, *prec;
    actual = prec = root;
    while (actual) {
        prec = actual;

        if (val <= actual->label)
            actual = actual->left;
        else
            actual = actual->right;
    }

    if (!root)
        root = NewNode;
    else if (val <= prec->label)
        prec->left = NewNode;
    else
        prec->right = NewNode;
}

int Conto(Node *tree) {
    if (tree == nullptr) return 0;
    int LConto = Conto(tree->left);
    int RConto = Conto(tree->right);

    if (!tree->left && !tree->right) {
        if (tree->label == 0)
            return 2;
        else if (tree->label % 2 == 0)
            return -1;
        else
            return 1;
    } else {
        tree->conto += LConto + RConto;
        return tree->conto;
    }
}

void Print(Node *tree, int K) {
    if (tree == nullptr) return;
    Print(tree->left, K);
    if (tree->conto > K)
        cout << tree->label << endl;
    Print(tree->right, K);
}

int main()  {
    int N, K;
    cin >> N >> K;

    for (int i = 0, tmp; i < N; ++i) {
        cin >> tmp;
        Insert(root, tmp);
    }

    Conto(root);
    Print(root, K);

    return 0;
}
