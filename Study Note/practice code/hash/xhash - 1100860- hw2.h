// xhash internal header

#ifndef XHASH
#define XHASH

#include <list>
using std::list;

#include "type_traits.h"

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using pointer    = value_type *;

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

template< typename Iter >
struct HashVec
{
   using value_type = Iter;
   using size_type  = size_t;

   HashVec()
      : myData()
   {
   }

   // set the elements stored here to cells copies of val
   void assignGrow( const size_type cells, const value_type val )
   {
      if( myData.myFirst < myData.myEnd ) // nonempty
         delete[] myData.myFirst;

      myData.myFirst = new value_type[ cells ]();
      myData.myLast = myData.myEnd = myData.myFirst + cells;
      for( value_type *p = myData.myFirst; p < myData.myLast; ++p )
         *p = val;
   }

   ~HashVec()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   VectorVal< value_type > myData;
};

// CLASS TEMPLATE Hash
template< typename Traits >
class Hash // hash table -- list with vector of iterators for quick access
{
protected:
   using MyList         = list< typename Traits::value_type >;
   using KeyCompare     = typename Traits::key_compare;

public:
   using key_type       = typename Traits::key_type;
   using value_type     = typename MyList::value_type;
   using size_type      = typename MyList::size_type;

   using iterator       = typename MyList::const_iterator;
   using const_iterator = typename MyList::const_iterator;

   static const size_type MinBuckets = 8; // must be a positive power of 2

protected:
   Hash( const KeyCompare &parg ) // construct empty hash table
      : traitsObj( parg ), // copy
        myList(),
        myVec(),
        mask( MinBuckets - 1 ),
        maxidx( MinBuckets )
   {     
      myVec.assignGrow( MinBuckets * 2, myList.end() );
   }

public:
   // Returns the number of elements in the unordered_set container.
   size_type size() const
   {
      return myList.size();
   }

   // Returns the number of buckets in the unordered_set container.
   size_type bucket_count() const
   {
      return maxidx;
   }

   // Returns the bucket number where the element with value keyVal is located.
   size_type bucket( const key_type& keyVal ) const
   {
      return traitsObj( keyVal ) & mask;
//      return traitsObj.operator()( keyVal ) & mask;
//      return traitsObj( keyVal ) % maxidx;
//      return traitsObj.operator()( keyVal ) % maxidx;
   }

   // Returns the number of elements in bucket n.
   size_type bucket_size( size_type n ) const
   {
      if( n >= maxidx )
         return 0;

      // bucket[ n ] is empty
      if( myVec.myData.myFirst[ 2 * n ] == myList.end() )
         return 0;

      // bucket[2*n] = bucket[2*n + 1]  only 1 element
      if (myVec.myData.myFirst[2 * n] == myVec.myData.myFirst[2 * n + 1])
          return 1;

      size_type count = 0;
      auto it = myVec.myData.myFirst[2 * n]; // 獲取桶的起始迭代器 auto 自動獲得變量的類型

      // 從起始迭代器遍歷直到桶的結尾迭代器
      while (it != myVec.myData.myFirst[2 * n + 1]) {
          ++count;  // 計數元素
          ++it;     // 移動到下一個元素
      }

      // 返回總計數，記得包括最後一個元素
      return count + 1;


   }

   // Inserts a new element in the unordered_set.
   // The element is inserted only if it is not equivalent to any other element
   // already in the container ( elements in an unordered_set have unique values ).
   // This effectively increases the container size by one.
   void insert( const value_type &val )
   {
      if( find( val ) == myList.end() )
      {
         if( myList.size() == maxidx )
         {
            if( maxidx == 8 || maxidx == 64 )
               maxidx *= 8;
            else
               maxidx *= 2;
            mask = maxidx - 1;

            myVec.assignGrow( 2 * maxidx, myList.end() );

            MyList oldList(myList);
            myList.clear();
            for (iterator it = oldList.begin(); it != oldList.end(); ++it)
                putIn(*it);
            oldList.clear();
         }

         putIn( val );
      }
   }

   // Removes from the unordered_set a single element.
   // This effectively reduces the container size by one.
   void erase( const key_type &keyVal )
   {
      iterator it = find( keyVal );

      if( it != myList.end() ) // found
      {
         size_type bucketNo = bucket( keyVal );

         if (myVec.myData.myFirst[2 * bucketNo] == it)
         {
             // 如果桶中有多個元素，更新桶的起點為下一個元素
             if (myVec.myData.myFirst[2 * bucketNo + 1] != it)
             {
                 myVec.myData.myFirst[2 * bucketNo] = std::next(it);
             }
             else  // 如果桶中只有一個元素，將該桶標記為空
             {
                 myVec.myData.myFirst[2 * bucketNo] = myList.end();
                 myVec.myData.myFirst[2 * bucketNo + 1] = myList.end();
             }
         }

         // 如果 it 是桶的最後一個元素
         else if (myVec.myData.myFirst[2 * bucketNo + 1] == it)
         {
            myVec.myData.myFirst[2 * bucketNo + 1] = std::prev(it);            
         }

         //為中間的元素則直接刪除
         myList.erase( it );
      }
   }

   // Searches the unordered_set for an element with keyVal as value and
   // returns an iterator to it if found, otherwise it returns myList.end()
   iterator find( const key_type &keyVal )
   {
      size_type bucketNo = bucket( keyVal );

      // bucket[ bucketNo ] is empty
      if( myVec.myData.myFirst[ 2 * bucketNo ] == myList.end() )
         return myList.end();


      iterator it = myVec.myData.myFirst[2 * bucketNo];       // 桶的起点
      iterator lastInBucket = myVec.myData.myFirst[2 * bucketNo + 1]; // 桶的最后一个元素

      // 处理桶中只有一个元素的情况
      if (it == lastInBucket)
          return (*it == keyVal) ? it : myList.end();

      // !=  myVec.myData.myFirst[2 * bucketNo + 1] 會跑不到最後一個
      // 遍历桶中的所有元素，包括最后一个
      do {
          if (*it == keyVal)
              return it;
      } while (it++ != lastInBucket);
      

      return myList.end();
   }

private:
   // put a new element in the unordered_set when myVec is large enough
   void putIn( const value_type &val )
   {
      size_type bucketNo = bucket( val );

      if (myVec.myData.myFirst[2 * bucketNo] == myList.end())
      {
          myList.push_back(val);
          //back() 是return 值
          iterator pos = std::prev(myList.end());
          myVec.myData.myFirst[2 * bucketNo] = pos;
          myVec.myData.myFirst[2 * bucketNo + 1] = pos; 
      }
      else
      {
          // 桶已经有元素，获取桶中第一个元素的位置
          auto insertPos = myVec.myData.myFirst[2 * bucketNo];
          auto newPos = myList.insert(insertPos, val);  // 返回插入元素的位置
          myVec.myData.myFirst[2 * bucketNo] = newPos;

      }

   }

protected:
   Traits traitsObj;          // traits to customize behavior
   MyList myList;             // list of elements, must initialize before myVec
   HashVec< iterator > myVec; // "vector" of list iterators for buckets:
                              // each bucket is 2 iterators denoting
                              // the closed range of elements in the bucket,
                              // or both iterators set to end() if the bucket is empty.
   size_type mask;            // the key mask, equals maxidx - 1
   size_type maxidx;          // current maximum key value, must be a power of 2
};

#endif // XHASH