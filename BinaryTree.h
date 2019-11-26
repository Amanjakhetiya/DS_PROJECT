#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define max 2 // This defines the number of marks needed

struct student1 {
    char    name[20];
    float   marks[max];
    char    studentNumber[100];
    struct  student1 *left;
    struct  student1 *right;
    struct  student1 *parent;
};

struct student1 *node;

// Functions Prototype Declaration
void addStudent(char *name, char *studentNumber, float marks[]);
void addMark(struct student1 *root, char *name, int p, float mark);
void printRecord(struct student1 *node);
void printStudent(struct student1 *node, char *name);
void recurInsertStudent(struct student1 *node, struct student1 *newStudent );
void writeList(const struct student1 *node);
void readList(void);
void saveList(const struct student1 *node, FILE *list);

struct student1 *root = NULL;
struct student1 *findMin(struct student1 *node);
struct student1 *findMax(struct student1 *node);
struct student1 *findHeight(struct student1 *node);
struct student1 *Remove(struct student1 *remove);
struct student1 *search(struct student1 *node, char *name);

int count = 0;


// Create a student and allocate memory
void addStudent(char *sname, char *Number, float marks[]) {
    // Create the new student:
    count++; // counter incremented
    // Allocates memory for new Nodes
    struct student1 *newStudent = (struct student1 *) malloc(sizeof(struct student1));
    strcpy(newStudent->name, sname);
    strcpy(newStudent->studentNumber, Number);
    int i;
    for (i = 0; i < max; i++) {
        newStudent->marks[i] = marks[i];
    }
    newStudent->left = NULL;
    newStudent->right = NULL;
    newStudent->parent = NULL;

    // Checks if database is empty
    if (root == NULL ) {
        root = newStudent;
        root->left   = NULL;
        root->right  = NULL;
        root->parent = NULL;
        return;
    }
    // Adding student recursively
    else{
        recurInsertStudent(root, newStudent);
        return;
    }
}
/* Insert student in the binary tree
 * adds a new binary students - sorted alphabetically
 * doesn't allow addition of students with the same name
 * create and choose the condition to insert the node.
 */
void recurInsertStudent(struct student1 *node, struct student1 *newStudent){
    // Alphabetical Ordering: if strcmp result == 0 that means that the Student already exists.
    if (strcmp(newStudent->name, node->name) == 0) {
        printf("Name already exist.\n");
    }
    // Alphabetical Ordering: if strcmp result > 0 that means that the Student goes to the right
    if (strcmp(newStudent->name, node->name) > 0) {
        if (node->right == NULL ) {
            node->right = newStudent; newStudent->parent = node;
            return;
        }
        //if there is no more branch to move to, add student profile here
        else {
            recurInsertStudent(node->right, newStudent);
        }
    }
    // Alphabetical Ordering: if strcmp result < 0 that means that the Student goes to the left
    if  (strcmp(newStudent->name, node->name) < 0) {
        if (node->left == NULL ) {
            node->left = newStudent;
            newStudent->parent = node;
            return;
        }
        //if there is no more branch to move to, add student profile here
        else {
            recurInsertStudent(node->left, newStudent);
        }
    }
}

//add mark to a student
void addMark(struct student1 *node, char *name, int p, float mark) {
    //search the database for student you want to add mark
    struct student1 *toAddMark = search(root, name);
    if(toAddMark == NULL){
        printf("student to add mark to not found\n");
        return;
    }
    //add marks entred -1 to mark since the array starts at 0.
    toAddMark->marks[p-1] = mark;
    return;
}

// Recursive Function : Prints all Students Info in Alphabetical Orderr from left to right
void printRecord(struct student1 *node) {
    if(root == NULL){ // Database empty (This condition is used in Main)
        return;
    }
    //print from left to right
    if (node->left) {
        printRecord(node->left);
    }

    printf("\n%s \t\t%s \n",node->name, node->studentNumber);
    int j;
    for (j = 0; j < max; j++)
    {
        printf("\t\t\t\t\t\tMarks[%d] = %.2f %%\n\n",
               j+1, node->marks[j]);
    }
    printf("\n");
    if (node->right) {
        printRecord(node->right);
    }
}
// this function displays a singular student record
void printStudent(struct student1 *node, char *name)
{
    int j;
    node = search(root, name);
    if(node != NULL)
    {
        printf("Name \tStudent Number \tStudent Marks\n\n");
        printf("\n%s \t\t%s \n",node->name, node->studentNumber);
        for (j = 0; j < max; j++)
        {
            printf("\t\t\t\t\t\tMarks[%d] = %.2f %%\n\n",
                   j+1, node->marks[j]);
        }
    }
    else{
        printf("student not found\n");
    }
}

