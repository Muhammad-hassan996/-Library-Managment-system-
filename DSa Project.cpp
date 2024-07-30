#include <iostream>
#include <string>
using namespace std;
class security {
private:
    static const string adminUsername;
    static const string adminPassword;
    static const int maxUsers = 2;
    static string userCred[maxUsers][2];

public:
    static bool forAdmin(string username, string password);
    static bool ForUser(string username, string password);
};

const string security::adminUsername = "admin";
const string security::adminPassword = "adminpass";
string security::userCred[maxUsers][2] = {
    {"hassan@gmail.com", "user1"},
    {"amnaasifch90@gmail.com", "user2"} };

bool security::forAdmin(string username, string password) {
    return (username == adminUsername && password == adminPassword);
}

bool security::ForUser(string username, string password) {
    for (int i = 0; i < maxUsers; ++i) {
        if (userCred[i][0] == username && userCred[i][1] == password) {
            return true;
        }
    }
    return false;
}
struct Node {
    string title;
    int quantity;
    double price;
    Node* next;

    Node(string t, int q, double p) : title(t), quantity(q), price(p), next(nullptr) {}
};
class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void addBook(string title, int quantity, double price) {
        Node* newNode = new Node(title, quantity, price);
        newNode->next = head;
        head = newNode;
    }

    void viewBooks() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Title: " << current->title << "\tQuantity: " << current->quantity << "\tPrice: $" << current->price << endl;
            current = current->next;
        }
    }
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(Node* bookNode) {
        bookNode->next = top;
        top = bookNode;
    }

    Node* pop() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return nullptr;
        }

        Node* temp = top;
        top = top->next;
        temp->next = nullptr;
        return temp;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(Node* bookNode) {
        if (isEmpty()) {
            front = rear = bookNode;
        }
        else {
            rear->next = bookNode;
            rear = bookNode;
        }
    }

    Node* dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return nullptr;
        }

        Node* temp = front;
        front = front->next;
        temp->next = nullptr;
        return temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};
class BinarySearchTree {
private:
    struct TreeNode {
        Node* bookNode;
        TreeNode* left;
        TreeNode* right;

        TreeNode(Node* node) : bookNode(node), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    void insert(TreeNode*& node, Node* bookNode) {
        if (node == nullptr) {
            node = new TreeNode(bookNode);
        }
        else if (bookNode->title < node->bookNode->title) {
            insert(node->left, bookNode);
        }
        else {
            insert(node->right, bookNode);
        }
    }

