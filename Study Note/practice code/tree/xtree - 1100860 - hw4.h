// xtree internal header

#ifndef XTREE
#define XTREE

template< typename Ty >
struct TreeNode
{
   using NodePtr = TreeNode *;
   using value_type = Ty;

   NodePtr    left;   // left subtree, or smallest element if head
   NodePtr    parent; // parent, or root of tree if head
   NodePtr    right;  // right subtree, or largest element if head
   char       color;  // 0: Red, 1: Black; Black if head
   char       isNil;  // 1 only if head (also nil) node
   value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
   using NodePtr = TreeNode< Ty > *;

   using value_type = Ty;
   using size_type  = size_t;

   TreeVal()
      : myHead( new TreeNode< value_type > ),
        mySize( 0 )
   {
      myHead->left = myHead;
      myHead->parent = myHead;
      myHead->right = myHead;
      myHead->color = 1; //black
      myHead->isNil = 1;
   }

   ~TreeVal()
   {
      clear( myHead->parent );
      delete myHead;
   }

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< value_type > *node )
   {
      if( !node->isNil ) // node is not an external node
      {
         clear( node->left );
         clear( node->right );
         delete node;
      }
   }

   // rebalance for insertion; n points to the inserted node
   void reBalance( TreeNode< value_type > *n )
   {  // n->parent cannot be the root
      TreeNode< value_type > *p = n->parent;
      TreeNode< value_type > *g = p->parent;
      TreeNode< value_type > *u; // uncle of n

      if( p == g->left )
         u = g->right;
      else
         u = g->left;

      if( u->color == 0 ) // ( red )
      {
         p->color = 1;
         u->color = 1;

         if( g->parent != myHead ) // g is not the root
         {
            g->color = 0;
            if( ( g->parent )->color == 0 )
               reBalance( g );
         }
      }
      else // u->color == 1 ( black )
      {
         if( n == p->left && p == g->left )
         {
            p->color = 1;
            g->color = 0;
            rightRotation( g );
         }
         if( n == p->left && p == g->right )
         {
            n->color = 1;
            g->color = 0;
            rightRotation( p );
            leftRotation( g );
         }
         if( n == p->right && p == g->left )
         {
            n->color = 1;
            g->color = 0;
            leftRotation( p );
            rightRotation( g );
         }
         if( n == p->right && p == g->right )
         {
            p->color = 1;
            g->color = 0;
            leftRotation( g );
         }
      }
   }

   // rotate right at g
   void rightRotation( TreeNode< value_type > *g )
   {
      TreeNode< value_type > *p = g->left;
      TreeNode< value_type > *temp = p->right;

      /*p->right = g;
      p->parent = g->parent;
      g->parent = p;
      g->left = temp;
      temp->parent = g;*/
      p->right = g;          // 將g設為p的右子節點
      g->left = temp;        // 將p的右子樹設為g的左子樹

      // 更新父節點連結
      if (temp != myHead) // temp 不是 NIL 節點
          temp->parent = g;        // 將g設為temp的父節點

      p->parent = g->parent;       // 將p的父節點設為g的父節點

      // 更新g的父節點
      if (g->parent == myHead) // 如果g是根節點
          myHead->parent = p;  // p成為新的根
      else if (g == g->parent->left)    // 如果g是左子節點
          g->parent->left = p;          // 更新左子連結
      else                              // 如果g是右子節點
          g->parent->right = p;         // 更新右子連結

      g->parent = p;                    // 最後設置g的父節點為p

   }

   // rotate left at g
   void leftRotation( TreeNode< value_type > *g )
   {
      TreeNode< value_type > *p = g->right;
      TreeNode< value_type > *temp = p->left;

      /*p->left = g;
      p->parent = g->parent;
      g->parent = p;
      g->right = temp;
      temp->parent = g;*/
      p->left = g;          
      g->right = temp;      

      // 更新父節點連結
      if (temp != myHead) 
          temp->parent = g;        

      p->parent = g->parent;      

      // 更新g的父節點
      if (g->parent == myHead) 
          myHead->parent = p; 
      else if (g == g->parent->left)    
          g->parent->left = p;          
      else                             
          g->parent->right = p;        

      g->parent = p;
   }

   // erase erasedNode provided that the degree of erasedNode is at most one
   // erasedNode points to the node to be deleted
   // erasedNode == M in "Ch 3 Sec 9.pptx"
   void eraseDegreeOne( TreeNode< value_type > *erasedNode )
   {
      TreeNode< value_type > *child;
      if( erasedNode->left != myHead )
         child = erasedNode->left;
      else if( erasedNode->right != myHead )
         child = erasedNode->right;
      else
         child = myHead;

      if( erasedNode == myHead->parent ) // erasedNode points to the root; Cases 2 & 3 in "Ch 3 Sec 9.pptx"
      {
          if (child == myHead) {
              // 如果树变为空
              myHead->parent = myHead;
              myHead->left = myHead;
              myHead->right = myHead;
          }
          else {
              // 设置新根节点
              myHead->parent = child;
              child->parent = myHead;
              if (child->color == 0)
                  fixUp(child, erasedNode->parent);

              // 更新 myHead->left 指向最小的节点
              TreeNode<value_type>* minNode = myHead->parent;
              while (minNode->left != myHead) {
                  minNode = minNode->left;
              }
              myHead->left = minNode;

              // 更新 myHead->right 指向最大的节点
              TreeNode<value_type>* maxNode = myHead->parent;
              while (maxNode->right != myHead) {
                  maxNode = maxNode->right;
              }
              myHead->right = maxNode;
          }
      }
      else
      {
          TreeNode<value_type>* parent = erasedNode->parent;

          // 更新父节点的子节点指针
          if (erasedNode == parent->left)
              parent->left = child;
          else
              parent->right = child;

          // 更新子节点的父指针
          if (child != myHead)
              child->parent = parent;

          // 更新 myHead 的左右指针
          if (myHead->left == erasedNode) {
              if (child != myHead)
                  myHead->left = child;
              else
                  myHead->left = parent;
          }
          if (myHead->right == erasedNode) {
              if (child != myHead)
                  myHead->right = child;
              else
                  myHead->right = parent;
          }
                   

         if( erasedNode->color == 1 ) 
            if( child->color == 0 ) // Case 2 in "Ch 3 Sec 9.pptx"
               child->color = 1;
            else                   // Case 4 in "Ch 3 Sec 9.pptx"
               fixUp( child, erasedNode->parent );
      
      }

      delete erasedNode;
      mySize--;
   }

   // rebalance for deletion;  // Case 4 in "Ch 3 Sec 9.pptx"
   template<typename value_type>
   void fixUp(TreeNode<value_type>* N, TreeNode<value_type>* P) {
       while (N != myHead->parent && (N == myHead || N->color == 1)) {
           TreeNode<value_type>* S; // N 的兄弟节点

           if (N == P->left) {  // N 是左子节点的情况
               S = P->right;

               // 情况1：兄弟节点S是红色
               if (S->color == 0) {  // 红色=0，黑色=1
                   S->color = 1;      // 兄弟节点变黑
                   P->color = 0;      // 父节点变红
                   leftRotation(P);   // 左旋父节点
                   S = P->right;      // 更新兄弟节点
               }

               // 情况2：兄弟节点和其子节点都是黑色
               if ((S->left == myHead || S->left->color == 1) &&
                   (S->right == myHead || S->right->color == 1)) {
                   S->color = 0;      // 兄弟节点变红
                   N = P;             // 将双黑问题向上传递到父节点
                   P = N->parent;     // 更新父指针
               }
               else {
                   // 情况3：兄弟节点是黑色，其左子节点是红色，右子节点是黑色
                   if (S->right == myHead || S->right->color == 1) {
                       if (S->left != myHead)
                           S->left->color = 1;  // 兄弟的左子节点变黑
                       S->color = 0;            // 兄弟节点变红
                       rightRotation(S);        // 右旋兄弟节点
                       S = P->right;            // 更新兄弟节点
                   }

                   // 情况4：兄弟节点是黑色，其右子节点是红色
                   S->color = P->color;         // 兄弟节点继承父节点的颜色
                   P->color = 1;                // 父节点变黑
                   if (S->right != myHead)
                       S->right->color = 1;     // 兄弟的右子节点变黑
                   leftRotation(P);             // 左旋父节点
                   N = myHead->parent;          // 将N设置为根节点以结束循环
                   P = N->parent;               // 更新父节点指针
               }
           }
           else {  // N 是右子节点的情况 - 与上述情况对称
               S = P->left;

               // 情况1：兄弟节点是红色
               if (S->color == 0) {
                   S->color = 1;
                   P->color = 0;
                   rightRotation(P);
                   S = P->left;
               }

               // 情况2：兄弟节点和其子节点都是黑色
               if ((S->left == myHead || S->left->color == 1) &&
                   (S->right == myHead || S->right->color == 1)) {
                   S->color = 0;
                   N = P;
                   P = N->parent;
               }
               else {
                   // 情况3：兄弟节点是黑色，其右子节点是红色，左子节点是黑色
                   if (S->left == myHead || S->left->color == 1) {
                       if (S->right != myHead)
                           S->right->color = 1;
                       S->color = 0;
                       leftRotation(S);
                       S = P->left;
                   }

                   // 情况4：兄弟节点是黑色，其左子节点是红色
                   S->color = P->color;
                   P->color = 1;
                   if (S->left != myHead)
                       S->left->color = 1;
                   rightRotation(P);
                   N = myHead->parent;          // 将N设置为根节点以结束循环
                   P = N->parent;               // 更新父节点指针
               }
           }
       }

       if (N != myHead)  // 确保节点为黑色（如果存在）
           N->color = 1;
   }
   NodePtr myHead;   // pointer to head node
   size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
   using value_type = typename Traits::value_type;

