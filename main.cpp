#include <iostream>
#include <string>

template<typename tn>
struct Node{
    Node* next = nullptr;
    Node* prev = nullptr;
    tn value;
};

template<typename tn> //tn тип данных переменной value
class List{
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
    Node<tn>* PushElement (tn value){
        auto *node = new Node<tn>;
        if (first == nullptr){
            first = node;
            last = node;
        } else {
            last->next = node;
            first->prev = node;
        }
        node->value = value;
        node->next = first;
        node->prev = last;
        return node;
    }
public:
    void PushBack(tn value){
        last = PushElement(value);
    }
    void PushForward(tn value){
        first = PushElement(value);
    }
    void PushByIndex(int number, tn value){
        if (number == 0){
            PushForward(value);
        } else if (number == size()-1){
            PushBack(value);
        } else if (number < size()-1){
            int counter = 0;
            Node<tn>* temp = first;
            while (counter != number){
                counter++;
                temp = temp->next;
            }
            auto* node = new Node<tn>;
            node->value = value;
            temp->next->prev = node;
            node->next = temp->next;
            temp->next = node;
            node->prev = temp;
        } else {
            std::cout << "Index out of range" << std::endl;
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
    tn remove(int n){
        tn value;
        if (n == 0){
            last->next = first->next;
            value = first->value;
            delete first;
            first = last->next;
            first->prev = last;
        } else if (n == size()-1){
            first->prev = last->prev;
            value = last->value;
            delete last;
            last = first->prev;
            last->next = first;
        } else {
            Node<tn>* TempNode = FindNode(n);
            TempNode->prev->next = TempNode->next;
            TempNode->next->prev = TempNode->prev;
            value = TempNode->value;
            delete TempNode;
        }
        return value;
    }
    int find(tn value){ //функция find озращает номер элемента который бы передан в неё. В противном случае возращается -1
        int counter = 0;
        Node<tn>* temp = first;
        while (counter != size()-1){
            if (temp->value == value){
                return counter;
            }
            counter++;
            temp = temp->next;
        }
        return -1;
    }
    int FindByAddress(Node<tn>* node){
        int counter = 0;
        bool flag = false;
        Node<tn>* iter = first;
        while (iter != last){
            if (iter == node){
                flag = true;
                break;
            }
            iter = iter->next;
            counter++;
        }
        if (!flag){
            return -1;
        } else {
            return counter;
        }
    }
    void PushByAddress(Node<tn>* node, tn value){
        int position = FindByAddress(node);
        if (position == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            PushByIndex(position, value);
        }
    }
    tn PopByAddress(Node<tn>* node){
        int position = FindByAddress(node);
        if (position == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            return remove(position);
        }
    }
    tn operator [] (int n) {
        return FindNode(n)->value;
    }
};
int main() {
    //Не пишите только так, чтобы элементы был вне списка, иначе программа сломается :)
    //для пользовательского типа нужно будет перегрузить операторы << и ==
    //Блок тестов для проверки раоты программы со строками
    List <std::string> Mylist;
    Mylist.PushBack("World");
    Mylist.PushForward("Hello");
    Mylist.PushBack("Matvey");
    Mylist.PushByIndex(1, "I'm");
    Mylist.PushByIndex(5, "and");
    std::string str = Mylist[0];
    std::cout << Mylist.find("World") << std::endl;
    std::cout << Mylist.find("Worlddfw") << std::endl;
    std::cout << Mylist.size() << std::endl;
    Mylist.print();
    std::cout << Mylist.remove(1) << std::endl;
    Mylist.print();
    std::cout << Mylist.remove(1) << std::endl;
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
