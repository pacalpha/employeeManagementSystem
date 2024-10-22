#include<iostream>
#include<vector>
#include<string>

//Superclass
class Person 
{
    private:
    std::string name;

    public:
    Person(std::string n) : name(n){} //constructor

    std::string getName() const {return name;}
};

//Derived class
class Employee : public Person
{
    private:
    int employeeId;

    public:
    //constructor that intializes the base class and derived attributes
    Employee(std::string n,int id) : Person(n),employeeId(id) {}
}; 

class CastMember : public Employee
{
    public:
    CastMember(std::string n,int id) :Employee(n,id){}
};

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

int main()
{
     int option;

     std::cout << "1: Add new cast member" << std::endl;    
     std::cout << "Choose an option: ";    
     std::cin >> option;    
     
     switch (option)    
     {    
        case 1: 
            addCastMember();       
             break;    
        
      
        default:        
        std::cout << "Invalid option." << std::endl;        
        break;

    }
}

