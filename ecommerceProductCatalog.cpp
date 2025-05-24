#include <bits/stdc++.h>
using namespace std;


class Product{
  
  public:
  
  int product_id;
  string product_type;
  string product_name;
  int product_price;
  int product_amount;
  
  Product(int id,string name,string type,int price,int amt)
  {
    product_id=id;
    product_price=price;
    product_name=name;
    product_type=type;
    product_amount=amt;
  }
  
  
  int getProductPrice()
  {
    return product_price;
  }
  
  bool isProductAvailable()
  {
    return product_amount>0;
  }
  
  
  string getProductName()
  {
    return product_name;
  }
  
  int getProductCnt()
  {
    return product_amount;
  }
  
  
};

// user can add products to cart, increase number
// user can checkout
// user can search for products Trie implementation
// admin will add products 

class Node{
  public:
  Node* links[26];
  bool flag;
  
  Node()
  { 
    
    flag=false;
    for(int i=0;i<26;i++)
    {
      links[i]=NULL;
    }
  }
  
  
  bool containsKey(char ch)
  {
    return links[ch-'a']!=NULL;
  }
  Node* getNode(char ch)
  {
    return links[ch-'a'];
  }
  void putNode(char ch, Node* node)
  {
    links[ch-'a']=node;
  }
  
  bool isEnd()
  {
    return flag;
  }
  
  void setEnd()
  {
    flag=true;
  }
};


class Trie{
  public:
  Node* root;
  Trie()
  {
    root=new Node();
  }
  
  void addWord(string word)
  {
    
    Node* node=root;
    
    for(int i=0;i<word.size();i++)
    {
      if(!node->containsKey(word[i]))
      {
        node->putNode(word[i],new Node());
      }
      node=node->getNode(word[i]);
    }
    
    node->setEnd();
  }
  
  
  bool searchWord(string word)
  {
    
    Node* node=root;
    
    for(int i=0;i<word.size();i++)
    {
      if(!node->containsKey(word[i]))
      {
        return false;
      }
      node=node->getNode(word[i]);
    }
    
    return node->isEnd();
  }
  
};


class Inventory{
  public:
  set<Product*> inventory;
  Trie* trie;
  Inventory()
  {
    trie=new Trie();
  }
  
  void addProductItem(Product* product)
  {
    inventory.insert(product);
    trie->addWord(product->getProductName());
  }
  
  void removeProductItem(Product* product)
  {
    inventory.erase(product);
  }
  
  void displayInventory()
  {
    for(auto it:inventory)
    {
      cout<<it->getProductName()<<"( "<<it->getProductPrice()<<")"<<endl;
    }
  }
  
  bool searchProduct(string word)
  {
    return trie->searchWord(word);
  }
  
};


class Admin{
  public:
  
  Inventory* inventory;
  
  Admin(Inventory* inv)
  {
    inventory=inv;
  }
  
  void addProduct(Product* product)
  {
     inventory->addProductItem(product);
  }
  
  void removeProduct(Product* product)
  {
    inventory->removeProductItem(product);
  }
  
};


class Cart{
  
  public:
  unordered_map<Product*,int> products;
  
  void addItem(Product* product)
  {
    products[product]++;
  }
  
  void removeItem(Product* product)
  {
    products[product]--;
  }
  
  void increaseCounter(Product* product)
  {
    products[product]++;
  }
  
  void decreaseCounter(Product* product)
  {
    products[product]--;
    if(products[product]==0)
    {
      products.erase(product);
    }
  }
  
  int getTotalAmount()
  {
    int total_amt=0;
    
    for(auto it:products)
    {
      int price=it.first->getProductPrice();
      int cnt=it.second;
      
      total_amt+=price*cnt;
    }
    return total_amt;
  }
  
  void clearCart()
  {
    products.clear();
  }
  
};

class User{
  public:
  Cart* cart;
  int user_id;
  
  User(int id)
  {
    user_id=id;
    cart=new Cart();
  }
  
  
  void addToCart(Product* product)
  {
    cart->addItem(product);
    
  }
  
  void removeFromCart(Product* product)
  {
    cart->removeItem(product);
   
  }
  
  void increaseProductNumber(Product* product)
  {
    cart->increaseCounter(product);
    
  }
  
  void decreaseProductNumber(Product* product)
  {
    cart->decreaseCounter(product);
    
  }
  
  int checkout()
  {
     cout<<"Pay Total Amount "<<cart->getTotalAmount()<<endl;
     cart->clearCart();
     return cart->getTotalAmount();
    
  }
  
 
  
};

int main() 
{
  
    Inventory* inv = new Inventory();
    Admin* admin = new Admin(inv);

    Product* p1 = new Product(1, "iphone", "Electronics", 100000, 10);
    Product* p2 = new Product(2, "tshirt", "Clothing", 1500, 20);
    Product* p3 = new Product(3, "notebook", "Stationery", 100, 50);
    Product* p4 = new Product(4, "charger", "Electronics", 1200, 15);

    admin->addProduct(p1);
    admin->addProduct(p2);
    admin->addProduct(p3);
    admin->addProduct(p4);

  
    cout << "\nInventory:\n";
    inv->displayInventory();

    User* user = new User(101);

    
    user->addToCart(p1);
    user->addToCart(p2);
    user->addToCart(p2);  
    user->addToCart(p4);


    cout << "\n--- Checkout ---\n";
    user->checkout();

    
    inv->displayInventory();


    cout << "\n--- Product Search ---\n";
    string search1 = "tshirt";
    string search2 = "shoes";

    cout << "Searching for '" << search1 << "': "
         << (inv->searchProduct(search1) ? "Found" : "Not Found") << endl;

    cout << "Searching for '" << search2 << "': "
         << (inv->searchProduct(search2) ? "Found" : "Not Found") << endl;

    return 0;
}
