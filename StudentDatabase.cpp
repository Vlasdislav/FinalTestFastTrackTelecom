#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

// Расположение полей специально устроено так,
// чтобы из-за выравнивания
// меньше памяти на структуру тратить
struct Student {
    int id;
    int age;
    std::string name;
};

class StudentDatabase {
private:
    // `std::unordered_map` тоже выбран не случайно, из-за
    // Вставка:  \O(1)
    // Удаление: \O(1)
    // Поиск:    \O(1)
    std::unordered_map<int, std::shared_ptr<Student>> database;

public:
    void addStudent(const int& id, const std::string& name, const int& age) {
        std::shared_ptr<Student> student = std::make_shared<Student>();
        student->id = id;
        student->name = name;
        student->age = age;
        database[id] = student;
    }

    void removeStudent(const int& id) {
        auto it = database.find(id);
        if (it != database.end()) {
            database.erase(it);
            std::cout << "Студент с идентификатором " << id << " был удален из базы данных." << std::endl;
        } else {
            std::cout << "Студент с идентификатором " << id << " не существует в базе данных." << std::endl;
        }
    }

    void getStudentInfo(const int& id) {
        auto it = database.find(id);
        if (it != database.end()) {
            std::shared_ptr<Student> student = it->second;
            std::cout << "Студенческий билет: " << student->id << ", Имя: " << student->name << ", Возраст: " << student->age << std::endl;
        } else {
            std::cout << "Студент с идентификатором " << id << " не существует в базе данных." << std::endl;
        }
    }
};

int main() {
    StudentDatabase db;
    
    db.addStudent(1, "Alice", 20);
    db.addStudent(2, "Bob", 21);
    db.addStudent(3, "Charlie", 22);
    
    db.getStudentInfo(1);
    db.getStudentInfo(4);
    
    db.removeStudent(2);
    db.removeStudent(4);
}
