
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

/**
 * @brief : Prints the levels of the every item in the
 *  Skiplist
 *
 * @param Out : is the outstream
 * @param SkipL : is the skiplist being called
 * @return ostream& - desired output
 */
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int level{SkipL.maxLevel - 1}; level >= 0; level--) {

    Out << "Level: " + to_string(level);
    Out << " -- ";
    if (SkipL.iNT_MIN[level] != nullptr) {
      SNode *Curr = SkipL.iNT_MIN[level];

      while (Curr != nullptr) {
        Out << to_string(Curr->value) + ", ";
        Curr = Curr->forward;
      }
    }
    Out << "\n";
  }

  return Out;
}

// Skiplist Node Constructor
SNode::SNode(int value)
    : value{value}, forward{nullptr}, backward{nullptr}, up{nullptr},
      down{nullptr} {}

/**
 * @brief Construct a new Skip List:: Skip List object
 *
 * @param maxLevel - The highest a snode can go in the skiplist
 * @param probability - the probability for a snode to go to the next level
 */
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

/**
 * @brief Creates the probabilty of the value in the first
 *  level to go up or not
 *
 * @return true - if the snode should go up
 * @return false - the snode should NOT go up
 */
bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

/**
 * @brief Adds one integer at a time in the given vector
 *  Iterates through the vector and calls the
 *  add function below
 *
 * @param values - vector to be added
 * @return true - if every item was added to the skiplist
 * @return false - if at least one value is not added
 */
bool SkipList::add(const vector<int> &values) {
  bool result = values.size() > 0;
  if (!result)
    return false;
  for (int val : values) {
    result = add(val);
  }

  return result;
}

/**
 * @brief This function adds a integer to a
 *  skiplist
 *
 * the function is O(n*log(n)) since we wanted to check before adding
 *
 * @param value - integer to add to the skiplist
 * @return true - if the value was added successfuly
 * @return false - if the value already exists in the skiplist
 */
bool SkipList::add(int value) {
  if (this->contains(value))
    return false;
  SNode *newNode = new SNode(value);

  if (head == nullptr) {
    head = newNode;
    tail = head;
    iNT_MIN[0] = head;
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

/**
 * @brief This function determines if the integer will
 *  go higher in the skip list and link them to the
 *
 * @param a - node that may go higher
 * @param level - level to start going higher
 */
void SkipList::goHigher(SNode *a, int level) {
  while (shouldInsertAtHigher() && level < maxLevel) {
    SNode *newptr = new SNode(a->value);
    if (iNT_MIN[level] == nullptr) {
      iNT_MIN[level] = newptr; // link the new node to be the minimum
      iNT_MAX[level] = newptr; // Linke th new node to the max
      a->up = newptr;          // link the node below to the new node above
      newptr->down = a;        // linke the node above to the node below
    } else if (iNT_MIN[level]->value > newptr->value) {
      newptr->forward = iNT_MIN[level];  // link new node to first node in row
      iNT_MIN[level]->backward = newptr; // link first node in row to new node
      iNT_MIN[level] = newptr; // link the first node in the row to be new node
      a->up = newptr;          // link the node below to the new node above
      newptr->down = a;        // linke the node above to the node below
    } else {
      SNode *curr =
          iNT_MIN[level]; // get the first value on current level that we are on
      curr = getPrevNode(curr, a->value); // get the value
      // If it returns a null pointer then there was a
      // repeat of numbers trying to be entered
      addBefore(newptr, curr);
      a->up = newptr;
      newptr->down = a;
    }
    a = a->up;
    level++;
  }
}

/**
 * @brief
 * // This will return the pointer that has the node less than the value
 * // The Node pointer must not be null pointer
 * // If is the same value then it will return a nullptr
 *
 * @param minPointer - Pointer to compare the the value to
 * @param value - targeted value that we want to return a node value before or
 * at the targeted node
 * @return SNode* - retuern the node with a value before, at, or null pointer if
 * not found
 */
SNode *SkipList::getPrevNode(SNode *&minPointer, int &value) const {
  while (minPointer->forward != nullptr &&
         minPointer->forward->value <= value) {
    minPointer = minPointer->forward;
  }
  // if (minPointer->value == value)
  //   return nullptr;
  return minPointer;
}

/**
 * @brief
 * // Given a SNode, place it before the given Previous Node
 *
 * @param NewNode - Node to be added before
 * @param PrevNode - node that will be in front of new node
 */
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
  }
}

/**
 * @brief Destroy the Skip List:: Skip List object
 */
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

/**
 * @brief removes data in the skiplist
 *
 * @param data - desired integer to be removed
 * @return true - if the integer was removed from the skiplist
 * @return false - if the integer doesn't exists
 */
bool SkipList::remove(int data) {
  SNode *temp = containsSNode(data);

  if (temp == nullptr) {
    delete temp;
    temp = nullptr;
    return false;
  }
  int level = {0};
  while (temp->up != nullptr) {
    if (temp->backward != nullptr) {
      temp->backward->forward = temp->forward;
    } else {
      iNT_MIN[level] = temp->forward;
    }

    if (temp->forward != nullptr) {
      temp->forward->backward = temp->backward;
    }
    SNode *tempUp = temp->up;
    delete temp;
    temp = tempUp;
    level++;
    tempUp = nullptr;
  }

  if (temp->forward == nullptr && temp->backward == nullptr)
    iNT_MIN[level] = nullptr;
  else if (temp->forward != nullptr && temp->backward == nullptr) {
    iNT_MIN[level] = temp->forward;
    iNT_MIN[level]->backward = nullptr;
  } else if (temp->backward != nullptr && temp->forward == nullptr) {
    temp->backward->forward = temp->forward;
  } else {
    temp->backward->forward = temp->forward;
    temp->forward->backward = temp->backward;
  }

  delete temp;
  temp = nullptr;
  return true;
}

/**
 * @brief
 * // Checks to see whether or not a data value exists in the list
 * // Returns the NODE if the value exists in the SkipList.
 * // Returns nullptr otherwise
 *
 * @param data - targeted integer value
 * @return SNode* - targeted snode that we want to remove/validate that the
 * skiplist contains it
 */
SNode *SkipList::containsSNode(int data) const {
  int level = maxLevel - 1;
  SNode *start = iNT_MIN[level];
  // Start from the level that has the first value;
  while (start == nullptr && iNT_MIN[0] != nullptr) {
    level--;
    start = iNT_MIN[level];
  }
  while (start != nullptr) {
    // If the value is less than the data that needs to be found then find
    // the value in the level that would be right before the desired value.
    if (start->value <= data) {
      start = getPrevNode(start, data);
      // If we find the value you return the node in the lowest level
      if (start != nullptr && start->value == data) {
        while (start->down != nullptr) {
          start = start->down;
        }
        return start;
      }
    } // If the value is greater and not the smallest on the
      // level go backwards
    else if (start->value >= data && start != iNT_MIN[level]) {
      while (start->backward != nullptr && start->value > data &&
             start != iNT_MIN[level]) {
        start = start->backward;
      }
    }
    // If we have reached the first level and have found the value
    if (start != nullptr && start->down == nullptr && start->value == data)
      return start;
    // If the pointer has reached outside the skiplist then exit with null
    // pointer
    if (start == nullptr)
      return nullptr;

    // If we haven't reached the end go down a level
    if (start != nullptr) {

      start = start->down;
      level--;
    }
  }
  // return the pointer allocation
  start = nullptr;
  return nullptr;
}

/**
 * @brief
 * // Checks to see whether or not a data value exists in the list
 * // Returns true if the value exists in the SkipList.
 * // Returns false otherwise
 *
 * @param data - integer that is going to be checked if in the skiplist
 * @return true - if the integer is in the skiplist
 * @return false - if the integer is not in the skiplist
 */
bool SkipList::contains(int data) const {
  SNode *temp = containsSNode(data);
  if (temp == nullptr) {
    return false;
  }
  return temp->value == data;
}
