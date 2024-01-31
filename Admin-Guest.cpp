#include<iostream>
using namespace std;
#include<cassert>

class Guest {
	string fullname;
	string connected_date; //tarix saat
public:
	Guest(string fullname, string date)
	{
		this->setFullname(fullname);
		this->setDate(date);
	}

	// Copy Constructor
	Guest(const Guest& guest)
	{
		this->setFullname(guest.getFullname());
		this->setDate(guest.getDate());
	}


	void setFullname(string fullname) {
		if (fullname.length() > 0 && fullname.length() < 100) {
			this->fullname = fullname;
		}
	}

	void setDate(string date) {
		if (connected_date.length() > 0 && connected_date.length() < 100) {
			this->connected_date = date;
		}
	}

	string getFullname() const {
		if (fullname.length() > 0 && fullname.length() < 100) {
			return this->fullname;
		}
	}

	string getDate() const {
		if (connected_date.length() > 0 && connected_date.length() < 100) {
			return this->connected_date;
		}
	}
};

class Admin {
	string username;
	string password;
public:

	Admin(string username, string password) {
		this->SetUsername(username);
		this->SetPassword(password);
	}

	// Copy Constructor
	Admin(const Admin& admin) {
		this->SetUsername(admin.GetUsername());
		this->SetPassword(admin.GetPassword());
	}

	void SetUsername(string username) {
		if (username.length() > 1 && username.length() < 100) {
			this->username = username;
		} 
	}

	void SetPassword(string password) {
		if (username.length() > 1 && username.length() < 100) {
			this->password = password;
		}
	}

	string GetUsername() const {
		return this->username;
	}

	string GetPassword()const {
		return this->password;
	}

};

class Product {
	static int _id;
	int id; //avtomatik
	string name;
	string description;
	double price;
	double discount;
	int quantity;
	double tax; //vergi faizi
public:

	Product()
	{
		id = ++_id;
	}

	Product(string name, double price, int quantity = 1)
		:Product()
	{
		this->setName(name);
		this->setPrice(price);
		this->setQuantity(quantity);
	}


	Product(string name, string description, double price, double discount, double tax, int quantity = 1)
		:Product(name, price, quantity)
	{
		this->setDescription(description);
		this->setDiscount(discount);
		this->setTax(tax);
	}

	// Copy constructor
	Product(const Product& product)
		:Product(product.getName(), product.getDescription(), product.getPrice(), product.getDiscount(), product.getTax(), product.getQuantity())
	{
		this->id = product.id;
	}

	/* Set and Get Methods */
	void setName(string name) {
		if (name.length() > 1 && name.length() < 100) {
			this->name = name;
		}
	}

	void setDescription(string description) {
		if (name.length() > 1 && name.length() < 100) {
			this->description = description;
		}
	}

	void setPrice(double price) {
		this->price = price;
	}

	void setDiscount(double discount) {
		if (0 < discount && discount > 100) {
			this->discount = discount;
		}
	}

	void setTax(double tax) {
		if (0 < tax && tax > 100) {
			this->tax = tax;
		}
	}

	void setQuantity(int quantity) {
		if (0 < quantity && quantity < 100) {
			this->quantity = quantity;
		}
	}

	string getName()const {
		return this->name;
	}

	string getDescription()const {
		return this->description;
	}

	double getPrice()const {
		return this->price;
	}

	double getDiscount()const {
		return this->discount;
	}

	double getTax()const {
		return this->tax;
	}

	int getId()const {
		return this->id;
	}

	int getQuantity()const {
		return this->quantity;
	}
};

int Product::_id = 0;


template<typename T>
class DbSet {
	T** items = nullptr;
	int count = 0;
public:
	void add(const T* item)
	{
		if (items == nullptr)
		{
			items = new T * [++count];
			items[0] = new T(*item);
		}
		else
		{
			T** nItems = new T * [count + 1];
			for (size_t i = 0; i < count; i++)
				nItems[i] = items[i];


			nItems[count] = new T(*item);
			delete[] items;
			items = nItems;
			count++;
		}
	}

	bool checkId(const int& id)
	{
		for (size_t i = 0; i < count; i++)
			if (items[i]->getId() == id)
				return true;
		return false;

	}

	void deleteByid(const int& id)
	{
		if (checkId(id))
		{
			T** nItems = new T * [count - 1];
			int index = 0;

			for (size_t i = 0; i < count; i++)
			{
				if (items[i]->getId() != id)
					nItems[index++] = items[i];
				else
					delete items[i];
			}
			delete[] items;
			items = nItems;
			count--;
		}
	}

	T* getItem(const int& id)
	{
		if (checkId(id))
			for (size_t i = 0; i < count; i++)
				if (items[i]->getId() == id)
					return items[i];
		return nullptr;
	}

	int getCount() const
	{
		return count;
	}

	T** getItems() const
	{
		return items;
	}

	~DbSet()
	{
		if (items != nullptr)
		{
			for (size_t i = 0; i < count; i++)
				if (items[i] != nullptr)
					delete items[i];
			delete[] items;
		}
	}
};


