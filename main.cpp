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
    airline(string flight, string departure, string destination, int fPrice, int totalSeats){
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
    void update(string flight){
        ifstream in(R"(X:\GitHub\CPP_minorProject\databook.txt)");
        ofstream out(R"(X:\GitHub\CPP_minorProject\databook.temp)");
        string line;
        while (getline(in, line)){
            int position = line.find(flight);
            if(position != string::npos){
                int current = seats-1;
                seats = current;
                stringstream ss;
                ss>>current;
                string strCurrent = ss.str();

                int seatPosition = line.find_last_of("  ");
                line.replace(seatPosition + 3, string::npos, strCurrent);
            }
            out<<line<<endl;
        }
        out.close();
        in.close();
        remove(R"(X:\GitHub\CPP_minorProject\databook.txt)");
        rename(R"(X:\GitHub\CPP_minorProject\databook.txt)", R"(X:\GitHub\CPP_minorProject\databook.temp)");
        cout<<"Seat reserved successfully!"<<endl;
    }

};

void display(){
    ifstream in(R"(X:\GitHub\CPP_minorProject\databook.txt)");

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
    airline flight1("MH371", "Singapore", "London", 1200, 221);
    airline flight2("AI771", "India", "Frankfurt", 880, 124);

    ofstream out(R"(X:\GitHub\CPP_minorProject\databook.txt)");
    if(!out){
        cout<<"Couldn't access file."<<endl;
    }
    else{
        out<<flight1.getFlight()<<"   "<<flight1.getDepr()<<"   "<<flight1.getDestn()<<"   "<<flight1.getPrice()<<"   "
        <<flight1.getSeats()<<endl<<endl;

        out<<flight2.getFlight()<<"   "<<flight2.getDepr()<<"   "<<flight2.getDestn()<<"   "<<flight2.getPrice()<<"   "
        <<flight2.getSeats()<<endl<<endl;
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
                flight1.update(flight);
            }
            else if(flight1.getSeats() < 0){
                cout<<"Sorry no seats available."<<endl;
            }

            if(flight == flight2.getFlight() && flight2.getSeats() > 0){
                flight2.update(flight);
            }
            else if(flight2.getSeats() < 0){
                cout<<"Sorry no seats available."<<endl;
            }

            // if(flight == flight3.getFlight() && flight3.getSeats() > 0){
            //     flight3.update(flight);
            // }
            // else if(flight3.getSeats() < 0){
            //     cout<<"Sorry no seats available."<<endl;
            // }
            Sleep(4000);
        }
        else if(choice == 3){
            system("cls");
            exit = true;
            cout<<"Good Luck!"<<endl;
            Sleep(3000);
        }
    }
    return 0;
}