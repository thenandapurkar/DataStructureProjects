#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  //insert an item at the tail
  list->insert(1, 4);

  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  if (list->get(1) == 4) {
    cout << "SUCCESS: 4 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 4 is not at the 1st index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  //insert an item in the middle
  list->insert(1, 76);

  if (list->size() == 3) {
    cout << "SUCCESS: List has size 2 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  if (list->get(1) == 76 && list->get(2) == 4) {
    cout << "SUCCESS: Successfully inserted in between two numbers." << endl;
  } else {
    cout << "FAIL: 76 is not at the 1st index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  //remove from the middle
  list->remove(1);

  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after one deletion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one deletion.";
    cout << endl;
  }

  if (list->get(1) == 4) {
    cout << "SUCCESS: Successfully removed from in between two numbers." << endl;
  } else {
    cout << "FAIL: 4 is not at the 1st index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

//remove from the front
  list->remove(0);

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 2 after one deletion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one deletion.";
    cout << endl;
  }

  if (list->get(0) == 4) {
    cout << "SUCCESS: Successfully removed from the front." << endl;
  } else {
    cout << "FAIL: 4 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  //remove from only
  list->remove(0);

  if (list->size() == 0) {
    cout << "SUCCESS: List has no elements." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one deletion.";
    cout << endl;
  }

  // Clean up memory.
  delete list;
}
