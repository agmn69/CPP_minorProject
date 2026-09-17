#include <iostream>
#include <fstream>
#include <cstdio>
#include <limits>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

const string DATA_FILE = R"(X:\GitHub\CPP_minorProject\databook.txt)";
const string TEMP_FILE = R"(X:\GitHub\CPP_minorProject\databook.temp)";

class airline{
    string Flight, dptr, dstn;
    int seats, price, totalSeats;

    bool changeSeats(int change){
        ifstream in(DATA_FILE);
        ofstream out(TEMP_FILE);
        if(!in || !out){
            return false;
        }

        string line;
        bool updated = false;
        while(getline(in, line)){
            string flight, departure, destination;
            int flightPrice, currentSeats;
            stringstream parser(line);

            if(parser >> flight >> departure >> destination >> flightPrice >> currentSeats){
                if(flight == Flight){
                    int newSeats = currentSeats + change;
                    if(newSeats < 0 || newSeats > totalSeats){
                        in.close();
                        out.close();
                        remove(TEMP_FILE.c_str());
                        return false;
                    }
                    currentSeats = newSeats;
                    updated = true;
                }
                out << flight << "   " << departure << "   " << destination << "   "
                    << flightPrice << "   " << currentSeats;
            }
            else{
                out << line;
            }
            out << endl;
        }

        in.close();
        out.close();
        if(!updated || !MoveFileExA(TEMP_FILE.c_str(), DATA_FILE.c_str(), MOVEFILE_REPLACE_EXISTING)){
            remove(TEMP_FILE.c_str());
            return false;
        }

        seats += change;
        return true;
    }

    public: 
    airline(string flight, string departure, string destination, int fPrice, int totalSeats){
        Flight = flight;
        dptr = departure;
        dstn = destination;
        seats = totalSeats;
        price = fPrice;
        this->totalSeats = totalSeats;
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

    bool loadSeats(){
        ifstream in(DATA_FILE);
        string line;
        while(getline(in, line)){
            string flight, departure, destination;
            int flightPrice, savedSeats;
            stringstream parser(line);
            if(parser >> flight >> departure >> destination >> flightPrice >> savedSeats && flight == Flight){
                if(savedSeats >= 0 && savedSeats <= totalSeats){
                    seats = savedSeats;
                }
                return true;
            }
        }
        return false;
    }

    bool reserve(){
        return changeSeats(-1);
    }

    bool cancel(){
        return changeSeats(1);
    }

};

void display(){
    ifstream in(DATA_FILE);

    if(!in){
        cout<<"Couldn't read file."<<endl;
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

    ifstream existing(DATA_FILE);
    if(!existing){
        ofstream out(DATA_FILE);
        if(!out){
            cout<<"Couldn't access file."<<endl;
            return 1;
        }
        out<<flight1.getFlight()<<"   "<<flight1.getDepr()<<"   "<<flight1.getDestn()<<"   "<<flight1.getPrice()<<"   "
        <<flight1.getSeats()<<endl<<endl;
        out<<flight2.getFlight()<<"   "<<flight2.getDepr()<<"   "<<flight2.getDestn()<<"   "<<flight2.getPrice()<<"   "
        <<flight2.getSeats()<<endl<<endl;
        out.close();
    }
    existing.close();

    flight1.loadSeats();
    flight2.loadSeats();

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
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid choice."<<endl;
            Sleep(1500);
            continue;
        }
        if(choice == 1){
            system("cls");
            display();
            string flight;
            cout<<"Enter flight no. ";
            cin>>flight;

            if(flight == flight1.getFlight()){
                if(flight1.getSeats() == 0){
                    cout<<"Sorry no seats available."<<endl;
                }
                else if(flight1.reserve()){
                    cout<<"Seat reserved successfully!"<<endl;
                }
                else{
                    cout<<"Could not update the booking file."<<endl;
                }
            }
            else if(flight == flight2.getFlight()){
                if(flight2.getSeats() == 0){
                    cout<<"Sorry no seats available."<<endl;
                }
                else if(flight2.reserve()){
                    cout<<"Seat reserved successfully!"<<endl;
                }
                else{
                    cout<<"Could not update the booking file."<<endl;
                }
            }
            else{
                cout<<"Flight not found."<<endl;
            }
            Sleep(4000);
        }
        else if(choice == 2){
            system("cls");
            display();
            string flight;
            cout<<"Enter flight no. ";
            cin>>flight;

            if(flight == flight1.getFlight()){
                if(flight1.cancel()){
                    cout<<"Flight cancelled successfully!"<<endl;
                }
                else{
                    cout<<"Could not cancel this flight."<<endl;
                }
            }
            else if(flight == flight2.getFlight()){
                if(flight2.cancel()){
                    cout<<"Flight cancelled successfully!"<<endl;
                }
                else{
                    cout<<"Could not cancel this flight."<<endl;
                }
            }
            else{
                cout<<"Flight not found."<<endl;
            }
            Sleep(4000);
        }
        else if(choice == 3){
            system("cls");
            exit = true;
            cout<<"Good Luck!"<<endl;
            Sleep(3000);
        }
        else{
            cout<<"Invalid choice."<<endl;
            Sleep(1500);
        }
    }
    return 0;
}
