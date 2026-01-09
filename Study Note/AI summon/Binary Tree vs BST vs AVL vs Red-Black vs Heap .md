# 樹的家族比較：Binary Tree vs BST vs AVL vs Red-Black vs Heap

## 樹的進化史

```
Binary Tree (二元樹)
    ↓ 加入「左小右大」規則
Binary Search Tree (BST)
    ↓ 加入「平衡」保證
Balanced BST
    ├─ AVL Tree (嚴格平衡)
    ├─ Red-Black Tree (寬鬆平衡)
    └─ B-Tree (多路平衡)

Heap (堆)
    ← 特殊的完全二元樹，只關心「父大於子」
```

## 核心差異總表

| 樹類型 | 核心特性 | 查找 | 插入 | 刪除 | 主要用途 |
|-------|---------|------|------|------|---------|
| **Binary Tree** | 每節點最多 2 子 | O(n) | - | - | 表達階層關係 |
| **BST** | 左 < 根 < 右 | O(log n)* | O(log n)* | O(log n)* | 動態有序資料 |
| **AVL** | BST + 高度平衡 | O(log n) | O(log n) | O(log n) | 查詢密集場景 |
| **Red-Black** | BST + 顏色平衡 | O(log n) | O(log n) | O(log n) | 讀寫平衡場景 |
| **Heap** | 父 ≥ 子（Max）| O(n) | O(log n) | O(log n)** | 優先佇列 |

\* 平均情況，最壞 O(n)  
\*\* 僅刪除最大值

## 詳細拆解

### 1. Binary Tree（二元樹）

```
定義：每個節點最多有 2 個子節點

特點：
- 最基礎的樹結構
- 沒有排序要求
- 沒有平衡要求

變體：
- Full Binary Tree:  每節點 0 或 2 個子節點
- Complete Binary Tree: 除最後一層外都填滿，最後一層靠左
- Perfect Binary Tree: 所有葉節點在同一層

應用場景：
✓ 表達式樹（數學表達式）
✓ 決策樹
✓ 資料夾結構
✓ HTML DOM 樹

不適合：
✗ 搜尋操作（無序，需遍歷）
✗ 動態維護有序資料

程式碼：
class Node {
    int val;
    Node left, right;
}
```

### 2. Binary Search Tree（二元搜尋樹）

```
定義：左子樹 < 根 < 右子樹（遞迴適用）

特點：
+ 中序遍歷 = 有序輸出
+ 平均 O(log n) 操作
- 可能退化成鏈（最壞 O(n)）

插入規則：
- 比根小 → 往左
- 比根大 → 往右
- 重複值？看定義（忽略 / 計數 / 插入左或右）

刪除規則：
1. 葉節點：直接刪
2. 一個子節點：子節點替代
3. 兩個子節點：用「右子樹最小」或「左子樹最大」替代

何時退化：
❌ 輸入已排序：1,2,3,4,5
❌ 輸入接近排序
結果：變成鏈狀，高度 = n

面試陷阱：
Q: "設計一個支援快速查找的結構"
錯誤：用普通 BST（沒提到防退化）
正確：強調要用「平衡」BST 或說明假設隨機輸入

程式碼關鍵：
Node insert(Node root, int val) {
    if (root == null) return new Node(val);
    if (val < root.val) 
        root.left = insert(root.left, val);
    else 
        root.right = insert(root.right, val);
    return root;
}
```

### 3. AVL Tree（嚴格平衡樹）

```
定義：BST + 任一節點的左右子樹高度差 ≤ 1

平衡因子：BF = height(left) - height(right)
有效範圍：-1, 0, 1

旋轉操作（插入後可能需要）：
1. LL (Left-Left):   右旋
2. RR (Right-Right): 左旋
3. LR (Left-Right):  先左旋後右旋
4. RL (Right-Left):  先右旋後左旋

優點：
✓ 查詢最快（樹高最小 ~1.44 log n）
✓ 最壞情況有保證
✓ 結構穩定

缺點：
✗ 插入/刪除需要更多旋轉
✗ 實作複雜
✗ 刪除操作可能需要 O(log n) 次旋轉
✗ 常數因子較大

適用場景：
✓ 查詢遠多於插入/刪除（讀多寫少）
✓ 需要最快查詢速度
✓ 資料相對穩定

不適合：
✗ 頻繁插入刪除
✗ 對插入效能敏感

記憶技巧：
AVL = "A Very strict Leveling"
想像潔癖強迫症，容不得一點不平衡

程式碼關鍵：
int height(Node n) {
    return n == null ? 0 : n.height;
}

int getBalance(Node n) {
    return n == null ? 0 : height(n.left) - height(n.right);
}

Node rightRotate(Node y) {
    Node x = y.left;
    Node T2 = x.right;
    x.right = y;
    y.left = T2;
    // 更新高度
    y.height = max(height(y.left), height(y.right)) + 1;
    x.height = max(height(x.left), height(x.right)) + 1;
    return x;
}
```

### 4. Red-Black Tree（紅黑樹）

