#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;



struct item{
    string type;
    int price;
    bool forSale;
};


int main(){
    ifstream line_in;
    string filename;
    cin >> filename;
    line_in.open(filename);
    item ITS[100];
    string line, s1, s2, s3, s4, s5, s6;

    int p1, p2, p3, x1;
    const char* str1;
    int p, items_sold, type_index;
    int search_arry_cntr = 0;
    int file_read_cntr = 0;
    int counter = 0;
    bool found = false;
    bool forS;
    int index;
    int arry_shift;
    arry_shift = 0;
    while(getline(line_in, line)){
        if(line[0] != ' '){
            file_read_cntr ++;
            p1 = line.find(",");
            //s1 is the type
            s1 = line.substr(0, p1);
            s2 = line.substr(p1 + 1);
            p2 = s2.find(",");
            //s3 is the wanted/forsale
            s3 = s2.substr(0, p2);
            s5 = s3.substr(1);
            s4 = s2.substr(p2 + 2);
            p3 = s4.find(" ");
            s6 = s2.substr((p2 + 2), p3);


            str1 = s6.c_str();

            p = atoi(str1);

            if(s5 == "for sale"){
                forS = 0;
            }else{
                forS = 1;
            }

            if(s5 == "wanted"){
                for(int x=0; x <= counter; x++){
                    if(ITS[x].type == s1){
                        if(ITS[x].forSale == 0){
                            if(ITS[x].price <= p){
                                cout << ITS[x].type << " " << ITS[x].price << endl;
                                found = true;
                                search_arry_cntr++;
                                items_sold++;
                                for(int j = x; j<= index; j++){
                                    ITS[j].type = ITS[j + 1].type;
                                    ITS[j].price = ITS[j + 1].price;
                                    ITS[j].forSale = ITS[j + 1].forSale;
                                    arry_shift++;
                                }
                                counter --;
                                break;
                            }
                        }
                    }
                }
            }
            if(found == false){
                cout << " type: " << s1 << " price: " << p << " forsale: " << forS << endl;
                ITS[counter].type = s1;
                ITS[counter].price = p;
                ITS[counter].forSale = forS;
            }

            found = false;
            counter++;
        }
    }

    cout << "Items sold." << endl;
    cout << "#" << items_sold << endl;
    cout << "Items remaining in the message board after reading all lines from the file." << endl;
    cout << "#" << counter + 1 << endl;
    cout << "file read: " << file_read_cntr << endl;
    cout << "search array: " << search_arry_cntr << endl;
    cout << "shift array: " << arry_shift << endl;

}
