#ifndef MERGESORT_H
#define MERGESORT_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;



template<class T, class Comparator>
void mergeSort(vector<T>& input, Comparator comp);
template<class T, class Comparator>
void mergeSort_h(vector<T>& input, int beg, int end, Comparator comp);
template<class T, class Comparator>
void merge(vector<T>& input, int s1, int e1, int s2, int e2, Comparator comp);  





template<class T, class Comparator>
void mergeSort(vector<T>& input, Comparator comp){
  mergeSort_h(input, 0, input.size()-1, comp);
}

template<class T, class Comparator>
void mergeSort_h(vector<T>& input, int start, int complete, Comparator comp){
  int midpoint;
  if(start < complete){
    //find midpoint to begin
    midpoint = (start+complete)/2;
    //recurse
    mergeSort_h(input, start, midpoint, comp);
    mergeSort_h(input, midpoint+1, complete, comp);
    merge(input, start, midpoint, midpoint+1, complete, comp);
  }
}
template<class T, class Comparator>
void merge(vector<T>& input, int s1, 
                 int e1, int s2, int e2, Comparator comp){
  int offset = s1;
  vector<T> temp;

  while(s1<=e1 && s2<=e2){
    if(comp(input[s1],input[s2])){
      temp.push_back(input[s1]);
      s1++;
    }
    else{
      temp.push_back(input[s2]);
      s2++;
    }
  }
  if(s1>e1){
    while(s2<=e2){
    temp.push_back(input[s2]);  
    s2++;
    }
  }
  else{
    while(s1<=e1){
    temp.push_back(input[s1]);  
    s1++;
    }
  }
  for(int i=0; i<temp.size(); i++){
    //we know that temp will be all elements from s1->e2
    //so we offset by s1 and insert to input
    input[offset+i] = temp[i];
  }
}
#endif