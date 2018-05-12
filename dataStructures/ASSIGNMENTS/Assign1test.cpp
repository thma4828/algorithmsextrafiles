#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

int search_arry_cntr = 0;
int delete_arry_cntr = 0;
int file_read_cntr = 0;
int counter = 0;
bool found = false;

struct item{
    string type;
    int price;
    bool forSale;
};

int SearchArray(item ITS[], string v, int the_price, bool ForSale){

    int index = -1;
    int x = 0;
    string temp_type;
    int temp_price;
    bool temp_forsale;

    while(found == false){
        temp_type = ITS[x].type;
        temp_price = ITS[x].price;
        temp_forsale = ITS[x].forSale;

        if(temp_type == v){
            if(temp_forsale != ForSale){
                if((temp_forsale == 0 && the_price >= temp_price ) || (temp_forsale == 1 && the_price <= temp_price)){
                    index = x;
                    found = true;
                }
            }else if(temp_forsale == ForSale){
                x++;
            }

        }else{
            x++;
        }

    }
    return index;
}

void deleteArrayItem(item ITS[], int index){
    for(int x=index; x<counter-2; x++){
        ITS[x].type = ITS[x + 1].type;
        ITS[x].forSale = ITS[x + 1].forSale;
        ITS[x].price = ITS[x + 1].price;
        delete_arry_cntr = delete_arry_cntr + 4;
    }
    counter = counter - 1;
}

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
    bool temp_sale;
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

            if(s5 == "wanted"){
                temp_sale = 1;
            }
            if(s5 == "for sale"){
                temp_sale = 0;
            }
            //searching for matching type
            type_index = SearchArray(ITS, s1, p, temp_sale);

            if(found == true){
                deleteArrayItem(ITS, type_index);
            }
            else{

                if(s5 == "wanted"){
                    ITS[counter].forSale = 1;
                }
                else if(s5 == "for sale"){
                    ITS[counter].forSale = 0;
                }

                temp_sale = ITS[counter].forSale;
                ITS[counter].type = s1;
                ITS[counter].price = p;
            }


            counter ++;
        }
    }

    cout << "Items sold." << endl;
    cout << "#" << items_sold << endl;
    cout << "Items remaining in the message board after reading all lines from the file." << endl;
    cout << "#" << counter << endl;
    cout << "file read: " << file_read_cntr << endl;
    cout << "search array: " << search_arry_cntr << endl;
    cout << "shift array: " << delete_arry_cntr << endl;

}
