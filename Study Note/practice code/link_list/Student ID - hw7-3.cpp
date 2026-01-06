// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <string>
using std::string;

template< typename BidIt >
class ReverseIterator // wrap iterator to run it backwards
{
public:
   using value_type = typename BidIt::value_type;
   using difference_type = typename BidIt::difference_type;
   using pointer = typename BidIt::pointer;
   using reference = typename BidIt::reference;

   // construct with value-initialized wrapped iterator
   ReverseIterator() = default;

   // construct wrapped iterator from right
   ReverseIterator( BidIt right )
      : current( right )
   {
   }

   ReverseIterator( const ReverseIterator &right )
      : current( right.current ) // initialize with compatible base
   {
   }

   // assign from compatible base
   ReverseIterator& operator=( const ReverseIterator &right )
   {
      current = right.current;
      return *this;
   }

   BidIt base() const // return wrapped iterator
   {
      return current;
   }

   reference operator*() const // return designated value
   {
      BidIt tmp = current;
      return *--tmp;
   }

   pointer operator->() const // return pointer to class object
   {
      BidIt tmp = current;
      --tmp;
      return tmp.operator->();
   }

   ReverseIterator& operator++() // preincrement
   {
      --current;
      return *this;
   }

   ReverseIterator operator++( int ) // postincrement
   {
      ReverseIterator tmp = *this;
      --current;
      return tmp;
   }

   ReverseIterator& operator--()	// predecrement
   {
      ++current;
      return *this;
   }

   ReverseIterator operator--( int ) // postdecrement
   {
      ReverseIterator tmp = *this;
      ++current;
      return tmp;
   }

   // increment by integer
   ReverseIterator& operator+=( const difference_type off )
   {
      current -= off;
      return *this;
   }

   // return this + integer
   ReverseIterator operator+( const difference_type off ) const
   {
      return ReverseIterator( current - off );
   }

   // decrement by integer
   ReverseIterator& operator-=( const difference_type off )
   {
      current += off;
      return *this;
   }

   // return this - integer
   ReverseIterator operator-( const difference_type off ) const
   {
      return ReverseIterator( current + off );
   }

   // subscript
   reference operator[]( const difference_type off ) const
   {
      return current[ static_cast< difference_type >( -off - 1 ) ];
   }

protected:
   BidIt current{}; // the wrapped iterator
};

template< typename BidIt1, typename BidIt2 >
bool operator==( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return left.base() == right.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator!=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( left == right );
}

template< typename BidIt1, typename BidIt2 >
bool operator<( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return right.base() < left.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator>( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return right < left;
}

template< typename BidIt1, typename BidIt2 >
bool operator<=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( right < left );
}

template< typename BidIt1, typename BidIt2 >
bool operator>=( const ReverseIterator< BidIt1 > &left,
   const ReverseIterator< BidIt2 > &right )
{
   return !( left < right );
}


