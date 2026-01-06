### AI 補充

### Tree (樹)

你的筆記中涵蓋了樹的基本定義、術語、類型（如二元樹、紅黑樹）和一些特性，但有部分拼寫錯誤（如 "BFS 先走一個子樹根再另外一個 (深度優先)" 應為 DFS 是深度優先，BFS 是廣度優先），並缺少 traversal (遍歷) 的詳細說明、時間複雜度和範例。我會修正並補充完整結構，包括常見操作和應用。

#### 基本定義
- **Tree**: 一種無環的無向圖 (undirected acyclic graph)，由節點 (nodes) 和邊 (edges) 組成。你的筆記提到 "Undirected Simple graph"，正確，但樹是圖的特例，無環 (no cycles) 且連通 (connected)。如果不連通，則為森林 (forest)。
- **Rooted Tree**: 有根的樹，你的筆記有 "Rooted tree a directed graph" – 實際上，它是定向的 (directed)，從根指向子節點，確保從根到任何節點有唯一路徑。
- **Isolated Node**: 無邊連接的節點。
- **Loop**: 節點連到自己，但樹中不允許 loop (會形成環)。
- **Simple Path**: 不重複節點的路徑。
- **Cycle Path**: 有環的路徑 (樹中不存在)。
- **Regular Graph**: 每個節點度數相同，但樹通常不是 regular，除非是滿二元樹等特殊情況。

#### 術語 (你的筆記已列出大部分，我補充英文/中文並修正)
| 術語 (English) | 術語 (Chinese) | 說明 |
|---------------|---------------|-----|
| Node | 節點 | 樹的組成單位。 |
| Root | 根節點 | 樹的頂端節點，每棵樹只有一個。 |
| Parent | 父節點 | 某一節點的上層。 |
| Child | 子節點 | 某一節點的下層。 |
| Sibling | 兄弟節點 | 同一父節點的子節點。 |
| Leaf/Terminal | 葉節點/終端節點 | 無子節點的節點。 |
| Internal Node | 內部節點 | 非葉節點 (你的筆記有 "Not a leaf")。 |
| Ancestor | 祖先 | 從根到該節點路徑上的節點 (proper ancestor 不包括自己)。 |
| Descendant | 後代 | 從該節點向下所有子孫。 |
| Level | 層級 | 從根開始，根為 level 1 (你的筆記說 "從最上 1 開始")。 |
| Degree | 度數/分支度 | 節點的子節點數 (在圖中為連接邊數)。 |
| Depth/Height of Node | 節點深度/高度 | 從根到該節點的邊數 (你的筆記有 "Rooted level = Rooted 到 node 的 长度")。 |
| Height of Tree | 樹高度 | 從根到最深葉節點的邊數 (空樹高度為 -1，你的筆記正確)。 |
| Length of Path | 路徑長度 | 邊的數量 (你的筆記有 "Tree 的 长度 : Rooted 至 根 至 末 的 leaf 树 枝 edge 的 数")。 |

#### 樹的類型 (你的筆記涵蓋部分，我補充)
- **Binary Tree (二元樹)**: 每個節點最多 2 個子節點。
  - **Full Binary Tree**: 每個節點有 0 或 2 個子節點 (你的筆記正確)。
  - **Perfect Binary Tree**: 所有層級完全填滿 (你的筆記 "同一 level 的 都 至 部 填 满")。
  - **Complete Binary Tree**: 除最後一層外全滿，最後一層從左填滿 (你的筆記正確，可用陣列實現，適合 heap)。
- **k-ary Tree**: 每個節點最多 k 個子節點 (你的筆記 "每個 node 最 少 k 個 children" – 應為最多，min 是至少)。
- **Binary Search Tree (BST, 二元搜尋樹)**: 左子樹 < 根 < 右子樹，支持快速搜尋/插入/刪除 (平均 O(log n))。
- **AVL Tree**: BST 的平衡版本，每節點左右子樹高度差 ≤ 1 (你的筆記有 "Binary Search TREE + balance height")。
- **Red-Black Tree (紅黑樹)**: 自平衡 BST，你的筆記詳細規則：
  1. 每個節點紅或黑。
  2. 根為黑。
  3. 葉 (external/null) 為黑。
  4. 無連續紅節點。
  5. 每條路徑黑節點數相同。
  - Insertion: 如你的筆記，用 BST 插入新紅節點，然後旋轉/變色維持平衡。時間 O(log n)。

#### 遍歷 (Traversal) – 你的筆記有 BFS/DFS，但混淆
- **Depth-First Search (DFS, 深度優先)**: 先探深再探寬，使用 stack (LIFO)。你的筆記 "走到底才探索一條走到底" 正確。
  - Preorder (前序): 根 → 左 → 右。
  - Inorder (中序): 左 → 根 → 右 (BST 中序為排序序列)。
  - Postorder (後序): 左 → 右 → 根。
- **Breadth-First Search (BFS, 廣度優先)**: 層級遍歷，使用 queue (FIFO)。你的筆記 "走完一層才走下一層" 正確，保證最短路徑 (在無權圖中)。
- 時間/空間複雜度 (你的筆記有 O(bS) for BFS, O(bm) for DFS – b 為分支因子, S/m 為深度/寬度):
  - BFS: Time O(V+E), Space O(V) (V 節點數, E 邊數)。
  - DFS: Time O(V+E), Space O(h) (h 為高度，最壞 O(V))。

