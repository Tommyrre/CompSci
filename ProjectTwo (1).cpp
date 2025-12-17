// ProjectTwo.cpp
// CS 300 - ABCU Advising Assistance Program
// Developer: Tommy Reid
// Description: Reads course data from CSV, loads into Binary Search Tree, and provides menu for advisors.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a course
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Node structure for Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = right = nullptr;
    }
};

// Binary Search Tree class
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        } else if (course.courseNumber < node->course.courseNumber) {
            addNode(node->left, course);
        } else {
            addNode(node->right, course);
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            inOrder(node->right);
        }
    }

    Course* search(Node* node, string courseNumber) {
        if (node == nullptr) return nullptr;
        if (node->course.courseNumber == courseNumber) return &node->course;
        if (courseNumber < node->course.courseNumber) return search(node->left, courseNumber);
        return search(node->right, courseNumber);
    }

public:
    BinarySearchTree() { root = nullptr; }

    void Insert(Course course) {
        addNode(root, course);
    }

    void PrintInOrder() {
        if (root == nullptr) {
            cout << "No data loaded. Please load data first.\n";
            return;
        }
        inOrder(root);
    }

    Course* Search(string courseNumber) {
        return search(root, courseNumber);
    }
};

string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

void loadCourses(const string& fileName, BinarySearchTree& bst) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file. Please check the file name and try again.\n";
        return;
    }

    string line;
    int lineCount = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            Course course;
            course.courseNumber = toUpper(tokens[0]);
            course.courseTitle = tokens[1];
            for (size_t i = 2; i < tokens.size(); ++i) {
                if (!tokens[i].empty()) course.prerequisites.push_back(toUpper(tokens[i]));
            }
            bst.Insert(course);
            lineCount++;
        }
    }

    file.close();
    cout << lineCount << " courses loaded successfully.\n";
}

void printCourseInfo(BinarySearchTree& bst, const string& courseNumber) {
    Course* course = bst.Search(courseNumber);

    if (course == nullptr) {
        cout << "Course not found. Please check the course number and try again.\n";
        return;
    }

    cout << course->courseNumber << ", " << course->courseTitle << endl;

    if (!course->prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Prerequisites: None\n";
    }
}

int main() {
    BinarySearchTree bst;
    string fileName = "CS 300 ABCU_Advising_Program_Input (1).csv";
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                loadCourses(fileName, bst);
                break;
            case 2:
                cout << "Here is a sample schedule:" << endl;
                bst.PrintInOrder();
                break;
            case 3: {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                courseNumber = toUpper(courseNumber);
                printCourseInfo(bst, courseNumber);
                break;
            }
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}
