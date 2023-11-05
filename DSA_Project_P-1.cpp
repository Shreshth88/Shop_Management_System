#include <iostream>
#include <string>

using namespace std;

struct Product {
    string id;
    string name;
    int originalPrice;
    int price;
    int quantity;
    Product* next;
};

typedef Product* ProductNode;

struct User {
    string name;
    string surname;
    string contact;
    string address;
    string date;
};

typedef User* UserNode;

struct Admin {
    string username;
    string password;
};

typedef Admin* AdminNode;

struct BucketItem {
    string productId;
    string productName;
    int productPrice;
    int ogproductPrice;
    int productQuantity;
    BucketItem* next;
};

typedef BucketItem* BucketItemNode;

struct InvoiceRecord {
    string date;
    int amount;
    int ogtotal; 
    InvoiceRecord* next;
};

typedef InvoiceRecord* InvoiceRecordNode;

InvoiceRecordNode createInvoiceRecord(InvoiceRecordNode top, int sum, int ogtotal, string date) {
    InvoiceRecordNode record = new InvoiceRecord;
    record->date = date;
    record->amount = sum;
    record->ogtotal = ogtotal; 
    record->next = top;
    top = record;
    return top;
}

void calculateTotalRevenue(InvoiceRecordNode top) {
    int totalRevenue = 0;
    int totalogRevenue = 0;
    string endDate;
    cout << "Enter the date on which you want to calculate revenue (DD-MM-YYYY): " << endl;
    cin >> endDate;

    while (top != nullptr) {
        if (top->date == endDate) {
            totalRevenue += top->amount;
            totalogRevenue += top->ogtotal; 
        }
        top = top->next;
    }

    if (totalRevenue > 0) {
        int profit = totalRevenue - totalogRevenue;
        cout << "Total revenue for this duration is: " << totalRevenue << endl;
        cout << "Total profit for this duration is: " << profit << endl;
    } else {
        cout << "There was a problem or there is no record. Please try again :)" << endl;
    }
}

int calculateTotalPrice(BucketItemNode head) {
    int total = 0;
    BucketItemNode temp = head;
    while (temp != nullptr) {
        total += (temp->productQuantity) * (temp->productPrice);
        temp = temp->next;
    }
    return total;
}

int login(AdminNode& adminHead) {
    string username;
    string password;
    adminHead = new Admin;
    adminHead->username = "sm9779";
    adminHead->password = "SRM@55";
    cout << "Enter the Username: " << endl;
    cin >> username;
    cout << "Enter the Password: " << endl;
    cin >> password;
    if (username == adminHead->username && password == adminHead->password) {
        return 1;
    }
    return 0;
}

ProductNode insertProduct(ProductNode head, string id, string name, int price, int quantity, int originalPrice) {
    ProductNode newNode = new Product;
    newNode->id = id;
    newNode->name = name;
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->originalPrice = originalPrice;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        ProductNode temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return head;
}

ProductNode deleteProduct(ProductNode head) {
    string id;
    cout << "Enter the product id of the product to be deleted: ";
    cin >> id;

    if (head == nullptr) {
        cout << "Can't perform deletion since there are no products." << endl;
    }
    else if (head->id == id) {
        ProductNode temp = head;
        head = head->next;
        delete temp;
    }
    else {
        ProductNode temp = head;
        ProductNode prev = nullptr;
        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr) {
            prev->next = temp->next;
            delete temp;
        }
        else {
            cout << "Product not found." << endl;
        }
    }

    return head;
}

ProductNode userInsertProduct(ProductNode head) {
    int price, quantity, originalPrice;
    string id, name;
    cout << "Enter item ID: ";
    cin >> id;
    cout << "Enter product name: ";
    cin >> name;
    cout << "Enter the original price of the product at which you have purchased it: ";
    cin >> originalPrice;
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;
    head = insertProduct(head, id, name, price, quantity, originalPrice);
    cout << "New product is added :)" << endl;
    return head;
}

string checkProductName(ProductNode head) {
    string productName;
    while (1) {
        cout << "Enter Product Name: ";
        cin >> productName;
        ProductNode temp = head;
        while (temp != nullptr) {
            if (temp->name == productName) {
                return temp->id;
            }
            temp = temp->next;
        }
        cout << "Product not found. Please try again." << endl;
    }
}

