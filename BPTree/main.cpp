#include "BpTree.h"
#include <iostream>


int main() {

  char inp;

  BpTree t(3);
  do {
    int c;
    cout << "\tMENU" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Find" << endl;
    cout << "3. Print Keys" << endl;
    cout << "4. Print Values" << endl;
    cout << "5. Delete Key" << endl;
    cout << "Enter: ";
    cin >> c;
    switch (c) {
    case 1: {
      int k;
      string s;
      cout << "\nEnter key : ";
      cin >> k;
      cout << "Enter value : ";
      cin >> s;
      t.insert(k, s);
      break;
    }
    case 2: {
      int x;
      cout <<"\nEnter key to be found : ";
      cin >> x;
      cout << t.find(x);
      break;
    }
    case 3: {
      t.printKeys();
      break;
    }
    case 4: {
      t.printValues();
      break;
    }
    case 5: {
      int x;
      cout <<"\nEnter key to be deleted : ";
      cin >> x;
      t.remove(x);
      break;
    }
    default:
      break;
    }
    cout << "\nDo you want to continue ?(y/Y)";
    cin >> inp;
  } while (inp == 'y' || inp == 'Y');

  /*
  t.insert(2, "a");

  t.insert(11, "c");

  t.insert(13, "h");

  t.insert(21, "i");

  t.insert(64, "k");

  t.insert(4, "b");
  t.insert(23, "j");
  t.insert(9, "e");
  t.insert(19, "f");
  t.insert(5, "d");
  t.insert(10, "g");
  t.insert(6, "g");
  t.insert(7, "g");
  t.insert(60, "g");
  t.insert(71, "g");
  t.insert(93, "g");
  t.insert(77, "g");

  t.printKeys();
  t.remove(71);
  t.printKeys();
  t.remove(60);
  t.printKeys();
  t.remove(4);
  t.printKeys();
  t.remove(7);
  t.printKeys();
  t.remove(5);
  t.printKeys();
  t.remove(64);
  t.printKeys();

  */

  return 0;
}
