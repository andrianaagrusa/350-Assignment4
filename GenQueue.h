
#include <iostream>
#include "ListNode.h"
using namespace std;

template <class T>
class GenQueue
{
public:
    int elements;
    ListNode<T> *front;
    ListNode<T> *back;
    GenQueue();
    ~GenQueue();
    void enqueue(T d);
    T dequeue();
    T vFront();
    T vBack();
    void printQ();
    bool isEmpty();
    int getSize();
};

template <class T>
GenQueue<T>::GenQueue()
{
  elements = 0;
  front = NULL;
  back = NULL;
}

template <class T>
GenQueue<T>::~GenQueue() {}

template <class T>
void GenQueue<T>::enqueue(T d)
{
  ListNode<T> *node = new ListNode<T>(d);

  if(elements == 0)
  {
    front = node;
  }
  else
  {
    back->next = node;
    node->prev = back;
  }

  back = node;
  ++elements;
}

template <class T>
T GenQueue<T>::dequeue()
{
  if(!isEmpty())
  {
    ListNode<T> *node = front;
    T temp = node->data;
    if(front->next == NULL)
    {
        front = NULL;
        back = NULL;
    }
    else
    {
      front->next->prev = NULL;
      front = front->next;
    }

    delete node;
    --elements;
    return temp;
  }

  else
  {
    return T();
  }
}
template <class T>
T GenQueue<T>::vFront()
{
  return front->data;
}

template <class T>
T GenQueue<T>::vBack()
{
  return back->data;
}

template <class T>
void GenQueue<T>::printQ()
{
  ListNode<T> *curr = front;
  while(true)
  {
    if(curr != NULL)
    {
      curr = curr->next;
    }

    else
    {
      break;
    }
  }
}

template <class T>
bool GenQueue<T>::isEmpty()
{
  return (elements == 0);
}

template <class T>
int GenQueue<T>::getSize()
{
  return elements;
}
