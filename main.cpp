#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

class Container
{
public:

    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;


    virtual void print() = 0;


    virtual ~Container() { };
};

class LinkedList: public Container{
    private:
    Node* head;
    public:
    LinkedList(){
        this->head = NULL;
    }
    ~LinkedList(){

    }
    void insert(int value){
        Node *nd = new Node;
        nd->data = value;
        nd->next = NULL;
        if(this->head == NULL)
            this->head = nd;
        else
        {
            Node* current = this->head;
            while(current->next != NULL)
                current = current->next;
            current->next = nd;
        }
    }
    bool exists(int value){
        Node* current = this->head;
        while(current->next != NULL){
            if(current->data == value) return 1;
            current = current->next;
        }
        return 0;
    }
    void remove(int value){
        Node* current = this->head;
        Node* prev;
        if(current->data == value){this->head = current->next; delete current;}
        else{
            while((current->next)->next != NULL){
                if((current->next)->data == value){
                    prev = current->next;
                    current->next = (current->next)->next;
                    delete prev;
                    break;
                }
                current = current->next;
            }
        }
    }
    void print(){
        Node *current = this->head;
        while(current)
        {
            cout << current->data << endl;
            current = current->next;
        }
    }

};

int main()
{
    Container* c = new LinkedList();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);

    cout << "Container after creation:" << endl;
    c->print();

    if(c->exists(25))
        cout << "Search for value 25: found" << endl;

    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    c->remove(25);
    cout << "Container after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}
