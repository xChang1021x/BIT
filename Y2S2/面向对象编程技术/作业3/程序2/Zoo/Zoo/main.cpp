#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// 基类 Animal
class Animal {
public:
    string species;
    int age;
    float weight;

public:
    Animal(string s, int a, float w) : species(s), age(a), weight(w) {}

    virtual ~Animal() {}

    virtual void eat() = 0; // 纯虚函数，派生类需要实现
    void grow() {
        age++;
        weight += 10; // 假设每年增加10kg体重
    }

    void displayInfo() const {
        cout << "Species: " << species << ", Age: " << age << ", Weight: " << weight << endl;
    }

    string getName() { return species; }
};

// 派生类 Lion
class Lion : public Animal {
public:
    Lion(int a, float w) : Animal("Lion", a, w) {}

    void eat() override {
        cout << "Lion eats 20kg of meat." << endl;
        // 假设狮子每次吃20kg食物
    }
};

// 派生类 Elephant
class Elephant : public Animal {
public:
    Elephant(int a, float w) : Animal("Elephant", a, w) {}

    void eat() override {
        cout << "Elephant eats 100kg of vegetation." << endl;
        // 假设大象每次吃100kg食物
    }
};

// 派生类 Penguin
class Penguin : public Animal {
public:
    Penguin(int a, float w) : Animal("Penguin", a, w) {}

    void eat() override {
        cout << "Penguin eats 5kg of fish." << endl;
        // 假设企鹅每次吃5kg食物
    }
};

// 类 Zoo
class Zoo {
private:
    unordered_map<string, vector<Animal*>> animals;

public:
    void addAnimal(Animal* animal) {
        animals[animal->species].push_back(animal);
    }

    void displayAllAnimals() {
        for (const auto& pair : animals) {
            cout << "Species: " << pair.first << endl;
            for (Animal* animal : pair.second) {
                animal->displayInfo();
            }
        }
    }

    void feedAnimals() {
        for (const auto& pair : animals) {
            cout << "Feeding " << pair.first << "s:" << endl;
            for (Animal* animal : pair.second) {
                animal->eat();
            }
        }
    }

    void ageOneYear() {
        for (auto& pair : animals) {
            for (Animal* animal : pair.second) {
                animal->grow();
            }
        }
    }

    Animal* findAnimal(const string& species, const string& name) {
        for (const auto& pair : animals) {
            for (Animal* animal : pair.second) {
                if (animal->species == species && animal->getName() == name) {
                    return animal;
                }
            }
        }
        return nullptr;
    }
};

int main() {
    // 创建动物实例
    Lion lion(5, 150);
    Elephant elephant(10, 5000);
    Penguin penguin(3, 20);

    // 创建动物园实例
    Zoo zoo;

    // 添加动物到动物园
    zoo.addAnimal(&lion);
    zoo.addAnimal(&elephant);
    zoo.addAnimal(&penguin);

    // 显示所有动物
    zoo.displayAllAnimals();

    // 喂食所有动物
    zoo.feedAnimals();

    // 动物成长一年
    zoo.ageOneYear();

    // 再次显示所有动物
    zoo.displayAllAnimals();

    return 0;
}