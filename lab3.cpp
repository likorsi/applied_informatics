#include <iostream>
#include <algorithm>
#include <sstream>
#include <cassert>

class int_list_t {
private:
    struct node_t {
        int value;
        node_t* prev = nullptr;
        node_t* next = nullptr;
    };
    node_t* first = new node_t;
    node_t* last = new node_t;
    size_t size;

    node_t* find(size_t pos) const {
        node_t* pos_elem;
        if (pos < size / 2)
        {
            pos_elem = last->next;
            size_t i = 0;
            while (i < pos) {
                pos_elem = pos_elem->next;
                i++;
            }
        }
        else
        {
            pos_elem = first;
            size_t i = size;
            while (pos != i) {
                pos_elem = pos_elem->prev;
                i--;
            }
        }
        return pos_elem;
    }

public:
    int_list_t() {
        last->next = first;
        first->prev = last;
        size = 0;
    }; 

    int_list_t(const int_list_t& other) {
        last->next = first;
        first->prev = last;
        size = 0;
        node_t* c = other.last->next;
        size_t i = 0;
        while (i != other.size) {
            push_back(c->value);
            c = c->next;
            i++;
        }
    }; 

    int_list_t(size_t count, int value) {
        last->next = first;
        first->prev = last;
        size = 0;
        for (size_t i = 0; i < count; i++) {
            push_back(value);
        }
    }; 

    ~int_list_t() {
        clear();
        delete first;
        delete last;
    };  

    int_list_t& operator=(const int_list_t& other) {
        if (this == &other)
            return *this;
        else {
            clear();
            for (size_t i = 0; i != other.size; i++) {
                push_back(other[i]);
            }
            return *this;
        }
    }; 

    int& operator[](size_t pos) {
        return find(pos)->value;
    };

    const int operator[](size_t pos) const {
        return find(pos)->value;
    };

    int& back() {
        return first->prev->value;
    }; 

    const int back() const {
        return first->prev->value;
    };

    int& front() {
        return last->next->value;
    };  

    const int front() const {
        return last->next->value;
    }; 

    void clear() {
        while (size != 0) {
            erase(0);
        }
    }; 

    size_t list_size() const {
        return size;
    }; 

    bool empty() const {
        return size == 0;
    }; 

    void insert(size_t pos, int new_val) {
        node_t* pos_elem = find(pos);
        node_t* new_elem = new node_t;
        new_elem->next = pos_elem;
        new_elem->prev = pos_elem->prev;
        pos_elem->prev->next = new_elem;
        pos_elem->prev = new_elem;
        new_elem->value = new_val;
        size++;
    }; 

    void push_front(int new_val) {
        insert(0, new_val);
    };

    void push_back(int new_val) {
        insert(size, new_val);
    }; 

    void erase(size_t pos) {
        node_t* c = find(pos);
        c->next->prev = c->prev;
        c->prev->next = c->next;
        delete c;
        size--;
    }; 

    void pop_front() {
        erase(0);
    }; 

    void pop_back() {
        erase(size - 1);
    };  

    int_list_t splice(size_t start_pos, size_t count) {
        int_list_t list;
        node_t* start_elem = find(start_pos);            
        node_t* end_elem = find(start_pos + count - 1);
        node_t* prev_elem = find(start_pos - 1);
        node_t* next_elem = find(start_pos + count);
        
        list.last->next = start_elem;
        list.first->prev = end_elem;
        list.size += count;
        
        prev_elem->next = next_elem;
        prev_elem->next->prev = next_elem->prev;
        next_elem->prev = prev_elem;
        next_elem->prev->next = prev_elem->next;
        size -= count;
        
        return list;
    }; 

    int_list_t& merge(int_list_t& other) {
        if (other.size != 0) {
            node_t* first_elem = other.last->next;
            node_t* last_elem = other.first->prev;
            first->prev->next = first_elem;
            first_elem->prev->next = last_elem->next;
            last_elem->next->prev = first_elem->prev;
            first_elem->prev = first->prev;
            first->prev = last_elem;
            last_elem->next = first;
            size += other.size;
            other.size = 0;
        }
        return *this;
    }; 

    void reverse() {
        node_t* c = first->prev;
        first->prev->next = last;
        std::swap(first->prev, last->next);
        while(c != last) {
            std::swap(c->next, c->prev);
            c = c->next;
        }
    }; 

    void swap(int_list_t& other) {
        std::swap(this->last, other.last);
        std::swap(this->first, other.first);
        std::swap(size, other.size);
    }; 

    friend std::istream& operator>>(std::istream& stream, int_list_t& list) {
        int val = 0;
        std::string line;
        std::getline(stream, line);
        std::istringstream ss(line);
        while (ss >> val) {
            list.push_back(val);
        }
        return stream;
    }; 

    friend std::ostream& operator<<(std::ostream& stream, const int_list_t& list) {
        size_t i = 0;
        while (i != list.size) {
            stream << list[i] << " ";
            i++;
        }
        stream << "\n";
        return stream;
    }; 

};

int main()
{
    int_list_t l1(5, 1);
    std::cout << "l1: " << l1 << std::endl;
    int_list_t l2(l1);
    std::cout << "l2: " << l2 << std::endl;
    l2.push_back(456);
    std::cout << "push_back(456): " << l2 << std::endl;
    std::cout << "back: " << l2.back() << "\n\n";
    l2.erase(0);
    std::cout << "erase(0): " << l2 << std::endl;
    l2.push_front(20);
    std::cout << "push_front(20): " << l2 << std::endl;
    std::cout << "front: " << l2.front() << "\n\n";
    l2.pop_front();
    std::cout << "pop_front: " << l2 << std::endl;
    l2.pop_back();
    std::cout << "pop_back: " << l2 << std::endl;
    l2.insert(l2.list_size(), 61);
    std::cout << "insert(l2.list_size(), 61): " << l2 << std::endl;
    l2.merge(l1);
    std::cout << "merge: " << l2 << std::endl;
    l2 = l2;
    std::cout << "l2=l2: " << l2 << std::endl;
    l1 = l2;
    std::cout << "l1=l2: " << l1 << std::endl;
    std::cout << "add values to l1: ";
    std::cin >> l1;
    std::cout << std::endl;

    std::cout << "l1: " << l1 << std::endl;

    std::cout << "splice part of l2: " << l2.splice(0, 2) << "l2: " << l2 << std::endl;
    
    l2.reverse();
    std::cout << "reverse: " << l2 << std::endl;
    l2.clear();
    std::cout << "clear l2: " << l2 << std::endl;
    l2.swap(l1);
    std::cout << "l2.swap(l1): " << l2 << std::endl;
    if (l1.empty())
    {
        std::cout << "l1 is empty: " << l1 << std::endl;
    }
    
}