#### 操作與複雜度
| 操作 | BST 平均 | BST 最壞 | AVL/紅黑樹 |
|------|---------|----------|-----------|
| Search | O(log n) | O(n) | O(log n) |
| Insert | O(log n) | O(n) | O(log n) |
| Delete | O(log n) | O(n) | O(log n) |

#### 補充範例
- BST 插入: 插入 5 到樹 [3,1,4,6] → 成為 [3,1,4,5,6]。
- 應用: 檔案系統、資料庫索引。

### Heap (堆)

你的筆記涵蓋 max/min heap、insert/extract，但可加實現細節和優先隊列應用。

- **Heap**: 完整二元樹 (complete binary tree)，用陣列實現 (你的筆記 "array, complete binary tree")。根為 level 1。
- **Max Heap**: 父 ≥ 子 (你的筆記正確，sibling 無序)。
- **Min Heap**: 父 ≤ 子。
- **Insert (Heapify Up)**: 加到末尾，向上比較/交換 (up-heap, O(log n))。
- **Extract (Heapify Down)**: 移除根，用末尾替換，向下比較/交換 (down-heap, O(log n))。

#### 陣列實現
- 索引 i 的父: floor((i-1)/2), 左子: 2i+1, 右子: 2i+2。
- 範例: Max Heap [10,7,8,3,4] – 陣列 [10,7,8,3,4]。

#### 複雜度
- Build Heap: O(n)
- 應用: 優先隊列 (priority queue)、Heap Sort (O(n log n))。

### Graph (圖)

你的筆記有基本定義、度數、BFS/DFS，但缺少有向圖、權重和演算法。

- **Graph**: 節點 (V) 和邊 (E) 集合。你的筆記 "G(V,E)" 正確。
- **Undirected/Directed**: 無向/有向。
- **Degree**: In-degree (入度), Out-degree (出度) – 你的筆記有。
- **Adjacency List/Matrix**: List 適合稀疏圖 (O(V+E) space), Matrix 適合稠密 (O(V^2))。
- **Traversal**: BFS/DFS 如上。
- **其他類型**: Weighted (邊有權重), Multiple Edges (多邊，你的筆記有)。

#### 演算法補充
- Shortest Path: BFS (無權), Dijkstra (非負權, O((V+E) log V))。
- UCS (Uniform Cost Search): 你的筆記有，是 Dijkstra 的變體。

#### 複雜度
- BFS/DFS: Time O(V+E), Space O(V)。

### Hash Table (雜湊表)

你的筆記詳細 hash function、collision resolution，但有拼寫錯誤 (e.g., "bigf Folding" 應為 "Digit Folding")，補充 load factor 和再雜湊。

- **Hash Function**: 將 key 映射到 index。你的筆記有 Division (k % m), Mid-Square (平方取中), Folding (shift/boundary), Digits Analysis。
  - Perfect Hash: 無 collision (罕見)。
  - 性質: 快速、均勻分佈 (你的筆記正確)。
  - FNV-1/FNV-1a: 非加密 hash，適合 32/64/128 bits。
- **Collision**: 多 key 同一 hash (你的筆記有)。
- **Bucket/Slot**: Bucket 是位置，slot 是 bucket 內槽。
- **Overflow Resolution**:
  - Open Addressing: Linear Probing (h(k)+i % m), Quadratic (h(k)+i^2 % m), Double Hashing (h1(k) + i*h2(k) % m) – 你的筆記詳細。
  - Chaining: 每個 bucket 用 linked list (你的筆記有 "back A lkdlist")。
- Load Factor (α = n/m): >0.7 需 rehash。
- 複雜度: 平均 O(1) search/insert, 最壞 O(n)。

### Linked List (鏈結串列)

你的筆記只提 "Link List"，缺少細節，我補充。

- **Singly Linked List**: 每個節點有 data + next 指標。
- **Doubly Linked List**: + prev 指標，支持雙向。
- 操作: Insert/Delete O(1) 如果有指標, Search O(n)。
- 應用: 實現 stack/queue, 比陣列動態。

### Queue (隊列)

你的筆記在 BFS 提 FIFO，但無獨立部分。

- **Queue**: FIFO (先進先出)。
- 操作: Enqueue (加尾), Dequeue (取頭), O(1)。
- 實現: 陣列 (circular) 或 linked list。
- 應用: BFS, 任務排程。

### Deque (雙端隊列)

你的筆記詳細實現 (map, off, size, insert/erase)，補充。

- **Deque**: 雙端 queue，支持前後加/刪。
- 實現: 多塊陣列 (你的 "map size 8", "my off", "my size")，copy 時 resize。
- Insert/Erase: 前/後半調整 (你的筆記有 off <=/>= mySize)。
- 複雜度: Amortized O(1)。

### Stack (堆疊)

你的筆記在 DFS 提 LIFO。

- **Stack**: LIFO (後進先出)。
- 操作: Push (加頂), Pop (取頂), O(1)。
- 實現: 陣列或 linked list。
- 應用: DFS, 遞迴模擬, 括號匹配。
