// #include "heap.h"
// #include <time.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <iostream>
// #include <functional>

// using namespace std;

// int main()
// {
// srand(time(NULL));

//  Heap<int, greater<int>, greater<int> >* new_heap = new Heap<int, greater<int>, greater<int> >(2, greater<int>(), greater<int>());


// new_heap->push(55);
// new_heap->push(4);
// new_heap->push(25);
// new_heap->push(33);
// new_heap->push(12);
// new_heap->push(77);
// new_heap->push(85);
// new_heap->push(2);
// new_heap->push(8);
// new_heap->push(29);

// 	cout << "MIN HEAP" << endl;
// for (int i=0; i< 10; i++)
// {


// 	cout << i << " number is: " << new_heap->top() << endl;
// 	new_heap->pop();
// }

// // new_heap->push(55);
// // new_heap->push(4);
// // new_heap->push(25);
// // new_heap->push(33);
// // new_heap->push(12);
// new_heap->push(2);
// new_heap->push(2);
// new_heap->push(2);
// new_heap->push(2);
// new_heap->push(2);

// new_heap->updated_key(33, 27);

// cout << "After updating" << endl;
// for (int i=0; i< 4; i++)
// {


// 	cout << i << " number is: " << new_heap->top() << endl;
// 	new_heap->pop();
// }
 
// }