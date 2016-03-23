// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"


// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false
template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename std::list<T>::const_iterator a_itr = a.begin();
  typename std::list<T>::const_iterator b_itr = b.begin();
  while (a_itr != a.end()) {
    if (*a_itr != *b_itr) return false;
    a_itr++;
    b_itr++;
  }
  return true;
}


// ================================================================================
// This program stress tests the templated MultiLL container class
int main() {


  // The test data (stored in STL lists)
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();


  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
    my_list.add(*itr);
  }
  assert (songs.size() == my_list.size());



  // -------------------
  // iterator tests

  // test the chronological iterator (forwards)
  std::cout << "chronological order" << std::endl;
  std::list<std::string> chrono_order;
  MultiLL<std::string>::iterator itr = my_list.begin_chronological();
  while (itr != my_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(songs,chrono_order));


  // test the sorted order iterator (forwards)
  std::cout << "sorted order" << std::endl;
  std::list<std::string> sorted_order;
  itr = my_list.begin_sorted();
  while (itr != my_list.end_sorted()) {
    std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_songs,sorted_order));


  // test the random order iterator
  std::cout << "random order" << std::endl;
  std::list<std::string> random_order;
  itr = my_list.begin_random();
  for (int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<std::string>::iterator itr2 = random_order.begin();
  for (int i = 0; i < my_list.size(); i++,itr++,itr2++) {
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_songs,random_order_check));



  // test the re-randomization by creating a new random iterator
  std::cout << "random order 2" << std::endl;
  std::list<std::string> random_order2;
  itr = my_list.begin_random();
  for (int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));


  
  // -------------------
  // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  assert (*itr == "hound dog");
  itr = my_list.erase(itr);
  assert (*itr == "poker face");
  assert (my_list.size() == 9);
  std::cout << "erased: hound dog" << std::endl;

  // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 7; i++) { itr++; }
  assert (*itr == "stairway to heaven");
  itr = my_list.erase(itr);
  assert (*itr == "walk like an egyptian");
  assert (my_list.size() == 8);  
  std::cout << "erased: stairway to heaven" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  std::string tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 7);
  assert (!my_list.empty());

  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;



  // ---------------------------
  // ADD YOUR OWN TEST CASES BELOW
  
  // be sure to test:
  //   copy constructor
  //   assignment operator
  //   destructor
  //   all corner cases of erase
  //   decrement operator for the chronological & sorted iterators
  //   pre vs. post increment & decrement operations for iterators
  //   MultiLL containing types other than std::string
  //   anything else that is necessary




  std::cout << " ***  OUTPUT FROM YOUR TEST CASES ***" << std::endl;
cout << "check copy constructer with 1 value" << endl;
 my_list.add("hound dog");
MultiLL<std::string> my_1_list_copy(my_list);

 MultiLL<std::string>::iterator itr_a = my_list.begin_chronological();
  MultiLL<std::string>::iterator itr_b = my_1_list_copy.begin_chronological();
  cout << " comparison of original and copy side by side" << endl;
  while (itr_a != my_list.end_chronological()) {
	  cout << *itr_a << endl;
	  cout << *itr_b << endl;
   assert (*itr_a == *itr_b);
    itr_a++;
    itr_b++;
  }
 
cout << "check copy constructor with all values" << endl;
   
  my_list.add("poker face");
   my_list.add("brown eyed girl");
  my_list.add("let it be");
  my_list.add("walk like an egyptian");
   my_list.add("man in the mirror");
  my_list.add("stairway to heaven");
  my_list.add("dancing in the street");
  my_list.add("every breath you take");
   my_list.add("hotel california");
  
MultiLL<std::string> my_list_copy(my_list);

  MultiLL<std::string>::iterator itr_new = my_list.begin_chronological();
  MultiLL<std::string>::iterator itr_copy = my_list_copy.begin_chronological();
  cout << " comparison of original and copy" << endl;
  while (itr_new != my_list.end_chronological()) {
	
   assert (*itr_new == *itr_copy);
    itr_new++;
    itr_copy++;
  }
cout << "good" << endl;
 
  cout << endl << "size check" << endl;
  itr_new = my_list_copy.begin_chronological();
assert (my_list.size() == my_list_copy.size());
cout << "good" << endl;
  cout << "size check after erasing " << endl;
  cout << "should be different because only erasing one" << endl;
my_list_copy.erase(itr_new);

  cout << "original size with nothing removed " << my_list.size() << endl;
cout << "copy with 1 removed " << my_list_copy.size() << endl;

   // MultiLL<std::string>::iterator itr_new1 = my_list.begin_chronological();
    // MultiLL<std::string>::iterator itr_copy1 = my_list_copy.begin_chronological();
   // while (itr_new1 != my_list.end_chronological()) {
	  // cout << *itr_new1 << endl;
	  
   
    // itr_new1++;
  
  // }
   // while (itr_copy1 != my_list_copy.end_chronological()) {

	  // cout << *itr_copy1 << endl;
   
   
    // itr_copy1++;
  // }

cout << "clear and then checking of size " << endl;
my_list.clear();
my_list_copy.clear();

 cout << "original " << my_list.size() << endl;
cout << "copy " << my_list_copy.size() << endl;

 // MultiLL<std::string>::iterator itr_test1 = my_list_copy.begin_chronological();
 //cout << *my_list_copy.erase(itr_test1) << endl;

// cout << my_list_copy.size() << endl;

 
	cout << "copy constructer worked correctly" << endl;
}
