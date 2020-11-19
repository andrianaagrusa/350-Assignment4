// class ListNode {
//
//   public:
//
//     ListNode();
//     ListNode(int d);
//     ~ListNode();
//     int data;
//     ListNode *next;
//     ListNode *prev;
//
// };
//
//
// //seperate file .cpp
// ListNode::ListNode(){}
//
// ListNode::ListNode(int d)
// {
//   data = d;
//   next = NULL;
//   prev = NULL;
// }
//
//
// ListNode::~ListNode()
// {
//   //do this
// }


// seperate file, .h for doubly linked list

#include "ListNode.h"

template <class T>
class DoublyLinkedList {

  private:
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insertFront(T d);
    void insertBack(T d);
    T removeFront();
    T removeBack();
    T find(T value); // AKA search

    //int deletePos(int pos);
    T removeNode(T key); // find the key/value then proceed to delete


    void printList();
    bool isEmpty();
    unsigned int getSize();

};

// seperate file .cpp implementation
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  front = NULL;
  back = NULL;
  size = 0;
}
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  // do this
}

template <class T>
void DoublyLinkedList<T>::insertFront(T d)
{
  ListNode<T> *node = new ListNode<T>(d);
  if (size == 0) {
    back = node;
  }
  else {
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <class T>
void DoublyLinkedList<T>::insertBack(T d)
{
  ListNode<T> *node = new ListNode<T>(d);
  if (front == NULL)
  {
    front = back;
  }
  else {
    back->next = node;
    node->next = back;
  }
  back = node;
  ++size;
}

template <class T>
T DoublyLinkedList<T>::removeFront()
{
  ListNode<T> *node = front;
  // check if empty before proceeding. do this

  if(front->next == NULL)
  {
    back = NULL;
  }
  else
  {
    //more than one node in the list
    front->next->prev = NULL;
  }

  front = front->next;
  node->next = NULL;
  T temp = node->data;

  size--;
  delete node;
  return temp;
}

template <class T>
T DoublyLinkedList<T>::removeBack()
{
  // do this
  // picture
}

template <class T>
void DoublyLinkedList<T>::printList()
{
  ListNode<T> *curr = front;

  while (curr != NULL)
  {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
T DoublyLinkedList<T>::find(T value)
{
  T pos = -1;
  ListNode<T> *curr = front;

  while (curr != NULL)
  {
    ++pos;
    if (curr->data == value)
    {
      break;
    }
    curr = curr->next;
  }

  if (curr == NULL)
  {
    pos = -1;
  }

  return pos;
}

template <class T>
T DoublyLinkedList<T>::removeNode(T key)
{
  ListNode<T> *curr = front;

  // check if empty (do)
  // if not empty, you can leverage find() to determine if value even exists

   while (curr->data != key)
   {
    curr = curr->next;

    if (curr == NULL)
    {
      //i reached the end of my linked list and did not find the key/value
      return -1;
    }
   }

   //if i make it here, found node that needs to be deleted

   if (curr == front)
   {
    front = curr->next;
    front->prev = NULL;
   }

   else if (curr == back)
   {
    back = curr->prev;
    back->next = NULL;
   }

   else
   {
    // it's between front and back

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
   }

   curr->next = NULL;
   curr->prev = NULL;

   T temp = curr->data;
   size--;
   delete curr;

   return temp;
}