// CLASS TEMPLATE VectorConstIterator
template< typename MyVec >
class VectorConstIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = const value_type &;
   using TPtr = typename MyVec::pointer;

   VectorConstIterator()
      : ptr()
   {
   }

   VectorConstIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorConstIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorConstIterator operator++( int )
   {
      VectorConstIterator temp = *this;
      ++*this;
      return temp;
   }

   VectorConstIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorConstIterator operator--( int )
   {
      VectorConstIterator temp = *this;
      --*this;
      return temp;
   }

   VectorConstIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorConstIterator operator+( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp += off;
   }

   VectorConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorConstIterator operator-( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorConstIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorConstIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorConstIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorConstIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorConstIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorConstIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorIterator
template< typename MyVec >
class VectorIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = value_type &;
   using TPtr = typename MyVec::pointer;

   VectorIterator()
      : ptr()
   {
   }

   VectorIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorIterator operator++( int )
   {
      VectorIterator temp = *this;
      ++*this;
      return temp;
   }

   VectorIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorIterator operator--( int )
   {
      VectorIterator temp = *this;
      --*this;
      return temp;
   }

   VectorIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorIterator operator+( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp += off;
   }

   VectorIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorIterator operator-( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
      myLast(),
      myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = VectorIterator< ScaryVal >;
   using const_iterator = VectorConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   vector()
      : myData()
   {
   }

   vector( const size_type count )
      : myData()
   {
       if (count != 0) {
           myData.myFirst = new value_type[count]();
           myData.myLast = myData.myFirst + count;
           myData.myEnd = myData.myFirst + count;
       }
   }

   vector( const vector &right )
      : myData()
   {
       myData.myFirst = new value_type[right.size()];
       myData.myLast = myData.myEnd = myData.myFirst + right.size();

       for (int i = 0; i < right.size(); i++) {
           myData.myFirst[i] = right.myData.myFirst[i];
       }
   }

   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   void push_back( const value_type &val )
   {
      size_type originalSize = size();
      size_type originalCapacity = capacity();
      if( originalSize == originalCapacity )
      {
         size_type newCapacity;
         if( originalCapacity <= 1 )
            newCapacity = originalCapacity + 1;
         else
            newCapacity = originalCapacity * 3 / 2;
         value_type* newFirst = new value_type[newCapacity];


         for (size_type i = 0; i < originalSize; ++i) {
             newFirst[i] = myData.myFirst[i];
         }

         delete[] myData.myFirst;

         myData.myFirst = newFirst;
         myData.myLast = myData.myFirst + originalSize;
         myData.myEnd = myData.myFirst + newCapacity;
      }
      myData.myFirst[size()] = val;
      myData.myLast++;

   }

   vector& operator=( const vector &right )
   {
      if( this != &right ) // avoid self-assignment
      {
         size_type rightSize = right.size();
         if( rightSize > capacity() )
         {
            if( size() > 0 )
               delete[] myData.myFirst; // release space

            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < rightSize )
               newCapacity = rightSize;
            myData.myFirst = new value_type[newCapacity];
            myData.myEnd = myData.myFirst + newCapacity;

         }
         for (size_type i = 0; i < rightSize; ++i) {
             myData.myFirst[i] = right.myData.myFirst[i];
         }
         myData.myLast = myData.myFirst + rightSize;
      }

      return *this; // enables x = y = z, for example
   }

   void resize( const size_type newSize )
   {
      size_type originalSize = size();
      if( newSize > originalSize )
      {
         if( newSize > capacity() )
         {
            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < newSize )
               newCapacity = newSize;

            value_type* newFirst = new value_type[newCapacity]; // 分配新的内存
            std::copy(myData.myFirst, myData.myFirst + originalSize, newFirst); // 复制原有数据
            delete[] myData.myFirst; // 释放旧内存

            // 更新指针
            myData.myFirst = newFirst;
            myData.myLast = myData.myFirst + originalSize;
            myData.myEnd = myData.myFirst + newCapacity;
         }

         // 填充新添加的部分
         std::fill(myData.myLast, myData.myFirst + newSize, 0);
         myData.myLast = myData.myFirst + newSize; // 更新末尾指针

      }
      else {
          // 缩小大小，但不释放容量
          myData.myLast = myData.myFirst + newSize;
      }
   }

   void pop_back()
   {
      if( size() > 0 )
         --myData.myLast;
   }

   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   iterator begin()
   {
      return iterator( myData.myFirst );
   }

   iterator end()
   {
      return iterator( myData.myLast );
   }

   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   value_type& front()
   {
      return *myData.myFirst;
   }

   const value_type& front() const
   {
      return *myData.myFirst;
   }

   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two vectors are equal and return true, otherwise return false
