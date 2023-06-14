#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 产品类
class Product {
private:
	int productId;
	string productName;
	int productQuantity;
	double productPrice;

public:
	// 构造函数
	Product(int id, string name, int quantity, double price)
		: productId(id), productName(name), productQuantity(quantity), productPrice(price) {}

	// 获取产品ID
	int getProductId() const {
		return productId;
	}

	// 获取产品名称
	string getProductName() const {
		return productName;
	}

	// 获取产品数量
	int getProductQuantity() const {
		return productQuantity;
	}

	// 获取产品价格
	double getProductPrice() const {
		return productPrice;
	}
};

// 性别枚举
enum Gender {
	Male,
	Female
};

// 基类Person
class Person {
private:
	string name;
	Gender gender;
	string phoneNumber;
	string address;

public:
	// 构造函数
	Person(string n, Gender g, string phone, string addr)
		: name(n), gender(g), phoneNumber(phone), address(addr) {}

	// 获取姓名
	string getName() const {
		return name;
	}

	// 获取性别
	Gender getGender() const {
		return gender;
	}

	// 获取手机号码
	string getPhoneNumber() const {
		return phoneNumber;
	}

	// 获取地址
	string getAddress() const {
		return address;
	}
};

// 子类Customer
class Customer : public Person {
private:
	int customerId;
	double capital;
	vector<Product> products;

public:
	// 构造函数
	Customer(string n, Gender g, string phone, string addr, int id)
		: Person(n, g, phone, addr), customerId(id), capital(5000) {}

	// 获取客户ID
	int getCustomerId() const {
		return customerId;
	}

	// 获取资本
	double getCapital() const {
		return capital;
	}

	// 获取购买的产品列表
	vector<Product> getProducts() const {
		return products;
	}

	// 添加产品到购买列表
	void addProduct(const Product& product) {
		products.push_back(product);
	}
};

// 子类Manager
class Manager : public Person {
private:
	int age;
	string title;

public:
	// 构造函数
	Manager(string n, Gender g, string phone, string addr, int a, string t)
		: Person(n, g, phone, addr), age(a), title(t) {}

	// 获取年龄
	int getAge() const {
		return age;
	}

	// 获取职称
	string getTitle() const {
		return title;
	}
};

// 产品类和Person类的定义

class MainProcess {
private:
	vector<Product> products; // 所有产品的向量
	vector<Customer> customers; // 所有客户的向量
	Manager manager; // 管理经理
	Customer currentCustomer; // 当前购买产品的客户

public:
	// 构造函数
	MainProcess(const Manager& mgr) : manager(mgr) {}

	// 主菜单
	void showMainMenu() {
		cout << "********************" << endl;
		cout << "*1: manager*" << endl;
		cout << "*2: customer*" << endl;
		cout << "*3: quit the program*" << endl;
		cout << "********************" << endl;
		cout << "Please input a number to set your role: ";
	}

	// 经理菜单
	void showManagerMenu() {
		cout << "********************" << endl;
		cout << "*1: add products*" << endl;
		cout << "*2: query products*" << endl;
		cout << "*3: add customers*" << endl;
		cout << "*4: query customers*" << endl;
		cout << "*5: move to parent menu*" << endl;
		cout << "********************" << endl;
		cout << "Please input a number to run the program: ";
	}

	// 经理菜单操作：添加产品
	void addProduct() {
		int productId;
		string productName;
		int productQuantity;
		double productPrice;
		int choice;

		do {
			cout << "Product id: ";
			cin >> productId;

			// 检查产品ID是否已存在
			auto it = find_if(products.begin(), products.end(), [&](const Product& p) {
				return p.getProductId() == productId;
				});

			if (it != products.end()) {
				cout << "Product ID already exists. Please enter a different ID." << endl;
				continue;
			}

			cout << "Product name: ";
			cin >> productName;

			cout << "Product amount: ";
			cin >> productQuantity;

			cout << "Product price: ";
			cin >> productPrice;

			// 创建新产品并添加到产品向量中
			products.push_back(Product(productId, productName, productQuantity, productPrice));

			cout << "Add another product (0: no, 1: yes)? ";
			cin >> choice;
		} while (choice != 0);

		showManagerMenu();
	}

