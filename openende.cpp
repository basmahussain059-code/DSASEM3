#include <iostream>
#include <cstring>
using namespace std;
struct Student {
    int roll;
    char name[50];
    Student* left;
    Student* right;
};
struct QNode {
    int roll;
    QNode* next;
};

Student* root = NULL;     // top of the BST
QNode* qFront = NULL;     // first request (served first)
QNode* qRear = NULL;      // last request (new requests join here)

// Returns the student with this roll number, or NULL if not found.
Student* searchStudent(int roll) {
    Student* cur = root;
    while (cur != NULL) {
        if (roll == cur->roll) return cur;          // found
        if (roll < cur->roll) cur = cur->left;      // smaller, go left
        else cur = cur->right;                      // bigger, go right
    }
    return NULL;                                    // not found
}

// Adds a new student. (Duplicate is checked before calling this.)
void insertStudent(int roll, const char* name) {
    Student* n = new Student;
    n->roll = roll;
    strcpy(n->name, name);
    n->left = NULL;
    n->right = NULL;

    if (root == NULL) {                             // tree is empty
        root = n;
        return;
    }

    Student* cur = root;
    while (true) {
        if (roll < cur->roll) {
            if (cur->left == NULL) { cur->left = n; return; }
            cur = cur->left;
        } else {
            if (cur->right == NULL) { cur->right = n; return; }
            cur = cur->right;
        }
    }
}

// Inorder (left, node, right) prints students sorted by roll number.
void displayInorder(Student* node) {
    if (node == NULL) return;
    displayInorder(node->left);
    cout << "  " << node->roll << "\t" << node->name << endl;
    displayInorder(node->right);
}
//postorder
void destroyTree(Student* node) {
    if (node == NULL) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
//QUEUE FUNCTIONS 

bool isQueueEmpty() {
    return qFront == NULL;
}

// Add a request at the rear.
void enqueue(int roll) {
    QNode* n = new QNode;
    n->roll = roll;
    n->next = NULL;

    if (qRear == NULL) {                // queue was empty
        qFront = n;
        qRear = n;
    } else {
        qRear->next = n;
        qRear = n;
    }
}

// Remove and return the request at the front
int dequeue() {
    QNode* temp = qFront;
    int roll = temp->roll;
    qFront = qFront->next;
    if (qFront == NULL) qRear = NULL;   // queue became empty
    delete temp;
    return roll;
}

void addStudent() {
    int roll;
    char name[50];
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter name: ";
    cin.ignore(1000, '\n');             
    cin.getline(name, 50);             

    if (searchStudent(roll) != NULL)
        cout << "Error: roll number " << roll << " already exists.\n";
    else {
        insertStudent(roll, name);
        cout << "Student added.\n";
    }
}

void searchMenu() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    Student* s = searchStudent(roll);
    if (s == NULL)
        cout << "Roll number " << roll << " not found.\n";
    else
        cout << "Found: " << s->roll << "  " << s->name << endl;
}

void displayAll() {
    if (root == NULL) {
        cout << "No students registered.\n";
        return;
    }
    cout << "  Roll\tName\n";
    displayInorder(root);
}

void addRequest() {
    int roll;
    cout << "Enter roll number: ";
    cin >> roll;

    if (searchStudent(roll) == NULL)
        cout << "Rejected: student " << roll << " is not registered.\n";
    else {
        enqueue(roll);                  // repeated requests are allowed
        cout << "Help request added for roll number " << roll << ".\n";
    }
}

void serveRequest() {
    if (isQueueEmpty()) {
        cout << "No pending help requests.\n";
        return;
    }
    int roll = dequeue();
    Student* s = searchStudent(roll);
    cout << "Serving: " << s->roll << "  " << s->name << endl;
}

void helpMenu() {
    int choice;
    cout << "  1. Add help request\n";
    cout << "  2. Serve next request\n";
    cout << "  Enter choice: ";
    cin >> choice;

    if (choice == 1) addRequest();
    else if (choice == 2) serveRequest();
    else cout << "Invalid choice.\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Help Desk =====\n";
        cout << "1. Add student\n";
        cout << "2. Search student by roll number\n";
        cout << "3. Display all students\n";
        cout << "4. Help requests\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {              
            cout << "\nInvalid input. Exiting...\n";
            break;                     
        }

        if (choice == 1) addStudent();
        else if (choice == 2) searchMenu();
        else if (choice == 3) displayAll();
        else if (choice == 4) helpMenu();
        else if (choice == 5) cout << "Exiting...\n";
        else cout << "Invalid choice.\n";
    } while (choice != 5);

    // free all memory before exit
    destroyTree(root);
    while (!isQueueEmpty()) dequeue();

    return 0;
}