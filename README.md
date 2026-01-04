# 🚀 Data Structures and Algorithms - 1st Semester

A comprehensive collection of **Data Structures and Algorithms (DSA)** implementations in C.  
Organized by topics with practical applications and exercises.

---

## 📂 Repository Structure

### 1️⃣ Array List
- **Arrays/arrayList/** - Multiple variations (1-4) of array-based list implementations
- Dynamic list operations, insertions, deletions, and searching

### 2️⃣ Linked List
- **linkedlist/** - Singly linked list implementations (v1, v2)
- Node-based dynamic data structure

### 3️⃣ Stack (Array & Linked List)
- **Arrays/arraystack/** - Array-based stack (v1, v2)
- **LL stack/** - Linked list-based stack (v1)
- LIFO operations: push, pop, peek

### 4️⃣ Queue (Array & Linked List)
- **Arrays/arrayqueue/** - Array-based queue (v1, v2)
- **LL queue/** - Linked list-based queue (v1, v2)
- FIFO operations: enqueue, dequeue

### 5️⃣ Cursor-Based List
- **cursor based list/** - Cursor-based list using virtual heap (v1, v2)
- Simulates dynamic memory using array indices

### 6️⃣ Bit Vector Set
- **bitvectorset/** - Bit vector set implementations (v1, v2, v3)
- Memory-efficient set operations using bit manipulation

### 7️⃣ Open & Closed Hashing
- **openhashing/** - Open hashing with chaining (external)
- **closedhashing.c/** - Closed hashing with progressive overflow (internal)
- Hash table implementations with collision handling

### 8️⃣ Priority Queue
- **binaryheappq/** - Binary heap-based priority queue
- Min/Max heap operations with efficient priority management

### 9️⃣ Heap Sort
- **heapsort/** - Heap sort algorithm implementation
- Sorting using binary heap structure

### 🔟 Binary Search Tree (BST)
- **BST/1/** - BST with DFS traversals (inorder, preorder, postorder)
- **BST/2/** - BST with insertion, deletion, and search operations
- Tree operations and recursive algorithms

### 📁 ADTExercises
Complete project implementations demonstrating real-world applications:

#### 🏭 **Warehouse Inventory System** (`warehouse/`)
- Stack-based inventory management
- Three separate stacks with 5-container capacity
- Automatic overflow handling
- Files: `arrayStack.h`, `arrayStack.c`, `warehouse.c`

#### 💊 **Pharmacy Queueing System** (`pharmacy/`)
- Dual-queue system (Regular & Priority)
- Priority-first service logic
- Sequential customer numbering
- Files: `arrayQueue.h`, `arrayQueue.c`, `pharmacy.c`

#### 📚 **Knowledge Base Management** (`knowledgebase/`)
- Cursor-based list implementation
- Virtual heap (20 cells)
- Article CRUD operations
- Files: `cursorList.h`, `cursorList.c`, `knowledgebase.c`

#### ✈️ **Airport Code Lookup** (`airport/`)
- Closed hashing dictionary
- Progressive overflow collision handling
- Cursor-based virtual heap
- Hash function for airport codes
- Files: `closedHash.h`, `closedHash.c`, `airport.c`

---

## ✅ Complete Topic Checklist

All 13 core DSA topics implemented:

1. ✅ **Array List** - `Arrays/arrayList/`
2. ✅ **Linked List** - `linkedlist/`
3. ✅ **Stack (Array & LL)** - `Arrays/arraystack/`, `LL stack/`
4. ✅ **Queue (Array & LL)** - `Arrays/arrayqueue/`, `LL queue/`
5. ✅ **Cursor-Based List** - `cursor based list/`
6. ✅ **Bit Vector Set** - `bitvectorset/`
7. ✅ **Open & Closed Hashing** - `openhashing/`, `closedhashing.c/`
8. ✅ **Priority Queue** - `binaryheappq/`
9. ✅ **Heap Sort** - `heapsort/`
10. ✅ **Binary Tree (BST)** - `BST/` with BFS, DFS, and Operations

---

## 🎯 Key Features

### Data Structure Operations
- **Insertion, Deletion, Search** across all structures
- **Traversal algorithms** (DFS: inorder, preorder, postorder)
- **Collision handling** in hash tables (chaining & progressive overflow)
- **Heap operations** for priority queues and sorting
- **Virtual heap management** for cursor-based structures

### Hashing Implementations
- **Open Hashing**: Separate chaining with linked lists
- **Closed Hashing**: Progressive overflow with cursor-based storage

### Tree Operations
- **Binary Search Tree** with full CRUD operations
- **DFS Traversals**: Inorder, Preorder, Postorder
- Recursive and iterative approaches



