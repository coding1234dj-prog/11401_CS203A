# 搜尋結構比較：Hash Table vs BST vs Balanced BST

## 🎯 核心決策樹（最重要！）

```
需要搜尋資料結構？
    ↓
需要「有序」操作嗎？
    ↓
    ├─ 否 → Hash Table
    │        O(1) 平均，超快但無序
    │
    └─ 是 → 需要「保證」效能嗎？
             ↓
             ├─ 否 → Binary Search Tree
             │        O(log n) 平均，可能退化
             │
             └─ 是 → Balanced BST
                      O(log n) 保證，生產環境標準
```

## 📊 三大結構對照表

| 特性 | Hash Table | BST | Balanced BST |
|------|-----------|-----|--------------|
| **搜尋** | O(1) 平均<br>O(n) 最壞 | O(log n) 平均<br>O(n) 最壞 | **O(log n) 保證** |
| **插入** | O(1) 平均<br>O(n) 最壞 | O(log n) 平均<br>O(n) 最壞 | **O(log n) 保證** |
| **刪除** | O(1) 平均<br>O(n) 最壞 | O(log n) 平均<br>O(n) 最壞 | **O(log n) 保證** |
| **最小值/最大值** | O(n) 需遍歷 | O(log n) 平均<br>O(n) 最壞 | **O(log n) 保證** |
| **有序遍歷** | ❌ 不支援 | ✅ O(n) | ✅ O(n) |
| **範圍查詢** | ❌ 不支援 | ✅ O(k + log n) | ✅ O(k + log n) |
| **第 k 小元素** | ❌ O(n) | ❌ O(n) 或需額外結構 | ✅ O(log n)* |
| **前驅/後繼** | ❌ 不支援 | ✅ O(log n) | ✅ O(log n) |
| **記憶體效率** | ⚠️ 需預留空間<br>負載因子 < 1 | ✅ 僅指標開銷 | ✅ 僅指標+平衡資訊 |
| **快取友善度** | ⚠️ 取決於實作 | ❌ 指標跳躍 | ❌ 指標跳躍 |
| **最壞情況** | 所有鍵碰撞 | 退化成鏈 | **不會退化** |
| **實作難度** | 中等 | 簡單 | 困難 |

*需要 Augmented Tree（增強樹）

k = 查詢結果數量

## 🗂️ Hash Table：速度之王（無序時）

### ✅ 優點
```
1. 平均 O(1) 操作
   - 查找：幾乎瞬間
   - 插入：直接定位
   - 刪除：快速移除

2. 實作相對簡單
   - 基本概念直觀
   - 標準庫完善

3. 常數因子小
   - 不像樹有多次比較
   - 不需旋轉平衡
```

### ❌ 缺點
```
1. 無法有序操作
   ❌ 不能按順序遍歷
   ❌ 找不到「下一個更大的值」
   ❌ 範圍查詢不支援

2. 最壞情況 O(n)
   ⚠️ 惡意構造輸入
   ⚠️ 雜湊函數設計不良
   ⚠️ 所有鍵碰撞

3. 空間浪費
   - 需維持低負載因子（通常 < 0.75）
   - 空桶浪費記憶體
   - rehash 成本高

4. 鍵的限制
   - 鍵必須可雜湊
   - 需實作良好的 hashCode
   - 浮點數做鍵有風險
```

### 🎯 適用場景
```
✅ 完美場景（首選）：
1. 純鍵值查找
   - 字典查詢
   - 資料庫記錄查找
   - 配置表

2. 去重檢查
   - Set 操作
   - 判斷是否存在
   - 快速成員測試

3. 計數問題
   - 字符頻率統計
   - 單詞計數
   - 事件計數器

4. 演算法輔助
   - 兩數之和
   - 最長無重複子串
   - 字母異位詞分組

❌ 不適合（換別的）：
1. 需要有序輸出
2. 範圍查詢
3. 找最大/最小值（頻繁）
4. 需要穩定 O(log n)（安全關鍵）
```

