
#ifndef multi_linked_list_h_
#define multi_linked_list_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.


#include <iostream>
#include <cmath>
#include <string>
#include <cassert>



#include "MersenneTwister.h"


using namespace std;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
    Node() : chrono_next_(NULL), chrono_prev_(NULL), sorted_next_(NULL), sorted_prev_(NULL), random_next_(NULL) {}
    Node(const T& v) : value_(v), chrono_next_(NULL), chrono_prev_(NULL), sorted_next_(NULL), sorted_prev_(NULL), random_next_(NULL) {}

    // REPRESENTATION
    T value_;
    Node<T>* chrono_next_;
    Node<T>* chrono_prev_;
    Node<T>* sorted_next_;
    Node<T>* sorted_prev_;
    Node<T>* random_next_;
};

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
    list_iterator() : ptr_(NULL), Type(NULL) {}
    list_iterator(Node<T>* p, int type) : ptr_(p), Type(type) {}
    list_iterator(list_iterator<T> const& old) : ptr_(old.ptr_), Type(old.Type) {}
    ~list_iterator() {}

    list_iterator<T> & operator=(const list_iterator<T> & old) {
        ptr_ = old.ptr_;
        Type = old.Type;
        return *this; }

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->value_;  }


    // increment & decrement operators
    list_iterator<T> & operator++() {
        if (Type == 1){
            ptr_ = ptr_->chrono_next_;
            return *this;
        }
        if (Type == 2){
            ptr_ = ptr_->sorted_next_;
            return *this;
        }
        if (Type == 3){
            ptr_ = ptr_->random_next_;
            return *this;
        }
    }
    list_iterator<T> operator++(int) {
        //not quite sure what the int does. Can you please explain it to me in the grading?
        if (Type == 1){
            list_iterator<T> temp(*this);
            ptr_ = ptr_->chrono_next_;
            return temp;
        }
        if (Type == 2){
            list_iterator<T> temp(*this);
            ptr_ = ptr_->sorted_next_;
            return temp;
        }

        list_iterator<T> temp(*this);
        ptr_ = ptr_->random_next_;
        return temp;

    }

    list_iterator<T> & operator--() {
        if (Type == 1){
            ptr_ = ptr_->chrono_prev_;
            return *this;
        }
        if (Type == 2){
            ptr_ = ptr_->sorted_prev_;
            return *this;
        }
        if (Type == 3){
            cerr << "error: previous on random?" << endl;
            exit(1);

        }
    }

    list_iterator<T> operator--(int) {
        if (Type == 1){
            list_iterator<T> temp(*this);
            ptr_ = ptr_->chrono_prev_;
            return temp;
        }
        if (Type == 2){
            list_iterator<T> temp(*this);
            ptr_ = ptr_->sorted_prev_;
            return temp;
        }
        if (Type == 3){
            cerr << "error: previous on random(int)?" << endl;
            exit(1);

        }
    }

    friend class MultiLL<T>;

    // Comparions operators are straightforward
    friend bool operator==(const list_iterator<T>& l, const list_iterator<T>& r) {
        return l.ptr_ == r.ptr_; }
    friend bool operator!=(const list_iterator<T>& l, const list_iterator<T>& r) {
        return l.ptr_ != r.ptr_; }

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int Type; //which type of iterator you are using
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class MultiLL {
public:
    MultiLL() : chrono_head_(NULL), chrono_tail_(NULL), sorted_head_(NULL), sorted_tail_(NULL), random_head_(NULL), size_(0) {}
    MultiLL(const MultiLL<T>& old) {
        //initialization of variables
        chrono_head_ = NULL;
        chrono_tail_ = NULL;
        sorted_head_ = NULL;
        sorted_tail_ = NULL;
        random_head_ = NULL;
        size_ = 0;
        this->copy_list(old); }
    ~MultiLL() { this->destroy_list(); }
    MultiLL& operator= (const MultiLL<T>& old);


    int size() const { return size_; }
    bool empty() const { return chrono_head_ == NULL && sorted_head_ == NULL && random_head_ == NULL; }
    void clear() { this->destroy_list(); }


    void add(const T& v);
    typedef list_iterator<T> iterator;
    iterator erase(iterator itr);

    //public iterator functions to return list locations
    iterator begin_chronological() { return iterator(chrono_head_,1); }
    iterator end_chronological() { return iterator(chrono_tail_ -> chrono_next_,1); }
    iterator begin_sorted() { return iterator(sorted_head_,2); }
    iterator end_sorted() { return iterator(sorted_tail_ -> sorted_next_,2); }

    //beging random function which rerandomizes the list every time its called.
    iterator begin_random() {


        MTRand a;

        int randnum;
        //creates array of numbers.
        int* temparray = new int[size_];

        //sets array to go from 1 to 10
        for (int i = 0; i < size_; i++) {
            temparray[i] = i;
        }
        //randomizes array value locations
        int switcher = 0;
        for (int i = 0; i < size_; i++) {
            randnum = a.randInt(size_ - (i+1)) + i;
            switcher = temparray[i];
            temparray[i] = temparray[randnum];
            temparray[randnum] = switcher;
        }

        //setting random chain to go in the order of the array pulling from the random values of sorted.

        random_head_ = sorted_head_;
        iterator temp_itr = iterator(sorted_head_,2);
        iterator final_itr = iterator(random_head_,3);


        for (int i = 0; i < temparray[0]; i++){
            random_head_ = random_head_ -> sorted_next_;

        }
        final_itr.ptr_ = random_head_;


        for (int i = 1; i < size_; i++){

            temp_itr = iterator(sorted_head_,2);
            int index = 0;
            while (index < temparray[i]) {
                temp_itr++;
                index++;
            }

            final_itr.ptr_ -> random_next_ = temp_itr.ptr_;

            if (i < size_ - 1){
                final_itr++;
                final_itr.ptr_ = temp_itr.ptr_;
            }

            else {
                final_itr++;
                final_itr.ptr_ -> random_next_ = random_head_;


            }



        }
        //memory fixing
        delete [] temparray;



        //spent hours with and without ta's trying to get this to work and in the end couldn't get it to work
        //without repeating a random sort twice. So I switched to array



        // for (int i = 0; i != size_; i++) {

        // randnum = a.randInt(size_ - (i+1));
        // if (i == 0){
        // for (int j = 0; j < randnum; j++){
        // temp++;
        // }
        // random_head_ = temp.ptr_ -> random_next_;

        // rand.ptr_ = random_head_;

        // }
        // else {

        // if (temp.ptr_ -> random_next_ ==  temp.ptr_ || temp.ptr_ -> random_next_ == NULL){

        // rand.ptr_ = temp.ptr_;
        // rand.ptr_ -> random_next_ = random_head_;
        // break;
        // }
        // else {
        // //1 or 0?
        // for (int j = 0; j < i; j++){
        // temp++;
        // }
        // rand.ptr_ -> random_next_ = temp.ptr_ -> random_next_;
        // rand++;
        // rand.ptr_ = temp.ptr_;


        // if (size_ > 2){
        // if (temp.ptr_ -> random_next_ == NULL){

        // cout << "what" << endl;
        // cout << (temp.ptr_ -> value_) << endl;
        // temp.ptr_ -> random_next_ = temp.ptr_;

        // }
        // else {
        // if(temp.ptr_ -> random_next_ -> random_next_ == NULL){
        // temp.ptr_ -> random_next_ -> random_next_ = temp.ptr_;
        // }
        // else {
        // temp.ptr_ -> random_next_ = temp.ptr_ -> random_next_ -> random_next_;

        // }


        // }

        // }

        // else {

        // temp.ptr_ -> random_next_ = temp.ptr_;

        // }

        // }

        // }

        // }



        //returning the start of the random list.
        return final_itr;



    }


private:
    void copy_list(MultiLL<T> const & old);
    void destroy_list();

    //REPRESENTATION
    //add specific heads and tails
    Node<T>* chrono_head_;
    Node<T>* chrono_tail_;
    Node<T>* sorted_head_;
    Node<T>* sorted_tail_;
    Node<T>* random_head_;
    int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
// the assignment operator
template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
    if (&old != this) {
        this->destroy_list();
        this->copy_list(old);
    }
    return *this;
}

