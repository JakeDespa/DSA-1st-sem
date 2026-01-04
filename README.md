# 🚀 Data Structures and Algorithms - 1st Semester

A comprehensive collection of **Data Structures and Algorithms (DSA)** implementations in C.  
Organized by topics with practical applications and exercises.

---

## 📂 Repository Structure

### 📁 Arrays
Various array implementations and variations:
- **arrayList/** - List implementations (variations 1-4)
- **arrayqueue/** - Queue using array (v1, v2)
- **arraystack/** - Stack using array (v1, v2)

### 📁 Advanced Data Structures
- **bitvectorset/** - Bit vector set implementations (v1, v2, v3)
- **cursor based list/** - Cursor-based list implementations (v1, v2)
- **linkedlist/** - Linked list implementations (v1, v2)
- **LL queue/** - Queue using linked list (v1, v2)
- **LL stack/** - Stack using linked list (v1)

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

## 🧩 Implemented Topics

✅ **Arrays & Array-based ADTs**  
✅ **Linked Lists** (Singly Linked, Cursor-based)  
✅ **Stacks** (Array & Linked List implementations)  
✅ **Queues** (Array & Linked List implementations)  
✅ **Bit Vector Sets**  
✅ **Hash Tables** (Closed Hashing with Progressive Overflow)  
✅ **Virtual Heap Management**

---

## 🔧 How to Compile and Run

### Warehouse System
```bash
gcc -o warehouse ADTExercises/warehouse/warehouse.c ADTExercises/warehouse/arrayStack.c -I ADTExercises/warehouse
./warehouse
```

### Pharmacy System
```bash
gcc -o pharmacy ADTExercises/pharmacy/pharmacy.c ADTExercises/pharmacy/arrayQueue.c -I ADTExercises/pharmacy
./pharmacy
```

### Knowledge Base System
```bash
gcc -o knowledgebase ADTExercises/knowledgebase/knowledgebase.c ADTExercises/knowledgebase/cursorList.c -I ADTExercises/knowledgebase
./knowledgebase
```

### Airport Code Lookup
```bash
gcc -o airport ADTExercises/airport/airport.c ADTExercises/airport/closedHash.c -I ADTExercises/airport
./airport
```

---


