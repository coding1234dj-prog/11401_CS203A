// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      for (size_type i = 0; i < count; ++i) {
          nodePtr newNode = new node;
          newNode->myVal = Ty();
          newNode->next = myData.myHead;
          newNode->prev = myData.myHead->prev;
          myData.myHead->prev->next = newNode;
          myData.myHead->prev = newNode;
      }
      myData.mySize = count;

   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // Inserts a new element at the beginning of the list,
   // right before its current first element.
   // The content of val is copied (or moved) to the inserted element.
   // This effectively increases the container size by one.
   void push_front( const Ty &val )
   {     
       nodePtr newnode = new node;
       newnode->myVal = val;
       if (myData.mySize == 0) {        
           myData.myHead->next = newnode;
           myData.myHead->prev = newnode;
           newnode->next = myData.myHead;
           newnode->prev = myData.myHead;
       }
       else {
           newnode->next = myData.myHead->next;
           newnode->prev = myData.myHead;
           myData.myHead->next->prev = newnode;
           myData.myHead->next = newnode;
       }
       myData.mySize++;
   }

   // Removes the first element in the list container,
   // effectively reducing its size by one.
   // This destroys the removed element.
   void pop_front() {
       if (myData.mySize != 0) {
           nodePtr deleted = myData.myHead->next;
           deleted->prev->next = deleted->next;
           deleted->next->prev = myData.myHead;
           delete deleted;
           myData.mySize--;
       }
   }



   // Adds a new element at the end of the list container,
   // after its current last element.
   // The content of val is copied (or moved) to the new element.
   // This effectively increases the container size by one.
   void push_back( const Ty &val )
   {
      
       nodePtr newnode = new node;
       newnode->myVal = val;
       if (myData.mySize == 0) {
           myData.myHead->next = newnode;
           myData.myHead->prev = newnode;
           newnode->next = myData.myHead;
           newnode->prev = myData.myHead;
       }
       else {
           newnode->prev = myData.myHead->prev;
           newnode->next = myData.myHead;
           myData.myHead->prev->next = newnode;
           myData.myHead->prev = newnode;
           
       }
       myData.mySize++;
   }

   // Removes the last element in the list container,
   // effectively reducing the container size by one.
   void pop_back()
   {
       if (myData.mySize != 0) {
           nodePtr deleted = myData.myHead->prev;
           deleted->prev->next = deleted->next;
           deleted->next->prev = deleted->prev;
           delete deleted;
           myData.mySize--;
       }
      
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
         while( myData.myHead->next != myData.myHead )
         {
            myData.myHead->next = myData.myHead->next->next;
            delete myData.myHead->next->prev;
         }

         myData.myHead->prev = myData.myHead;
         myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

#endif // LIST