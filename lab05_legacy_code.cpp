// ============================================================
// Lab No. 05 - Static Code Analysis (SonarQube)
// File: lab05_legacy_code.cpp
// Description: Raw / Legacy code for Task 1 and Task 2
//              (as given in the Lab Manual)
// ============================================================

#include <string>
#include <iostream>

using namespace std;

// ============================================================
// TASK 1 - Example 1 (Legacy Code)
// ============================================================

class Address {
public:
    static Address* singleton;

    static Address* GetSingleton();
    static void ClearSingleton();
    char* GetCity();
};

class Person {
public:
    char* GetCityFromAddressFactory();
    bool IsValidName(string filename);
    void SaveAll(string filename);
};

// ---------- Person Class Implementation ----------

char* Person::GetCityFromAddressFactory()
{
    Address* pAddress = Address::GetSingleton();
    char* city = pAddress->GetCity();
    Address::ClearSingleton();
    return city;
}

bool Person::IsValidName(string filename)
{
    throw;
}

void Person::SaveAll(string filename)
{
    throw;
}

// ---------- Address Class Implementation ----------

Address* Address::singleton = NULL;

Address* Address::GetSingleton()
{
    if (singleton == NULL)
        singleton = new Address();
    return singleton;
}

void Address::ClearSingleton()
{
    // CountReference();   // <-- undefined function call
    if (singleton != NULL)
    {
        delete singleton;
        singleton = NULL;
    }
}

char* Address::GetCity()
{
    throw;
}


// ============================================================
// TASK 2 - Example 2 (Legacy Code)
// ============================================================

class Address2 {
private:
    static Address2* singleton;
    static void CountReference() { }

public:
    static Address2* GetSingleton();
    static void ClearSingleton();
    string GetCity();
};

class Person2 {
public:
    static string GetCityFromAddressFactory();
    void Save(const string& filename);

private:
    bool IsValidName(const string& filename);
    void SaveAll(const string& filename);
};

// ---------- Address2 Class Implementation ----------

Address2* Address2::singleton = NULL;

Address2* Address2::GetSingleton()
{
    if (singleton == NULL)
        singleton = new Address2();
    return singleton;
}

void Address2::ClearSingleton()
{
    if (singleton != NULL)
    {
        delete singleton;
        singleton = NULL;
    }
}

string Address2::GetCity()
{
    throw;
}

// ---------- Person2 Class Implementation ----------

string Person2::GetCityFromAddressFactory()
{
    Address2* pAddress = Address2::GetSingleton();
    string city = "SampleCity";     // useless assignment
    pAddress->GetCity();
    Address2::ClearSingleton();
    return city;
}

bool Person2::IsValidName(const string& filename)
{
    return !filename.empty();
}

void Person2::SaveAll(const string& filename)
{
    cout << "Saving to " << filename << endl;
}

void Person2::Save(const string& filename)
{
    if (!IsValidName(filename))
    {
        throw invalid_argument("Invalid filename");
    }
    SaveAll(filename);
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    // ---- Task 1 test ----
    Person p1;
    try {
        char* city = p1.GetCityFromAddressFactory();
        cout << "City: " << city << endl;
    }
    catch (...) {
        cout << "Task 1: Exception caught" << endl;
    }

    // ---- Task 2 test ----
    Person2 p2;
    try {
        string city = Person2::GetCityFromAddressFactory();
        cout << "City: " << city << endl;
        p2.Save("example.txt");
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}