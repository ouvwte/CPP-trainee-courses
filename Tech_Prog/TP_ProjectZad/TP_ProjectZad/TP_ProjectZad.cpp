/*Задание:
Описать класс, реализующий бинарное дерево, обладающее возможностью добавления новых элементов,
удаления существующих, поиска элемента по ключу, а также последовательного доступа ко всем элементам.
Написать программу, использующую этот класс для представления англо-русского словаря.
Программа должна содержать меню, позволяющее осуществить проверку всех методов класса.
Предусмотреть возможность формирования словаря из файла и с клавиатуры.
*/

#include <iostream>
#include <fstream>
#include <string>

class DictionaryTree {
private:
    struct Node {
        std::string key;
        std::string value;
        Node* left;
        Node* right;
        Node(const std::string& k, const std::string& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const std::string& key, const std::string& value) {
        if (!node) return new Node(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        return node;
    }

    Node* search(Node* node, const std::string& key) const {
        if (!node || node->key == key) return node;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    Node* deleteNode(Node* node, const std::string& key) {
        if (!node) return node;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    Node* minValueNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->key << ": " << node->value << std::endl;
            inorder(node->right);
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    DictionaryTree() : root(nullptr) {}
    ~DictionaryTree() { clear(root); }

    void insert(const std::string& key, const std::string& value) {
        root = insert(root, key, value);
    }

    void search(const std::string& key) const {
        Node* result = search(root, key);
        if (result)
            std::cout << "Found: " << result->key << ": " << result->value << std::endl;
        else
            std::cout << "Not Found" << std::endl;
    }

    void deleteNode(const std::string& key) {
        root = deleteNode(root, key);
    }

    void display() const {
        inorder(root);
    }
};

void menu() {
    DictionaryTree dict;
    int choice;
    std::string key, value, filename;

    do {
        std::cout << "1. Insert\n2. Search\n3. Delete\n4. Display\n5. Load from file\n6. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter value: ";
            std::cin >> value;
            dict.insert(key, value);
            break;
        case 2:
            std::cout << "Enter key to search: ";
            std::cin >> key;
            dict.search(key);
            break;
        case 3:
            std::cout << "Enter key to delete: ";
            std::cin >> key;
            dict.deleteNode(key);
            break;
        case 4:
            dict.display();
            break;
        case 5:
            std::cout << "Enter filename: ";
            std::cin >> filename;
            {
                std::ifstream file(filename);
                if (file.is_open()) {
                    while (file >> key >> value) {
                        dict.insert(key, value);
                    }
                    file.close();
                }
                else {
                    std::cout << "Unable to open file\n";
                }
            }
            break;
        case 6:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}