// the add node function
template <class T>
void MultiLL<T>::add(const T& v) {
    Node<T>* newp = new Node<T>( v );

    // special case:  initially empty list
    if (!chrono_tail_) {
        chrono_head_ = chrono_tail_ = newp;
        sorted_head_ = sorted_tail_ = newp;

    }

    else {
        // normal case:  at least one node already
        newp -> chrono_prev_ = chrono_tail_;
        chrono_tail_ -> chrono_next_ = newp;
        chrono_tail_ = newp;


        iterator additr = begin_sorted();
        while(additr.ptr_ != NULL){
            if ((newp -> value_ < *additr) || (newp -> value_ == *additr)){
                newp -> sorted_next_ = additr.ptr_;
                newp -> sorted_prev_ = additr.ptr_ -> sorted_prev_;
                if (additr.ptr_ != sorted_head_){
                    additr.ptr_ -> sorted_prev_ -> sorted_next_ = newp;
                    additr.ptr_ -> sorted_prev_ = newp;
                }
                else {
                    additr.ptr_ -> sorted_prev_ = newp;
                    sorted_head_ = newp;
                }

                break;
            }
            additr++;
        }
        //finally adding it at the end
        if (additr.ptr_ == NULL){
            sorted_tail_ -> sorted_next_ = newp;
            newp -> sorted_prev_ = sorted_tail_;
            sorted_tail_ = newp;
        }



    }




    ++size_;

    begin_random();
}




