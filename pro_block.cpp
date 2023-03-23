#include <iostream>
#include <string.h>
#include <ctime>
#include <sstream>
#include<vector>
using namespace std;

class Block
{
    public:

    int nonce , divlvl ,i;
    vector<int> trans_no;
    vector<long int>tra_hash;
    hash<string>  h_trans;
    string preHash;
    size_t merkle , p_hash;
    Block *pre, *next;

    Block()
    {  
        preHash="1"; //by default hash value of previous block
        cout<<"\n\n Enter the transaction: ";
        int val; // will take input of transaction
        while (cin>>val)
        {
            if(val==0)
            {
                break;  //when user will give input "0" it will not take any further inputs
            }
            else
            {
                trans_no.push_back(val);  //stores the transaction into vector transaction
                tra_hash.push_back(h_trans(to_string(val)));  //converts the transaction value into string and then stores into h_trans
                                                            //& pushback into (t_hash)
            }
        }
        pre = NULL;
        next = NULL;}

    Block(int nonce,int divlvl,vector<int>trans_no,vector<long int>tra_hash,size_t merkle)
    {
        this->nonce=nonce;
        this->divlvl=divlvl;
        this->trans_no=trans_no;
        this->tra_hash=tra_hash;
        this->merkle=merkle;
        this->pre = NULL;
        this->next = NULL;
    }
    long int hash_f()  //creates the hash of previous block
    {
        long int hash_f = h_trans(preHash);  //converts the hash of whole previous block
        for(auto i = tra_hash.begin();i!=tra_hash.end();i++)  //i is iterator, auto is a keyword in C++ that tells the compiler to automatically
                                                          // deduce the data type of a variable based on its initialization value.
        {
            hash_f = hash_f + *i;  //*i will take the hash value from the address of (i=t_hash.begin())
        }
        return (h_trans(to_string(hash_f)));  //converts the hash_f into hash value
    }
};
Block *genesisblock /*head*/= NULL;


class BlockChain : public Block
{
    public :

    BlockChain()
    {}

    void Insert_block(int nonce,int divlvl,vector<int>trans_no,vector<long int>tra_hash,size_t merkle)
    {
        while (nonce != divlvl)
        {
            nonce++;
        }
        Block *newblock = new Block(nonce , divlvl, trans_no, tra_hash, merkle);
        if (genesisblock/*head*/ == NULL)
        {
            cout << "\nGenesis block is created";
            genesisblock/*head*/ = newblock;
            newblock->p_hash = NULL;
        }
        else
        {
            Block *temp = genesisblock;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newblock;
            newblock->pre = temp;
            newblock->preHash=to_string(temp->hash_f());
            // cout<<"Prev hash: "<<hashofprev;
        }
    } 
    void displayBlockChain()
    {
        Block *temp = genesisblock;
        if (genesisblock == NULL)
        {
            cout << "\nNo block is exists in the BlockChain";
        }
        else
        {
            cout << "\n||------Block In Block Chain------||";
            while (temp != NULL)
            {
                cout << "\nprevhash: " << temp->p_hash;
                cout << "\nmerkleroot: " << temp->merkle;
                cout << "difflvl: " << temp->divlvl;
                cout << "\nnonce: " << temp->nonce;
                cout << "\n------------------------------------";
                temp = temp->next;
            }
        }
    }

    // void display_transid()
    // {
    //     cout<<"\nYour Transaction are: ";
    //     for(auto i=trans_no.begin();i!=trans_no.end();i++)
    //     {
    //         cout<<"  "<<*i;    //display transaction at address i
    //     }
    //     cout<<"\nTransaction hash is: ";
    //     for(auto i=tra_hash.begin();i!=tra_hash.end();i++)
    //     {
    //         cout<<" "<<*i;    //display the hash valuse of at address i
    //     }
    //     merkle=get_merkle_root(tra_hash);
    //     cout<<"\nMerkle root is: "<<merkle;   //display value of merkle root
    // }
    long int get_merkle_root(vector<long int> rt)
    {
        if(rt.size()==1)
        {
            return rt[0];   //if there is only one block exists in chain it will simply display
                            //hash value of that block as merkle root

        }
        else
        {
            vector<long int> parent;   //will stores hash of parent node
            for(int i=0;i<rt.size();i+=2)
            {
                long int lc = rt[0];  //left child
                long int rc;          //right child
                if(i+1<rt.size())
                {
                    rc=rt[i+1];
                }
                else
                {
                    rc=lc;          //child node which does not gets pair of other child will have its pair child
                }
                long int str = h_trans(to_string(lc+rc));  //generates the combine hash value of two child node
                parent.push_back(str);
            }
            return get_merkle_root(parent);
        }
    }
};

int main()  //main method of calling the class method
{
    BlockChain c1;
    int choice;
    do{
        cout<<"\n1.Insert Transaction: ";
        cout<<"\n2.Display: ";
        cout<<"\n3.Exit: ";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                c1.Insert_block(c1.nonce , c1.divlvl, c1.trans_no, c1.tra_hash, c1.merkle);
                
                    if (genesisblock==NULL)
                    {
                        cout << "\nEnter difficulty target: ";
                        cin >> c1.divlvl;
                        c1.nonce = 0;
                        switch(c1.divlvl)
                        {
                            case 1:
                            c1.Insert_block(c1.nonce , c1.divlvl, c1.trans_no, c1.tra_hash, c1.merkle);
                            break;
                            case 2:
                            c1.displayBlockChain();
                            break;
                            
                        }
                    }
                break;

            case 2:
                c1.displayBlockChain();
                break;
            case 3:
                exit(0);
                break;
        default:
            break;
        }
    }while(choice!=3);
   
    return 0;
}