### 💼 實際應用案例
```
✅ 使用 Hash：
- Python: dict（字典實作）
- Java: HashMap（通用映射）
- Redis: String/Hash 類型
- 瀏覽器: Cookie 儲存
- DNS: 域名解析快取

範例：LeetCode 1. 兩數之和
Map<Integer, Integer> map = new HashMap<>();
for (int i = 0; i < nums.length; i++) {
    int complement = target - nums[i];
    if (map.containsKey(complement)) {
        return new int[] {map.get(complement), i};
    }
    map.put(nums[i], i);
}
```

### ⚠️ Hash Table 的陷阱

#### 陷阱 1: 雜湊碰撞攻擊
```
問題：惡意構造大量碰撞的鍵
結果：O(1) → O(n)，服務拒絕

防禦：
1. 使用隨機化雜湊（Random Seed）
2. 碰撞過多時轉為樹（Java 8+）
3. 限制單個桶的大小
```

#### 陷阱 2: 浮點數做鍵
```
問題：
0.1 + 0.2 != 0.3  // 浮點誤差

錯誤：
Map<Double, String> map = new HashMap<>();
map.put(0.1 + 0.2, "value");
map.get(0.3);  // 找不到！

正確：
1. 用整數（乘以精度）
2. 用字串表示
3. 用 Decimal 類型
```

#### 陷阱 3: 負載因子設定
```
太高（>0.9）：
❌ 碰撞增加
❌ 效能下降

太低（<0.5）：
❌ 空間浪費
❌ rehash 頻繁

最佳實踐：
✅ 0.75（Java 預設）
✅ 預估容量時 × 1.5
```

## 🌲 Binary Search Tree：有序但不穩

### ✅ 優點
```
1. 支援有序操作
   ✅ 中序遍歷 = 排序輸出
   ✅ 找前驅/後繼
   ✅ 範圍查詢

2. 實作簡單直觀
   - 插入邏輯清晰
   - 刪除相對簡單
   - 容易理解

3. 平均效能好
   - O(log n) 隨機輸入
   - 動態結構
```

### ❌ 缺點
```
1. 最壞退化成 O(n)
   ⚠️ 順序插入
   ⚠️ 近乎有序的輸入
   ⚠️ 惡意構造

2. 對輸入順序敏感
   - 隨機輸入：平衡
   - 有序輸入：鏈狀

3. 實務中很少單獨使用
   - 生產環境用平衡樹
   - 只在教學中常見
```

### 🎯 適用場景
```
✅ 適合：
1. 學習用途（理解樹）
2. 原型開發（快速驗證）
3. 輸入確定隨機
4. 不在乎最壞情況

❌ 不適合（生產環境）：
1. 用戶輸入可控
2. 安全關鍵系統
3. 需保證效能
4. 長時間運行服務
```

### ⚠️ 何時退化到 O(n)

#### 場景 1: 順序插入
```
輸入：1, 2, 3, 4, 5

結果：
    1
     \
      2
       \
        3
         \
          4
           \
            5

搜尋 5: 需要 5 次比較（O(n)）
```

#### 場景 2: 逆序插入
```
輸入：5, 4, 3, 2, 1

結果：
            5
           /
          4
         /
        3
       /
      2
     /
    1

搜尋 1: 需要 5 次比較（O(n)）
```

#### 場景 3: 接近有序
```
輸入：1, 3, 2, 5, 4, 7, 6

結果：仍然高度不平衡
      1
       \
        3
       / \
      2   5
         / \
        4   7
           /
          6

平均查詢時間接近 O(n)
```

### 🛡️ 避免退化的方法

```
方法 1: 使用平衡樹（最推薦）
✅ AVL Tree
✅ Red-Black Tree
✅ B-Tree

方法 2: 打亂輸入
適用：一次性建構
Collections.shuffle(list);
for (int val : list) {
    tree.insert(val);
}

方法 3: 隨機化樹
✅ Treap（隨機優先級）
✅ Skip List（隨機層數）

方法 4: 改用 Hash（放棄有序）
如果不需要順序 → 直接用 HashMap
```

## ⚖️ Balanced BST：生產環境標準