//save the list in a file
void writeList(const struct student1 *node){
    FILE *studentList;
    studentList = fopen("studentList.bin","wb"); //opens file studentList
    saveList(node, studentList);
    fclose(studentList);
    return;
}

// Recursive Function : insert each struct in the list in alphabetical order
void saveList(const struct student1 *node, FILE *studentList){
    if (node->left) {
        saveList(node->left,studentList);
    }
    fwrite(node, sizeof(struct student1), 1, studentList); // Write into the File
    printf("WRITTING Student ***| %s |** \n",node->name);
    if (node->right) {
        saveList(node->right,studentList);
    }
}

// Opens the file previously created and reads the data from it
void readList(){
    struct student1 *readStudent = (struct student1 *)malloc(sizeof(struct student1));
    FILE *studentList = fopen("studentList.bin", "rb");

    //reads file and passes each read to readstudent function
    size_t READ = fread(readStudent, sizeof(struct student1), 1, studentList);

    while(READ == 1){  // do while loop to read data from file
        printf("READING Student ***| %s |*** \n", readStudent->name);
        if (root == NULL){
            root = readStudent;
            root->left   = NULL;
            root->right  = NULL;
            root->parent = NULL;
        }
        else{
            readStudent->left=NULL;
            readStudent->right=NULL;
            readStudent->parent = NULL;
        }
        count++;
        readStudent = (struct student1 *)malloc(sizeof(struct student1));
        READ = fread(readStudent, sizeof(struct student1), 1, studentList);
        recurInsertStudent(root, readStudent); // add students first before displaying
        printStudent(readStudent, readStudent->name); // pass paramaters to printstudent function

    }
    printf("\t\t\n*** %s *** is root\n\n",root->name);
    fclose(studentList);
    return;
}

//find the most left leaf
struct student1 *findMin(struct student1 *node)
{
    if (node->left == NULL)
        return node;
    else
        findMin(node->left);

    return NULL;
}


struct student1 *findMax(struct student1 *node) {
    while (node->right != NULL ) {
        return findMax(node->right);
    }
    return node;
}

// Recursive Function : searches the tree by diving it in half
struct student1 *search(struct student1 *node, char *name) {
    if (node == NULL) {
        printf("Not found.\n");
        return NULL;
    }
    //if strcmp result < 0 we search for the tudent in left child
    if (strcmp(name, node->name) < 0) {
        if(node->left){
            return search(node->left, name);
        }
        else{
            return NULL;
        }
    }
    //if strcmp result > 0 we search for the student in right
    if (strcmp(name, node->name) > 0) {
        if(node->right){
            return search(node->right, name);
        }
        else{
            return NULL;
        }
    }
    //if strcmp result == 0 return node
    if (strcmp(name, node->name) == 0){
        return node;
    }
    return node;

}

// finds height of tree recursively
struct student1 *findHeight(struct student1 *node){
    if(node == NULL) {return 0;}        // if the input is NULL return 0
    struct student1 *left;
    struct student1 *right;
    left  = findHeight(node->left);    // check left node's height
    right = findHeight(node->right);    // and rights

    if(left > right){return left + 1;}        // if left is bigger return left's height plus one for the current node
    else return right + 1;                // else return right's height plus one
}



// right rotates a node
void rightRotateBinary(struct student1 *node)
{
    struct student1 *temp; struct student1 *original; struct student1 *left;

    //checks if node that was passed was null or had no left children
    if(node == NULL || node->left == NULL)
    {
        return;
    }

    original = node;
    left = original->left;

    temp = (struct student1*)malloc(sizeof(struct student1));

    // copies info from org node to temp
    strcpy(temp->name, original->name);
    strcpy(temp->studentNumber, original->studentNumber);

    // copies info from left node to org node
    strcpy(original->name,left->name);
    strcpy(original->studentNumber, left->studentNumber);

    // moves temp between the org and right and saves value of left's left
    temp->left = left->right;
    temp->right = original->right;
    original->left = left->left;
    original->right = temp;

    // frees old left value
    free(left);
}

// left rotates a node
void leftRotateBinary(struct student1 *node)
{
    struct student1 *temp;   struct student1 *original;   struct student1 *right;

    // checks if node that was passed was null or had no right children
    if(node == NULL || node->right == NULL)
    {
        return;
    }

    original = node;
    right = original->right;
    temp = (struct student1*)malloc(sizeof(struct student1));

    // copies info from original node to temp
    strcpy(temp->name, original->name);
    strcpy(temp->studentNumber, original->studentNumber);

    // copies info from right node to original node
    strcpy(original->name, right->name);
    strcpy(original->studentNumber, right->studentNumber);

    // moves temp between the original and left and saves value of right's right
    temp->right = right->left;
    temp->left = original->left;
    original->right = right->right;
    original->left = temp;

    // frees old right value
    free(right);
}

