
// modified by mashhadi on 14th feb to add an alternative op<<
/*
  Modified and implimented by Tyler A. Moore

*/
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int level{SkipL.maxLevel - 1}; level >= 0; level--) {

    Out << "Level: " + to_string(level);
    Out << " -- ";
    if (SkipL.iNT_MIN[level] != nullptr) {
      SNode *Curr = SkipL.iNT_MIN[level];

      while (Curr != nullptr) {
        Out << to_string(Curr->value) + ", ";
        if (Curr == SkipL.tail) {
          Out << "<-- Tail";
        }
        Curr = Curr->forward;
      }
    }
    Out << "\n";
  }

  return Out;
}

/*
  // This was previously provided
// I had to change it from above.

  for (int Index = SkipL.Depth - 1; Index >= 0; Index--) {
    Out << "Level: " + to_string(Index) + " -- ";
    SkipList::SNode* Curr = SkipL.FrontGuards[Index];
    while(Curr != nullptr) {
      Out<< to_string(Curr->Data) + ", ";
      Curr = Curr->Next;
    }
    Out << "\n";
  }
  return Out;


ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int d = skip.maxLevel - 1; d >= 0; d--) {
    out << d << ": ";
    auto *curr = skip.head->forward[d];
    if (curr != skip.tail) {
      out << curr->value;
      curr = curr->forward[d];
    }
    while (curr != nullptr && curr != skip.tail) {
      out << "-->" << curr->value;
      curr = curr->forward[d];
    }
    out << endl;
  }
  return out;
}
*/

// Skiplist Node Constructor
SNode::SNode(int value)
    : value{value}, forward{nullptr}, backward{nullptr}, up{nullptr},
      down{nullptr} {}

// how many forward/backward pointers it has
int SNode::height() const {
  int height{0};
  while (this->forward != nullptr) {
    height++;
  }

  int height2{0};
  while (this->backward != nullptr) {
    height2++;
  }

  height = (height > height2) ? height : height2;

  return height;
}

// increase the number of forward/backward pointers it has
void SNode::increaseHeight() {}

// array of Depth SNode* objects as FrontGuards linking levels
SNode **FrontGuards;

// array of Depth SNode* objects as RearGuards linking levels
SNode **RearGuards;

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);

  // Added in accordance with the Assignment 4 instructions
  // first and the last items at each of the levels
  // SNode *temp = new SNode(NULL);
  // SNode *temp2 = new SNode(NULL);

  for (int level{maxLevel}; level > 0; level--) {

    iNT_MIN.push_back(nullptr);

    iNT_MAX.push_back(nullptr);
  }

  cout << "Int min and max size: " << endl;

  cout << iNT_MIN.size() << endl;
  cout << iNT_MAX.size() << endl;
}

bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

// bool SkipList::add(const vector<int> &values) { return true; }

bool SkipList::add(int value) {
  // if (this->contains(value))
  //   return false;

  SNode *newNode = new SNode(value);

  if (head == nullptr) {
    head = newNode;
    tail = head;
    iNT_MIN[0] = head;
    iNT_MAX[0] = head;
  } else if (head->value > value) {
    newNode->forward = head;
    newNode->forward->backward = newNode;
    head = newNode;
    iNT_MIN[0] = head;
  } else {
    SNode *curr = head;
    while (curr->forward != nullptr && curr->forward->value <= value) {
      if (curr->forward->value == newNode->value) {
        delete newNode;
        return false;
      }
      curr = curr->forward;
    }
    // New Node's next will point to the current pointer's next

    newNode->forward = curr->forward;

    // if the current node's next is not null then have the
    // current node's previous point back to the new node
    if (curr->forward != nullptr) {

      newNode->forward->backward = curr->backward;
    }

    // point the current node to the new node
    curr->forward = newNode;
    // point the new nodes back to
    newNode->backward = curr;
    // If the newNode's value is larger than the tail the tail
    // gets pointed to the new node
    if (value > tail->value) {
      tail = newNode;
      iNT_MAX[0] = tail;
    }

    curr = nullptr;
  }

  return true;
}

SkipList::~SkipList() {
  // need to delete individual nodes
  SNode *curr = head;
  while (curr != nullptr) {
    SNode *next = curr->forward;
    delete curr;
    curr = next;
    next = nullptr;
  }

  // Head is already deleted
  // delete head;
  this->iNT_MAX.clear();
  iNT_MAX.shrink_to_fit();
  this->iNT_MIN.clear();
  iNT_MIN.shrink_to_fit();

  head = nullptr;
  curr = nullptr;
}

// bool SkipList::remove(int data) { return true; }

// Given a SNode, place it before the given NextNode
// void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
//   // Link next to node in front
//   NewNode->forward = NextNode;
//   // Link prev to node behind
//   NewNode->backward = NextNode->backward;
//   // Link node in back to new node
//   NextNode->backward->forward = NewNode;
//   // Link node in front to new node
//   NextNode->backward = NewNode;
// }
// This was previously provided
// I had to change it from above.
// // Link next to node in front
// NewNode->Next = NextNode;
// // Link prev to node behind
// NewNode->Prev = NextNode->Prev;
// // Link node in back to new node
// NextNode->Prev->Next = NewNode;
// // Link node in front to new node
// NextNode->Prev = NewNode;

// get the node that would be before this data
// at level-0
// vector<SNode *> SkipList::getBeforeNodes(int data) const {
//  vector<SNode *> v(maxLevel);
//  return v;
//}

// Checks to see whether or not a data value exists in the list
// Returns the NODE if the value exists in the SkipList.
// Returns nullptr otherwise

// SNode *SkipList::containsSNode(int data) const { return nullptr; }

// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise

// bool SkipList::contains(int data) const { return true; }

// private methods to ease linking
// void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {

// }

// void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}
