/*
  Raúl Negrón
  801-13-4680
  CCOM3034 - Fall 2014

  dequeClient.cpp
  
*/

#include "deque.cpp"
#include <iostream>

using namespace std;

int main() {


  cout << "\n\n\t\tWelcome! Let's test our DEQUE class!" << endl;
  cout << "\t\tNOTE: empty = 1, not empty = 0!\n" << endl << endl;
  Deque test;

  cout << "It should be empty! Let's check: " << test.empty() << endl;

  cout << "Let's add some elements. Adding 9 to the front." << endl;
  test.push_front(9);

  cout << "Now let's add 6 to the front, too." << endl;
  test.push_front(6);

  cout << "It should now be '6 9', right? Let's see: ";
  test.print();

  cout << "Obviously, it's no longer empty: " << test.empty() << endl << endl;

  cout << "Pushing 11 to the back." << endl;
  test.push_back(11);

  cout << "Pushing 8 to the front." << endl;
  test.push_front(8);

  cout << "Let's see how the deque looks like now!: ";
  test.print();

  cout << "Here is the last element: ";
  cout << test.getBack() << endl << endl;

  cout << "Let's delete 3 elements from the front.";
  test.pop_front(); test.pop_front(); test.pop_front();
  cout << endl;

  cout << "How's that deque looking?: ";
  test.print(); cout << endl;

  cout << "Let's call pop_back() to remove that last one.";
  test.pop_back(); cout << endl;

  cout << "What happens if we try to getFront() now?: ";
  test.getFront(); cout << endl;

  cout << "Cool! That was an error message. Adding 1 to the front, 2 to"
       << " the front then 3 to the back.";
  test.push_front(1); test.push_front(2); test.push_back(3);

  cout << endl << "Let's call getBack to get that '3'!: ";
  cout << test.getBack() << endl << endl;

  cout << "And finally, let's print out '213'!!: ";
  test.print(); cout << endl;

  return 0;
}