```
定義：BST + 顏色規則實現平衡

五大規則：
1. 每個節點非紅即黑
2. 根節點是黑色
3. 葉節點(NIL)是黑色
4. 紅色節點的子節點必須是黑色（不能有連續紅）
5. 從根到葉的任意路徑，黑色節點數相同（黑高度）

平衡保證：
- 最長路徑 ≤ 2 * 最短路徑
- 樹高 ≤ 2 log(n+1)

旋轉次數：
- 插入：最多 2 次旋轉
- 刪除：最多 3 次旋轉
（AVL 刪除可能 O(log n) 次）

優點：
✓ 插入/刪除比 AVL 快
✓ 最多 3 次旋轉（常數時間重平衡）
✓ 實務中表現優異
✓ 工業標準（C++ STL, Java TreeMap）

缺點：
✗ 查詢稍慢於 AVL（樹稍高）
✗ 實作非常複雜（40+ 種情況）
✗ 難以理解和 debug

適用場景：
✓ 讀寫操作都頻繁（通用場景）
✓ 需要保證效能但不要太複雜的旋轉
✓ 標準庫實作（大多數語言選擇）

記憶技巧：
Red-Black = 紅黑兩色有彈性
比 AVL 寬鬆但比 BST 穩定
通用中庸之道

實際應用：
- C++ std::map, std::set
- Java TreeMap, TreeSet
- Linux CFS 調度器
```

### 5. Heap（堆）

```
定義：完全二元樹 + 堆性質

堆性質：
- Max Heap: parent ≥ children（最大值在根）
- Min Heap: parent ≤ children（最小值在根）

關鍵差異：
與 BST 不同！
- BST: 左 < 根 < 右（嚴格有序）
- Heap: 父 > 子（只保證局部性質）

結構特點：
- 完全二元樹（可用陣列表示）
- 陣列索引關係：
  parent(i) = (i-1) / 2
  left(i) = 2*i + 1
  right(i) = 2*i + 2

操作：
- getMax/Min:  O(1) 直接回傳 root
- insert:      O(log n) 上濾(bubble up)
- extractMax:  O(log n) 下濾(bubble down)
- heapify:     O(n) 從陣列建堆

核心操作：
上濾（Bubble Up）：
插入到最後，與父節點比較，不符合就交換，重複直到符合

下濾（Bubble Down）：
移除根後，最後元素放到根，與較大子節點比較交換，重複

優點：
✓ 實作簡單（用陣列）
✓ 空間效率高（無指標開銷）
✓ O(1) 取極值
✓ 快取友善（連續記憶體）

缺點：
✗ 搜尋任意元素 O(n)
✗ 無法有序遍歷
✗ 不支援範圍查詢

適用場景：
✓ Priority Queue（優先佇列）
✓ Heap Sort（堆排序）
✓ Top K 問題（找前 K 大/小）
✓ 中位數維護（兩個 Heap）
✓ Dijkstra 最短路徑
✓ 任務調度

不適合：
✗ 需要搜尋任意值
✗ 需要有序輸出全部
✗ 需要範圍查詢

程式碼：
class MinHeap {
    private int[] heap;
    private int size;
    
    void bubbleUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap, index, parent);
            index = parent;
        }
    }
    
    void bubbleDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
            
            if (left < size && heap[left] < heap[smallest])
                smallest = left;
            if (right < size && heap[right] < heap[smallest])
                smallest = right;
                
            if (smallest == index) break;
            swap(heap, index, smallest);
            index = smallest;
        }
    }
}
```

## 容易混淆的點

### 混淆 1：BST vs Heap

```
❌ 錯誤理解：Heap 也是搜尋樹
✓ 正確理解：

BST: 
- 左 < 根 < 右（全局有序）
- 中序遍歷 = 排序結果
- 可搜尋任意值 O(log n)

Heap:
- 父 > 子（局部性質）
- 無法有序遍歷
- 只能快速找極值

視覺對比：
     BST          Max Heap
      5               9
     / \             / \
    3   7           7   6
   / \   \         / \
  1   4   8       3   5

BST 中序：1,3,4,5,7,8（有序）
Heap 遍歷：9,7,6,3,5（無序）
```

### 混淆 2：AVL vs Red-Black

```
常見誤區："AVL 一定比 RB 好"

實際情況：
查詢為主 → AVL 稍快（樹更矮）
插入刪除多 → RB 更快（旋轉少）
通用場景 → RB（工業標準）

數據對比：
               AVL        RB
查詢          1.00x      1.05x
插入（隨機）   1.20x      1.00x
刪除          1.50x      1.00x

這就是為什麼 STL 選 RB 不選 AVL
```

### 混淆 3：Complete vs Perfect Binary Tree

```
Complete（完全二元樹）：
- 除最後一層外都填滿
- 最後一層靠左填充
- Heap 就是 Complete Binary Tree

      1
     / \
    2   3
   / \
  4   5

Perfect（完美二元樹）：
- 所有層都填滿
- 葉節點都在最後一層
- 節點數 = 2^h - 1

      1
     / \
    2   3
   / \ / \
  4  5 6  7

關鍵：
- Heap 要求 Complete（陣列無空洞）
- Perfect 是 Complete 的特例
```