template< typename Ty >
bool operator==( vector< Ty > &left, vector< Ty > &right )
{
   if( left.size() != right.size() )
      return false; // vectors of different number of elements

   typename vector< Ty >::iterator it1 = left.begin();
   typename vector< Ty >::iterator it2 = right.begin();
   for( ; it1 != left.end(); ++it1, ++it2 )
      if( *it1 != *it2 )
         return false; // vector contents are not equal

   return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( vector< Ty > &left, vector< Ty > &right )
{
   return !( left == right );
}


// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = const value_type &;

   ListConstIterator()
      : ptr()
   {
   }

   ListConstIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListConstIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListConstIterator operator++( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListConstIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListConstIterator operator--( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListConstIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = value_type &;

   ListIterator()
      : ptr()
   {
   }

   ListIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListIterator operator++( int )
   {
      ListIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListIterator operator--( int )
   {
      ListIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
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

   using iterator = ListIterator< ScaryVal >;
   using const_iterator = ListConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

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

   list( const list &right )
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      nodePtr temp = right.myData.myHead;

      for (size_t i = 0; i < right.size(); i++) {
          temp = temp->next;

          nodePtr temp2 = new node;
          temp2->myVal = temp->myVal;
          temp2->next = myData.myHead;
          temp2->prev = myData.myHead->prev;
          myData.myHead->prev->next = temp2;
          myData.myHead->prev = temp2;
          myData.mySize++;
      }


   }

   ~list()
   {
      clear();
      delete myData.myHead;
   }

   list& operator=( const list &right )
   {
      if( this != &right )
      {
         if( right.myData.mySize == 0 ) // the right list is empty
         {
            if( myData.mySize != 0 ) // the left list is not empty
               clear();
         }
         else // the right list is not empty
         {
             if (myData.mySize < right.myData.mySize)
             {
                 while (right.myData.mySize > myData.mySize) {
                     nodePtr temp = new node;
                     temp->myVal = Ty();
                     temp->next = myData.myHead;
                     temp->prev = myData.myHead->prev;
                     myData.myHead->prev->next = temp;
                     myData.myHead->prev = temp;

                     myData.mySize++;

                 }
             }
             else
             {
                 while (right.myData.mySize < myData.mySize) {

                     myData.myHead->prev = myData.myHead->prev->prev;
                     delete myData.myHead->prev->next;
                     myData.myHead->prev->next = myData.myHead;

                     myData.mySize--;
                 }

             }
             //assign
             nodePtr mytemp = myData.myHead;
             nodePtr righttemp = right.myData.myHead;

             for (size_t i = 0; i < right.size(); i++) {
                 mytemp = mytemp->next;
                 righttemp = righttemp->next;
                 mytemp->myVal = righttemp->myVal;
             }
         }

        

      }
      

      return *this;
   }

   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   iterator end()
   {
      return iterator( myData.myHead );
   }

   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   void resize( size_type newSize )
   {
      if( myData.mySize != newSize )
      {
          if (newSize < myData.mySize) {
              nodePtr deleted = myData.myHead->prev; //last one
              if (newSize == 0) {
                  clear();
              }
              for (size_t i = newSize; i < myData.mySize; i++) {
                  nodePtr temp = deleted->prev;
                  deleted->prev->next = deleted->next;
                  deleted->next->prev = deleted->prev;
                  delete deleted;
                  deleted = temp;
              }
          }
          else {
              nodePtr current = myData.myHead->prev;//last one
              for (size_t i = myData.mySize; i < newSize; ++i) {
                  nodePtr newnode = new node;
                  newnode->myVal = Ty();
                  newnode->prev = current;
                  newnode->next = current->next;
                  current->next->prev = newnode;
                  current->next = newnode;
                  current = newnode;
              }
          }
          myData.mySize = newSize;


      }
   }

   size_type size() const
   {
      return myData.mySize;
   }

   bool empty() const
   {
      return myData.mySize == 0;
   }

   reference front()
   {
      return myData.myHead->next->myVal;
   }

   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

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

   void pop_back()
   {
       if (myData.mySize > 0)
       {
           nodePtr deleted = myData.myHead->prev;
           deleted->prev->next = deleted->next;
           deleted->next->prev = deleted->prev;
           delete deleted;
           myData.mySize--;
       }
   }

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

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( list< Ty > &left, list< Ty > &right )
{
   if( left.size() != right.size() )
      return false; // vectors of different number of elements

   typename list< Ty >::iterator it1 = left.begin();
   typename list< Ty >::iterator it2 = right.begin();
   for( ; it1 != left.end(); ++it1, ++it2 )
      if( *it1 != *it2 )
         return false; // vector contents are not equal

   return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( list< Ty > &left, list< Ty > &right )
{
   return !( left == right );
}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   HugeInteger( string str );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( HugeInteger &right ); // less than or equal to

   bool operator<( HugeInteger &right );  // less than

   bool operator<=( HugeInteger &right ); // less than or equal to

   HugeInteger square( value_type powerTwo ); // the square of HugeInteger
   HugeInteger squareRoot( value_type powerTwo ); // the square root of HugeInteger

   bool isZero();           // return true if and only if all digits are zero
private:
   T integer;
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
}

template< typename T >
HugeInteger< T >::HugeInteger( string str )
{
   value_type digits[ 1001 ] = {};
   size_type last = str.size() - 1;
   for( size_type i = 0; i <= last; ++i )
      digits[ i ] = static_cast< value_type >( str[ last - i ] ) - '0';

   size_type numDigits = sizeof( value_type ) - 1;
   for( size_type i = 0; i <= last; i += numDigits )
   {
      value_type bigDigit = digits[ i ] + digits[ i + 1 ] * 10 + digits[ i + 2 ] * 100;
      if( sizeof( value_type ) == 8 )
         bigDigit += digits[ i + 3 ] * 1000 +
                    digits[ i + 4 ] * 10000 +
                    digits[ i + 5 ] * 100000 +
                    digits[ i + 6 ] * 1000000;

      integer.push_back( bigDigit );
   }
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger &right )
{
    if (integer.size() < right.integer.size())
        return true;

    if (integer.size() > right.integer.size())
        return false;

    typename T::iterator it1 = integer.end();
    typename T::iterator it2 = right.integer.end();

    do {
        it1--, it2--;
        if (*it1 < *it2)
            return true;
        else if (*it1 > *it2)
            return false;
    } while (it1 != integer.begin());

    return false;


} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger &right )
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_type squareSize = 2 * integer.size();
   HugeInteger square( squareSize );
   typename T::iterator iti = integer.begin();
   size_type n = integer.size();

   for (size_type i = 0; i < n; ++i) {
       value_type carry = 0;
       typename T::iterator itj = integer.begin();
       typename T::iterator it = square.integer.begin();
       for (int k = 0; k < i; k++) {
           it++;
       }
       for (size_type j = 0; j < n; ++j) {
           value_type product = *(iti) * *(itj)+*it + carry;
           *it = product % powerTwo;
           carry = product / powerTwo;
           ++itj;
           ++it;
       }
       if (carry > 0 && (i + n < squareSize)) {
           it = square.integer.begin();
           for (int k = 0; k < i+n; k++) {
               it++;
           }
           *it += carry;
       }

       ++iti;
   }


   while (!square.integer.empty() && square.integer.back() == 0) {
       square.integer.pop_back();
   }

   return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_type sqrtSize = ( integer.size() + 1 ) / 2;
   HugeInteger sqrt( sqrtSize );
   HugeInteger sq;
   typename T::iterator it = sqrt.integer.end();
   it--;
   for (int i = 0; i < sqrtSize; ++i) {
       size_type low = 0;
       size_type high = (sizeof(value_type) == 8) ? 9999999 : 999;
       size_type mid;
       while (low <= high) {
           mid = (low + high) / 2;
           *it = mid;
           sq = sqrt.square(powerTwo);
           if (*this == sq) {
               return sqrt;
           }
           else if (*this < sq) {
               high = mid - 1;
           }
           else {
               low = mid + 1;
           }
       }
       if (*this < sq) {
           --mid;
       }
       *it = mid;
       it--;
   }

   return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::reverse_iterator it = hugeInteger.integer.rbegin();
   output << *it;
   for( ++it; it != hugeInteger.integer.rend(); ++it )
      output << setw( numDigits ) << setfill( '0' ) << *it;

   return output; // enables cout << x << y;
}

template< typename T1, typename T2 >
void solution2()
{
   T2 powerTwo = 1000;
   if( sizeof( T2 ) == 8 )
      powerTwo = 10000000;

   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      string str;
      cin >> str;

      HugeInteger< T1 > hugeInteger( str );

      cout << hugeInteger.squareRoot( powerTwo ) << endl;

      if( i < numCases )
         cout << endl;
   }
}

template< typename T >
void solution1()
{
   // execute the following 2 instructions one by one, each of them should get an AC
   solution2< vector< T >, T >();
   //solution2< list< T >, T >();
}

int main()
{
   // execute the following 4 instructions one by one, each of them should get an AC
   //solution1< long int >();
//   solution1< unsigned long int >();
   solution1< long long int >();
//   solution1< unsigned long long int >();
}