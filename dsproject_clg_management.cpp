///Student
//Student ID
//Student Name
//ViewStudents()
//AddStudent()
//RemoveStudent()

///Class Faculty
//Faculty ID
//Faculty Name
//Subject Code
//Current Batches

//AddStudent()
//GiveAttendance()

/*
Login:
Admin - Password
Faculty - FacultyID, Password
Student - StudentID, Password

Menu:
Admin - Display All Students, Add New Student, Delete Student, Update Student Details,
        Display All Faculty,  Add New Faculty, Delete Faculty, Update Faculty Details
Faculty - Display All Student, Add Marks, Update Marks, Add Attendance, Update Attendance, Edit Personal Details
Student - Check Marks, Check Attendance, Edit Personal Details
*/

#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#include <ctime>
using namespace std;

string adminPassword = "admin";

///Student
class Sgpa
{
public:
    char grade;
    Sgpa *next;

    Sgpa()
    {
        grade = NULL;
        next = NULL;
    }
    Sgpa(char g)
    {
        grade = g;
        next = NULL;
    }
};

class Student
{
public:
    //Student Details
    int studentID;
    string studentName;
    string password;
    Sgpa *grades;
    int totalClasses;
    int attendedClasses;

    //AVL Attributes
    Student *left;
    Student *right;
    int height;

    //Functions
    void setDetails()
    {
        cout << "\n\tEnter Student ID: ";
        cin >> studentID;
        cout << "\tEnter Student Name: ";
        cin >> studentName;

        cout << "\tEnter Password for Login: ";
        cin >> password;

        grades = NULL;
        totalClasses = 0;
        attendedClasses = 0;
        left = right = NULL;
        height = 1;
    }
    void updateMarks(char g)
    {
        if(grades!=NULL)
        {
            Sgpa *current = grades;
            while(current->next != NULL)
            {
                current = current->next;
            }
            current->next = new Sgpa(g);
        }
        else
        {
            grades = new Sgpa(g);
        }
    }
    void viewStudent()
    {
        cout << "\tStudent ID: " << studentID << endl;
        cout << "\tStudent Name: " << studentName << endl;
    }
    void viewGrades()
    {
        viewStudent();
        cout << "\n\tGrades: " << endl;
        Sgpa *current = grades;
        int i = 1;
        if(current == NULL)
        {
            cout << "No Grades..." << endl;
        }
        else
        {
            while(current!=NULL)
            {
                cout << "\t\tSem " << i << " SGPA: " << current->grade << endl;
                i++;
                current = current->next;
            }
        }
        cout << endl;
    }
    void addPresentAttendance()
    {
        cout << "\tMarked Present" << endl;
        attendedClasses++;
        totalClasses++;
    }
    void addAbsentAttendance()
    {
        cout << "\tMarked Absent" << endl;
        totalClasses++;
    }
    void viewAttendance()
    {
        if(totalClasses == 0)
        {
            cout << "\tNo Data for Attendance" << endl<< endl;
            return;
        }
        else
        {
            cout << "\tAttended Classes: " << attendedClasses << endl;
            cout << "\tTotal Classes: " << totalClasses << endl;
            cout << "\tPercentage: " << (float)(attendedClasses/totalClasses) * 100 << endl;
        }
        cout << endl;
    }
    void updateAttendance()
    {
        viewStudent();
        viewAttendance();
        cout << "\tUpdate Total Classes: ";
        cin >> totalClasses;
        cout << "\tUpdate Classes Attended: ";
        cin >> attendedClasses;
        Sleep(500);
        cout << "\tAttendance Updated" << endl;
        Sleep(500);
    }
};

///GLOBAL VARIABLE FOR STUDENTS
Student *rootStudent = NULL;

