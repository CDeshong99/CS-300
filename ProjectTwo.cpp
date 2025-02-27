#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    // Constructor
    Course(string c = "", string t = "") : courseNumber(c), title(t) {}
};

// Node structure for BST
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Constructor
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BinarySearchTree {
private:
    Node* root;

    // Helper function for in-order traversal
    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->course.courseNumber << ": " << node->course.title << endl;
            inOrderTraversal(node->right);
        }
    }

    // Helper function for inserting a course
    Node* insert(Node* node, Course course) {
        if (!node) return new Node(course);
        if (course.courseNumber < node->course.courseNumber)
            node->left = insert(node->left, course);
        else
            node->right = insert(node->right, course);
        return node;
    }

    // Helper function for searching a course
    Node* search(Node* node, const string& courseNumber) {
        if (!node || node->course.courseNumber == courseNumber)
            return node;
        if (courseNumber < node->course.courseNumber)
            return search(node->left, courseNumber);
        return search(node->right, courseNumber);
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Insert a course into the BST
    void insert(Course course) {
        root = insert(root, course);
    }

    // Display all courses in sorted order
    void displayInOrder() {
        inOrderTraversal(root);
    }

    // Print course information
    void printCourseInfo(const string& courseNumber) {
        Node* courseNode = search(root, courseNumber);
        if (courseNode) {
            cout << "Course: " << courseNode->course.courseNumber << " - " << courseNode->course.title << endl;
            if (!courseNode->course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const auto& pre : courseNode->course.prerequisites)
                    cout << pre << " ";
                cout << endl;
            } else {
                cout << "No prerequisites." << endl;
            }
        } else {
            cout << "Course not found." << endl;
        }
    }
};

// Function to read course data from a file
void loadCoursesFromFile(BinarySearchTree& bst, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, title, prereq;
        vector<string> prerequisites;

        getline(ss, courseNumber, ',');
        getline(ss, title, ',');

        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Course course(courseNumber, title);
        course.prerequisites = prerequisites;
        bst.insert(course);
    }
    file.close();
}

// Menu system for user interaction
void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1. Load Courses from File\n";
    cout << "2. Print Course List (Sorted)\n";
    cout << "3. Print Course Information\n";
    cout << "4. Exit\n";
}

int main() {
    BinarySearchTree bst;
    string filename = "courses.txt";
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline

        switch (choice) {
            case 1:
                loadCoursesFromFile(bst, filename);
                cout << "Courses loaded successfully.\n";
                break;
            case 2:
                cout << "Course List (Sorted):\n";
                bst.displayInOrder();
                break;
            case 3:
                cout << "Enter course number to search: ";
                {
                    string courseNumber;
                    cin >> courseNumber;
                    bst.printCourseInfo(courseNumber);
                }
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
