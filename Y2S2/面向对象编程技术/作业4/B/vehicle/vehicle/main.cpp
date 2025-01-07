#include<iostream>
#include<string>
using namespace std;

class Vehicle {
private:
	string brand;
	int year;

public:
	Vehicle(const string& brand, int year):brand(brand), year(year){}
	virtual void display() { cout << "brand: " << brand << endl << "year: " << year << endl; }
	virtual ~Vehicle(){}
};

class Car: public Vehicle{
private:
	int doors;

public:
	Car(const string& brand, int year, int doors):Vehicle(brand, year), doors(doors) {}
	void display() override { 
		Vehicle::display();
		cout << "doors: " << doors << endl;
	}
};

class Bicycle : public Vehicle {
private:
	bool hasGear;

public:
	Bicycle(const string& brand, int year, bool hasGear) :Vehicle(brand, year), hasGear(hasGear) {}
	void display() override {
		Vehicle::display();
		cout << "hasGear: " << (hasGear ? "Yes" : "No") << endl;
	}
};

class Boat : public Vehicle{
private:
	float length;

public:
	Boat(const string& brand, int year, float length):Vehicle(brand, year), length(length) {}
	void display() override {
		Vehicle::display();
		cout << "Length: " << length << "meters" << endl;
	}
};

int main() {
	Car car("Toyota", 2020, 4);
	Bicycle bicycle("Trek", 2019, true);
	Boat boat("Yamaha", 2017, 6.5);

	car.display();
	bicycle.display();
	boat.display();

	return 0;
}