//erase function. returns next value
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
    assert(size_ > 0);
    // if (size_ > 0){

    iterator result0(itr.ptr_ -> chrono_next_,1);
    // One node left in the list.
    if (itr.ptr_ == chrono_head_ && chrono_head_ == chrono_tail_) {
        chrono_head_ = chrono_tail_ = NULL;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == chrono_head_) {
        chrono_head_ = chrono_head_ -> chrono_next_;
        chrono_head_ -> chrono_prev_ = NULL;
    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == chrono_tail_) {
        chrono_tail_ = chrono_tail_ -> chrono_prev_;
        chrono_tail_ -> chrono_next_ = NULL;
    }
    // Normal remove
    else {
        itr.ptr_ -> chrono_prev_ -> chrono_next_ = itr.ptr_ -> chrono_next_;
        itr.ptr_ -> chrono_next_ -> chrono_prev_ = itr.ptr_ -> chrono_prev_;
    }

    iterator result1(itr.ptr_ -> sorted_next_,2);
    // One node left in the list.
    if (itr.ptr_ == sorted_head_ && sorted_head_ == sorted_tail_) {
        sorted_head_ = sorted_tail_ = NULL;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == sorted_head_) {
        sorted_head_ = sorted_head_ -> sorted_next_;
        sorted_head_ -> sorted_prev_ = NULL;
    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == sorted_tail_) {
        sorted_tail_ = sorted_tail_ -> sorted_prev_;
        sorted_tail_ -> sorted_next_ = NULL;
    }
    // Normal remove
    else {
        itr.ptr_ -> sorted_prev_ -> sorted_next_ = itr.ptr_ -> sorted_next_;
        itr.ptr_ -> sorted_next_ -> sorted_prev_ = itr.ptr_ -> sorted_prev_;
    }

    iterator result2(itr.ptr_ -> random_next_,3);
    if (itr.Type == 3){
        // One node left in the list.
        if (itr.ptr_ == random_head_ && size_ == 1) {
            random_head_ = NULL;
        }
        // Removing the head in a list with at least two nodes
        else if (itr.ptr_ == random_head_) {
            random_head_ = random_head_ -> random_next_;
        }
        // Normal remove
        else {
            iterator temprandom(result2.ptr_,3);
            while (temprandom.ptr_ -> random_next_ -> random_next_ != result2.ptr_){
                temprandom++;
            }
            itr.ptr_ = temprandom.ptr_ -> random_next_;
            itr.ptr_ -> random_next_ = NULL;
            temprandom.ptr_ -> random_next_ = temprandom.ptr_ -> random_next_ -> random_next_;


        }
    }
    delete itr.ptr_;
    --size_;
    if (itr.Type == 1)
        return result0;
    if (itr.Type == 2)
        return result1;

    return result2;
    // }
    // iterator resultwrong(NULL,1);
    // return resultwrong;
}


//copy function
template <class T>
void MultiLL<T>::copy_list(MultiLL<T> const & old) {

    // Handle the special case of an empty list.
    if (old.size_ == 0) {
        chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;
        return;
    }
    else {
        // Create a new head node.
        Node<T>* old_node = old.chrono_head_;
        for (int i = 0; i < old.size_; i++){
            this -> add(old_node -> value_);
            old_node = old_node -> chrono_next_;
        }


    }
}

//cleanup
template <class T>
void MultiLL<T>::destroy_list() {

    Node<T> *p = chrono_head_;
    while(chrono_head_){
        chrono_head_ = chrono_head_-> chrono_next_;
        delete p;
        p = chrono_head_;
    }

    size_ = 0;
    chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;

}


#endif
