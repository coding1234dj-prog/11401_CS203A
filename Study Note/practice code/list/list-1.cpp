// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list 6-1.h" // include definition of class template list

template< typename T >
void testList();

template< typename T >
void testFillConstructor();

template< typename T >
void testCopyConstructor();

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
   testFillConstructor< T >();
   testCopyConstructor< T >();
   cout << endl;
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

const int number = 500;

template< typename T >
void testFillConstructor()
{
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
   {
      list< T > list1( n );
      std::list< T > list2( n );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
      for( int i = 1; i <= n; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         *( p2 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         p2 = *( reinterpret_cast< size_t ** >( p2 ) );
      }

      if( !equal( list1, list2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor()
{
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
   {
      list< T > list1( n );
      std::list< T > list2( n );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
      for( int i = 1; i <= n; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         *( p2 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         p2 = *( reinterpret_cast< size_t ** >( p2 ) );
      }

      list< T > list3( list1 );
      std::list< T > list4( list2 );

      if( !equal( list3, list4 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n";
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