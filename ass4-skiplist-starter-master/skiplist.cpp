
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
}

bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

bool SkipList::add(const vector<int> &values) {
  bool result = values.size() > 0;
  if (!result)
    return false;
  for (int val : values) {
    add(val);
  }

  return true;
}

bool SkipList::add(int value) {
  // if (this->contains(value))
  //   return false;

  SNode *newNode = new SNode(value);

  if (head == nullptr) {
    head = newNode;
    tail = head;
    iNT_MIN[0] = head;
    iNT_MAX[0] = head;
    goHigher(newNode, 1);

  } else if (head->value > value) {
    newNode->forward = head;
    newNode->forward->backward = newNode;
    head = newNode;
    iNT_MIN[0] = head;
    goHigher(newNode, 1);

  } else {
    // Start at the head
    SNode *curr = iNT_MIN[0];
    /* Keep looking forward if the current node is not null and
    less than the value*/
    curr = getPrevNode(curr, value);

    // If it returns a pointer with the same value
    // then the new node will delete

    if (curr->value == value) {
      delete newNode;
      newNode = nullptr;

      return false;
    }
    addBefore(newNode, curr);

    goHigher(newNode, 1);
    curr = nullptr;
  }

  return true;
}

/* Memory Leaks are occuring here! at the else if and the else */
void SkipList::goHigher(SNode *a, int level) {
  while (shouldInsertAtHigher() && level < maxLevel) {
    SNode *newptr = new SNode(a->value);
    if (iNT_MIN[level] == nullptr) {
      iNT_MIN[level] = newptr;
      iNT_MAX[level] = newptr;
      a->up = newptr;
      newptr->down = a;
    } else if (iNT_MIN[level]->value > newptr->value) {
      newptr->forward = iNT_MIN[level];
      iNT_MIN[level]->backward = newptr;
      iNT_MIN[level] = newptr;
      a->up = newptr;
      newptr->down = a;
    } else {
      SNode *curr = iNT_MIN[level];
      curr = getPrevNode(curr, a->value);
      // If it returns a null pointer then there was a
      // repeat of numbers trying to be entered

      addBefore(newptr, curr);
      a->up = newptr;
      newptr->down = a;
      a = a->up;
    }
    level++;
  }
}

// This will return the pointer that has the node less than the value
// The Node pointer must not be null pointer
// If is the same value then it will return a nullptr
SNode *SkipList::getPrevNode(SNode *minPointer, int &value) const {
  while (minPointer->forward != nullptr &&
         minPointer->forward->value <= value) {
    minPointer = minPointer->forward;
  }
  // if (minPointer->value == value)
  //   return nullptr;
  return minPointer;
}

// Given a SNode, place it before the given Previous Node
void SkipList::addBefore(SNode *NewNode, SNode *PrevNode) {
  // Link next to node in front
  NewNode->forward = PrevNode->forward;
  // point the current node to the new node
  PrevNode->forward = NewNode;
  // point the new nodes back to
  NewNode->backward = PrevNode;

  if (NewNode->forward != nullptr)
    NewNode->forward->backward = NewNode;

  // If the newNode's value is larger than the tail the tail
  // gets pointed to the new node
  if (NewNode->value > tail->value) {
    tail = NewNode;
    iNT_MAX[0] = tail;
  }
}

SkipList::~SkipList() {
  // need to delete individual nodes
  for (int level{maxLevel - 1}; level >= 0; level--) {

    if (iNT_MIN[level] != nullptr) {
      SNode *curr = iNT_MIN[level];

      while (curr != nullptr) {
        SNode *next = curr->forward;
        delete curr;
        curr = next;
        next = nullptr;
      }
      curr = nullptr;
    }
  }
  this->iNT_MAX.clear();
  iNT_MAX.shrink_to_fit();
  this->iNT_MIN.clear();
  iNT_MIN.shrink_to_fit();

  head = nullptr;
}

// bool SkipList::remove(int data) { return true; }

// Checks to see whether or not a data value exists in the list
// Returns the NODE if the value exists in the SkipList.
// Returns nullptr otherwise

SNode *SkipList::containsSNode(int data) const {
  int level = maxLevel - 1;
  SNode *start = iNT_MIN[level];
  // Start from the level that has a value;
  while (start == nullptr && iNT_MIN[0] != nullptr) {
    start = iNT_MIN[--level];
  }
  while (start != nullptr) {
    start = getPrevNode(start, data);
    if (start->forward->value == data)
      return start->forward;

    start = start->down;
  }

  return nullptr;
}

// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise

// bool SkipList::contains(int data) const { return true; }

// private methods to ease linking
// void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {

// }

// void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}