### ✅ 優點
```
1. 保證 O(log n)
   ✅ 不懼怕任何輸入
   ✅ 最壞情況有保證
   ✅ 效能穩定可預測

2. 支援所有有序操作
   ✅ 有序遍歷
   ✅ 範圍查詢
   ✅ 前驅後繼
   ✅ 第 k 小元素

3. 工業標準實作
   ✅ 經過大量實戰驗證
   ✅ 標準庫提供
   ✅ 文檔完善
```

### ❌ 缺點
```
1. 實作極度複雜
   - AVL: 4 種旋轉
   - RB: 40+ 種情況
   - 難以手寫和 debug

2. 常數因子較大
   - 比 Hash 慢 2-3 倍
   - 旋轉和平衡維護開銷

3. 記憶體開銷
   - 指標（16 bytes/節點）
   - 平衡資訊（1-4 bytes）
```

### 🎯 適用場景
```
✅ 必須用的場景：
1. 需要有序 + 保證效能
   - 訂單系統（按時間排序）
   - 排行榜（隨時查詢排名）

2. 範圍查詢頻繁
   - 找出所有 10 < price < 100
   - 時間範圍查詢

3. 動態維護有序集合
   - 實時更新排名
   - 滑動窗口中位數

4. 需要穩定效能保證
   - 金融系統
   - 實時系統
   - 安全關鍵應用

❌ 不必用的場景：
1. 不需要順序 → 用 Hash
2. 資料量小（< 100）→ 排序陣列
3. 一次性建構 → 排序後用 Array
```

### 🏆 常見實作對比

#### AVL Tree（嚴格平衡）
```
特點：
- 左右子樹高度差 ≤ 1
- 樹高 ~1.44 log n（最矮）
- 查詢最快

旋轉：
- 插入：最多 2 次
- 刪除：最多 O(log n) 次

適用：
✅ 查詢遠多於插入/刪除
✅ 對查詢延遲極度敏感
❌ 頻繁插入刪除
```

#### Red-Black Tree（寬鬆平衡）
```
特點：
- 黑高度相同
- 樹高 ~2 log n
- 平衡適中

旋轉：
- 插入：最多 2 次
- 刪除：最多 3 次（關鍵！）

適用：
✅ 讀寫操作都頻繁（通用）
✅ 標準庫實作
✅ 不確定時的預設選擇

實際應用：
- C++ std::map, std::set
- Java TreeMap, TreeSet
- Linux CFS 調度器
```

#### B-Tree（多路平衡）
```
特點：
- 每節點多個鍵（100-200+）
- 高度極低（3-4 層百萬數據）
- 磁碟 I/O 友善

適用：
✅ 資料庫索引（MySQL）
✅ 檔案系統（ext4, NTFS）
✅ 磁碟儲存
❌ 記憶體內結構（過度複雜）
```

### 💼 實際應用案例

#### 案例 1: 排行榜系統
```java
// 需求：實時排名，支援查詢某用戶排名
TreeMap<Integer, String> leaderboard = new TreeMap<>(
    Collections.reverseOrder()  // 分數從高到低
);

// 更新分數：O(log n)
leaderboard.put(score, username);

// 查詢前 10 名：O(10 + log n)
leaderboard.entrySet().stream()
    .limit(10)
    .forEach(System.out::println);

// 查詢排名：O(log n)
int rank = leaderboard.headMap(userScore, false).size() + 1;

為什麼不用 Hash？
❌ 無法按分數排序
❌ 無法範圍查詢
```

#### 案例 2: 時間範圍查詢
```java
// 需求：查詢 10:00-12:00 的所有訂單
TreeMap<LocalTime, Order> orders = new TreeMap<>();

// 範圍查詢：O(k + log n)
NavigableMap<LocalTime, Order> range = orders.subMap(
    LocalTime.of(10, 0), true,   // 包含 10:00
    LocalTime.of(12, 0), false   // 不包含 12:00
);

為什麼不用 Hash？
❌ 必須遍歷所有元素 O(n)
```

