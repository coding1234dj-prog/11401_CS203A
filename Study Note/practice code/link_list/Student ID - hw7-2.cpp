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

// list standard header
#ifndef LIST
#define LIST

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

   using iterator = node *;
   using const_iterator = const node *;

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
       if (this != &right)
       {
           //myData.mySize=right.myData.mySize
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
      if( myData.mySize > 0 )
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
   for( ; it1 != left.end(); it1 = it1->next, it2 = it2->next )
      if( it1->myVal != it2->myVal )
         return false; // vector contents are not equal

   return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( list< Ty > &left, list< Ty > &right )
{
   return !( left == right );
}

#endif // LIST


// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

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

#endif

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
    if (integer.size() < right.integer.size()) {
        return true;
    }
    else if (integer.size() > right.integer.size()) {
        return false;
    }

    typename T::iterator it1 = integer.end();
    typename T::iterator it2 = right.integer.end();
    do {
        it1 = it1->prev;
        it2 = it2->prev;

        if (it1->myVal > it2->myVal)
            return false;

        if (it1->myVal < it2->myVal)
            return true;

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
    size_t squareSize = 2 * integer.size();
    HugeInteger square(squareSize);
    typename T::iterator iti = integer.begin();   
    size_type n = integer.size();

    for (size_type i = 0; i < n; ++i) {
        typename T::iterator it = square.integer.begin();
        value_type carry = 0;
        typename T::iterator itj = integer.begin();
        for (int k = 0; k < i; k++) {
            it = it->next;
        }
        for (size_type j = 0; j < n; ++j) {
            value_type product = (iti->myVal) * (itj->myVal)+ it->myVal + carry;
            it->myVal = product % powerTwo; 
            carry = product / powerTwo; 
            itj = itj->next;
            it = it->next;
        }  
        if (carry > 0 && (i + n < squareSize)) {
            it->myVal += carry;
        }

        iti = iti->next;
    }

    /**/while (!square.integer.empty() && square.integer.back() == 0) {
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

   size_type sqrtSize = (integer.size() + 1) / 2;
   HugeInteger sqrt(sqrtSize);
   HugeInteger sq;
   size_type mid;
   typename T::iterator it = sqrt.integer.end();
   it = it->prev; // true end

   for (int i = 0; i < sqrtSize; i++) {
       size_type low = 0;
       size_type high = (sizeof(value_type) == 8) ? 9999999 : 999;
       size_type pos = sqrtSize - 1 - i;
      
       while (low <= high) {
           mid = (low + high) / 2;
           it->myVal = mid;
           /*cout << "sqrt" << endl;
           cout << sqrt << endl;
           cout << "integer" << endl;
           cout << *this << endl;
           cout << "sq" << endl;
           cout << sq << endl;*/
           sq = sqrt.square(powerTwo); // 计算中间值的平方
           if (*this == sq) {
               return sqrt; // 找到确切的平方根
           }
           else if ( *this< sq ) { // 如果平方小于原始数
               high = mid - 1;
           }
           else { // 如果平方大于原始数
               low = mid + 1;
           }
       }
       /*     if (*this < sq) {
            --mid;
        }
        sqrt.integer.begin()[pos] = mid;*/
      it->myVal = (*this < sq) ?  (it->myVal = it->myVal - 1):it->myVal;
      it = it->prev;
   }
   return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); it = it->next )
      if( it->myVal != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::iterator it = hugeInteger.integer.end()->prev;
   output << it->myVal;
   for( it = it->prev; it != hugeInteger.integer.begin()->prev; it = it->prev )
      output << setw( numDigits ) << setfill( '0' ) << it->myVal;

   return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
   T powerTwo = 1000;
   if( sizeof( T ) == 8 )
      powerTwo = 10000000;

   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      string str;
      cin >> str;

      HugeInteger< list< T > > hugeInteger( str );

      cout << hugeInteger.squareRoot( powerTwo ) << endl;

      if( i < numCases )
         cout << endl;
   }
}

int main()
{
   // execute the following 4 instructions one by one, each of them should get an AC
   solution< long int >();
//   solution< unsigned long int >();
//   solution< long long int >();
//   solution< unsigned long long int >();
}