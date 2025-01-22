#include <iostream>
#include <vector>
#include <ctime>

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
                      << "\t";
            member.checkClockStatus();
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
                std::cout << "3. Total time worked\n";
                std::cout << "4. Clock history\n";
                std::cout << "5.EXIT\n";
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
                    member.totalTimeWorked();
                    break;
                case 4:
                    member.displayClockHistory();
                    break;
                case 5:
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
                    std::cout << "3. Clock History\n";
                    std::cout << "4. List all castmembers\n";
                    std::cout << "5. Create cast member\n";
                    std::cout << "6. EXIT\n";
                    std::cout << "Please select an option: ";

                    int managerMenu = validateInput();

                    switch (managerMenu)
                    {
                    case 1:
                        mg.checkClockStatus();
                        break;
                    case 2:
                        mg.changeClockStatus();
                        break;
                    case 3:
                        mg.displayClockHistory();
                        break;
                    case 4:
                        mg.listAllCastMembers(castmembers);
                        break;
                    case 5:
                        mg.createCastMember(castmembers);
                        break;
                    case 6:
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