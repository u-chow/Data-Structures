# Data Structure

```
Homework 3
```
## • 題意說明

Imagine you are managing an employee database. Each employee record contains
information such as employee ID, name, and salary. You need to maintain this database
efficiently and perform various operations on it. In this scenario, you can use a Binary
Search Tree to store employee records, with employee IDs as the keys.
In this assignment, you are tasked with implementing a program that allows users to work
with Binary Search Trees (BST) and perform both basic and advanced operations. The
program will include functionalities such as inserting, deleting, searching for nodes, in-
order traversal, finding the lowest common ancestor, checking tree balance, and finding
the k-th smallest element.

## • 程式功能要求

1. Create a data structure for storing the binary search tree.
    Implement the following basic functions. (total 50 分)
(a) Insertion:
    - Implement a function to insert a new node (storing IDs) into the BST. (10分)
       Ensure that the binary search tree property is maintained after insertion.
    - A dataset is initially provided. The program can read from a text file. A line in the
       file contains the information of the inserted IDs (separated by spaces). The order of
       the input IDs is random. (at least 20 data). (10分)
(b) Deletion: (10分)
    - Implement a function to delete a node with a given value from the BST.
       Handle cases where the node to be deleted has zero, one, or two children.
       Ensure that the binary search tree property is maintained after deletion.
(c) Search: (10分)
    - Implement a function to search for a node with a specific value in the BST.
       Return the node if found or a message indicating that the value was not found.
(d) In-order Traversal: (10分)
    - Implement a function to perform an in-order traversal of the BST.
       Print the values of the nodes in ascending order.


2. Provide additional functions: (total 30分)
(a) Compute balance factor of a specific node: (10分)
    - Implement a function that compute the balance factor of a specific node (given an
       existing IDs in the BST.
The balance factor of a node is defined as the difference between the heights of the
left and right subtrees of the node.
(b) Find the k-th Smallest Element:
    - Implement a function that finds the k-th smallest element in the BST. (10分)
       The k-th smallest element is the k-th smallest value when the tree is traversed in-
       order.
       If each node in the Binary Search Tree (BST) keeps a count of the number of nodes
       in its left subtree, you can efficiently find the k-th smallest element by traversing the
       tree based on this count. (10分)
3. User Interaction:
Follow the provided user interface to perform the provided functions.
- 程式評分標準
    1. 正確性及程式撰寫模組化 (功能需採用對應模組撰寫)。( 80 分)。
    2. 輸出入介面(請依助教提供範例格式，若不了解或有特殊需要改變的原因，
       請跟助教溝通)。 (10分)
    3. 書面報告: 各主要功能簡要說明，輸出入方式說明，檢附自行測試畫面結果。
       (10分)
4. on time (- 10 分 each day late)
- Turned in

從moodle上傳 (必須附書面報告及source code), 若需要請配合助教在規定時間內demo。

明顯相互抄襲程式內容(e.g. 只有變數名稱不同者)、未繳交書面報告及無法執行未配合助教 **demo** 者，以 **0** 分計算。




# Example

```
( 1 ) Read dataset
( 2 ) Insert a new node (storing IDs) into the BST
( 3 ) Delete a node with a given value from the BST (If the node does not exist, print not found)
( 4 ) Search for a node with a specific value in the BST (If the node does not exist, print not found)
( 5 ) Perform an in-order traversal of the BST (Print the values of the nodes in ascending order)
( 6 ) Compute balance factor of a specific node
( 7 ) Find the k-th Smallest Element
( 8 ) Exit
```
### (1)(2) (3)(4) ID not found

### Step 1. dataset (ID 20 data)

#### 56 16 14 25 28 20 35 42 11 27 3 38 45 57 34 17 32 58 33 55

#### 1

```
input file path: ./dataset.txt
```

### Step 2. Insertion

#### 2

```
input ID: 24
```
### Step 3. Insertion

```
binary search tree
```
```
binary search tree
```

#### 2

```
input ID: 60
```
### Step 4. Deletion

#### 3

```
input ID: 35
```
```
binary search tree
```

### Step 5. Deletion

#### 3

```
input ID: 60
```
```
binary search tree
```
```
binary search tree
```

### Step 6. Deletion

#### 3

```
input ID: 14
```
### Step 7. Deletion

#### 3

```
input ID: 26
output: not found
```
### Step 8. Search

#### 4

```
input ID: 34
output: find it
```
#### 4

```
input ID: 40
output: not found
```
```
binary search tree
```

## Step 9. In-order Traversal


#### 16 42 36 8 32 34 15 47 24 2 11 0 3 27 4 9 5 28 20 49

### dataset.txt

#### 1

```
input file path: ./dataset.txt
```
### binary search tree

### Step 2. Deletion

#### 3

```
input ID: 32
```

### binary search tree

### Step 3. Insertion

#### 2

```
input ID: 38
```
### binary search tree

### Step 4. Deletion


#### 3

```
input ID: 16
```
### binary search tree

### Step 5. Search

#### 4

```
input ID: 10
output: not found
```
### Step 6. In-order Traversal

#### 5

```
output: 0 2 3 4 5 8 9 11 15 20 24 27 28 34 36 38 42 47 49
```
### Step 7. Compute balance factor of a specific node

#### 6

```
input ID: 36
output: 2
```
#### 6

```
input ID: 9
```

## Step 8. Find the k-th Smallest Element

### Step 9. Exit

   -
- output:
   - Step 10. Compute balance factor of a specific node
- input ID:
- output:
   -
- input ID:
- output: -
   -
- input ID:
- output: -
   - Step 11. Find the k-th Smallest Element
- input k:
- output:
   -
- input k:
- output:
   - Step 12. Exit
- output:
   -
- input k:
- output:
   -
- input k:
- output:
   - Step 9. Exit


