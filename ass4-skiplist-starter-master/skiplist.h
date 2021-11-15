/**
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 * also used by MemSQL
 * https://www.singlestore.com/blog/what-is-skiplist-why-skiplist-index-for-memsql/
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * For our implementation p = 50%
 * All elements are inserted at the lowest Depth (1)
 * 50% of the elements inserted in Depth = 2
 * 50% of 50%, or 25% of the elements inserted in Depth = 3
 * and so on
 *
 * If a Skip List has only 1 level, such as p = 0%
 * Insert O(n), Search O(n)
 * For Depth > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 *
 */

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;

class SNode {
  friend class SkipList;
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // constructor
  explicit SNode(int value);

  // data contained in the object
  int value{0};

  // link to Next SNode
  SNode *forward;

  // link to Prev SNode
  SNode *backward;

  // link to up node
  SNode *up;

  // link to down SNode
  SNode *down;

  // how many forward/backward pointers it has
  int height() const;

  // increase the number of forward/backward pointers it has
  void increaseHeight();
};

class SkipList {
  // display with level
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // maximum number of levels
  int maxLevel = 1;

  // probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  // Assignment called out for 50/50
  int probability = 50;

  // head of linked levels
  SNode *head = nullptr;

  // tail of linked levels
  SNode *tail;

  // Added in accordance with the Assignment 4 instructions
  // first and the last items at each of the levels
  vector<SNode *> iNT_MIN;
  vector<SNode *> iNT_MAX;

  // given a SNode, place it before the given nextNode
  void addBefore(SNode *newNode, SNode *nextNode);

  // return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  bool shouldInsertAtHigher() const;

  // connect 2 nodes in a line
  static void connect2AtLevel(SNode *a, SNode *b, int level);

  // connect 3 nodes in a line
  static void connect3AtLevel(SNode *a, SNode *b, SNode *c, int level);

  SNode *containsSNode(int data) const;

  vector<SNode *> getBeforeNodes(int data) const;

public:
  // default SkipList has only 1 level, just one doubly-linked list
  explicit SkipList(int maxLevel = 1, int probability = 0);

  // destructor
  virtual ~SkipList();

  // copy not allowed
  SkipList(const SkipList &other) = delete;

  // move not allowed
  SkipList(SkipList &&other) = delete;

  // assignment not allowed
  SkipList &operator=(const SkipList &other) = delete;

  // move assignment not allowed
  SkipList &operator=(SkipList &&other) = delete;

  // return true if successfully added, no duplicates allowed
  bool add(int value);

  // return true if successfully added, no duplicates
  bool add(const vector<int> &values);

  // return true if successfully removed
  bool remove(int data);

  // return true if found in SkipList
  bool contains(int data) const;
};

#endif // ASS4_SKIPLIST_H
       //
       /**
        * @brief
        *  What is the move method supposed to do and what does 2 "&&" do?
        *
        *  Are we given the output stream operator? Because it is commented out.
        *  I just want to know if this could be a great tool to test my logic of the
        *  code.
        *
        *  How should I think about calculating the height of the node?
        *  Should it be length instead? or should we measure up and down?
        *  Can I do:
        *
        *  For increase height is the intent to add empty Nodes?
        *
        *
        *
        *
        *
        */