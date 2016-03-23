HOMEWORK 5: MULTI LINKED LISTS


NAME:  Jacob Martin


TIME SPEND ON THIS ASSIGNMENT:  20



COLLABORATORS: 
You must do this assignment on your own, as described in the CS2
Academic Integrity Policy.  If you did discuss the problem or error
messages, etc. with anyone, please list their names here.



TESTING & DEBUGGING STRATEGY:
I check the corner case, if the copy is null, check all the values and check erase.
I check add, and the destructor with clear, and multi erases.



ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

default constructor O(1)

copy constructor O(n)

assignment operator O(n)

destructor O(n)

size O(1)

empty O(1)

clear O(n)

add O(n)

erase O(1) 

begin_chronological O(1)

end_chronological O(1)

begin_sorted O(1)

end_sorted O(1)

begin_random O(n^2) 


ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.

When the value of an iterater is changed so that it points to null because what it was pointing at was removed or changed.

An example would be if you didnt set the iterater passed into erase to the return value of the erase function and it becoming null.



EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Did you implement the improvement?
Describe.
it would be your add function because of it sometimes having to iterate all the way to the end to add the new node in the right place.

I did not have time to implement this :(



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
I spent hours with TA's trying to get my custom begin_random() to work and in the end I just changed it to be an array because I could not get it to work.
In the end I couldnt get the last 2 test cases to work. What was I doing wrong?

