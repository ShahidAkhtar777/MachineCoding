#include<iostream>
using namespace std;

class Ingredient{
    public:
    string name;
    int quantity;

    int getQuantity(){return quantity;}
    void setQuantity(int quan){
        quantity = quan;
    }
    void setName(string  _name){
        name = _name;
    }
    string getName(){
        return name;
    }
    void printIngredient(){
        cout<<"name: "<<getName()<<", AmountLeft: "<<quantity<<endl;
    }

};

class hot_water : public Ingredient{
    public:
    hot_water(int quan){
        setName("hot_water");
        setQuantity(quan);
    }    
};
class hot_milk : public Ingredient{
    public:
    hot_milk(int quan){
        setName("hot_milk");
        setQuantity(quan);
    }    
};
/*  ============================== */
class Beverage{
    string name;
    
    public:
    int total_num_ing ;
    Ingredient* list_of_ing;
    string get_name(){return name;}
    void set_name(string _name){name = _name; }

};

class hot_tea: public Beverage{
    public:
    hot_tea(){
        set_name("hot_tea");
        total_num_ing = 2;

        list_of_ing = new Ingredient[total_num_ing];
        list_of_ing[0] =  hot_water(200);
        list_of_ing[1] =  hot_milk(100);
    }
};

class hot_coffee: public Beverage{
    public:
    hot_coffee(){
        set_name("hot_coffee");
        total_num_ing = 2;

        list_of_ing = new Ingredient[total_num_ing];
        list_of_ing[0] =  hot_water(100);
        list_of_ing[1] =  hot_milk(400);
    }
};

/******************    Main Class : Coffee Machine **************/
class Coffee_Machine{
    public:
    int total_num_bev;
    Beverage* list_of_bev;
    
    int total_num_available_ing;
    Ingredient* available_ing;
    
    Coffee_Machine(){
        total_num_bev = 2;
        list_of_bev = new Beverage[total_num_bev];
        list_of_bev[0] =  hot_tea();
        list_of_bev[1] =  hot_coffee();

        total_num_available_ing = 2;
        available_ing = new Ingredient[total_num_available_ing];
        available_ing[0] = hot_water(500);
        available_ing[1] = hot_milk(500);
        
    }

    void add_stock(string name, int value){
        if(value < 0) {
           cout<< "Error: Can't add negative amount of ingredient";
            return;
        }

        if(name == "hot_water"){
            available_ing[0].setQuantity( available_ing[0].getQuantity()+value );
        }else if(name == "hot_milk"){
            available_ing[1].setQuantity( available_ing[1].getQuantity()+value );
        }else
        {
            cout<<"Error: Ingredient not found, not adding to machine";
        }
    }

    void get_stock(){
        cout<<endl<<"List of avaiable stocks with CoffeeMachine:"<<endl;
        for(int i=0;i<total_num_available_ing;i++){
            available_ing[i].printIngredient();
        }
    }
    void prepare(string name){
        for(int i=0;i<total_num_bev;i++){
            if(list_of_bev[i].get_name()==name){

                Beverage b = list_of_bev[i];
                cout<<"=debug preparing beverage"<<b.get_name()<<endl;
                //We need to check if Beverage b can be prepared with the available quantity of Ing

                //Loop over list of Ingredients required for beverage b
                for(int j=0;j<b.total_num_ing;j++){

                    Ingredient curr_ing = b.list_of_ing[j];

                    //Loop over list of available Ingredients with the machine
                    for(int k=0;k<total_num_available_ing;k++){
                        if(available_ing[k].getName() == curr_ing.getName()  ){
                            if(available_ing[k].getQuantity() < curr_ing.getQuantity()){
                                cout<<"Error: Sufficient quantity of ingredient "<<available_ing[k].getName()<<"not available"<<endl;
                                return;
                            }
                        }
                    }
                }

                //Loop over list of quantity and reduce the avialble ingredients 
                for(int j=0;j<b.total_num_ing;j++){

                    Ingredient curr_ing = b.list_of_ing[j];
                    cout<<"=debug checking curr_ing"<<curr_ing.getName()<<endl;
                    for(int k=0;k<total_num_available_ing;k++){
                        if(available_ing[k].getName() == curr_ing.getName()  ){
                            cout<<"=debug checking avail_ing"<<available_ing[k].getName()<<endl;
                            available_ing[k].setQuantity(available_ing[k].getQuantity() - curr_ing.getQuantity());
                            break;
                        }
                    }
                }

                cout<<"Beverage was prepared sucesfully"<<endl;
                get_stock();
                break;
            }
            
        }

        //if we reach here, we have sufficient quantity, so reduce the used from the total avaiable quantity of ingredient

    }
};

int main(){
    Coffee_Machine c_m = Coffee_Machine();
    do{
        cout<<"Menu: ";
        cout<<"1. add_stock()";
        cout<<"2. get_stock()";
        cout<<"3. prepare Beverage";
        cout<<"4. exit";
        cout<<endl;

        int choice;
        cin>>choice;

        string name;
        int quantity;

        switch (choice)
        {
        case 1:
            cout<<"Name of Ingredient::"; 
            cin>>name;
            cout<<"\nquantity:";
            cin>>quantity;
            
            c_m.add_stock(name,quantity);
            break;
        case 2:
            c_m.get_stock();
            break;
        case 3:
            cout<<"Enter name of Beverage"<<endl;
            cin>>name;
            c_m.prepare(name);
            break;
        case 4:
            return 0;
        default:
            cout<<"Menu command not found.Try again"<<endl;
            break;
        }                
    }while(1);

    return 0;
}