// ============================================================
// Lab No. 05 - Static Code Analysis (SonarQube)
// File: lab05_refactored_code.cpp
// Description: Refactored code for BOTH Task 1 and Task 2
//              Fixes all 4 SonarQube issues from legacy code
// ============================================================

#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

namespace AddressBook {

// ============================================================
// TASK 1 - Example 1 (Refactored)
// ============================================================

class Address {
private:
    static std::unique_ptr<Address> singleton;

    Address() = default;
    Address(const Address&) = delete;
    Address& operator=(const Address&) = delete;

public:
    static Address& GetSingleton() {
        if (!singleton) {
            singleton = std::make_unique<Address>();
        }
        return *singleton;
    }

    static void ClearSingleton() {
        singleton.reset();
    }

    [[nodiscard]] std::string GetCity() const {
        throw std::runtime_error("GetCity not implemented");
    }
};

std::unique_ptr<Address> Address::singleton = nullptr;

class Person {
public:
    static std::string GetCityFromAddressFactory() {
        Address& pAddress = Address::GetSingleton();
        std::string city = pAddress.GetCity();
        Address::ClearSingleton();
        return city;
    }

    bool IsValidName(const std::string& filename) const {
        if (filename.empty()) {
            throw std::invalid_argument("IsValidName: filename is empty");
        }
        return true;
    }

    void SaveAll(const std::string& filename) const {
        if (!IsValidName(filename)) {
            throw std::invalid_argument("SaveAll: invalid filename");
        }
        std::cout << "Saving to " << filename << std::endl;
    }
};

// ============================================================
// TASK 2 - Example 2 (Refactored)
// ============================================================

class Address2 {
private:
    static std::unique_ptr<Address2> singleton;

    Address2() = default;
    Address2(const Address2&) = delete;
    Address2& operator=(const Address2&) = delete;

public:
    static Address2& GetSingleton() {
        if (!singleton) {
            singleton = std::make_unique<Address2>();
        }
        return *singleton;
    }

    static void ClearSingleton() {
        singleton.reset();
    }

    [[nodiscard]] std::string GetCity() const {
        return "SampleCity";
    }
};

std::unique_ptr<Address2> Address2::singleton = nullptr;

class Person2 {
public:
    static std::string GetCityFromAddressFactory() {
        Address2& pAddress = Address2::GetSingleton();
        std::string city = pAddress.GetCity();
        Address2::ClearSingleton();
        return city;
    }

    void Save(const std::string& filename) {
        if (!IsValidName(filename)) {
            throw std::invalid_argument("Save: Invalid filename");
        }
        SaveAll(filename);
    }

private:
    [[nodiscard]] bool IsValidName(const std::string& filename) const {
        return !filename.empty();
    }

    void SaveAll(const std::string& filename) const {
        std::cout << "Saving to " << filename << std::endl;
    }
};

} // namespace AddressBook


// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    using namespace AddressBook;

    // ---- Task 1 test ----
    Person p1;
    try {
        std::string city = Person::GetCityFromAddressFactory();
        std::cout << "Task 1 City: " << city << std::endl;
        p1.SaveAll("example1.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Task 1 Error: " << e.what() << std::endl;
    }

    // ---- Task 2 test ----
    Person2 p2;
    try {
        std::string city = Person2::GetCityFromAddressFactory();
        std::cout << "Task 2 City: " << city << std::endl;
        p2.Save("example2.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Task 2 Error: " << e.what() << std::endl;
    }

    return 0;
}