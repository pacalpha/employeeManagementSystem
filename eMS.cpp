// First Commit

#include <iostream>
#include <vector>
#include <string>

class Person
{
private:
    std::string name;

public:
    Person(std::string n) : name(n) {}
    std::string getName() const { return name; }
};

class Employee : public Person
{
private:
    int employeeId;
    bool clockIn;

public:
    Employee(std::string n, int id) : Person(n), employeeId(id), clockIn(false) {}
    int getEmployeeId() const { return employeeId; }
};

class CastMember : public Employee
{
private:
public:
    CastMember(std::string n, int id) : Employee(n, id) {}
};

std::vector<CastMember> castmembers =
    {
        CastMember("j", 1),
        CastMember("jay", 2)};

class Manager : public Employee
{
private:
public:
    Manager(std::string n, int id) : Employee(n, id) {}
};

std::vector<Manager> managers =
    {
        Manager("jj", 100)};

int main()
{
    std::cout << "Enter employee ID:";
    int employeeNum;
    std::cin >> employeeNum;

    for (CastMember &member : castmembers)
    {
        if (employeeNum == member.getEmployeeId())
        {
            std::cout << "Welcome " << member.getName() << "!\n";
            std::cout << "1. Check clock status\n";
            std::cout << "2. Change clock status\n";
            std::cout << "3. Weekly hours\n";
            std::cout << "4.EXIT\n";
            std::cout << "Please select an option\n";

            int castMenu;
            std::cin >> castMenu;

            switch (castMenu)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
            }
        }
        for (Manager &mg : managers)
        {
            if (employeeNum == mg.getEmployeeId())
            {
                std::cout << "1. Check clock status\n";
                std::cout << "2. Change clock staus\n";
                std::cout << "3. Your weekly hours\n";
                std::cout << "4. List all castmembers\n";
                std::cout << "5. Create cast member\n";
                std::cout << "6. EXIT\n";
                std::cout << "Please select an option\n";

                int managerMenu;
                std::cin >> managerMenu;

                switch (managerMenu)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                }
            }
        }
    }
}