	// 经理菜单操作：查询产品
	void queryProducts() {
		string productId;

		cout << "Input a product Id (input \"*\" to list all products): ";
		cin >> productId;

		if (productId == "*") {
			cout << "Product ID\tName\t\tAmount\tPrice" << endl;
			for (const auto& product : products) {
				cout << product.getProductId() << "\t\t" << product.getProductName() << "\t\t"
					<< product.getProductQuantity() << "\t\t" << product.getProductPrice() << endl;
			}
		}
		else {
			auto it = find_if(products.begin(), products.end(), [&](const Product& p) {
				return to_string(p.getProductId()) == productId;
				});

			if (it != products.end()) {
				cout << "Product ID\tName\t\tAmount\tPrice" << endl;
				cout << it->getProductId() << "\t\t" << it->getProductName() << "\t\t"
					<< it->getProductQuantity() << "\t\t" << it->getProductPrice() << endl;
			}
			else {
				cout << "No product found!" << endl;
			}
		}

		showManagerMenu();
	}

	// 经理菜单操作：添加客户
	void addCustomer() {
		int customerId;
		string customerName;
		int customerGender;
		string customerPhoneNumber;
		string customerAddress;
		int choice;

		do {
			cout << "Customer id: ";
			cin >> customerId;

			// 检查客户ID是否已存在
			auto it = find_if(customers.begin(), customers.end(), [&](const Customer& c) {
				return c.getCustomerId() == customerId;
				});

			if (it != customers.end()) {
				cout << "Customer ID already exists. Please enter a different ID." << endl;
				continue;
			}

			cout << "Customer name: ";
			cin >> customerName;

			cout << "Customer gender (1: male, 2: female): ";
			cin >> customerGender;

			cout << "Mobile number: ";
			cin >> customerPhoneNumber;

			cout << "Address: ";
			cin.ignore();
			getline(cin, customerAddress);

			// 创建新客户并添加到客户向量中
			customers.push_back(Customer(customerId, customerName, static_cast<Gender>(customerGender),
				customerPhoneNumber, customerAddress));

			cout << "Add another customer (0: no, 1: yes)? ";
			cin >> choice;
		} while (choice != 0);

		showManagerMenu();
	}

	// 经理菜单操作：查询客户
	void queryCustomers() {
		string customerId;

		cout << "Input a customer Id (input \"*\" to list all customers): ";
		cin >> customerId;

		if (customerId == "*") {
			cout << "Customer ID\tName\t\tGender\tMobile number" << endl;
			for (const auto& customer : customers) {
				cout << customer.getCustomerId() << "\t\t" << customer.getCustomerName() << "\t\t"
					<< static_cast<int>(customer.getCustomerGender()) << "\t\t" << customer.getCustomerPhoneNumber() << endl;
			}
		}
		else {
			auto it = find_if(customers.begin(), customers.end(), [&](const Customer& c) {
				return to_string(c.getCustomerId()) == customerId;
				});

			if (it != customers.end()) {
				cout << "Customer ID\tName\t\tGender\tMobile number" << endl;
				cout << it->getCustomerId() << "\t\t" << it->getCustomerName() << "\t\t"
					<< static_cast<int>(it->getCustomerGender()) << "\t\t" << it->getCustomerPhoneNumber() << endl;
			}
			else {
				cout << "No customer found!" << endl;
			}
		}

		showManagerMenu();
	}