class Database {
public:
	DbSet<Product>products;
	DbSet<Admin>admins;
	DbSet<Guest>guest;


	bool checkAdmin(string username)
	{
		for (size_t i = 0; i < admins.getCount(); i++)

			if (admins.getItems()[i]->GetUsername() == username)
				return true;
		return false;
	}

	bool adminLogin(string username, string password)
	{
		for (size_t i = 0; i < admins.getCount(); i++)
			if (admins.getItems()[i]->GetUsername() == username && admins.getItems()[i]->GetPassword() == password)
				return true;
		return false;
	}
};


void start() {

	Database db;

	Admin* admin = new Admin("admin", "admin");
	db.admins.add(admin);


	Guest guest("guest", "2021-05-05 12:00:00");


	Product product("Samsung S21", "Samsung S21", 15.36, 1, 1, 10);

	string menuOne = R"(
				[1] => As Gusest
				[2] => As Admin
				[0] => Exit
		)";

	string menuAdmin = R"(
				[1] => Add Product
				[2] => Delete Product
				[3] => Show All Products
				[4] => Show All Guests
				[5] => Update Product
				[6] => Delete All Products
				[7] => Delete All Guests
				[8] => Show Total price by Id
				[0] => Exit
		)";


	while (true)
	{
		cout << menuOne << endl;
		cout << "Menudan secim edin: ";

		int select;
		cin >> select;

		if (select == 1)
		{
			cout << "Welcome Guest!" << endl;
		}
		else if (select == 2)
		{
			string username, password;
			cout << "username: ";
			cin >> username;
			cout << "password: ";
			cin >> password;

			if (db.checkAdmin(username)) {
				if (db.adminLogin(username, password)) {
					cout << "Welcome Admin!" << endl;

					while (true) {
						cout << menuAdmin << endl;
						cout << "Select an option: ";

						int adminSelect;
						cin >> adminSelect;

						switch (adminSelect) {
						case 1:
						{
							string name, description;
							double price, discount, tax;
							int quantity;

							cout << "Enter product name: ";
							cin >> name;

							cout << "Enter product description: ";
							cin >> description;

							cout << "Enter product price: ";
							cin >> price;

							cout << "Enter product discount: ";
							cin >> discount;

							cout << "Enter product tax: ";
							cin >> tax;

							cout << "Enter product quantity: ";
							cin >> quantity;

							Product newProduct(name, description, price, discount, tax, quantity);
							db.products.add(&newProduct);

							cout << "Product added successfully." << endl;
						}
						break;
						case 2:
						{
							int productId;
							cout << "Enter the product ID to delete: ";
							cin >> productId;

							db.products.deleteByid(productId);
							cout << "Product deleted successfully." << endl;
						}
						break;
						case 3:
						{
							for (int i = 0; i < db.products.getCount(); ++i) {
								Product* product = db.products.getItems()[i];
								cout << "Product ID: " << product->getId() << ", Name: " << product->getName() << ", Price: $" << product->getPrice() << ", Quantity: " << product->getQuantity() << endl;
							}
						}
						break;
						case 4:
						{
							for (int i = 0; i < db.guest.getCount(); ++i) {
								Guest* guest = db.guest.getItems()[i];
								cout << "Guest Fullname: " << guest->getFullname() << ", Connected Date: " << guest->getDate() << endl;
							}
						}
						break;
						case 5:
						{
							int productIdToUpdate;
							cout << "Enter the product ID to update: ";
							cin >> productIdToUpdate;

							Product* productToUpdate = db.products.getItem(productIdToUpdate);

							if (productToUpdate != nullptr) {
								cout << "Enter the updated product name: ";
								string updatedName;
								cin >> updatedName;
								productToUpdate->setName(updatedName);
								cout << "Product updated successfully." << endl;

							}
							else {
								cout << "Product not found." << endl;
							}
						}
						break;
						case 6:
						{
							db.products.~DbSet();
							cout << "All products deleted successfully." << endl;
						}
						break;
						case 7:
						{
							db.guest.~DbSet();
							cout << "All guests deleted successfully." << endl;
						}
						break;
						case 8:
						{
							int productIdToShowTotal;
							cout << "Enter the product ID to show total price: ";
							cin >> productIdToShowTotal;

							Product* productToShowTotal = db.products.getItem(productIdToShowTotal);

							if (productToShowTotal != nullptr) {
								double totalPrice = productToShowTotal->getPrice() * productToShowTotal->getQuantity();
								cout << "Total price for product ID " << productIdToShowTotal << ": $" << totalPrice << endl;
							}
							else {
								cout << "Product not found." << endl;
							}
						}
						break;
						case 0:
							break;
						default:
							cout << "Invalid selection from the Admin menu." << endl;
							break;
						}

						if (adminSelect == 0) {
							break; 
						}
					}
				}
				else {
					cout << "Password is incorrect. Login process is not accessible." << endl;
				}
			}
			else {
				cout << "Admin not found." << endl;
			}
		}
		else if (select == 0) {
			break; 
		}
		else {
			cout << "Invalid selection from the first menu." << endl;
		}
	}
}
void main(){
	start();
}