#### 案例 3: 動態中位數
```java
// 需求：資料流中隨時查詢中位數
class MedianFinder {
    TreeMap<Integer, Integer> map = new TreeMap<>();
    int size = 0;
    
    void addNum(int num) {
        map.put(num, map.getOrDefault(num, 0) + 1);
        size++;
    }
    
    double findMedian() {
        // 找第 size/2 個元素
        // 利用 TreeMap 的有序性
    }
}

為什麼不用 Hash？
❌ 無法快速找第 k 小元素
```

## 🔍 深度對比：何時用哪個？

### 決策場景 1: 純查找
```
需求：key-value 查找，不需順序

選擇：Hash Table
理由：
✅ O(1) 平均最快
✅ 實作簡單
✅ 內建支援好

範例：
- 用戶資料查詢（by ID）
- 快取系統
- Session 管理
```

### 決策場景 2: 需要排序輸出
```
需求：插入資料，需按順序輸出

錯誤方案：
❌ Hash + 每次排序 O(n log n)
❌ 維護額外排序列表

正確方案：
✅ Balanced BST（TreeMap）

理由：
- 插入 O(log n)
- 遍歷 O(n)（本身有序）
- 無需額外排序

範例：
- 日誌按時間輸出
- 成績排序
- 事件時間軸
```

### 決策場景 3: 範圍查詢
```
需求：找出 10 < value < 50 的所有元素

Hash：❌ 必須遍歷全部 O(n)
BST： ✅ O(k + log n)

實作：
TreeMap<Integer, String> map = new TreeMap<>();

// 範圍查詢
NavigableMap<Integer, String> subMap = 
    map.subMap(10, false, 50, false);
// O(k + log n)，k = 結果數
```

### 決策場景 4: 頻繁更新 + 查詢排名
```
需求：
- 頻繁更新分數
- 查詢用戶排名
- 查詢前 K 名

選擇：Balanced BST + Hash 組合

結構：
HashMap<UserId, Score> scoreMap;      // 快速查分數
TreeMap<Score, UserId> rankMap;       // 維護排名

操作：
updateScore(userId, newScore) {
    // O(log n)
    oldScore = scoreMap.get(userId);
    rankMap.remove(oldScore, userId);
    rankMap.put(newScore, userId);
    scoreMap.put(userId, newScore);
}

getRank(userId) {
    // O(log n)
    score = scoreMap.get(userId);
    return rankMap.headMap(score, false).size() + 1;
}
```

## ⚔️ 面試高頻問題

### Q1: 為什麼 HashMap 這麼快還需要 TreeMap？

```
精簡回答：
"HashMap 無法提供有序操作，當需要範圍查詢、
排序輸出、或找前驅後繼時，必須用 TreeMap。"

詳細對比：
場景                  HashMap      TreeMap
────────────────────────────────────────
單個查找              O(1) ⚡      O(log n)
範圍查詢              O(n) ❌      O(k+log n) ✅
有序遍歷              O(n log n)   O(n) ✅
第 k 小               O(n)         O(log n)*
最壞情況保證           O(n) ❌      O(log n) ✅

*需 Augmented Tree
```

### Q2: BST 什麼時候會退化？如何避免？

```
退化情況：
1. 輸入已排序：1,2,3,4,5
2. 輸入接近排序
3. 刪除操作破壞平衡

結果：樹變成鏈，O(log n) → O(n)

視覺化：
平衡 BST      退化 BST
    4             1
   / \             \
  2   6             2
 / \ / \             \
1  3 5  7             3
                       \
高度 log n              4
                         \
                          5
                        高度 n

避免方法（面試標準答案）：
"實務中使用 AVL 或 Red-Black Tree 等
自平衡樹，保證 O(log n)。如果確定輸入
隨機，可以用普通 BST，否則必須用平衡樹。"
```

### Q3: 什麼場景必須用 Balanced BST？

```
五大必須場景：

1. 範圍查詢
問題："找出所有 18 < age < 30 的用戶"
Hash: ❌ 必須遍歷全部
Tree: ✅ O(k + log n)

2. 動態維護排名
問題："即時查詢用戶排名"
Hash: ❌ 每次 O(n) 排序
Tree: ✅ O(log n) 查詢

3. 有序輸出
問題:"按分數輸出所有學生"
Hash: ❌ 需額外 O(n log n) 排序
Tree: ✅ O(n) 中序遍歷

4. 前驅/後繼查詢
問題："找比 X 大的最小值"
Hash: ❌ 不支援
Tree: ✅ O(log n)

5. 第 k 小元素
問題："找第 100 小的數"
Hash: ❌ O(n)
Tree: ✅ O(log n)（增強樹）

記憶口訣：
"凡是和『順序』有關的，用 Tree；
 純查找不需順序，用 Hash。"
```

