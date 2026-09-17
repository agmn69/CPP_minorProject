#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

class airline{
    string Flight, dptr, dstn;
    int seats, price;

    public: 
    airline(string flight, string departure, string destination, int totalSeats, int fPrice){
        Flight = flight;
        dptr = departure;
        dstn = destination;
        seats = totalSeats;
        price = fPrice;
    }

    string getFlight(){
        return Flight;
    }
    string getDepr(){
        return dptr;
    }
    string getDestn(){
        return dstn;
    }
    int getSeats(){
        return seats;
    }
    int getPrice(){
        return price;
    }

};

void display(){
    ifstream in(R"(C:\Users\Lenovo\Downloads\AviationSys\databook.txt)");

    if(!in){
        cout<<"Couldn'd read file."<<endl;
    }
    else{
        string content;
        while(getline(in, content)){
            cout<<content<<endl;
        }
    }   
}

int main() {
    airline flight1("MH371", "Singapore", "London", 221, 1200);
    airline flight2("AI771", "India", "Frankfurt", 142, 880);

    ofstream out(R"(C:\Users\Lenovo\Downloads\AviationSys\databook.txt)");
    if(!out){
        cout<<"Couldn't access file."<<endl;
    }
    else{
        out<<flight1.getFlight()<<"   "<<flight1.getDepr()<<"   "<<flight1.getDestn()<<"   "<<flight1.getSeats()<<"   "
        <<flight1.getPrice()<<endl<<endl;

        out<<flight2.getFlight()<<"   "<<flight2.getDepr()<<"   "<<flight2.getDestn()<<"   "<<flight2.getSeats()<<"   "
        <<flight2.getPrice()<<endl<<endl;
        cout<<"Data Saved!"<<endl;
        out.close();
    }

    bool exit = false;
    while(!exit){
        system("cls");
        cout<<"Welcome to Aviation management System"<<endl;
        cout<<"**************************************"<<endl;
        cout<<"[1] Book flight"<<endl;
        cout<<"================"<<endl;
        cout<<"[2] Cancel flight "<<endl;
        cout<<"================"<<endl;
        cout<<"[3] Exit "<<endl;
        cout<<"================"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;
        if(choice == 1){
            system("cls");
            display();
            string flight;
            cout<<"Enter flight no. ";
            cin>>flight;

            if(flight == flight1.getFlight() && flight1.getSeats() > 0){
                
            }
        }
    }
    return 0;
}