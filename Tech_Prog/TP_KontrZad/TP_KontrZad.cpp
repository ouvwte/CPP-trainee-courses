/*
Задание: Создать шаблон класса «очередь». Написать программу, демонстрирующую работу с этим шаблоном 
для различных типов параметров шаблона. 
Программа должна содержать меню, позволяющее осуществить проверку всех методов шаблона.
*/

#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& data) {
        Node* newNode = new Node(data);
        if (rear) {
            rear->next = newNode;
        }
        else {
            front = newNode;
        }
        rear = newNode;
        ++size;
    }

    void dequeue() {
        if (!isEmpty()) {
            Node* temp = front;
            front = front->next;
            delete temp;
            --size;
            if (!front) {
                rear = nullptr;
            }
        }
        else {
            std::cout << "Queue is empty!\n";
        }
    }

    T frontElement() const {
        if (!isEmpty()) {
            return front->data;
        }
        throw std::runtime_error("Queue is empty!");
    }

    T rearElement() const {
        if (!isEmpty()) {
            return rear->data;
        }
        throw std::runtime_error("Queue is empty!");
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void display() const {
        Node* current = front;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

void menu() {
    Queue<int> intQueue;
    Queue<std::string> stringQueue;
    int choice;
    int intData;
    std::string strData;

    do {
        std::cout << "1. Enqueue int\n2. Dequeue int\n3. Display int queue\n";
        std::cout << "4. Enqueue string\n5. Dequeue string\n6. Display string queue\n";
        std::cout << "7. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter integer to enqueue: ";
            std::cin >> intData;
            intQueue.enqueue(intData);
            break;
        case 2:
            intQueue.dequeue();
            break;
        case 3:
            intQueue.display();
            break;
        case 4:
            std::cout << "Enter string to enqueue: ";
            std::cin >> strData;
            stringQueue.enqueue(strData);
            break;
        case 5:
            stringQueue.dequeue();
            break;
        case 6:
            stringQueue.display();
            break;
        case 7:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