protected:
   using ScaryVal = TreeVal< value_type >;

public:
   using key_type      = typename Traits::key_type;
   using key_compare   = typename Traits::key_compare;

   using size_type       = size_t;

   Tree( const key_compare &parg )
      : keyCompare( parg ),
        scaryVal()
   {
   }

   ~Tree()
   {
   }

   // Extends the container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const value_type &val )
   {
      if( scaryVal.mySize == 0 )
      {
         TreeNode< value_type > *root = new TreeNode< value_type >;
         root->myval = val;
         root->left = scaryVal.myHead;
         root->right = scaryVal.myHead;
         root->isNil = 0;
         root->parent = scaryVal.myHead;
         root->color = 1;
         scaryVal.myHead->left = root;
         scaryVal.myHead->parent = root;
         scaryVal.myHead->right = root;
         scaryVal.mySize = 1;
      }
      else
      {                           // scaryVal.myHead->parent points to the root
         TreeNode< value_type > *tryNode = scaryVal.myHead->parent; // tryNode points to the root
         TreeNode< value_type > *result = nullptr;
         while( tryNode != scaryVal.myHead )
         {
            result = tryNode;
//              keyCompare.operator()( val, tryNode->myval )
            if( keyCompare( val, tryNode->myval ) ) // if( val < tryNode->myval )
               tryNode = tryNode->left;
            else if( keyCompare( tryNode->myval, val ) ) // if( val > tryNode->myval )
               tryNode = tryNode->right;
            else
               return;
         }

         // new node
         TreeNode< value_type >* newNode = new TreeNode< value_type >;
         newNode->myval = val;
         newNode->left = scaryVal.myHead;  // 左子節點為 NIL
         newNode->right = scaryVal.myHead; // 右子節點為 NIL
         newNode->isNil = 0;
         newNode->color = 0; // 新節點為紅色
         newNode->parent = result;

         // 根據比較結果決定新節點插入為左或右子節點
         if (keyCompare(val, result->myval)) // 如果 val < result->myval
             result->left = newNode;         // 插入為左子節點
         else
             result->right = newNode;        // 插入為右子節點\


         //  renew myHead->right(大)  / left (小)
         if (keyCompare(newNode->myval, scaryVal.myHead->left->myval)) 
             scaryVal.myHead->left = newNode;
         
         if (keyCompare(scaryVal.myHead->right->myval, newNode->myval)) 
             scaryVal.myHead->right = newNode;
         

         // 更新樹的大小
         scaryVal.mySize++;
         // question reblance  when can rebalance
         // solution check 5 rule -> number 5 must use reblance


         // use another stage the outcome
         //case 1 are in if{}
         //case 2 N is not the root of the tree, and P is black.
         if (newNode->parent->color == 0)
             scaryVal.reBalance(newNode);
         //case 3 4  are same to case 2 
        
      }
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
      TreeNode< key_type > *erasedNode = scaryVal.myHead->parent; // erasedNode points to the root
      while( erasedNode != scaryVal.myHead && val != erasedNode->myval )
      {
          // binary search tree
//           keyCompare.operator()( val, erasedNode->myval )
         if( keyCompare( val, erasedNode->myval ) ) // if( val < erasedNode->myval )
            erasedNode = erasedNode->left;
         else
            erasedNode = erasedNode->right;
      }

      if( erasedNode == scaryVal.myHead ) // not found
         return 0;
      else // found
      {  // deletes the node pointed by erasedNode


          if (erasedNode->left != scaryVal.myHead && erasedNode->right != scaryVal.myHead)
          {
              TreeNode<key_type>* successor = erasedNode->right;
              // 找到右子樹的最小節點（後繼節點）
              while (successor->left != scaryVal.myHead)
                  successor = successor->left;

              // 交換值，並讓 erasedNode 指向後繼節點（準備刪除後繼節點）
              erasedNode->myval = successor->myval;
              erasedNode = successor;
          }

          // 此時 erasedNode 的子節點數量至多為 1
          scaryVal.eraseDegreeOne(erasedNode);

         return 1;
      }
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE