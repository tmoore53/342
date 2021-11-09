
//modified by mashhadi on 14th feb to add an alternative op<<
/* 
  Modified and implimented by Tyler A. Moore

*/
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &Out, const SkipList &SkipL)
{
  for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--)
  {
    Out << "Level: " + (Index);
    Out << " -- ";
    SNode *Curr = SkipL.head;
    while (Curr != nullptr)
    {
      Out << to_string(Curr->value) + ", ";
      Curr = Curr->forward;
    }
    Out << "\n";
    Curr = Curr->down;
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
SNode::SNode(int value) : value{value}, forward{nullptr}, backward{nullptr}, up{nullptr}, down{nullptr} {}

// how many forward/backward pointers it has
int SNode::height() const
{
  int height{0};
  while (this->forward != nullptr)
  {
    height++;
  }

  int height2{0};
  while (this->backward != nullptr)
  {
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

SkipList::SkipList(int maxLevel, int probability) : maxLevel{maxLevel}, probability{probability}
{
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
}

bool SkipList::shouldInsertAtHigher() const
{
  return rand() % 100 < probability;
}

bool SkipList::add(const vector<int> &values) { return true; }

bool SkipList::add(int value)
{
  if (this->contains(value))
    return false;

  if (head == nullptr)
  {
    SNode *newNode = new SNode(value);
    head = newNode;
  }
  SNode *curr = head;
  while (curr != nullptr)
  {

    curr = curr->forward;
  }
  curr->value = value;

  return true;
}

SkipList::~SkipList()
{
  // need to delete individual nodes
  SNode *curr = head;
  while (curr != nullptr)
  {
    delete curr;
    curr = nullptr;
    curr = head->forward;
    if (head->forward == nullptr)
    {
      curr = head->down;
    }
  }
}

bool SkipList::remove(int data) { return true; }

// Given a SNode, place it before the given NextNode
void SkipList::addBefore(SNode *NewNode, SNode *NextNode)
{
  // Link next to node in front
  NewNode->forward = NextNode;
  // Link prev to node behind
  NewNode->backward = NextNode->backward;
  // Link node in back to new node
  NextNode->backward->forward = NewNode;
  // Link node in front to new node
  NextNode->backward = NewNode;
}
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
//vector<SNode *> SkipList::getBeforeNodes(int data) const {
//  vector<SNode *> v(maxLevel);
//  return v;
//}

// Checks to see whether or not a data value exists in the list
// Returns the NODE if the value exists in the SkipList.
// Returns nullptr otherwise

SNode *SkipList::containsSNode(int data) const { return nullptr; }

// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise

bool SkipList::contains(int data) const { return true; }

//private methods to ease linking
void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {}

void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}