// Balances a binary tree through Day-Stout-Warren algorithm
void balanceBinary(struct student1 *root)
{
    struct student1 *node;
    int expected, i, oddNodes;
    int numNodes = 0;

    node = root;

    // Unfolds tree by right rotating until there are no more left children
    while (node != NULL)
    {
        while(node->left != NULL)
        {
            rightRotateBinary(node);
        }
        node = node->right;
        numNodes++;
    }

    // Calculates floor nodes through 2n-1 as sum of 2^i from 0 to n is equal to 2^(n+1) - 1
    expected = numNodes - (pow(2,(floor(log2(numNodes+1)))) - 1);
    node = root;
    //folds expected floor values
    for(i = 0; i < expected; i++)
    {
        leftRotateBinary(node);
        node = node->right;
    }

    // rotates odd nodes along tree
    node = root;
    numNodes = numNodes - expected;
    oddNodes = (numNodes+1)/2;
    while(oddNodes > 1)
    {
        //left rotates root
        leftRotateBinary(root);

        //rotates odd nodes along the rest of the tree
        for(i=0;i<(oddNodes-1);i++)
        {
            leftRotateBinary(node->right);
            node = node->right;
        }

        //increments odd nodes
        oddNodes = (oddNodes+1)/2;
    }

}
//Given a binary search tree and a name, this function checks if the name is there
//and returns the new root to be deleted
void delet(struct student1 *remove, char *name){
    remove = search(root,name); // search the database for name and assign it remove
    struct student1 *var1 = NULL;
    struct student1 *var2 =NULL;
    struct student1 *var3 =NULL;

    if(remove->parent){
        // if remove node has a parent
        struct student1 *Parent = remove->parent;
        if(Parent->parent){
            var1 = Parent->parent;
            if(var1->left == Parent) var2 = var1->left;
                else var3 = var1->right;
                    }
        if(Parent->left == remove){
            Parent->left = NULL;
            remove->parent = NULL;
            if(var2 != NULL) var1->left = Parent;
                if(var3 != NULL) var1->right = Parent;
                    return;
        }
        else{
            Parent->right=NULL;
            remove->parent=NULL;
            struct student1 *del = Remove(remove);
            if(del != NULL) del->parent=Parent;
                Parent->right = del;
                if(del != NULL){}
            return;
        }
    }
    else{
        struct student1 *del = Remove(remove);
        root = del;
        return;
    }
}

//delete a student and balance its subtrees
struct student1 *Remove(struct student1 *remove){
    count--;
    if(remove->left){
        struct student1 *ne = findMin(remove->left);
        // Get the findMin: (smallest in the left subtree)
        if(ne->left){
            if(ne->parent == remove){
                if (remove->right) remove->right->parent = ne;
                remove->left = NULL;
                ne->right = remove->right;  //Copy the remove content to this new node
                remove->right = NULL;
                ne->parent = NULL;
                free(remove);
                balanceBinary(ne); // balance binary tree after removal
                return ne;
            }
            else{
                struct student1 *tmp = ne->left;
                tmp->parent = ne->parent;
                ne->parent->right = tmp;
                remove->right = NULL;
                remove->left = NULL;
                if (ne->right) ne->right->parent = ne;
                if (ne->left) ne->left->parent = ne;
                ne->parent = NULL;
                free(remove);
                return ne;
            }
        }
        else{
            struct student1 *tmp = ne->parent;
            if(tmp == remove){
                remove->left = NULL;
                ne->right = remove->right;
                remove->right = NULL;
                ne->parent = NULL;
                free(remove);
                balanceBinary(ne); // balance binary tree after removal
                return ne;
            }
            else{
                tmp->right  = NULL;
                ne->parent = NULL;
                if(remove->right){ remove->right->parent = ne;}
                remove->left->parent = ne;
                ne->left  = remove->left;
                ne->right = remove->right;
                free(remove); // derefrence 'remove'
                return ne;
            }
        }
    }
    if(remove->right){
        struct student1 *ne = remove->right;
        remove->right=NULL;
        ne->parent=NULL;
        free(remove);
        balanceBinary(ne); // balances binary tree after removal
        return ne;
    }
    if(remove->left == NULL && remove->right == NULL){
        free(remove);
        return NULL;
    }
    return remove;
}

#endif /* BinaryTree_h */
