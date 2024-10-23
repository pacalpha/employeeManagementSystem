#include<iostream>
#include<vector>
#include<string>

//Superclass
class Person 
{
    private:
    std::string name; //attribute that is encapsulated in the person class

    public:
    Person(std::string n) : name(n){} //constructor

    std::string getName() const {return name;} //getter or accessor function
};

//Derived class
class Employee : public Person
{
    private:
    int employeeId; //attribute that is encapsulated in the person class

    public:
    //constructor that intializes the base class and derived attributes
    Employee(std::string n,int id) : Person(n),employeeId(id) {}

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
    public:
    Manager(std::string n,int id) : Employee(n,id){}

    //function to create instances of Castmember
    void createCastMembers(std::string name,int id)
    {
        CastMember newCastMember(name,id);
        castMembers.push_back(newCastMember); //add new Castmember to the vector
        std::cout<< "Cast Member: "<<name<<" created with ID: "<<id<<std::endl;
    }
};
    
     Manager manager("John Smith", 101); // Create a Manager instance   
std::vector <Manager> managers;
void addCastMember()
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
            bool authenticateManager(int id) 
                {    
                    for (const auto& manager : managers) 
                    {        
                        if (manager.getEmployeeId() == id) 
                        {            
                            return true; // Manager is authenticated        
                        }    
                    }    
                    return false; // Manager not found
                }

int main()
{
    // Adding some managers for demonstration    
                        managers.emplace_back("John Smith", 101);    
                        // managers.emplace_back("Jane Doe", 102); 

     int option;
     int managerId;

       Manager authenticatedManager(manager.getName(), 0); // Variable to store the authenticated manager
    authentication:
     std::cout << "Enter your Manager ID: ";    
    std::cin >> managerId;    
    // Authenticate manager    
        if (!authenticateManager(managerId)) 
            {        
                std::cout << "Invalid Manager ID. Access Denied." << std::endl;       
                return 1; // Exit if authentication fails    
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
            addCastMember();  
            goto  menu;    
             break;    
        case 2:
            goto authentication;
        
      
        default:        
        std::cout << "Invalid option." << std::endl;        
        break;

    }
}


