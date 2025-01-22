#include <iostream>
#include <vector>

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

    void checkClockStatus()
    {
        if (clockIn)
        {
            std::cout << getName() << " is clocked in\n";
        }
        else
        {
            std::cout << getName() << " is clocked out\n";
        }
    }

    void changeClockStatus()
    {
        clockIn = !clockIn;

        if (clockIn)
        {
            std::cout << getName() << " has clocked in\n";
        }
        else
        {
            std::cout << getName() << " has clocked out\n";
        }
    }
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

    void listAllCastMembers(std::vector<CastMember> &castmembers)
    {
        std::cout << "List all Cast Members:\n";
        for (CastMember &member : castmembers)
        {
            std::cout << "Name: " << member.getName()
                      << " ID: " << member.getEmployeeId()
                      << std::endl;
        }
    }

    void createCastMember(std::vector<CastMember> &castmembers)
    {
        std::cout << "Enter Cast Member name: ";
        std::string castName;
        std::getline(std::cin >> std::ws, castName);

        int castNum = castmembers.size() + 1;

        castmembers.push_back(CastMember(castName, castNum));

        std::cout << getName() << " has successfully added " << castName << "with ID: " << castNum << "!\n";
    }
};

std::vector<Manager> managers =
    {
        Manager("jj", 100)};

int validateInput()
{
    int input;
    std::cin >> input;
    while (true)
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Please enter valid input\n";
        }
        else
        {
            return input;
        }
    }
}

int main()
{
employeeLogIn:
    std::cout << "Enter employee ID:";
    int employeeNum = validateInput();
    // std::cin >> employeeNum;

    while (true)
    {

        bool found = false;

        for (CastMember &member : castmembers)
        {
            if (employeeNum == member.getEmployeeId())
            {
                found = true;
                std::cout << "Welcome " << member.getName() << "!\n";
                std::cout << "1. Check clock status\n";
                std::cout << "2. Change clock status\n";
                std::cout << "3.EXIT\n";
                std::cout << "Please select an option: ";

                int castMenu = validateInput();
                // std::cin >> castMenu;

                switch (castMenu)
                {
                case 1:
                    member.checkClockStatus();
                    break;
                case 2:
                    member.changeClockStatus();
                    break;

                case 3:
                    goto employeeLogIn;
                    break;
                default:
                    std::cout << "Invalid input\n";
                    break;
                }
            }
            for (Manager &mg : managers)
            {
                if (employeeNum == mg.getEmployeeId())
                {
                    found = true;
                    std::cout << "welcome " << mg.getName() << "!\n";
                    std::cout << "1. Check clock status\n";
                    std::cout << "2. Change clock staus\n";
                    std::cout << "3. List all castmembers\n";
                    std::cout << "4. Create cast member\n";
                    std::cout << "5. EXIT\n";
                    std::cout << "Please select an option: ";

                    int managerMenu = validateInput();
                    // std::cin >> managerMenu;

                    switch (managerMenu)
                    {
                    case 1:
                        mg.checkClockStatus();
                        break;
                    case 2:
                        mg.changeClockStatus();
                        break;

                    case 3:
                        mg.listAllCastMembers(castmembers);
                        break;
                    case 4:
                        mg.createCastMember(castmembers);
                        break;
                    case 5:
                        goto employeeLogIn;
                        break;
                    default:
                        std::cout << "Invalid input\n";
                    }
                }
            }
            if (!found)
            {
                std::cout << "Invalid input.Please try again\n";
                goto employeeLogIn;
            }
        }
    }
}