#include<iostream>
#include<vector>
#include<string>

//Superclass
class Person 
{
    private:
    std::string name; //attribute that is encapsulated in the person class

    public:
    Person(std::string n) : name(n){} //constructor that intializes the private name attribute

    std::string getName() const {return name;} //getter or accessor function
};

//Derived class
class Employee : public Person
{
    private:
    int employeeId; //attribute that is encapsulated in the person class

    public:
    Employee(std::string n,int id) : Person(n),employeeId(id) {} //constructor that intializes the base class and derived attributes

    int getEmployeeId() const {return employeeId;} //getter for employeeId
}; 
//Derived class
class CastMember : public Employee
{
    public:
    CastMember(std::string n,int id) :Employee(n,id){} //constructor that intializes the private attributes of the base class 
};
//Derived class
class Manager : public Employee
{
    private:
    std::vector<CastMember> castMembers; //vector to keep track of castmembers
    int ManagerId;
    public:
    Manager(std::string n,int id,int mId) : Employee(n,id),ManagerId(mId){} //constructor that intializes the private attributes of the base class

    int getManagerId() const {return ManagerId;} //getter for manager id
    //function to create instances of Castmember
    void createCastMembers(std::string name,int id)
    {
        CastMember newCastMember(name,id);
        castMembers.push_back(newCastMember); //add new Castmember to the vector
        std::cout<< "Cast Member: "<<name<<" created with ID: "<<id<<std::endl;
    }
};
    
std::vector <Manager> managers;

//a function to emplace manager instances into the managers vector
void intializeManagers()
{
    managers.emplace_back("John Smith", 101,1);    
    managers.emplace_back("Jane Doe", 102,2); 
}

void addCastMember(Manager& manager) //pass manager by reference
{
      std::string name;        
             int id;        
             std::cout << "Enter the name of the cast member: ";        
             std::cin.ignore(); // Clear the input buffer        
             std::getline(std::cin, name); // Read full line for name        
             std::cout << "Enter the ID of the cast member: ";        
             std::cin >> id;        // Create a new cast member using the manager        
             manager.createCastMembers(name, id);       
}

// Function for manager authentication
            bool authenticateManager(int id,Manager& authenticatedManager) 
                {    
                    for (const auto& manager : managers) 
                    {        
                        if (manager.getEmployeeId() == id) 
                        {   
                            authenticatedManager = manager;         
                            return true; // Manager is authenticated        
                        }    
                    }    
                    return false; // Manager not found
                }

int main()
{
    
    intializeManagers(); //function call to intialize managers
     int option;
     int managerId;

       Manager authenticatedManager("", 0,0); // Variable to store the authenticated manager
    authentication:
     std::cout << "Enter your Manager ID: ";    
    std::cin >> managerId;    
    // Authenticate manager    
        if (!authenticateManager(managerId,authenticatedManager)) 
            {        
                std::cout << "Invalid Manager ID. Access Denied." << std::endl; 
                goto authentication;      
                return 0; // Exit if authentication fails    
            }
    menu:
    std::cout << "Welcome, " << authenticatedManager.getName() << "!" << std::endl;
     std::cout << "1: Add new cast member" << std::endl;  
     std::cout << "2: Exit"<< std::endl;  
     std::cout << "Choose an option: ";    
     std::cin >> option;    
     
     switch (option)    
     {    
        case 1: 
            addCastMember(authenticatedManager);  
            goto  menu;    
             break;    
        case 2:
            goto authentication;
        
      
        default:        
        std::cout << "Invalid option." << std::endl;        
        break;

    }
}


