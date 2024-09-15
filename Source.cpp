#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

template <typename T>
class Node {
public:
	T data;
	std::unique_ptr<Node<T>> next;

	Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
	std::unique_ptr<Node<T>> head;

public:
	LinkedList() : head(nullptr) {}

	void push_front(const T& value) {
		auto newNode = std::make_unique<Node<T>>(value);
		newNode->next = std::move(head);
		head = std::move(newNode);
	}

	void push_back(const T& value) {
		auto newNode = std::make_unique<Node<T>>(value);
		if (is_empty()) {
			head = std::move(newNode);
		}
		else {
			Node<T>* current = head.get();
			while (current->next) {
				current = current->next.get();
			}
			current->next = std::move(newNode);
		}
	}

	void pop_front() {
		if (!is_empty()) {
			head = std::move(head->next);
		}
	}

    
    void pop_back() {
        if (is_empty()) return;

        if (!head->next) {
            head.reset(); 
            return;
        }

        Node<T>* current = head.get();
        while (current->next && current->next->next) {
            current = current->next.get();
        }
        current->next.reset(); 
    }

    
    Node<T>* find(const T& value) {
        Node<T>* current = head.get();
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next.get();
        }
        return nullptr; 
    }

   
    void remove(const T& value) {
        if (is_empty()) return;

        if (head->data == value) {
            pop_front();
            return;
        }

        Node<T>* current = head.get();
        while (current->next) {
            if (current->next->data == value) {
                current->next = std::move(current->next->next);
                return;
            }
            current = current->next.get();
        }
    }

    
    void print() const {
        Node<T>* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    
    bool is_empty() const {
        return head == nullptr;
    }
};

int main() {
    LinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    list.print();

    list.pop_front();
    list.print(); 

    list.pop_back();
    list.print();

    list.push_back(3);
    list.push_back(2);
    list.print();

    list.remove(3);
    list.print(); 

    if (list.find(1)) {
        std::cout << "1 is found in the list." << std::endl;
    }
    else {
        std::cout << "1 is not found in the list." << std::endl;
    }

    return 0;
};