//Marking attendance of all Students
void addAttendance_of_students(Student *root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        addAttendance_of_students(root->left);

        int attendanceChoice = 0;

        while(attendanceChoice != 3)
        {
            root->viewStudent();
            Sleep(500);
            root->viewAttendance();
            Sleep(500);
            cout << "\t1. Present" << endl;
            cout << "\t2. Absent" << endl;
            cout << "\t3. Skip Attendance" << endl;

            Sleep(500);
            cout << "\tEnter your choice: ";
            cin >> attendanceChoice;

            if(attendanceChoice == 1)
            {
                root->addPresentAttendance();
                break;
            }
            else if(attendanceChoice == 2)
            {
                root->addAbsentAttendance();
                break;
            }
            else if(attendanceChoice == 3)
            {
                Sleep(500);
                cout << "\n\tSkipping Attendance for this Student...";
                Sleep(1000);
                return;
            }
            else
            {
                Sleep(500);
                cout << "\n\tPlease Enter Valid Input!!!" << endl;
                Sleep(500);
            }
        }

        addAttendance_of_students(root->right);
    }
}

//Giving Marks to all the Students
void addMarks_of_students(Student *root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        addMarks_of_students(root->left);

        char grade;
        root->viewStudent();
        cout << "\n\tEnter Grade of Student: ";
        cin >> grade;
        root->updateMarks(grade);

        addMarks_of_students(root->right);
    }
}

///AVL - Student Rotation Functions
//For Student
int height(Student *root)
{
    if(root==NULL)
        return 0;
    return root->height;
}

int max(int a, int b)
{
    return (a>b) ? a : b;
}

Student * leftRotate(Student *root)
{
    Student *rootRight = root->right;
    Student *rootRightLeft = rootRight->left;

    //Rotating
    rootRight->left = root;
    root->right = rootRightLeft;

    //Adjusting height
    root->height = 1 + max(height(root->left), height(root->right));
    rootRight->height = 1 + max(height(rootRight->left), height(rootRight->right));

    return rootRight;
}

Student * rightRotate(Student *root)
{
    Student *rootLeft = root->left;
    Student *rootLeftRight = rootLeft->right;

    //Rotating
    rootLeft->right = root;
    root->left = rootLeftRight;

    //Adjusting height
    root->height = 1 + max(height(root->left), height(root->right));
    rootLeft->height = 1 + max(height(rootLeft->left), height(rootLeft->right));

    return rootLeft;
}