	// 运行主进程
	void run() {
		int roleChoice;
		int managerChoice;

		do {
			showMainMenu();
			cin >> roleChoice;

			switch (roleChoice) {
			case 1: { // 经理操作
				showManagerMenu();
				cin >> managerChoice;

				switch (managerChoice) {
				case 1:
					addProduct();
					break;
				case 2:
					queryProducts();
					break;
				case 3:
					addCustomer();
					break;
				case 4:
					queryCustomers();
					break;
				case 5:
					break;
				default:
					cout << "Invalid option. Please try again." << endl;
					break;
				}
			} while (managerChoice != 5);  // 根据实际情况进行调整
			break;


			int main() {
				vector<Customer> customers;
				vector<Product> products;

				// 添加一些示例数据
				customers.push_back(Customer(1111, "Mike", Gender::Male, "1234567890", "123 Main St"));
				customers.push_back(Customer(2222, "Alice", Gender::Female, "0987654321", "456 Park Ave"));

				products.push_back(Product(1000, "Milk", 20, 25.70));
				products.push_back(Product(2000, "Pork", 10, 17.59));

				int role;
				int customerId;
				while (true) {
					cout << "********************" << endl;
					cout << "*1: manager*" << endl;
					cout << "*2: customer*" << endl;
					cout << "*3: quit the program *" << endl;
					cout << "********************" << endl;
					cout << "Please input a number to set your role: ";
					cin >> role;

					if (role == 1) {
						int managerChoice;

						do {
							showManagerMenu();
							cin >> managerChoice;

							switch (managerChoice) {
							case 1:
								addProduct();
								break;
							case 2:
								queryProducts();
								break;
							case 3:
								addCustomer();
								break;
							case 4:
								queryCustomers();
								break;
							case 5:
								break;  // 如果需要添加更多选项，请根据实际情况进行调整
							default:
								cout << "Invalid option. Please try again." << endl;
								break;
							}
						} while (managerChoice != 5);  // 根据实际情况进行调整
					}
					else if (role == 2) {
						// 客户操作
						cout << "please input your customer Id: ";
						cin >> customerId;

						// 检查客户Id是否存在
						bool customerExists = false;
						Customer currentCustomer;

						for (const auto& customer : customers) {
							if (customer.getCustomerId() == customerId) {
								customerExists = true;
								currentCustomer = customer;
								break;
							}
						}

						if (customerExists) {
							int option;

							while (true) {
								cout << "********************" << endl;
								cout << "*1: add products into cart*" << endl;
								cout << "*2: query products In cart*" << endl;
								cout << "*3: check up *" << endl;
								cout << "*4: move to parent menu *" << endl;
								cout << "********************" << endl;
								cout << "Please input a number to run the program: ";
								cin >> option;

								if (option == 1) {
									// 添加产品到购物车
									int productId, quantity;

									cout << "Please input product Id: ";
									cin >> productId;
									cout << "Input the amount of the product you want to buy: ";
									cin >> quantity;

									// 检查产品是否存在和数量是否足够
									bool productExists = false;
									Product currentProduct;

									for (const auto& product : products) {
										if (product.getProductId() == productId) {
											productExists = true;
											currentProduct = product;
											break;
										}
									}

									if (productExists) {
										if (currentCustomer.getCapital() >= quantity * currentProduct.getProductPrice() &&
											quantity <= currentProduct.getProductQuantity()) {
											currentCustomer.addProduct(productId);
											currentProduct.decreaseQuantity(quantity);
											currentCustomer.setCapital(currentCustomer.getCapital() - quantity * currentProduct.getProductPrice());

											cout << "add product into cart successfully!" << endl;
										}
										else {
											cout << "Insufficient funds or quantity not available." << endl;
										}
									}
									else {
										cout << "Product not found." << endl;
									}
								}
								else if (option == 2) {
									// 查询购物车中的产品
									string productId;

									cout << "Input a product Id for query (input \"*\" to list all products in your cart): ";
									cin >> productId;

									cout << "Product ID\tName\t\tAmount\tPrice" << endl;

									if (productId == "*") {
										// 列出购物车中的所有产品
										for (const auto& product : currentCustomer.getCart()) {
											const Product& currentProduct = getProductById(products, product.first);

											cout << currentProduct.getProductId() << "\t\t"
												<< currentProduct.getProductName() << "\t\t"
												<< product.second << "\t\t"
												<< currentProduct.getProductPrice() << endl;
										}
									}
									else {
										// 查询指定产品
										const Product& currentProduct = getProductById(products, stoi(productId));

										if (currentProduct.getProductId() != -1) {
											cout << currentProduct.getProductId() << "\t\t"
												<< currentProduct.getProductName() << "\t\t"
												<< currentCustomer.getProductQuantity(productId) << "\t\t"
												<< currentProduct.getProductPrice() << endl;
										}
										else {
											cout << "Product not found." << endl;
										}
									}
								}
								else if (option == 3) {
									// 结账
									cout << "Product ID\tName\t\tAmount\tPrice" << endl;

									for (const auto& product : currentCustomer.getCart()) {
										const Product& currentProduct = getProductById(products, product.first);

										cout << currentProduct.getProductId() << "\t\t"
											<< currentProduct.getProductName() << "\t\t"
											<< product.second << "\t\t"
											<< currentProduct.getProductPrice() << endl;
									}

									cout << "Total price: " << currentCustomer.calculateTotalPrice(products) << endl;
									cout << "Customer information:" << endl;
									currentCustomer.displayInfo();

									int confirm;
									cout << "Please confirm to check up (0:no, 1:yes)? ";
									cin >> confirm;

									if (confirm == 1) {
										currentCustomer.checkout(products);
										cout << "Checked up successfully!" << endl;
									}
								}
								else if (option == 4) {
									// 返回主菜单
									break;
								}
								else {
									cout << "Invalid option. Please try again." << endl;
								}
							}
						}
						else {
							cout << "Customer not found." << endl;
						}
					}
					else if (role == 3) {
						// 退出程序
						break;
					}
					else {
						cout << "Invalid role. Please try again." << endl;
					}
				}

				return 0;
			}
			}
		}
	}
};