ProductNode updateProductQuantityById(ProductNode head, int newQuantity, string productId) {
    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->id == productId) {
            if (temp->quantity >= newQuantity) {
                temp->quantity -= newQuantity;
                return head;
            }
            else {
                if (temp->quantity < newQuantity) {
                    char ch;
                    cout << "We don't have enough stock; we have only " << temp->quantity << " quantity. Do you want this?" << endl;
                    cout << "If Yes, then press Y" << endl;
                    cin >> ch;
                    if (ch == 'Y') {
                        temp->quantity = 0;
                        return head;
                    }
                    return head;
                }
                else if (temp->quantity == 0) {
                    cout << "Not enough quantity available." << endl;
                    return head;
                }
            }
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

ProductNode updateProductQuantityByName(ProductNode head, int newQuantity, string productName) {
    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->name == productName) {
            if (temp->quantity >= newQuantity) {
                temp->quantity -= newQuantity;
                return head;
            }
            else {
                if (temp->quantity < newQuantity) {
                    char ch;
                    cout << "We don't have enough stock; we have only " << temp->quantity << " quantity. Do you want this?" << endl;
                    cout << "If Yes, then press Y" << endl;
                    cin >> ch;
                    if (ch == 'Y') {
                        temp->quantity = 0;
                        return head;
                    }
                    return head;
                }
                else if (temp->quantity == 0) {
                    cout << "Not enough quantity available." << endl;
                    return head;
                }
            }
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

ProductNode changeProductQuantity(ProductNode head) {
    string productId;
    int newQuantity;
    cout << "Enter the Product ID for quantity update: ";
    cin >> productId;
    cout << "Enter the new quantity: ";
    cin >> newQuantity;

    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->id == productId) {
            temp->quantity = newQuantity;
            return head;
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

ProductNode changeProductPrice(ProductNode head) {
    string productId;
    int newPrice;
    cout << "Enter the Product ID for price update: ";
    cin >> productId;
    cout << "Enter the new price: ";
    cin >> newPrice;

    ProductNode temp = head;
    while (temp != nullptr) {
        if (temp->id == productId) {
            temp->price = newPrice;
            return head;
        }
        temp = temp->next;
    }

    cout << "Product not found." << endl;
    return head;
}

string checkProductId(ProductNode head) {
    string productId;
    while (1) {
        cout << "Enter the Product ID of the item you'd like: ";
        cin >> productId;
        ProductNode temp = head;
        while (temp != nullptr) {
            if (temp->id == productId) {
                return productId;
            }
            temp = temp->next;
        }
        cout << "Product not found. Please try again." << endl;
    }
}

BucketItemNode insertBucketItemById(ProductNode head, BucketItemNode head21, string productId, int newQuantity) {
    BucketItemNode newItem = new BucketItem;
    ProductNode temp = head;
    while (temp->id != productId) {
        temp = temp->next;
    }
    newItem->productId = temp->id;
    newItem->productName = temp->name;
    newItem->productPrice = temp->price;
    newItem->productQuantity = newQuantity;
    newItem->ogproductPrice = temp->originalPrice;
    newItem->next = nullptr;
    
    if (head21 == nullptr) {
        head21 = newItem;
    } else {
        BucketItemNode temp1 = head21;
        while (temp1->next != nullptr) {
            temp1 = temp1->next;
        }
        temp1->next = newItem;
    }
    return head21;
}

BucketItemNode insertBucketItemByName(ProductNode head, string productName, int newQuantity) {
    BucketItemNode head2 = nullptr;
    BucketItemNode newItem = new BucketItem;
    ProductNode temp = head;
    while (temp->name != productName) {
        temp = temp->next;
    }
    newItem->productId = temp->id;
    newItem->productName = temp->name;
    newItem->productPrice = temp->price;
    newItem->productQuantity = newQuantity;
    newItem->ogproductPrice = temp->originalPrice;
    newItem->next = nullptr;
    
    if (head2 == nullptr) {
        head2 = newItem;
    } else {
        BucketItemNode tempBucket = head2;
        while (tempBucket->next != nullptr) {
            tempBucket = tempBucket->next;
        }
        tempBucket->next = newItem;
    }
    return head2;
}

BucketItemNode Emptybucket (BucketItemNode head) {
    BucketItemNode temp = head;
    BucketItemNode temp1 = head->next;
    while (temp1 != nullptr)
    {
        delete temp;
        temp=temp1;
        temp1=temp1->next;
    }
    delete temp ;
    head = nullptr;
    return head;
}

UserNode insertUserInfo(UserNode head1) {
    head1 = new User;
    cout << "Enter the Name of the customer: ";
    cin >> head1->name;
    cout << "Enter the Surname of the customer: ";
    cin >> head1->surname;
    cout << "Enter the contact of the customer: ";
    cin >> head1->contact;
    cout << "Enter the address of the customer: ";
    cin >> head1->address;
    cout << "Enter the date of invoice: ";
    cin >> head1->date;
    return head1;
}

string displayUserInfo(UserNode head1) {
    cout << endl << "---------------------------------------------------INVOICE-------------------------------------------------------------" << endl;
    cout << endl << "                                             SHRESHTH's CLOTH STORE                                                      " << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Name of Customer: " << head1->name << " " << head1->surname << "                 " << "Contact Number: " << head1->contact << endl;
    cout << "Address: " << head1->address << "                                " << "Date of Invoice : " << head1->date << endl << endl << endl;
    return (head1->date);
}

void displayProducts(ProductNode head) {
    cout << "Product ID \t" << "Product Name \t" << "Product Price \t" << "Product Quantity" << endl;

    while (head != nullptr) {
        cout << head->id << "      \t" << head->name << "      \t" << head->price << "      \t" << head->quantity << endl;
        head = head->next;
    }
}

void displayBucketItems(BucketItemNode head) {
    cout << "Product ID \t" << "Product Name \t" << "Product MRP \t" << "Product Quantity \t  " << "Price" << endl;
    cout << "=============================================================================================================" << endl;
    while (head != nullptr) {
        cout << head->productId << "      \t" << head->productName << "      \t" << head->productPrice << "      \t" << head->productQuantity << "                         " << (head->productQuantity) * (head->productPrice) << endl;
        head = head->next;
    }
}

void totalsumdisplay(int total){
    cout << "-----------------------------------------------------------------------------------------------------------------------";
    cout << endl << "                                                            Total Price = " << total;
    cout << endl << "-----------------------------------------------------------------------------------------------------------------------";
}

int sumofogprice (BucketItemNode head){
    int Total_og = 0;
    while (head != nullptr){
        Total_og +=(head->productQuantity)*(head->ogproductPrice);
        head = head->next;
    }
    return Total_og;
}

int main() {
    ProductNode productHead = nullptr;
    UserNode userHead = nullptr;
    BucketItemNode bucketHead = nullptr;
    InvoiceRecordNode invoiceRecords = nullptr;
    string date;
    productHead = insertProduct(productHead, "P-1", "T-shirt", 500, 20, 250);
    productHead = insertProduct(productHead, "P-2", "Shirt", 600, 21, 300);
    productHead = insertProduct(productHead, "P-3", "Pants", 5000, 22, 2000);
    
    int choice, n, ch, original_price, nTries = 0;
    int verification;
    int newQuantity;
    string productId;
    AdminNode adminHead = nullptr;

    while (nTries != 3) {
        verification = login(adminHead);
        if (verification == 1) {
            do {
                cout << "------------------ Menu ------------" << endl;
                cout << "1. Insert Product" << endl;
                cout << "2. Change in Product Quantity" << endl;
                cout << "3. Change in Product Price" << endl;
                cout << "4. Delete Product" << endl;
                cout << "5. Display Products" << endl;
                cout << "6. Invoice Generation" << endl;
                cout << "7. Profit Calculator" << endl;
                cout << "8. Exit" << endl;

                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = userInsertProduct(productHead);
                        }
                        break;
                    case 2:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = changeProductQuantity(productHead);
                        }
                        break;
                    case 3:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = changeProductPrice(productHead);
                        }
                        break;
                    case 4:
                        cout << "Enter Number of Products: ";
                        cin >> n;
                        for (int i = 1; i <= n; i++) {
                            productHead = deleteProduct(productHead);
                        }
                        break;
                    case 5:
                        displayProducts(productHead);
                        break;
                    case 6:
                        userHead = insertUserInfo(userHead);
                        do {
                            cout << endl << "Enter the choice" << endl;
                            cout << "1. Insert Product By Product ID" << endl;
                            cout << "2. Insert Product By Name" << endl;
                            cout << "3. Exit" << endl;
                            cin >> ch;
                            switch (ch) {
                                case 1:
                                    int total;
                                    cout << "Enter Number of Products: ";
                                    cin >> n;
                                    for (int i = 1; i <= n; i++) {
                                        productId = checkProductId(productHead);
                                        cout << "Enter the quantity you want: ";
                                        cin >> newQuantity;
                                        productHead = updateProductQuantityById(productHead, newQuantity, productId);
                                        bucketHead = insertBucketItemById(productHead, bucketHead, productId, newQuantity);
                                    }
                                    date = displayUserInfo(userHead);
                                    displayBucketItems(bucketHead);
                                    total = calculateTotalPrice(bucketHead);
                                    totalsumdisplay(total);
                                    original_price = sumofogprice (bucketHead);
                                    invoiceRecords = createInvoiceRecord(invoiceRecords, total, original_price, date);
                                    bucketHead = Emptybucket (bucketHead);
                                    break;
                                case 2:
                                    cout << "Enter Number of Products: ";
                                    cin >> n;
                                    for (int i = 1; i <= n; i++) {
                                        string productName = checkProductName(productHead);
                                        cout << "Enter the quantity you want: ";
                                        cin >> newQuantity;
                                        productHead = updateProductQuantityByName(productHead, newQuantity, productName);
                                        bucketHead = insertBucketItemByName(productHead, productName, newQuantity);
                                    }
                                    date = displayUserInfo(userHead);
                                    displayBucketItems(bucketHead);
                                    total = calculateTotalPrice(bucketHead);
                                    totalsumdisplay(total);
                                    original_price = sumofogprice (bucketHead);
                                    invoiceRecords = createInvoiceRecord(invoiceRecords, total, original_price, date);
                                    bucketHead = Emptybucket (bucketHead);
                                    break;
                                case 3:
                                    break;
                                default:
                                    cout << "Entered something wrong, please try again.";
                                    break;
                            }
                        } while (ch != 3);
                        break;
                    case 7:
                        calculateTotalRevenue(invoiceRecords);
                        break;
                    case 8:
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 8);
            break;
        } else {
            cout << "You have entered wrong info. Try Again :)" << endl;
            nTries++;
        }
    }
    return 0;
}