## 面試高頻問題

### Q1: 為什麼 Heap 不能用來做一般搜尋？

```
因為 Heap 只保證「父子關係」，不保證「左右關係」

例如 Max Heap:
       9
      / \
     7   6
    / \
   3   5

問：能快速找到 6 嗎？
答：不能！必須遍歷，因為：
- 6 可能在左子樹（比 7 小）
- 也可能在右子樹（實際在這）
- 無法像 BST 那樣「往左或往右」決策

Heap 設計目的：
✓ 快速找極值
✗ 不是用來搜尋的
```

### Q2: 實務中真的會自己實作 AVL/RB 嗎？

```
短答案：基本不會

原因：
1. 複雜度極高（RB 樹有 40+ 種情況）
2. 標準庫已提供（C++ map, Java TreeMap）
3. 容易出 bug
4. 維護成本高

什麼時候會實作：
✓ 面試考察（理解原理）
✓ 特殊需求（如持久化樹）
✓ 學習目的
✓ 極致優化場景（客製化）

面試時的回答策略：
"實務中我會用 std::map，它底層是 RB 樹，
保證 O(log n)。但如果需要實作，我理解
平衡的核心是[解釋旋轉原理]..."
```

### Q3: Top K 問題為什麼用 Heap 不用排序？

```
問題：在 100 萬個數中找最大的 10 個

方案對比：
1. 完全排序：O(n log n) = 100 萬 * 20
2. Min Heap (size=K): O(n log K) = 100 萬 * 3.3

Heap 做法：
- 維護大小為 K 的 Min Heap
- 遍歷元素，若大於堆頂就替換
- 最後堆內就是 Top K

為什麼快：
- 不需要排序全部
- 只維護 K 個元素（K << n）
- log K << log n

程式碼：
PriorityQueue<Integer> minHeap = new PriorityQueue<>(K);
for (int num : nums) {
    if (minHeap.size() < K) {
        minHeap.offer(num);
    } else if (num > minHeap.peek()) {
        minHeap.poll();
        minHeap.offer(num);
    }
}
```

### Q4: 什麼時候選 AVL，什麼時候選 RB？

```
決策框架：

選 AVL：
✓ 查詢遠多於插入刪除（讀寫比 > 10:1）
✓ 對查詢延遲極度敏感
✓ 資料相對靜態

選 Red-Black：
✓ 讀寫操作都頻繁（讀寫比 < 5:1）
✓ 插入刪除較多
✓ 不確定時的預設選擇
✓ 想用標準庫實作

現實中的選擇：
大多數情況 → Red-Black（通用性）
特定優化 → AVL（明確的讀密集場景）

記住：
"不確定時選 Red-Black，
它是有理由成為工業標準的"
```

## 選擇決策樹

```
需要樹形結構？
    ↓
需要快速搜尋嗎？
    ↓ 是              ↓ 否
    需要有序嗎？        表達階層 → Binary Tree
    ↓ 是    ↓ 否
    保證效能？  只需極值？
    ↓ 是   ↓ 否   ↓
    讀多？  BST   Heap
    ↓ 是  ↓ 否   (Priority Queue)
    AVL   RB
```

## 記憶口訣

```
Binary Tree: 自由樹，表達結構用
BST:        有序樹，搜尋好但會歪
AVL:        強迫症，平衡最嚴格，查最快
Red-Black:  中庸道，工業標準選擇
Heap:       只看頂，優先隊列王

查詢密集 AVL 強
讀寫平衡 RB 穩
只要極值 Heap 用
通用不知選 RB 對
```

## 複雜度速查表

| 操作 | BST | AVL | Red-Black | Heap |
|-----|-----|-----|-----------|------|
| 搜尋 | O(log n)* | O(log n) | O(log n) | O(n) |
| 插入 | O(log n)* | O(log n) | O(log n) | O(log n) |
| 刪除 | O(log n)* | O(log n) | O(log n) | O(log n)** |
| 找最小 | O(log n)* | O(log n) | O(log n) | O(1) |
| 有序遍歷 | O(n) | O(n) | O(n) | ✗ |
| 空間 | O(n) | O(n) | O(n) | O(n) |

\* 平均，最壞 O(n)  
\*\* 僅針對根節點

---

**面試黃金句：**
> "樹的選擇不是比誰更好,而是比誰更適合。Heap 找極值最快但不能搜尋,AVL 查詢最快但插入慢,Red-Black 是工業界的平衡選擇。了解各自的權衡才能做出正確決策。"

**面試準備建議：**
1. 能手寫 BST 的插入/刪除
2. 理解 AVL 的旋轉（不用完全手寫）
3. 能解釋 RB 的平衡原理（不用手寫）
4. 熟練使用 Heap 解 Top K 問題
5. 知道什麼時候用哪個
