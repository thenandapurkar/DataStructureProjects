#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

// the default Item type from class
struct Item {
    int value;
    Item *next;
};

//This is an intermediate function that helps reading in nodes
void addItem(Item*& in, int value)
{
    // if the Head pointer is empty/NULL, then we make it a Item and simply set the value=value
    if (in == NULL)
    {
        in = new Item;
        in->value = value;
        in->next = NULL;          
    } 
    // if the Head Item exists, then 
    // make a temporary new Item, make the beginning of the list the new Item, 
    // make the value of the new Item the input value, point the new Item at the previous beginning Item
    else
    {
        Item* hold = in;
        while(hold->next != NULL) {
           hold = hold->next;

       }

       Item *temp = new Item;
       temp->next = NULL;
       temp->value = value;
       hold->next = temp;
    }
}

void readLists(char* filename, Item*& head1, Item*& head2){
    
    //Read in the file
    ifstream lists(filename);

    //Break them up into string streams
    string one; 
    string two; 
    getline(lists,one);
    getline(lists,two);
    stringstream list1(one);
    stringstream list2(two);

    //Populate first list
    while(!list1.eof()){
        int temp = 0;
        list1 >> temp;
        addItem(head1, temp);
    }

    while(!list2.eof()){
        int temp = 0;
        list2 >> temp;
        addItem(head2, temp);
    }

}

void print_Items(ofstream& filename, Item*& in)
{
    if (in != NULL) 
    {
        // get the value from the Item being pointed to as the beginning and write it to the console
        int value = in->value;
        filename << value << " ";
        // extract the pointer from the beginning Item (as to the address of the next Item) 
        // and have the beginning of the list point to that Item now
        Item *temp = in->next;
        print_Items(filename, temp);
    }
}

void removeConsecutive(Item* head){
    Item* temp = head;
    if(temp==NULL){
        return;
    }
    else{
        if(temp && temp->next){
            if(temp->value == temp->next->value){
                Item* nextOne = (temp->next)->next;
                delete temp->next;
                temp->next = nextOne;
                removeConsecutive(temp);
            }
            else{
                temp=temp->next;
                removeConsecutive(temp);
            }
        }
    }
}

Item* concatenate_h(Item* head1, Item* head2, Item* full){
    if(head1->next == NULL){
        head1->next = head2;
        return full;
    }
    else{
        return concatenate_h(head1->next, head2, full);
    }

}

Item* concatenate(Item* head1, Item* head2){
    if(head1 == NULL){
        return head2;
    }
    else if(head2 == NULL){
        return head1;
    }
    else{
        return concatenate_h(head1, head2, head1);
    }
}


 /* When this function terminates, the following holds:
    - smaller is the pointer to the head of a new singly linked list containing all elements <= pivot.
    - larger is the pointer to the head of a new singly linked list containing all elements > pivot.
    - the linked list "in" no longer exists (should be set to NULL). */    
void split (Item*& in, Item*& smaller, Item*& larger, int pivot)
{
    if (in != NULL) 
    { 
        Item *temp;
        temp = in->next;
//        int testnum = in->value;
        if ((in->value) > pivot) { 
//            add_Item(larger, testnum); 
            in->next = larger;
            larger = in;
        }
        else { 
//            add_Item(smaller, testnum);
            in->next = smaller;
            smaller = in;
        }

        in = temp;
        split(in, smaller, larger, pivot);
    }
}

int main(int argc, char* argv[])
{
    Item *in1 = NULL;
    Item *in2 = NULL;

    readLists(argv[1], in1, in2);
    //print_Items(in1);

    removeConsecutive(in1);
    concatenate(in1, in2);

    ofstream ofile(argv[2]);
    print_Items(ofile, in1);
   

}