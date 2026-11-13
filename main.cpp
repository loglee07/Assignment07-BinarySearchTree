#include <iostream>

// Represents one node in the binary search tree.
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int newValue) {
        value = newValue;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    // Inserts a value into the correct position.
    Node* insertNode(Node* current, int value) {
        if (current == nullptr) {
            return new Node(value);
        }

        if (value < current->value) {
            current->left = insertNode(current->left, value);
        } else if (value > current->value) {
            current->right = insertNode(current->right, value);
        }

        return current;
    }

    // Searches for a value.
    bool searchNode(Node* current, int value) const {
        if (current == nullptr) {
            return false;
        }

        if (value == current->value) {
            return true;
        }

        if (value < current->value) {
            return searchNode(current->left, value);
        }

        return searchNode(current->right, value);
    }

    // Left, current, right.
    void inorder(Node* current) const {
        if (current == nullptr) {
            return;
        }

        inorder(current->left);
        std::cout << current->value << " ";
        inorder(current->right);
    }

    // Current, left, right.
    void preorder(Node* current) const {
        if (current == nullptr) {
            return;
        }

        std::cout << current->value << " ";
        preorder(current->left);
        preorder(current->right);
    }

    // Left, right, current.
    void postorder(Node* current) const {
        if (current == nullptr) {
            return;
        }

        postorder(current->left);
        postorder(current->right);
        std::cout << current->value << " ";
    }

    // Returns the number of levels in the tree.
    int getHeight(Node* current) const {
        if (current == nullptr) {
            return 0;
        }

        int leftHeight = getHeight(current->left);
        int rightHeight = getHeight(current->right);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        }

        return rightHeight + 1;
    }

    // Finds the smallest node in a subtree.
    Node* findSmallest(Node* current) const {
        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    // Removes a value from the tree.
    Node* removeNode(Node* current, int value) {
        if (current == nullptr) {
            return nullptr;
        }

        if (value < current->value) {
            current->left = removeNode(current->left, value);
        } else if (value > current->value) {
            current->right = removeNode(current->right, value);
        } else {
            // Case 1: The node has no children.
            if (current->left == nullptr &&
                current->right == nullptr) {

                delete current;
                return nullptr;
            }

            // Case 2: The node only has a right child.
            if (current->left == nullptr) {
                Node* child = current->right;
                delete current;
                return child;
            }

            // Case 2: The node only has a left child.
            if (current->right == nullptr) {
                Node* child = current->left;
                delete current;
                return child;
            }

            // Case 3: The node has two children.
            Node* replacement = findSmallest(current->right);

            current->value = replacement->value;

            current->right = removeNode(
                current->right,
                replacement->value);
        }

        return current;
    }

    // Deletes all nodes when the tree is destroyed.
    void destroyTree(Node* current) {
        if (current == nullptr) {
            return;
        }

        destroyTree(current->left);
        destroyTree(current->right);
        delete current;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    bool search(int value) const {
        return searchNode(root, value);
    }

    void remove(int value) {
        root = removeNode(root, value);
    }

    void printInorder() const {
        inorder(root);
        std::cout << '\n';
    }

    void printPreorder() const {
        preorder(root);
        std::cout << '\n';
    }

    void printPostorder() const {
        postorder(root);
        std::cout << '\n';
    }

    int height() const {
        return getHeight(root);
    }
};

int main() {
    BinarySearchTree tree;

    // Ten distinct integers.
    int values[] = {
        50, 30, 70, 20, 40,
        60, 80, 35, 45, 65
    };

    for (int value : values) {
        tree.insert(value);
    }

    std::cout << "===== INITIAL TREE =====\n";

    std::cout << "Inorder: ";
    tree.printInorder();

    std::cout << "Preorder: ";
    tree.printPreorder();

    std::cout << "Postorder: ";
    tree.printPostorder();

    std::cout << "Height: "
              << tree.height() << "\n\n";

    std::cout << "===== SEARCH TESTS =====\n";

    std::cout << "Search for 45: "
              << (tree.search(45) ? "Found" : "Not found")
              << '\n';

    std::cout << "Search for 99: "
              << (tree.search(99) ? "Found" : "Not found")
              << "\n\n";

    std::cout << "===== REMOVE LEAF NODE =====\n";
    std::cout << "Removing 20\n";

    tree.remove(20);

    std::cout << "Inorder after removal: ";
    tree.printInorder();
    std::cout << '\n';

    std::cout << "===== REMOVE NODE WITH ONE CHILD =====\n";
    std::cout << "Removing 60\n";

    tree.remove(60);

    std::cout << "Inorder after removal: ";
    tree.printInorder();
    std::cout << '\n';

    std::cout << "===== REMOVE NODE WITH TWO CHILDREN =====\n";
    std::cout << "Removing 50\n";

    tree.remove(50);

    std::cout << "Inorder after removal: ";
    tree.printInorder();

    return 0;
}