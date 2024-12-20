#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct TreeNode
{
    int32_t id;
    struct TreeNode* left;
    struct TreeNode* right;
    int32_t height;
};

void readFromFileAndInsert(struct TreeNode** root, const char* filePath);
struct TreeNode* insertNode(struct TreeNode* root, int32_t id);
struct TreeNode* deleteNode(struct TreeNode* root, int32_t id);
struct TreeNode* searchNode(struct TreeNode* root, int32_t id);
void inOrderTraversal(struct TreeNode* root);
int32_t getHeight(struct TreeNode* root);
int32_t getBalanceFactor(struct TreeNode* root);
void updateHeight(struct TreeNode* root);
void kthSmallestElementHelper(struct TreeNode* root, int32_t* k);
void kthSmallestElement(struct TreeNode* root, int32_t k);
void freeTree(struct TreeNode* root);
struct TreeNode* createNode(int32_t id);
struct TreeNode* findMin(struct TreeNode* node);

int main()
{
    struct TreeNode* root = NULL;

    int32_t option, id, k;
    char inputPath[100];

    while(1)
    {
        printf("\nMenu:\n");
        printf("    (1) Read dataset\n");
        printf("    (2) Insert a new node\n");
        printf("    (3) Delete a node\n");
        printf("    (4) Search for a node\n");
        printf("    (5) In-order traversal\n");
        printf("    (6) Compute balance factor\n");
        printf("    (7) Find the k-th Smallest Element\n");
        printf("    (8) Exit\n");

        printf("Enter option: ");
        scanf("%d", &option);

        if(option == 1)
        {
            printf("input file path: ");
            scanf("%s", inputPath);
            readFromFileAndInsert(&root, inputPath);
        }
        else if(option == 2)
        {
            printf("input ID: ");
            scanf("%d", &id);
            root = insertNode(root, id);
        }
        else if(option == 3)
        {
            printf("input ID: ");
            scanf("%d", &id);
            struct TreeNode* searchResult = searchNode(root, id);
            if(searchResult != NULL)
            {
                root = deleteNode(root, id);
            }
            else
            {
                printf("output: not found\n");
            }
        }
        else if(option == 4)
        {
            printf("input ID: ");
            scanf("%d", &id);
            struct TreeNode* searchResult = searchNode(root, id);
            if(searchResult != NULL)
            {
                printf("output: find it\n");
            }
            else
            {
                printf("output: not found\n");
            }
        }
        else if(option == 5)
        {
            printf("output: ");
            inOrderTraversal(root);
            printf("\n");
        }
        else if(option == 6)
        {
            printf("input ID: ");
            scanf("%d", &id);
            int balanceFactor = getBalanceFactor(searchNode(root, id));
            printf("output: %d\n", balanceFactor);
        }
        else if(option == 7)
        {
            printf("input k: ");
            scanf("%d", &k);
            printf("output: ");
            kthSmallestElement(root, k);
            printf("\n");
        }
        else if(option == 8)
        {
            printf("EXIT\n");
            break;
        }
        else
        {
            printf("Invalid option\n");
        }
    }
    freeTree(root);
    return 0;
}

void readFromFileAndInsert(struct TreeNode** root, const char* filePath)
{
    FILE* file = fopen(filePath, "r");
    if(file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    int32_t id;
    while(fscanf(file, "%d", &id) != EOF)
    {
        *root = insertNode(*root, id);
    }

    fclose(file);
}

struct TreeNode* insertNode(struct TreeNode* root, int32_t id)
{
    if(root == NULL)
    {
        return createNode(id);
    }

    if(id < root->id)
    {
        root->left = insertNode(root->left, id);
    }
    else if(id > root->id)
    {
        root->right = insertNode(root->right, id);
    }
    updateHeight(root);
    return root;
}

struct TreeNode* deleteNode(struct TreeNode* root, int32_t id)
{
    if(root == NULL)
    {
        return root;
    }

    if(id < root->id)
    {
        root->left = deleteNode(root->left, id);
    }
    else if(id > root->id)
    {
        root->right = deleteNode(root->right, id);
    }
    else
    {
        if(root->left == NULL)
        {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = findMin(root->right);
        root->id = temp->id;
        root->right = deleteNode(root->right, temp->id);
    }
    return root;
}

struct TreeNode* searchNode(struct TreeNode* root, int32_t id)
{
    if(root == NULL || root->id == id)
    {
        return root;
    }

    if(id < root->id)
    {
        return searchNode(root->left, id);
    }
    else
    {
        return searchNode(root->right, id);
    }
}

void inOrderTraversal(struct TreeNode* root)
{
    if(root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->id);
        inOrderTraversal(root->right);
    }
}

int32_t getHeight(struct TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return root->height;
}
int32_t getBalanceFactor(struct TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    int32_t leftHeight = getHeight(root->left);
    int32_t rightHeight = getHeight(root->right);

    return leftHeight - rightHeight;
}
void updateHeight(struct TreeNode* root)
{
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));
}

void kthSmallestElementHelper(struct TreeNode* root, int32_t* k)
{
    if(root != NULL && *k > 0)
    {
        kthSmallestElementHelper(root->left, k);
        (*k)--;
        if(*k == 0)
        {
            printf("%d ", root->id);
            return;
        }
        kthSmallestElementHelper(root->right, k);
    }
}
void kthSmallestElement(struct TreeNode* root, int32_t k)
{
    kthSmallestElementHelper(root, &k);
}

void freeTree(struct TreeNode* root)
{
    if(root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

struct TreeNode* createNode(int32_t id)
{
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->id = id;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

struct TreeNode* findMin(struct TreeNode* node)
{
    struct TreeNode* current = node;
    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}