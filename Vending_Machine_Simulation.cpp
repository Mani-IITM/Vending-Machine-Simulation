#include<bits/stdc++.h>
using namespace std;
typedef pair <string,int> pairs;

/*
Defining state names

DISPLAY LIST OF ITEMS AVAILABLE                  - ST_MENU
DISPLAY AMOUNT TO BE PAID/ACCEPT CURRENCY        - ST_BILL
GIVE CHANGE AND THE PRODUCT TO THE CUSTOMER      - ST_DELIVERY
MODIFY LIST                                      - ST_MODIFY
*/

// ST_MENU defined correctly. Tested.
class ST_MENU
{
  public:
    vector<pairs> items_for_sale;
    vector<int> prices;
    int index;
    // MENU format: <index>  <name> <quantity> Rs.<price>
    void display_menu()
    {
      for(auto it = items_for_sale.begin(); it!= items_for_sale.end(); it++)
      {
        pairs temp = *it;
        int i = it - items_for_sale.begin();
        cout<<i<<"  "<<temp.first<<"  "<<temp.second<<"  Rs."<<prices.at(i)<<endl;
      }
    }

    int check_quantity()
    {
      pairs t = items_for_sale.at(index);
      return t.second;
    }
} menu;

//ST_BILL defined correctly. Tested.
class ST_BILL : public ST_MENU
{
  public:
    int index;
    int amount_paid;
    int balance;
    void display_bill()
    {
      balance = prices.at(index) - amount_paid;
      cout<<"Amount due: "<< balance<<endl;
    }
} bill;

//ST_DELIVERY defined correctly. Tested.
class ST_DELIVERY: public ST_BILL
{
  public:
    void display()
    {
      cout<<"Here is your change: "<< -1*balance<<endl;
      cout<<"Here is the item you ordered. Have a good day!"<<endl;
    }
    void change_quantity()
    {
      pairs t = items_for_sale.at(index);
      t.second--;
      items_for_sale.at(index) = t;
    }
} delivery;

//ST_MODIFY defined correctly. Tested.
class ST_MODIFY: public ST_MENU
{
  public:
    pairs new_item;
    int new_item_price;
    int index;
    void add_new()
    {
      items_for_sale.push_back(new_item);
      prices.push_back(new_item_price);
    }
    void del_item()
    {
      items_for_sale.erase(items_for_sale.begin() + index);
      prices.erase(prices.begin() + index);
    }
    void modify_item()
    {
      items_for_sale.at(index) = new_item;
      prices.at(index) = new_item_price;
    }
} temp;


int main()
{
  //Possible states
  enum STATES{
    ST_MENU,
    ST_BILL,
    ST_DELIVERY,
    ST_MODIFY
  };

  enum STATES CURRENT_STATE;
  CURRENT_STATE = ST_MENU;

  //initialize values
  int n = 2;
  menu.items_for_sale.push_back(make_pair("Lays",20));
  menu.items_for_sale.push_back(make_pair("Coca Cola",1));
  menu.items_for_sale.push_back(make_pair("Cup Noodles",30));
  menu.prices.push_back(10);
  menu.prices.push_back(20);
  menu.prices.push_back(30);

  while(true)
  {
      switch(CURRENT_STATE)
      {
    case ST_MENU :
        menu.display_menu();
        int input;
        cout<<"Do you want to buy or modify? Enter product number if you wish to purchase.\n";
        cout<<"Enter password if you want to modify\n";
        cin>>input;
        menu.index = input;
        if(input == -1)
        {
          CURRENT_STATE = ST_MODIFY;
        }
        else if(input >=0 && input<=n)
        {
          if(menu.check_quantity() != 0)
          {
            CURRENT_STATE = ST_BILL;
            bill.index = input;
            bill.amount_paid = 0;
            bill.prices = menu.prices;
          }
          else
            cout<<"Product not available\n";
        }
        else
        {
          cout<<"Invalid Code\n";
        }
        break;
    case ST_BILL:
        int flag;
        flag = -1;
        bill.display_bill();
        int money;
        cout << "Flag is -1.\n";
        while(bill.balance>0)
        {
          cout<<"Insert coins"<<endl;
          cin>>money;
          if(money != flag)
          {
            bill.amount_paid += money;
            bill.display_bill();
          }
          else
          {
            cout<<"Coins returned. Transaction unsuccessfull.\n";
            CURRENT_STATE = ST_MENU;
            break;
          }
        }
        if(money != flag)
        {
          CURRENT_STATE = ST_DELIVERY;
          delivery.balance = bill.balance;
          delivery.items_for_sale = menu.items_for_sale;
          delivery.prices = menu.prices;
          delivery.index = bill.index;
        }
        break;
    case ST_DELIVERY:
        delivery.display();
        delivery.change_quantity();
        menu.items_for_sale = delivery.items_for_sale;
        CURRENT_STATE  = ST_MENU;
        break;
    case ST_MODIFY:
        int choice;
        temp.items_for_sale = menu.items_for_sale;
        temp.prices = menu.prices;
        cout<<"Do you want to 1) Add a new item, 2)Delete an item or 3)Modify an item? Enter option number.\n";
        cin>>choice;
        switch(choice)
        {
          case 1:
              {
                 string str;
                 int quan,price;
                 cout<<"Enter Data in the format of <item_name> followed by <quantity> and then <price> :\n";
                 cin.ignore();
                 getline(cin,str);
                 cin>>quan>>price;
                 temp.new_item = make_pair(str,quan);
                 temp.new_item_price = price;
                 temp.add_new();
                 break;
             }
          case 2:
              {
                int index;
                cout<<"Enter index of the item:\n";
                cin>>index;
                temp.index = index;
                temp.del_item();
                n--;
                break;
              }
          case 3:
              {
                int index;
                cout<<"Enter index of the item:\n";
                cin>>index;
                if(index<0 || index>n)
                {
                  cout<<"Invalid Index\n";
                  break;
                }
                temp.index = index;
                string str;
                int quan,price;
                cout<<"Enter Data in the format of <item_name> followed by <quantity> and then <price> :\n";
                cin.ignore();
                getline(cin,str);
                cin>>quan>>price;
                temp.new_item = make_pair(str,quan);
                temp.new_item_price = price;
                temp.modify_item();
                break;
              }
          default:
              {
                cout<<"Invalid Choice\n";
              }
        }
        CURRENT_STATE = ST_MENU;
        menu.items_for_sale = temp.items_for_sale;
        menu.prices = temp.prices;
        break;

  }
  }

  return 0;

}
