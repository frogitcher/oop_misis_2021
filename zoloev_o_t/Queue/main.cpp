/*
    made by Omar Zoloev
*/

#include <iostream>
#include <string>

struct Node {
    std::string our_string;
    Node* next;
};

class Queue {

private:
    size_t our_size = 0; // размер очереди (сколько всего человек к ней)
    Node* head = nullptr; // голова очереди aka то, куда пушаем
    Node* tail = nullptr; // хвост очереди aka, то, откуда попаем

public:
    Queue() = default;
    Queue(const Queue& some_queue);
    ~Queue() {
        QueueClear();
    }

    bool Empty() {
        if(our_size == 0) {
            return true;
        } else {
            return false;
        }
    }

    int GetSize() {
        return our_size;
    }

    void Push(const std::string& some_string) {
        if(our_size == 0) {
            head = new Node{ some_string, nullptr };
            tail = head;
        } else {
            Node* new_head = new Node{ some_string, nullptr };
            head->next = new_head;
            head = new_head;
        }
        our_size+=1;
    }

    void Pop() {
        if(our_size == 0) {
            throw std::length_error("Queue empty!");
        } else {
                Node* next_tail = tail->next;
                delete tail;
                tail = next_tail;
                if(our_size == 1) {
                    head = nullptr;
                }
            }
        our_size-=1;
    }

    std::string WhoIsLast() {
        if(!Empty()) {
           return head->our_string;
        } else {
            throw std::length_error("Queue empty!");
        }

    }

    std::string WhoIsFirst() {
        if(!Empty()) {
        return tail->our_string;
        } else {
            throw std::length_error("Queue empty!");
        }
    }

    std::string WhoIsN(const int& n) {
        if(n > our_size || Empty()) {
            throw std::length_error("There is no such number in queue!");
        } else {
            int count = 0;
            Node* next_tail = tail->next;
            while(count != n) {
            next_tail = next_tail->next;
            count++;
            }
            return next_tail->our_string;
        }
    }

    void QueueClear() {
        while(our_size != 0) {
            Pop();
        }
    }

    void QueueOut() {
        int cnt = 1;
        Node* new_node = tail;
        while(cnt != our_size + 1) {
            std::cout << cnt << " - " << new_node->our_string << "\n";
            new_node = new_node->next;
            cnt++;
        }
    }

    void operator = ( Queue& some_queue) {
        QueueClear();

        Node* temp_tail = some_queue.tail;

        tail = new Node{ temp_tail->our_string, nullptr };
        head = tail;

        Node* temp_head;

        for(int i = 0; i < some_queue.our_size - 1; ++i) {
            temp_tail = temp_tail->next;
            temp_head = new Node{ temp_tail->our_string, nullptr };
            head->next = temp_head;
            head = temp_head;
        }
        our_size = some_queue.our_size;


    }

};

int main() {

    Queue MyQueue;

    MyQueue.Push("Zolove");//1
    MyQueue.Push("Kostya");//2
    MyQueue.Push("Max");//3
    MyQueue.Push("Uldar");//4
    MyQueue.Push("Egor");//5
    MyQueue.Push("Vanya");//6
    MyQueue.Push("Vlas");//7
    std::string s = MyQueue.WhoIsFirst();
    std::string s1 = MyQueue.WhoIsLast();
    //std::cout << s << " " << s1 << "\n";
    MyQueue.Pop();
    s = MyQueue.WhoIsFirst();
    s1 = MyQueue.WhoIsLast();
    //std::cout << s << " " << s1 << "\n";
    MyQueue.Pop();
    s = MyQueue.WhoIsFirst();
    s1 = MyQueue.WhoIsLast();
    //std::cout << s << " " << s1 << "\n";
    MyQueue.QueueOut();
//    string a[7];
//    memset(a, 0, sizeof(a));
//    std::cout << "-------------------------------------" << "\n";
    Queue MyQueue2;
    MyQueue2.Push("Omar");//1
    MyQueue2.Push("Roma");//2
    std::cout << "--------------------------------------" << "\n";
    //MyQueue2.QueueOut();
    MyQueue2 = MyQueue;
    MyQueue2.QueueOut();
//
//    s = MyQueue2.WhoIsFirst();
//    s1 = MyQueue2.WhoIsLast();
//    std::cout << s << " " << s1 << "\n";
//    MyQueue.Pop();
//    s = MyQueue2.WhoIsFirst();
//    s1 = MyQueue2.WhoIsLast();
//    std::cout << s << " " << s1 << "\n";
//    MyQueue.Pop();
//    s = MyQueue2.WhoIsFirst();
//    s1 = MyQueue2.WhoIsLast();
//    std::cout << s << " " << s1 << "\n";




    return 0;
}
