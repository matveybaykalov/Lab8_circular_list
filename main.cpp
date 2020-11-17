#include <iostream>
#include <string>

template<typename tn>
struct Node{
    Node* next = nullptr;
    Node* prev = nullptr;
    tn value;
};

template<typename tn> //tn тип данных переменной value
struct List{
private:
    Node<tn>* first = nullptr;
    Node<tn>* last = nullptr;
    Node<tn>* FindNode(int n){
        int counter = 0;
        Node<tn> *TempNode = first;
        while (counter != n) {
            TempNode = TempNode->next;
            ++counter;
        }
        return TempNode;
    }
public:
    void push_back(tn value){
        if (first == nullptr){
            auto *node = new Node<tn>;
            node->prev = nullptr;
            node->next = nullptr;
            node->value = value;
            first = node;
            last = node;
        } else {
            auto *node = new Node<tn>;
            node->prev = last;
            node->next = first;
            node->value = value;
            last->next = node;
            last = node;
        }
    }
    void push_forward(tn value){
        if (first == nullptr){
            auto *node = new Node<tn>;
            node->prev = nullptr;
            node->next = nullptr;
            node->value = value;
            first = node;
            last = node;
        } else {
            auto *node = new Node<tn>;
            node->prev = last;
            node->next = first;
            node->value = value;
            first->prev = node;
            first = node;
        }
    }
    unsigned int size(){
        unsigned int counter;
        if (first == nullptr && last == nullptr){
            counter = 0;
        } else counter = 1;
        Node<tn>* iter = first;
        while (iter != last){
            ++counter;
            iter = iter->next;
        }
        return counter;
    }
    void clear(){
        while (last != first){
            last = last->prev;
            delete last->next;
            last->next = first;
        }
        delete last;
        first = nullptr;
        last = nullptr;
    }
    void print(){
        Node<tn>* iter = first;
        while (iter != last){
            std::cout << iter->value << ' ';
            iter = iter->next;
        }
        std::cout << iter->value << std::endl;
    }
    void remove(int n){
        if(n == 0){
            first = first->next;
            delete first->prev;
        } else if(n == size()-1){
            last = last->prev;
            delete last->next;
        } else {
            Node<tn>* TempNode = FindNode(n);
            TempNode->prev->next = TempNode->next;
            TempNode->next->prev = TempNode->prev;
            delete TempNode;
        }
    }
    tn operator [] (int n) {
        return FindNode(n)->value;
    }
};
int main() {
    //Не пишите только так, чтобы элементы былb вне списка, иначе программа сломается :)

    //Блок тестов для проверки раоты программы со строками
    List <std::string> Mylist;
    Mylist.push_back("World");
    Mylist.push_forward("Hello");
    Mylist.push_back("I'm");
    std::string str = Mylist[0];
    std::cout << Mylist.size() << std::endl;
    Mylist.print();
    Mylist.remove(0);
    Mylist.print();
    Mylist.remove(1);
    Mylist.print();
    Mylist.clear();
    std::cout << Mylist.size() << std::endl;

    //Блок тестов проверки раоты программы с целыми значениями
    /*List <int> Mylist;
    Mylist.push_back(2);
    Mylist.push_forward(1);
    Mylist.push_back(3);
    std::cout << Mylist.size() << std::endl;
    int str= Mylist[0];*/
    /*std::cout << str << std::endl;
    Mylist.clear();
    std::cout << Mylist.size() << std::endl;*/

    //Блок для отслеживания работы программы с памятью через диспетчер задач
    /*List<int> Mylist;
    for (int i=0; i<30000000; ++i){
        Mylist.push_back(i);
    }
    for (int i=0; i<30000000-2; ++i){
        Mylist.remove(1);
    }
    Mylist.clear();*/
    return 0;
}