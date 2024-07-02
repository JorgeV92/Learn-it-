#include <iostream>
#include <memory>


struct node {
    int data;  
    std::weak_ptr<node> prev;  // Pointer to the previous node
    std::shared_ptr<node> next;  // Pointer to the next node

    node(int val) : data(val), prev(), next(nullptr) {}
};

// Function to insert a node at the front of the list
void insert_at_front(std::shared_ptr<node>& head, int data) {
    std::shared_ptr<node> new_node = std::make_shared<node>(data);
    new_node->next = head;

    if (head) {
        head->prev = new_node;
    }
    head = new_node;
}

// Function to insert a node after a given node
void insert_after_given_node(std::shared_ptr<node> given, int data) {
    if (!given) return;

    std::shared_ptr<node> new_node = std::make_shared<node>(data);
    new_node->next = given->next;
    given->next = new_node;
    new_node->prev = given;

    if (new_node->next) {
        new_node->next->prev = new_node;
    }
}

// Function to insert a node at the end of the list
void insert_at_end(std::shared_ptr<node>& head, int data) {
    std::shared_ptr<node> new_node = std::make_shared<node>(data);
    if (!head) {
        head = new_node;
        return;
    }

    std::shared_ptr<node> end = head;
    while (end->next) {
        end = end->next;
    }

    end->next = new_node;
    new_node->prev = end;
}

// Function to insert a node before a given node
void insert_before_given_node(std::shared_ptr<node> given, int data) {
    if (!given) return;

    std::shared_ptr<node> new_node = std::make_shared<node>(data);
    new_node->prev = given->prev;
    new_node->next = given;
    given->prev = new_node;

    if (auto prev = new_node->prev.lock()) {
        prev->next = new_node;
    }
}

// Function to delete a given node
void delete_given_node(std::shared_ptr<node>& head, std::shared_ptr<node> given) {
    if (!given) return;

    if (given == head) {
        head = given->next;
    }

    if (auto prev = given->prev.lock()) {
        prev->next = given->next;
    }

    if (given->next) {
        given->next->prev = given->prev;
    }
}

// Function to search for a node with a specific value
void search(const std::shared_ptr<node>& head, int target) {
    std::shared_ptr<node> temp = head;
    int index = 1;
    while (temp) {
        if (temp->data == target) {
            std::cout << "Found the target at node " << index << std::endl;
            return;
        }
        index++;
        temp = temp->next;
    }
    std::cout << "Target not found" << std::endl;
}

// Function to reverse the doubly linked list
void reverse(std::shared_ptr<node>& head) {
    std::shared_ptr<node> temp = nullptr;
    std::shared_ptr<node> current = head;

    while (current) {
        temp = current->prev.lock();
        current->prev = current->next;
        current->next = temp;
        current = current->prev.lock();
    }

    if (temp) {
        head = temp->prev.lock();
    }
}

int main() {
    std::shared_ptr<node> head = nullptr;

    // Example usage of the doubly linked list
    insert_at_front(head, 10);
    insert_at_front(head, 20);
    insert_at_end(head, 30);
    insert_after_given_node(head, 15);
    insert_before_given_node(head->next->next, 25);
    delete_given_node(head, head->next->next);
    search(head, 15);
    reverse(head);

    // Print the reversed list
    std::shared_ptr<node> temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    return 0;
}