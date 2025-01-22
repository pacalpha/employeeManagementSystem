#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm> //std::remove_if
#include <set>

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
    std::vector<std::pair<time_t, std::string>> clockInHistory;
    std::vector<std::pair<time_t, std::string>> clockOutHistory;

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

        time_t now = std::time(nullptr);
        char buff[100];
        std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        std::string timeStamp(buff);
        if (clockIn)
        {
            std::cout << getName() << " has clocked in at " + timeStamp + "\n";
            clockInHistory.push_back(std::pair(now, timeStamp));
        }
        else
        {
            std::cout << getName() << " has clocked out at " + timeStamp + "\n";
            clockOutHistory.push_back(std::pair{now, timeStamp});
        }
    }

    void displayClockHistory() const
    {
        std::cout << "Clock in History for " << getName() << ":\n";
        for (const auto &entry : clockInHistory)
        {
            const auto &timeStamp = std::get<0>(entry);
            const auto &timeValue = std::get<1>(entry);
            std::cout << timeStamp + "\n";
        }
        std::cout << "Clock out History:\n";
        for (const auto &entry : clockOutHistory)
        {
            const auto &timeStamp = std::get<0>(entry);
            const auto &timeValue = std::get<1>(entry);
            std::cout << timeStamp + "\n";
        }

        if (clockInHistory.empty() || clockOutHistory.empty())
        {
            std::cout << "No clock history avaliable\n";
        }
    }
    void totalTimeWorked()
    {

        size_t timeDiff = std::min(clockInHistory.size(), clockOutHistory.size());
        int i;
        std::cout << " Total time worked by " << getName() << ":\n";
        for (i = 0; i < timeDiff; i++)
        {
            time_t timeIn = clockInHistory[i].first;
            time_t timeOut = clockOutHistory[i].first;
            time_t timeWorked = timeOut - timeIn;
            int hours = (timeWorked / 3600);
            int minutes = ((timeWorked % 3600) / 60);
            int seconds = (timeWorked % 60);
            std::cout << hours << " hours " << minutes << " minutes " << seconds << " seconds\n";
        }
    }
};

std::vector<Employee> castMembers;
std::set<int> usedIds;
int nextId = 1;

class Manager : public Employee
{
private:
public:
    Manager(std::string n, int id) : Employee(n, id) {}

    void listAllCastMembers(std::vector<Employee> &castmembers)
    {
        std::cout << "List all Cast Members:\n";
        for (Employee &member : castmembers)
        {
            std::cout << "Name: " << member.getName()
                      << " ID: " << member.getEmployeeId()
                      << "\t";
            member.checkClockStatus();
        }
        if (castmembers.empty())
        {
            std::cout << "No Castmembers listed yet\n";
        }
    }

    void createCastMember(std::vector<Employee> &castmembers)
    {
        std::cout << "Enter Cast Member name: ";
        std::string castName;
        std::getline(std::cin >> std::ws, castName);

        while (usedIds.find(nextId) != usedIds.end())
        {
            nextId++; // increment until a free Id is found
        }

        castmembers.push_back(Employee(castName, nextId));
        usedIds.insert(nextId); // add new id to the set of IDs

        std::cout << getName() << " has successfully added " << castName << " with ID: " << nextId << "!\n";

        nextId++;
    }
    void deleteCastMember(std::vector<Employee> &castmembers, int id)
    {
        auto it = std::remove_if(castmembers.begin(), castmembers.end(), [id](const Employee &member)
                                 { return member.getEmployeeId() == id; });
        if (it != castmembers.end())
        {
            usedIds.erase(id);
            castmembers.erase(it, castmembers.end());
            std::cout << getName() << " ID: " << id << " has been successfully deleted.\n";
        }
        else
        {
            std::cout << " No castmember found with ID:" << id << ".\n";
        }
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
    std::vector<Employee> castMembers;
employeeLogIn:
    std::cout << "Enter employee ID:";
    int employeeNum = validateInput();

    while (true)
    {

        bool found = false;

        for (Employee &member : castMembers)
        {
            if (employeeNum == member.getEmployeeId())
            {
                found = true;
                std::cout << "Welcome " << member.getName() << "!\n";
                std::cout << "1. Check clock status\n";
                std::cout << "2. Change clock status\n";
                std::cout << "3. Total time worked\n";
                std::cout << "4. Clock history\n";
                std::cout << "5.EXIT\n";
                std::cout << "Please select an option: ";

                int castMenu = validateInput();

                switch (castMenu)
                {
                case 1:
                    system("clear");
                    member.checkClockStatus();
                    break;
                case 2:
                    system("clear");
                    member.changeClockStatus();
                    break;

                case 3:
                    system("clear");
                    member.totalTimeWorked();
                    break;
                case 4:
                    system("clear");
                    member.displayClockHistory();
                    break;
                case 5:
                    system("clear");
                    goto employeeLogIn;
                    break;
                default:
                    system("clear");
                    std::cout << "Invalid input\n";
                    break;
                }
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
                std::cout << "3. Clock History\n";
                std::cout << "4. List all castmembers\n";
                std::cout << "5. Create cast member\n";
                std::cout << "6. Delete Castmember\n";
                std::cout << "7. EXIT\n";
                std::cout << "Please select an option: ";

                int managerMenu = validateInput();

                switch (managerMenu)
                {
                case 1:
                    system("clear");
                    mg.checkClockStatus();
                    break;
                case 2:
                    system("clear");
                    mg.changeClockStatus();
                    break;
                case 3:
                    system("clear");
                    mg.displayClockHistory();
                    break;
                case 4:
                    system("clear");
                    mg.listAllCastMembers(castMembers);
                    break;
                case 5:
                    system("clear");
                    mg.createCastMember(castMembers);
                    break;
                case 6:
                    system("clear");
                    std::cout << "Enter ID for cast member to delete: ";
                    mg.deleteCastMember(castMembers, validateInput());
                    break;
                case 7:
                    system("clear");
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