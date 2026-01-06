// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list 6-4.h" // include definition of class template list

template< typename T >
void testList();

template< typename T >
void testResize1();

template< typename T >
void testResize2();

template< typename T >
bool efficientResize( list< T > &list1, size_t n, size_t length );

// return true iff list1 == list2
template< typename T >
bool equal( list< T > &list1, std::list< T > &list2 );

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testList< char >();
   testList< short >();
   testList< long >();
   testList< long long >();

   system( "pause" );
}

template< typename T >
void testList()
{
   testResize1< T >();
   testResize2< T >();
   cout << endl;
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

template< typename T >
void testResize1()
{
   const int number = 70;
   int numErrors = 0;
   for( size_t n = 0; n < number; n++ )
      for( size_t length = 0; length < number; length++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
         size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
         size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
         size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
         for( size_t i = 1; i <= n; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p1 + 2 ) = value;
            *( p2 + 2 ) = value;
            p1 = *( reinterpret_cast< size_t ** >( p1 ) );
            p2 = *( reinterpret_cast< size_t ** >( p2 ) );
         }

         list1.resize( length );
         list2.resize( length );

         if( !equal( list1, list2 ) )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testResize2()
{
   const int number = 100;
   int numErrors = 0;
   for( size_t n = 0; n < number; n++ )
      for( size_t length = 0; length < number; length++ )
      {
         list< T > list1( n );

         size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
         size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
         for( size_t i = 1; i <= n; i++ )
         {
            *( p1 + 2 ) = 1 + rand() % 99;
            p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         }

         if( !efficientResize( list1, n, length ) )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

// return true iff the addresses of nodes in list1[0 .. minSize]
// keep unchanged after list1.resize( length )
template< typename T >
bool efficientResize( list< T > &list1, size_t n, size_t length )
{
   size_t minSize = ( n < length ) ? n : length;
   // let k = minSize, and node 1, node 2, ..., node k be the first k nodes of list1.

   typename list< T >::iterator *addresses = new typename list< T >::iterator[ minSize + 1 ];

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   typename list< T >::iterator p = list1.begin();
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      addresses[ i ] = p; // save the address of node i

   // addresses[ i ] is the address of node i before the excution of list1.resize( length ).

   list1.resize( length );

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   p = list1.begin();
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      // p is the address of node i after the excution of list1.resize( length )
      if( addresses[ i ] != p )
         return false;

   // addresses[ i ] == p if and only if
   // node i of list1 before the excution of list1.resize( length ) is the same node as
   // node i of list1 after the excution of list1.resize( length )

   delete[] addresses;

   return true;
}

// return true iff list1 == list2
template< typename T >
bool equal( list< T > &list1, std::list< T > &list2 )
{
   if( list1.size() != list2.size() ) // different number of elements
      return false;

   if( list2.size() == 0 )
      return true;

   typename list< T >::iterator it1 = list1.begin();
   typename std::list< T >::iterator it2 = list2.begin();
   for( ; it2 != list2.end(); it1 = it1->next, ++it2 )
      if( it1->myVal != *it2 )
         return false;

   return true;
}