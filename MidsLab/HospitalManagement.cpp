#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

struct emergency {
    string name;
    int age;
    int dis;
    emergency *forw = NULL;
};

struct doctor {
    string dName;
    int dAge;
    int dType;
    doctor *next = NULL;
    emergency *patient = NULL;
};

doctor *head = NULL, *tail = NULL, *current = NULL;

void addDoctor() {
    current = new doctor;
    cout << "\n\t\tDoctor\n";
    cout << "Enter name: ";
    cin >> current -> dName;
    cout << "Enter age: ";
    cin >> current -> dAge;
    cout << "\n\tDoctor specialization?"
            "\nEnter 1 for ENT"
            "\nEnter 2 for Skin"
            "\nEnter 3 for Cardic: ";
    cin >> current -> dType;
    if (head == NULL) {
        head = tail = current;
    }
    else {
        tail -> next = current;
        tail = current;
    }
    cout << "\nSuccessful\n";
}

void doubleEnded() {
    int choice = 1;
    doctor *p = head;
    while (p -> dType != choice && p != NULL) {
        p = p -> next;
    }
    if (p -> dType == choice) {
        emergency *cur = new emergency;
        cur -> dis = choice;
        cout << "\n\t\tPatient\n";
        cout << "Enter name: ";
        cin >> cur -> name;
        cout << "Enter age: ";
        cin >> cur -> age;
        int opt;
        cout << "Enter 1 to add at front \nEnter 2 to add at rear: ";
        cin >> opt;
        if (p -> patient == NULL) {
            p -> patient = cur;
        }
        else {
            if (opt == 1) {
                cur -> forw = p -> patient;
                p -> patient = cur;
            }
            else {
                emergency *a = p -> patient;
                while (a -> forw != NULL) {
                    a = a -> forw;
                }
                a -> forw = cur;
            }
        }
        cout << "\nSuccessful\n";
    }
    else {
        cout << "\nDoctor not available!\n";
    }
}

void circular() {
    int choice = 2;
    doctor *p = head;
    while (p -> dType != choice && p != NULL) {
        p = p -> next;
    }
    if (p -> dType == choice) {
        emergency *cur = new emergency;
        cur -> dis = choice;
        cout << "\n\t\tPatient\n";
        cout << "Enter name: ";
        cin >> cur -> name;
        cout << "Enter age: ";
        cin >> cur -> age;
        if (p -> patient == NULL) {
            p -> patient = cur;
        }
        else {
            emergency *a = p -> patient;
            while (a -> forw != NULL) {
                a = a -> forw;
            }
            a -> forw = cur;
        }
        cout << "\nSuccessful\n";
    }
    else {
        cout << "\nDoctor not available!\n";
    }
}

void priority() {
    int choice = 3;
    doctor *p = head;
    while (p -> dType != choice && p != NULL) {
        p = p -> next;
    }
    if (p -> dType == choice) {
        emergency *b = p -> patient;
        emergency *cur = new emergency;
        cur -> dis = choice;
        cout << "\n\t\tPatient\n";
        cout << "Enter name: ";
        cin >> cur -> name;
        cout << "Enter age: ";
        cin >> cur -> age;
        if (p -> patient == NULL) {
            p -> patient = cur;
        }
        else if (b -> age == cur -> age) {
            cur -> forw = b -> forw;
            b -> forw = cur;
        }
        else if (cur -> age > b -> age) {
            cur -> forw = b;
            p -> patient = cur;
        }
        else {
            emergency *q = NULL;
            while (b -> age > cur -> age && b != NULL) {
                q = b;
                b = b -> forw;
            }
            if (b -> age == cur -> age) {
                cur -> forw = b -> forw;
                b -> forw = cur;
            }
            else {
                cur -> forw = b;
                q -> forw = cur;
            }
        }
        cout << "\nSuccessful\n";
    }
    else cout << "\nDoctor not available!\n";
}

void refering() {
    int choice;
    cout << "\nEnter 1 for ENT"
            "\nEnter 2 for Skin"
            "\nEnter 3 for Cardic: ";
    cin >> choice;
    if (choice == 1) {
        doubleEnded();
    }
    else if (choice == 2) {
        circular();
    }
    else if (choice == 3) {
        priority();
    }
    else {
        cout << "\nInvalid choice\n";
    }
}

void dequeDoubleEnded() {
    int choice = 1;
    doctor *p = head;
    while (p -> dType != choice) {
        p = p -> next;
    }
    if (p -> dType == choice) {
        if (p -> patient == NULL) {
            cout << "\nNo Patient!\n";
        }
        else {
            if (p -> patient -> forw == NULL) {
                delete p -> patient;
                p -> patient = NULL;
            }
            else {
                int opt;
                cout << "\nEnter 1 to exit from front \nEnter 2 to exit from rear: ";
                cin >> opt;
                if (opt == 1) {
                    emergency *a = p -> patient;
                    p -> patient = a -> forw;
                    delete a;
                }
                else {
                    emergency *b = p -> patient;
                    while (b -> forw -> forw != NULL) {
                        b = b -> forw;
                    }
                    delete b -> forw;
                    b -> forw = NULL;
                }
            }
        }
        cout << "\nSuccessful\n";
    }
    else cout << "\nInvalid choice\n";
}

void dequeue(int opt) {
    int choice = opt;
    doctor *p = head;
    while (p -> dType != choice) {
        p = p -> next;
    }
    if (p -> dType == choice) {
        if (p -> patient == NULL) {
            cout << "\nNothing patient!\n";
        }
        else {
            if (p -> patient -> forw == NULL) {
                delete p -> patient;
                p -> patient = NULL;
            }
            else {
                emergency *a = p -> patient;
                p -> patient = a -> forw;
                delete a;
            }
        }
        cout << "\nSuccessful\n";
    }
    else cout << "\nInvalid choice\n";
}

void dequeing() {
    int choice;
    cout << "\nEnter 1 for ENT"
            "\nEnter 2 for Skin"
            "\nEnter 3 for Cardic: ";
    cin >> choice;
    if (choice == 1) {
        dequeDoubleEnded();
    }
    else if (choice == 2 || choice == 3) {
        if (choice == 2) {
            dequeue(2);
        }
        else {
            dequeue(3);
        }
    }
    else {
        cout << "\nInvalid choice\n";
    }
}
