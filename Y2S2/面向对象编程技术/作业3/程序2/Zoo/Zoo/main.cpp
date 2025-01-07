#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ���� Animal
class Animal {
public:
    string species;
    int age;
    float weight;

public:
    Animal(string s, int a, float w) : species(s), age(a), weight(w) {}

    virtual ~Animal() {}

    virtual void eat() = 0; // ���麯������������Ҫʵ��
    void grow() {
        age++;
        weight += 10; // ����ÿ������10kg����
    }

    void displayInfo() const {
        cout << "Species: " << species << ", Age: " << age << ", Weight: " << weight << endl;
    }

    string getName() { return species; }
};

// ������ Lion
class Lion : public Animal {
public:
    Lion(int a, float w) : Animal("Lion", a, w) {}

    void eat() override {
        cout << "Lion eats 20kg of meat." << endl;
        // ����ʨ��ÿ�γ�20kgʳ��
    }
};

// ������ Elephant
class Elephant : public Animal {
public:
    Elephant(int a, float w) : Animal("Elephant", a, w) {}

    void eat() override {
        cout << "Elephant eats 100kg of vegetation." << endl;
        // �������ÿ�γ�100kgʳ��
    }
};

// ������ Penguin
class Penguin : public Animal {
public:
    Penguin(int a, float w) : Animal("Penguin", a, w) {}

    void eat() override {
        cout << "Penguin eats 5kg of fish." << endl;
        // �������ÿ�γ�5kgʳ��
    }
};

// �� Zoo
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
    // ��������ʵ��
    Lion lion(5, 150);
    Elephant elephant(10, 5000);
    Penguin penguin(3, 20);

    // ��������԰ʵ��
    Zoo zoo;

    // ��Ӷ��ﵽ����԰
    zoo.addAnimal(&lion);
    zoo.addAnimal(&elephant);
    zoo.addAnimal(&penguin);

    // ��ʾ���ж���
    zoo.displayAllAnimals();

    // ιʳ���ж���
    zoo.feedAnimals();

    // ����ɳ�һ��
    zoo.ageOneYear();

    // �ٴ���ʾ���ж���
    zoo.displayAllAnimals();

    return 0;
}