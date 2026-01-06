// algorithm standard header

#ifndef ALGORITHM
#define ALGORITHM

namespace MyNamespace
{

    /*  RanIt first：指向堆容器的開始位置。
        ptrdiff_t hole：表示插入或移動元素的位置索引。
        ptrdiff_t top：指向堆的頂端索引（通常是0）。
        Ty &val：插入或調整的元素。
        Pr pred：比較用的謂詞（predicate），用於決定是最小堆還是最大堆。
    */
   template< typename RanIt, typename Ty, typename Pr >
   inline void pushHeapByIndex( RanIt first, ptrdiff_t hole, ptrdiff_t top, Ty &val, Pr pred )
   {
       /**/
     //initial position
       auto idx = (hole - 1) / 2;

       // min heap
       //pred(val, c(idx)) = val < or >  c.idx => return bool 
       while (hole > top && !pred(val, *(first + idx))) {
           *(first + hole) = *(first + idx);  // 父節點移動到當前“洞”位置
           hole = idx;  // go up
           idx = (hole - 1) / 2;  // news parent node
       }
           
       *(first + hole) = val;

   }

   // push *(last - 1) onto heap at [first, last - 1), using pred
   template< typename RanIt, typename Pr >
   inline void push_heap( RanIt first, RanIt last, Pr pred )
   {
      ptrdiff_t count = last - first;
      if( count >= 2 )
      {
         --last;
         typename RanIt::value_type val = *last;
         --count;
         pushHeapByIndex( first, count, 0, val, pred );
      }
   }

   template< typename RanIt, typename Ty, typename Pr >
   inline void popHeapHoleByIndex( RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty &val, Pr pred )
   {
       //initial idx = left children  2*i + 1
       /**/auto idx = hole * 2 + 1;

       while (idx < bottom) {
           if (idx + 1 < bottom && ( pred(*(first + idx), *(first + idx + 1)) || *(first+idx) == *(first+idx+1))) {
               idx++;  // 選擇右子節點
           }

           // 如果當前值已經比子節點更優，則停止
           if (!pred(val, *(first + idx))) {
               break;
           }


           *(first + hole) = *(first + idx);
           hole = idx;
           idx = hole * 2 + 1;
       }     
       *(first + hole) = val;

   }

   // pop *first to *(last - 1) and reheap, using pred
   template< typename RanIt, typename Pr >
   inline void pop_heap( RanIt first, RanIt last, Pr pred )
   {
      if( last - first >= 2 )
      {
         --last;
         typename RanIt::value_type val = *last;
         popHeapHoleByIndex( first, 0, last - first, val, pred );
      }
   }

   // make [first, last) into a heap, using pred
   template< typename RanIt, typename Pr >
   inline void make_heap( RanIt first, RanIt last, Pr pred )
   {
      ptrdiff_t bottom = last - first;
      ptrdiff_t hole = bottom / 2;
      while( hole > 0 )
      {
         // reheap top half, bottom to top
         --hole;
         typename RanIt::value_type val = *( first + hole );
         popHeapHoleByIndex( first, hole, bottom, val, pred );
      }
   }
}

#endif // ALGORITHM