    void inOrderTraversal(TreeNode* node, LinkedList& sortedList) {
        if (node != nullptr) {
            inOrderTraversal(node->left, sortedList);
            sortedList.addBook(node->bookNode->title, node->bookNode->quantity, node->bookNode->price);
            inOrderTraversal(node->right, sortedList);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(Node* bookNode) {
        insert(root, bookNode);
    }

    void sortList(LinkedList& sortedList) {
        if (root != nullptr) {
            inOrderTraversal(root, sortedList);
        }
    }
};
class Registration {
public:
    string username;
    string password;

    Registration() {}

    Registration(string user, string pass) : username(user), password(pass) {}
};
class User {
public:
    string gmailUsername;
    string gmailPassword;
    string location;
    LinkedList* cart;

    User(Registration reg) : gmailUsername(reg.username), gmailPassword(reg.password), cart(new LinkedList()) {}

    void viewAvailableBooks(LinkedList* inventory) {
        cout << "Available Books:\n";
        inventory->viewBooks();
    }

    void searchBookByTitle(LinkedList* inventory) {
        string title;
        cout << "Enter the title of the book to search: ";
        cin >> title;

        Node* book = findBook(inventory, title);

        if (book != nullptr) {
            cout << "Book found:\n";
            cout << "Title: " << book->title << "\tQuantity: " << book->quantity << "\tPrice: $" << book->price << endl;
        }
        else {
            cout << "Book not found.\n";
        }
    }

    void selectBooks(LinkedList* inventory) {
        string title;
        int quantity;

        cout << "Enter the title of the book: ";
        cin >> title;

        Node* book = findBook(inventory, title);

        if (book != nullptr) {
            cout << "Enter the quantity: ";
            cin >> quantity;

            if (quantity <= book->quantity) {
                cart->addBook(book->title, quantity, book->price);
                cout << "Book added to cart.\n";
            }
            else {
                cout << "Insufficient quantity available.\n";
            }
        }
        else {
            cout << "Book not found.\n";
        }
    }

    Node* findBook(LinkedList* inventory, string title) {
        Node* current = inventory->head;
        while (current != nullptr) {
            if (current->title == title) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void provideLocation() {
        cout << "Enter your location (address): ";
        cin.ignore();
        getline(cin, location);
    }

    void displayCart() {
        cout << "Cart Contents:\n";
        if (cart->head == nullptr) {
            cout << "Your cart is empty.\n";
        }
        else {
            Node* current = cart->head;
            while (current != nullptr) {
                cout << "Title: " << current->title << "\tQuantity: " << current->quantity << "\tPrice: $" << current->price << endl;
                current = current->next;
            }
        }
    }

    void calculateTotal() {
        double total = 0.0;
        Node* current = cart->head;
        while (current != nullptr) {
            total += current->quantity * current->price;
            current = current->next;
        }
        cout << "Total amount in your cart: $" << total << endl;
    }

    void buyBooks() {
        if (cart->head == nullptr) {
            cout << "Your cart is empty. Please add books before proceeding to payment.\n";
            return;
        }

        displayCart();
        calculateTotal();
        provideLocation();

        cout << "Location: " << location << endl;
        cout << "Payment successful!\n";
    }
};
class Admin {
public:
    LinkedList* inventory;
    BinarySearchTree bst;
    LinkedList* salesList;

    Admin(LinkedList* inv) : inventory(inv), salesList(new LinkedList()) {}

    void addNewBook() {
        string title;
        int quantity;
        double price;

        cout << "Enter the title of the new book: ";
        cin >> title;
        cout << "Enter the quantity: ";
        cin >> quantity;
        cout << "Enter the price: $";
        cin >> price;

        Node* newBook = new Node(title, quantity, price);
        inventory->addBook(title, quantity, price);
        bst.insert(newBook);
        cout << "New book added to inventory.\n";
    }

    void viewBooks() {
        LinkedList sortedList;
        bst.sortList(sortedList);
        sortedList.viewBooks();
    }

    void viewSales() {
        LinkedList sortedSalesList;
        bst.sortList(*salesList);
        sortedSalesList.viewBooks();
    }

    void removeBook() {
        string title;
        cout << "Enter the title of the book to remove: ";
        cin >> title;

        Node* book = inventory->head;
        Node* prev = nullptr;

        while (book != nullptr && book->title != title) {
            prev = book;
            book = book->next;
        }

        if (book != nullptr) {
            if (prev == nullptr) {
                inventory->head = book->next;
            }
            else {
                prev->next = book->next;
            }

            bst.insert(book);
            delete book;
            cout << "Book removed from inventory.\n";
        }
        else {
            cout << "Book not found.\n";
        }
    }

    void sellBook() {
        string title;
        int quantity;

        cout << "Enter the title of the book to sell: ";
        cin >> title;
        cout << "Enter the quantity to sell: ";
        cin >> quantity;

        Node* book = inventory->head;
        Node* prev = nullptr;

        while (book != nullptr && book->title != title) {
            prev = book;
            book = book->next;
        }

        if (book != nullptr) {
            if (quantity <= book->quantity) {
                salesList->addBook(book->title, quantity, book->price);
                book->quantity -= quantity;
                cout << "Sold " << quantity << " copies of " << book->title << ".\n";
            }
            else {
                cout << "Insufficient quantity available.\n";
            }
        }
        else {
            cout << "Book not found.\n";
        }
    }

    void restockBook() {
        string title;
        int quantity;

        cout << "Enter the title of the book to restock: ";
        cin >> title;
        cout << "Enter the quantity to restock: ";
        cin >> quantity;

        Node* book = inventory->head;

        while (book != nullptr && book->title != title) {
            book = book->next;
        }

        if (book != nullptr) {
            book->quantity += quantity;
            cout << "Restocked " << quantity << " copies of " << book->title << ".\n";
        }
        else {
            cout << "Book not found.\n";
        }
    }
};
int main() {
    LinkedList* inventory = new LinkedList();

    inventory->addBook("Book1", 10, 20.99);
    inventory->addBook("Book2", 15, 15.50);
    inventory->addBook("Book3", 50, 30.75);
    inventory->addBook("Book4", 10, 200.99);
    inventory->addBook("Book6", 15, 150.50);
    inventory->addBook("Book7", 51, 301.75);
    inventory->addBook("Book8", 10, 202.99);
    inventory->addBook("Book9", 15, 152.50);
    inventory->addBook("Book10", 25, 304.375);
    inventory->addBook("Book11", 10, 204.99);
    inventory->addBook("Book12", 15, 156.50);
    inventory->addBook("Book13", 53, 307.75);
    inventory->addBook("Book14", 50, 301.75);
    inventory->addBook("Book15", 56, 303.75);

    User* user = nullptr;
    Admin* admin = new Admin(inventory);
    cout << "Welcome TO Online Book Store" << endl;

    cout << "Login(Admin,User)" << endl;
    cout << endl;

    string username, password;
    int userChoice{};

    do {
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (security::ForUser(username, password)) {
            Registration reg(username, password);
            user = new User(reg);

            do {
                cout << "\n1. View Available Books\n2. Search Book by Title\n3. Select Books\n4. View Cart\n5. Buy Books\n6. Logout\n";
                cin >> userChoice;

                switch (userChoice) {
                case 1:
                    user->viewAvailableBooks(inventory);
                    break;
                case 2:
                    user->searchBookByTitle(inventory);
                    break;
                case 3:
                    user->selectBooks(inventory);
                    break;
                case 4:
                    user->displayCart();
                    user->calculateTotal();
                    break;
                case 5:
                    user->buyBooks();
                    break;
                case 6:
                    delete user;
                    user = nullptr;
                    break;
                default:
                    cout << "Invalid choice.\n";
                }

            } while (user != nullptr);
        }
        else if (security::forAdmin(username, password)) {
            do {
                cout << "\n1. Add New Book\n2. View Books\n3. View Sales\n4. Remove Book\n5. Sell Book\n6. Restock Book\n7. Logout\n";
                cin >> userChoice;

                switch (userChoice) {
                case 1:
                    admin->addNewBook();
                    break;
                case 2:
                    admin->viewBooks();
                    break;
                case 3:
                    admin->viewSales();
                    break;
                case 4:
                    admin->removeBook();
                    break;
                case 5:
                    admin->sellBook();
                    break;
                case 6:
                    admin->restockBook();
                    break;
                case 7:
                    break;
                default:
                    cout << "Invalid choice.\n";
                }

            } while (userChoice != 7);
        }
        else {
            cout << "Invalid username or password.\n";
        }

    } while (userChoice != 7);

    delete inventory;
    delete admin;

    return 0;
}