int getBalance(Student *root)
{
    if(root==NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Student * addStudent(Student *root, Student *newStudent)
{
    if(root == NULL)
    {
        root = newStudent;
        return root;
    }
    else if(newStudent->studentID < root->studentID)
    {
        root->left = addStudent(root->left, newStudent);
    }
    else if(root->studentID < newStudent->studentID)
    {
        root->right = addStudent(root->right, newStudent);
    }
    else
    {
        cout << "\tCan't have same StudentID!!!" << endl;
        Sleep(500);
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    //Left Left
    if((balance > 1) && (newStudent->studentID < root->left->studentID))
    {
        return rightRotate(root);
    }
    //Right Right
    if((balance < -1) && (root->right->studentID < newStudent->studentID))
    {
        return leftRotate(root);
    }
    //Left Right
    if((balance > 1) && (root->left->studentID < newStudent->studentID))
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right Left
    if((balance < -1) && (newStudent->studentID < root->right->studentID))
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

///For Delete Student
Student * findMin(Student *root)
{
    while(root->left!=NULL)
    {
        root = root->left;
    }
    return root;
}

Student * deletionStudent(Student *root, int key)
{
    if(root==NULL)
    {
        return NULL;
    }
    else if(key < root->studentID)
    {
        root->left = deletionStudent(root->left, key);
    }
    else if(root->studentID < key)
    {
        root->right = deletionStudent(root->right, key);
    }
    else
    {
        if(root->left == NULL)
        {
            Student *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL)
        {
            Student *temp = root->left;
            delete root;
            return temp;
        }
        //Both Child
        else
        {
            Student *temp = findMin(root->right);
            //Copy Temp Data in Root Node
            root->studentID = temp->studentID;
            root->studentName = temp->studentName;
            root->password = temp->password;
            root->grades = temp->grades;
            root->totalClasses = temp->totalClasses;
            root->attendedClasses = temp->attendedClasses;
            root->right = deletionStudent(root->right, temp->studentID);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    //ROTATION
    //R0, R1 - RIGHT Rotate
    if(balance>1 && getBalance(root->left)>=0)
    {
        root = rightRotate(root);
    }
    //R-1 - LR Rotate
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }
    //L0, L-1 - LEFT Rotate
    if(balance<-1 && getBalance(root->right)<=0)
    {
        root = leftRotate(root);
    }
    //L1 - Right Left Rotate
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }

    return root;
}

//Searching in Student
Student * searchStudentLevelOrder(int studentID_to_search)
{
    if(rootStudent == NULL)
    {
        return NULL;
    }

    queue <Student *> q;
    q.push(rootStudent);

    while(!q.empty())
    {
        Student *current = q.front();
        q.pop();

        if(current->studentID == studentID_to_search)
        {
            return current;
        }
        if(current->left!=NULL)
        {
            q.push(current->left);
        }
        if(current->right!=NULL)
        {
            q.push(current->right);
        }
    }
    return NULL;
}

//Printing Students
void inorderStudent(Student *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        inorderStudent(root->left);
        root->viewStudent();
        cout << endl;
        inorderStudent(root->right);
    }
}


///Faculty
class Faculty
{
public:
    //Faculty Details
    int facultyID;
    string facultyName;
    string password;
    string currSubCode;

    //AVL Attributes
    Faculty *left;
    Faculty *right;
    int height;

    void setFaculty()
    {
        cout << "Enter Faculty ID: ";
        cin >> facultyID;
        cout << "Enter Faculty Name: ";
        cin >> facultyName;

        cout << "Enter Faculty Login Password: ";
        cin >> password;

        cout << "Enter Current Subject Code: ";
        cin >> currSubCode;

        left = NULL;
        right = NULL;
        height = 1;
    }
    void viewFaculty()
    {
        cout << "Faculty ID: " << facultyID << endl;
        cout << "Faculty Name: " << facultyName << endl << endl;
    }

    void updateFacultyDetails()
    {
        int updateFacultyChoice = 0;

        while(updateFacultyChoice != 4)
        {
            system("CLS");
            Sleep(500);
            cout << "******************************************************" << endl;
            Sleep(500);
            cout << "\t\t\t\t\tWelcome to Update Faculty Details Menu:- " << endl;
            Sleep(500);
            cout << "******************************************************" << endl;
            Sleep(500);
            viewFaculty();
            cout << endl;
            cout << "\t\t1. Update Faculty Name." << endl;
            cout << "\t\t2. Update Password." << endl;
            cout << "\t\t3. Update Current Subject Code." << endl;
            cout << "\t\t4. Return To Previous Menu." << endl;

            cout << "\n\t\tEnter Your Choice: ";
            cin >> updateFacultyChoice;

            cout << endl;

            switch(updateFacultyChoice)
            {
            case 1:
                {
                    cout << "\tOld Faculty Name: " << facultyName << endl;
                    cout << "\tEnter New Faculty Name: ";
                    cin >> facultyName;
                    Sleep(1000);
                    cout << "\n\tFaculty Name Updated..." << endl;
                    Sleep(2000);
                    break;
                }
            case 2:
                {
                    cout << "\tOld Faculty Password: " << password << endl;
                    cout << "\tEnter New Password: ";
                    cin >> password;
                    Sleep(1000);
                    cout << "\n\tFaculty Password Updated..." << endl;
                    Sleep(2000);
                    break;
                }
            case 3:
                {
                    cout << "\tOld Faculty Current Subject Code: " << currSubCode << endl;
                    cout << "\tEnter New Subject Code: ";
                    cin >> currSubCode;
                    Sleep(1000);
                    cout << "\n\tFaculty Current Subject Code Updated..." << endl;
                    Sleep(2000);
                    break;
                }
            case 4:
                {
                    Sleep(1000);
                    cout << "\n\tReturning to Previous Menu..." << endl;
                    Sleep(2000);
                    break;
                }
            default:
                {
                    Sleep(1000);
                    cout << "\n\tWrong Input!!! Kindly Enter Correct Choice!!!" << endl;
                    Sleep(2000);
                }
            }
        }
    }
};

///GLOBAL VARIABLES FOR FACULTY
Faculty *rootFaculty = NULL;

///AVL - Faculty Rotation Functions
//For Faculty
int height(Faculty *root)
{
    if(root==NULL)
        return 0;
    return root->height;
}

Faculty * leftRotate(Faculty *root)
{
    Faculty *rootRight = root->right;
    Faculty *rootRightLeft = rootRight->left;

    //Rotating
    rootRight->left = root;
    root->right = rootRightLeft;

    //Adjusting height
    root->height = 1 + max(height(root->left), height(root->right));
    rootRight->height = 1 + max(height(rootRight->left), height(rootRight->right));

    return rootRight;
}

Faculty * rightRotate(Faculty *root)
{
    Faculty *rootLeft = root->left;
    Faculty *rootLeftRight = rootLeft->right;

    //Rotating
    rootLeft->right = root;
    root->left = rootLeftRight;

    //Adjusting height
    root->height = 1 + max(height(root->left), height(root->right));
    rootLeft->height = 1 + max(height(rootLeft->left), height(rootLeft->right));

    return rootLeft;
}

int getBalance(Faculty *root)
{
    if(root==NULL)
        return 0;
    return (height(root->left) - height(root->right));
}

Faculty * addFaculty(Faculty *root, Faculty *newFaculty)
{
    if(root == NULL)
    {
        root = newFaculty;
        return root;
    }
    else if(newFaculty->facultyID < root->facultyID)
    {
        root->left = addFaculty(root->left, newFaculty);
    }
    else if(root->facultyID < newFaculty->facultyID)
    {
        root->right = addFaculty(root->right, newFaculty);
    }
    else
    {
        cout << "\n\tCan't have same FacultyID!!!" << endl;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    //Left Left
    if((balance > 1) && (newFaculty->facultyID < root->left->facultyID))
    {
        return rightRotate(root);
    }
    //Right Right
    if((balance < -1) && (root->right->facultyID < newFaculty->facultyID))
    {
        return leftRotate(root);
    }
    //Left Right
    if((balance > 1) && (root->left->facultyID < newFaculty->facultyID))
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right Left
    if((balance < -1) && (newFaculty->facultyID < root->right->facultyID))
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

///For Delete Faculty
Faculty * findMin(Faculty *root)
{
    while(root->left!=NULL)
    {
        root = root->left;
    }
    return root;
}

Faculty * deletionFaculty(Faculty *root, int key)
{
    if(root==NULL)
    {
        return NULL;
    }
    else if(key < root->facultyID)
    {
        root->left = deletionFaculty(root->left, key);
    }
    else if(root->facultyID < key)
    {
        root->right = deletionFaculty(root->right, key);
    }
    else if(root->facultyID == key)
    {
        if(root->left == NULL)
        {
            Faculty *temp = root->right;
            cout << "Deletion Successful!" << endl;
            delete root;
            return temp;
        }
        else if(root->right == NULL)
        {
            Faculty *temp = root->left;
            cout << "Deletion Successful!" << endl;
            delete root;
            return temp;
        }
        //Both Child
        else
        {
            Faculty *temp = findMin(root->right);
            //Copy Temp Data in Root Node
            root->facultyID = temp->facultyID;
            root->facultyName = temp->facultyName;
            root->password = temp->password;
            root->currSubCode = temp->currSubCode;
            Sleep(1000);
            cout << "\tDeletion Successful!" << endl;
            Sleep(1000);
            root->right = deletionFaculty(root->right, temp->facultyID);
        }
    }
    else
    {
        Sleep(1000);
        cout << "\tNo record found with Faculty ID " << key <<endl;
        Sleep(1000);
        return NULL;
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    //ROTATION
    //R0, R1 - RIGHT Rotate
    if(balance>1 && getBalance(root->left)>=0)
    {
        root = rightRotate(root);
    }
    //R-1 - LR Rotate
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }
    //L0, L-1 - LEFT Rotate
    if(balance<-1 && getBalance(root->right)<=0)
    {
        root = leftRotate(root);
    }
    //L1 - Right Left Rotate
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }

    return root;
}

//Printing for Faculty
void inorderFaculty(Faculty *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        inorderFaculty(root->left);
        root->viewFaculty();
        inorderFaculty(root->right);
    }
}

//Searching for Faculty - INORDER
void searchFaculty(Faculty *root, int facultyID_to_search)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        searchFaculty(root->left, facultyID_to_search);
        if(root->facultyID == facultyID_to_search)
        {
            root->updateFacultyDetails();
        }
        searchFaculty(root->right, facultyID_to_search);
    }
}

//Searching in Faculty - Level Order
Faculty * searchFacultyLevelOrder(int facultyID_to_search, string password_to_search)
{
    if(rootFaculty == NULL)
    {
        return NULL;
    }

    int flag = 0;
    queue <Faculty *> q;
    q.push(rootFaculty);

    while(!q.empty())
    {
        Faculty *current = q.front();
        q.pop();

        if(current->facultyID == facultyID_to_search)
        {
            flag = 1;
            if(current->password == password_to_search)
            {
                return current;
            }
            else
            {
                Sleep(500);
                cout << "\n\tPassword Incorrect!!! Kindly Login with Correct Password!!!" << endl;
                Sleep(500);
                return NULL;
            }
        }
        if(current->left!=NULL)
        {
            q.push(current->left);
        }
        if(current->right!=NULL)
        {
            q.push(current->right);
        }
    }
    if(flag == 0)
    {
        Sleep(500);
        cout << "\n\tFacultyID Not Found!!! Kindly Login with Correct FacultyID!!!" << endl;
        Sleep(500);
    }
    return NULL;
}

void adminMenu()
{
    int adminChoice = 0;
    while(adminChoice != 8)
    {
        Sleep(500);
        cout << "\n******************************************************" << endl;
        Sleep(500);
        cout << "\t\t\tWelcome to Admin Menu:" << endl;
        Sleep(500);
        cout << "******************************************************" << endl;
        Sleep(1000);
        cout << "\n\t\t1. Display Faculty." << endl;
        cout << "\t\t2. Add New Faculty." << endl;
        cout << "\t\t3. Delete Faculty." << endl;
        cout << "\t\t4. Update Faculty Details." << endl;
        cout << "\t\t5. Display Students." << endl;
        cout << "\t\t6. Add New Student." << endl;
        cout << "\t\t7. Delete Student." << endl;
        cout << "\t\t8. Return to Previous Menu." << endl;
        Sleep(500);

        cout << "\n\t\tEnter your choice: ";
        cin >> adminChoice;

        system("CLS");

        switch(adminChoice)
        {
        case 1:
            {
                if(rootFaculty == NULL)
                {
                    Sleep(500);
                    cout << "\n\tNo Faculty Members in Database!" << endl;
                    Sleep(1000);
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tFaculty List: " << endl;
                    Sleep(500);
                    inorderFaculty(rootFaculty);
                    Sleep(1000);
                    cout << endl;
                }
                break;
            }
        case 2:
            {
                Sleep(500);
                cout << "\n\tEnter Details of New Faculty Member:- " << endl;
                Faculty *newFaculty = new Faculty();
                newFaculty->setFaculty();

                Sleep(1000);
                cout << "\n\tAdding new Faculty member to the Database..." << endl;
                Sleep(1000);
                rootFaculty = addFaculty(rootFaculty, newFaculty);
                cout << "\n\tAdded Successfully..." << endl;
                Sleep(1000);
                break;
            }
        case 3:
            {
                Sleep(500);
                int deleteFacultyId;
                cout << "\n\tEnter the FacultyID to Delete from Database: ";
                cin >> deleteFacultyId;
                Sleep(500);

                cout << "\n\tDeleting Faculty Member..." << endl;
                Sleep(1000);
                rootFaculty = deletionFaculty(rootFaculty, deleteFacultyId);
                Sleep(1000);
                break;
            }
        case 4:
            {
                Sleep(500);
                int updatefacultyID;
                cout << "\n\tEnter Faculty ID to update details: " << endl;
                cin >> updatefacultyID;

                Sleep(500);
                searchFaculty(rootFaculty, updatefacultyID);
                Sleep(500);
                break;
            }
        case 5:
            {
                if(rootStudent == NULL)
                {
                    Sleep(1000);
                    cout << "\n\tNo Students in Database!" << endl;
                    Sleep(1000);
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tStudents List: " << endl;
                    Sleep(500);
                    inorderStudent(rootStudent);
                    cout << endl;
                }
                break;
            }
        case 6:
            {
                Sleep(500);
                cout << "\n\tEnter Details of New Student:- " << endl;
                Student *newStudent = new Student();
                newStudent->setDetails();

                Sleep(500);
                cout << "\n\tAdding new Student to the Database..." << endl;
                rootStudent = addStudent(rootStudent, newStudent);
                Sleep(1000);
                cout << "\n\tAdded Successfully..." << endl;
                Sleep(500);
                break;
            }
        case 7:
            {
                Sleep(500);
                int deleteStudentId;
                cout << "\n\tEnter the StudentID to Delete from Database: ";
                cin >> deleteStudentId;

                Sleep(500);
                cout << "\n\tDeleting Student..." << endl;
                rootStudent = deletionStudent(rootStudent, deleteStudentId);
                Sleep(500);
                cout << endl;
                break;
            }
        case 8:
            {
                Sleep(500);
                cout << "\n\tReturning to Previous Menu..." << endl;
                Sleep(1000);
                system("CLS");
                break;
            }
        default:
            {
                Sleep(500);
                cout << "\n\tWrong input! Kindly enter correct input!!!" << endl;
                Sleep(1000);
            }
        }
    }
}

void facultyMenu(Faculty *facultyPointer)
{
    int facultyChoice = 0;
    while(facultyChoice != 6)
    {
        Sleep(500);
        cout << "\n******************************************************" << endl;
        Sleep(500);
        cout << "\t\tWelcome " << facultyPointer->facultyName << " to Faculty Menu!" << endl;
        Sleep(500);
        cout << "******************************************************" << endl;
        Sleep(500);
        cout << "\t\t1. Display Students." << endl;
        cout << "\t\t2. Add Attendance of Students." << endl;
        cout << "\t\t3. Update Attendance of a Student." << endl;
        cout << "\t\t4. Submit Marks of Students." << endl;
        cout << "\t\t5. Update Account Details." << endl;
        cout << "\t\t6. Return to Previous Menu." << endl;

        Sleep(500);
        cout << "\n\t\tEnter your Choice: ";
        cin >> facultyChoice;
        Sleep(500);
        system("CLS");

        switch(facultyChoice)
        {
        case 1:
            {
                if(rootStudent == NULL)
                {
                    Sleep(500);
                    cout << "\n\tNo Students in Database!" << endl;
                    Sleep(1000);
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tStudents List: " << endl;
                    Sleep(500);
                    inorderStudent(rootStudent);
                    Sleep(500);
                    cout << endl;
                }
                break;
            }
        case 2:
            {
                Sleep(500);
                cout << "\n\tAdd Attendance of Students:-" << endl;
                Sleep(500);
                addAttendance_of_students(rootStudent);
                Sleep(500);
                cout << "Attendance Marked!" << endl;
                Sleep(1000);
                break;
            }
        case 3:
            {
                Sleep(500);
                cout << "\n\tUpdate Attendance of a Student:- " << endl;
                Sleep(500);
                int studentID_to_update_attendance;
                cout << "\n\t\tEnter StudentID to update attendance: ";
                cin >> studentID_to_update_attendance;

                Student *studentPointer = searchStudentLevelOrder(studentID_to_update_attendance);
                if(studentPointer != NULL)
                {
                    Sleep(500);
                    cout << "\n\tStudent Found..." << endl;
                    Sleep(500);
                    studentPointer->updateAttendance();
                    Sleep(1000);
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tStudentID NOT FOUND!" << endl;
                    Sleep(1000);
                }
                break;
            }
        case 4:
            {
                Sleep(500);
                cout << "\n\tSubmit Grade of all Students:-" << endl;
                Sleep(500);
                addMarks_of_students(rootStudent);
                Sleep(500);
                cout << "\n\tGrades Submitted!" << endl;
                Sleep(500);
                break;
            }
        case 5:
            {
                Sleep(500);
                cout << "\n\tEntering Update Faculty Details Menu..." << endl;
                Sleep(1000);
                system("CLS");

                facultyPointer->updateFacultyDetails();
                Sleep(500);
                cout << "\n\tDetails Updated!" << endl;
                Sleep(1000);
                break;
            }
        case 6:
            {
                Sleep(500);
                cout << "\n\tReturning to Previous Menu..." << endl;
                Sleep(500);
                system("CLS");
                break;
            }
        default:
            {
                Sleep(500);
                cout << "\n\tWrong Input!!! Kindly Enter Correct Choice!!!" << endl;
                Sleep(500);
            }
        }
    }
}

void studentMenu(Student *studentPointer)
{
    int studentChoice = 0;
    while(studentChoice != 4)
    {
        Sleep(500);
        cout << "******************************************************" << endl;
        Sleep(500);
        cout << "\t\tWelcome " << studentPointer->studentName << " to Student Menu!" << endl;
        Sleep(500);
        cout << "******************************************************" << endl;
        Sleep(500);
        cout << "\t\t1. Check Attendance." << endl;
        cout << "\t\t2. Check Marks." << endl;
        cout << "\t\t3. Edit Personal Details." << endl;
        cout << "\t\t4. Return to Previous Menu." << endl;
        Sleep(500);

        cout << "\t\tEnter your Choice: ";
        cin >> studentChoice;

        system("CLS");

        switch(studentChoice)
        {
        case 1:
            {
                Sleep(500);
                cout << "\n\tYour Attendance:-" << endl;
                Sleep(500);
                studentPointer->viewAttendance();
                Sleep(500);
                break;
            }
        case 2:
            {
                Sleep(500);
                cout << "\n\tYour Marks:-" << endl;
                Sleep(500);
                studentPointer->viewGrades();
                Sleep(500);
                break;
            }
        case 3:
            {
                Sleep(500);
                int updateDetailsChoice = 0;
                while(updateDetailsChoice != 3)
                {
                    Sleep(500);
                    cout << "******************************************************" << endl;
                    Sleep(500);
                    cout << "\t\t\tWelcome to Update Student Details Menu:" << endl;
                    Sleep(500);
                    cout << "******************************************************" << endl;
                    Sleep(500);
                    cout << "\n\t\t1. Update Student Name." << endl;
                    cout << "\t\t2. Update Student Login Password." << endl;
                    cout << "\t\t3. Return to Previous Menu." << endl;

                    Sleep(500);
                    cout << "\t\tEnter your choice: ";
                    cin >> updateDetailsChoice;

                    system("CLS");

                    switch(updateDetailsChoice)
                    {
                    case 1:
                        {
                            Sleep(500);
                            cout << "\n\tOld Student Name: " << studentPointer->studentName << endl;
                            Sleep(500);
                            cout << "\tEnter New Student Name: ";
                            cin >> studentPointer->studentName;
                            Sleep(1000);
                            cout << "\tUpdating Student Name..." << endl;
                            Sleep(1000);
                            cout << "\tStudent Name Updated!" << endl;
                            break;
                        }
                    case 2:
                        {
                            Sleep(500);
                            cout << "\n\tOld Student Password: " << studentPointer->password << endl;
                            Sleep(500);
                            cout << "\tEnter New Student password: ";
                            cin >> studentPointer->password;
                            Sleep(1000);
                            cout << "\tUpdating Student Password..." << endl;
                            Sleep(1000);
                            cout << "\tStudent Password Updated!" << endl;
                            break;
                        }
                    case 3:
                        {
                            Sleep(500);
                            cout << "\n\tReturning to Previous Menu..." << endl;
                            Sleep(2000);
                            system("CLS");
                            break;
                        }
                    default:
                        {
                            Sleep(500);
                            cout << "\n\tKindly enter a Valid Input!!!" << endl;
                            Sleep(1000);
                        }
                    }
                }
                break;
            }
        case 4:
            {
                Sleep(500);
                cout << "\n\tReturning to Previous Menu..." << endl;
                Sleep(1000);
                system("CLS");
                break;
            }
        default:
            {
                Sleep(500);
                cout << "\n\tWrong Input! Kindly enter correct input!!!" << endl;
                Sleep(1000);
            }
        }
    }
}

int main()
{
    system("color E0");
    int choice = 0;

    while(choice!=4)
    {
        system("CLS");
        Sleep(500);
        cout << "\n******************************************************" << endl;
        Sleep(500);
        cout << "\t\t\tWELCOME TO JIIT WEBPORTAL!" << endl;
        Sleep(500);
        cout << "******************************************************" << endl;
        Sleep(500);
        cout << "\t\tEnter type of user: " << endl;
        cout << "\t\t1. Admin" << endl;
        cout << "\t\t2. Faculty" << endl;
        cout << "\t\t3. Student" << endl;
        cout << "\t\t4. Exit" << endl;

        Sleep(500);
        cout << "\t\tEnter choice: ";
        cin >> choice;
        cout << endl;
        switch(choice)
        {
        case 1:
            {
                Sleep(500);
                string inputPassword;
                cout << "\n\t\tEnter Admin Password: ";
                cin >> inputPassword;
                if(inputPassword == adminPassword)
                {
                    Sleep(1000);
                    cout << "\n\tCorrect Admin Password!!!" << endl;
                    Sleep(1000);
                    cout << "\n\tLogging in as Admin..." << endl;
                    Sleep(2000);
                    system("CLS");
                    adminMenu();
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tWrong Password!!! Please try again!!!" << endl;
                    Sleep(1000);
                }
                break;
            }
        case 2:
            {
                int facultyID_to_login;
                string faculty_Password_to_login;

                cout << "\n\tEnter FacultyID to Login: ";
                cin >> facultyID_to_login;
                cout << "\n\tEnter Faculty Password to Login: ";
                cin >> faculty_Password_to_login;

                Faculty *facultyPointer = searchFacultyLevelOrder(facultyID_to_login, faculty_Password_to_login);
                if(facultyPointer != NULL)
                {
                    Sleep(500);
                    cout << "\n\tFacultyID Found!!!" << endl;
                    Sleep(500);
                    cout << "\n\tCorrect Password!!!" << endl;
                    Sleep(500);
                    cout << "\n\tLogging In..." << endl;
                    Sleep(1000);
                    system("CLS");

                    facultyMenu(facultyPointer);
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tKindly Retry!!!" << endl;
                    Sleep(1000);
                }

                break;
            }
        case 3:
            {
                int studentID_to_login;
                string student_Password_to_login;

                Sleep(500);
                cout << "\n\tEnter StudentID to Login: ";
                cin >> studentID_to_login;
                Sleep(500);
                cout << "\n\tEnter Student Password to Login: ";
                cin >> student_Password_to_login;

                Student *studentPointer = searchStudentLevelOrder(studentID_to_login);
                if(studentPointer != NULL)
                {
                    if(studentPointer->password == student_Password_to_login)
                    {
                        Sleep(1000);
                        cout << "\n\tStudentID Found!!!" << endl;
                        Sleep(500);
                        cout << "\n\tCorrect Password!!!" << endl;
                        Sleep(500);
                        cout << "\n\tLogging In..." << endl;
                        Sleep(1000);
                        system("CLS");

                        studentMenu(studentPointer);
                    }
                    else
                    {
                        Sleep(500);
                        cout << "\n\tIncorrect Password for Student Login" << endl;
                        Sleep(1000);
                    }
                }
                else
                {
                    Sleep(500);
                    cout << "\n\tStudentID NOT FOUND!!!" << endl;
                    Sleep(1000);
                }

                break;
            }
        case 4:
            {
                Sleep(500);
                cout << "\n\tExiting the Portal!" << endl;
                Sleep(1000);
                cout << "\n\tThank You for visiting!" << endl;
                Sleep(2000);
                break;
            }
        default:
            {
                Sleep(500);
                cout << "\n\tWrong Input! Kindly enter the values between 1 to 4!" << endl;
                Sleep(1000);
            }
        }
    }

    return 0;
}