### Q4: AVL vs Red-Black，實務怎麼選？

```
簡短答案：
"不確定時選 Red-Black，它是工業標準。"

選 AVL：
✅ 查詢遠多於更新（讀寫比 > 10:1）
✅ 對查詢延遲極度敏感
✅ 資料相對靜態

選 Red-Black：
✅ 讀寫操作都頻繁
✅ 插入刪除較多
✅ 通用場景（預設選擇）
✅ 想用標準庫

數據支持：
操作        AVL      Red-Black
查詢        1.0x     1.05x  （AVL 稍快）
插入        1.2x     1.0x   （RB 快 20%）
刪除        1.5x     1.0x   （RB 快 50%）

為什麼 STL 選 RB 不選 AVL？
"因為大多數場景是讀寫混合，Red-Black
的平衡性已經足夠好，但插入刪除更快。
AVL 過度嚴格的平衡在實務中收益不大。"
```

### Q5: 如何判斷該用 Hash 還是 Tree？

```
一句話決策：
"需要『順序』相關操作 → Tree
 純查找不需順序 → Hash"

詳細檢查表：
□ 需要按某個鍵排序輸出？        → Tree
□ 需要範圍查詢（BETWEEN）？     → Tree
□ 需要找最大/最小值（頻繁）？    → Tree
□ 需要前驅/後繼查詢？           → Tree
□ 需要第 k 大/小元素？          → Tree
□ 需要穩定的 O(log n) 保證？    → Tree

以上都不需要：
□ 純 key-value 查找             → Hash
□ 去重檢查                     → Hash (Set)
□ 計數問題                     → Hash
□ 不在乎最壞情況               → Hash

實務經驗：
70% 的場景用 Hash
25% 的場景用 Balanced BST
5% 的場景需要組合使用
```

## 💡 最佳實踐總結

### 預設選擇策略
```
1. 第一步：需要順序嗎？
   否 → HashMap（70% 情況）
   是 → 繼續

2. 第二步：資料量多大？
   小（< 1000）→ 排序陣列也可以
   大 → Balanced BST

3. 第三步：用哪種 BST？
   不確定 → TreeMap（Red-Black）
   查詢為主 → AVL Tree
   磁碟儲存 → B-Tree
```

### 組合使用技巧
```
場景：排行榜系統

單用 TreeMap：
✅ 可以查排名
❌ 通過用戶 ID 查分數慢 O(n)

單用 HashMap：
✅ 通過 ID 查分數快 O(1)
❌ 查排名需要排序 O(n log n)

最佳方案：HashMap + TreeMap
HashMap<UserId, Score> idToScore;
TreeMap<Score, Set<UserId>> scoreToIds;

結果：
✅ 查分數 O(1)
✅ 查排名 O(log n)
✅ 更新 O(log n)
```

### 效能調優建議
```
Hash Table:
1. 預估容量避免 rehash
   Map<K,V> map = new HashMap<>(expectedSize * 1.5);

2. 選擇好的雜湊函數
3. 監控負載因子
4. 考慮使用 LinkedHashMap（保持插入順序）

Balanced BST:
1. 批次插入比逐個插入快
2. 考慮用 TreeMap.putAll()
3. 範圍查詢用 subMap 而非 filter
4. 頻繁操作考慮快取結果
```

## 🔑 記憶口訣

```
Hash 超級快，但是不會排
Tree 有點慢，但是樣樣行
BST 會退化，生產別亂用
平衡樹穩當，標準庫首選

需要順序找 Tree（有序關鍵）
純粹查找用 Hash（速度至上）
不知道選啥？先試 Hash（70% 正確）
真的需要順序，Red-Black 不會錯
```

---
