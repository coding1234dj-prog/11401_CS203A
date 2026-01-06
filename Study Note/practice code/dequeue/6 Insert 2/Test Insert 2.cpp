#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "1100860- deque - insert.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testInsert();

template< typename T >
void testInsert1();

template< typename T >
void testInsert2();

template< typename T >
void testInsert3();

int main()
{
   testInsert< char >();

   testInsert< short >();

   testInsert< long >();

   testInsert< long long >();
}

template< typename T >
void testInsert()
{
   testInsert1< T >();

   testInsert2< T >();

   testInsert3< T >();
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
void testInsert1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = ( sizeof( T ) <= 2 ) ? 8 : 4 * sizeof( T );
   size_t numErrors = 0;
   size_t preNumErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            for( size_t position = 0; position <= mySize; ++position )
            {
               deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** > ( &deque1 );
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

               *mapSize1 = mapSize;
               *map1 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *mySize1 = mySize;

               T **map1Address = *map1;
               T **map2 = new T * [ mapSize ]();

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  map2[ block % mapSize ] = ( *map1 )[ block % mapSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i / dequeSize % mapSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.insert( deque1.begin() + position, static_cast< T >( myOff + mySize ) );

               if( position <= mySize / 2 )
               {
                  if( ( *myOff1 + 1 ) % ( dequeSize * mapSize ) != myOff )
                     numErrors++;
               }
               else
                  if( *myOff1 != myOff )
                     numErrors++;

               if( *mySize1 != mySize + 1 )
                  numErrors++;

               if( *mapSize1 == mapSize )
                  if( *map1 != map1Address )
                     numErrors++;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
                  if( ( *map1 )[ block % *mapSize1 ] != map2[ block % mapSize ] )
                     numErrors++;
            }
         }

         if( ( mapSize == 4 * sizeof( T ) && myOff % 16 == 15 ) ||
             ( mapSize == 8 * sizeof( T ) && myOff % 4 == 3 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testInsert2()
{
   size_t numErrors = 0;
   deque< T > deque1;
   T ***map1 = reinterpret_cast< T *** > ( &deque1 );
   size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
   size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
   size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

   *mapSize1 = 0;
   *myOff1 = 0;
   *mySize1 = 0;

   T value = 1 + rand() % 99;
   deque1.insert( deque1.begin(), value );

   if( *myOff1 != 8 * compDequeSize< T >() - 1 )
      numErrors++;

   if( *mySize1 != 1 )
      numErrors++;

   if( *mapSize1 != 8 )
      numErrors++;
   
   if( *map1 == nullptr )
      numErrors++;

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testInsert3()
{
   size_t numErrors = 0;
   const size_t maxMapSize = 256;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      *mapSize1 = mapSize;
      *map1 = new T * [ mapSize ]();
      *myOff1 = 0;
      *mySize1 = 0;

      T value = 1 + rand() % 99;
      deque1.insert( deque1.begin(), value );

      if( *myOff1 != mapSize * compDequeSize< T >() - 1 )
         numErrors++;

      if( *mySize1 != 1 )
         numErrors++;

      if( *mapSize1 != mapSize )
         numErrors++;
      
      if( *map1 == nullptr )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}