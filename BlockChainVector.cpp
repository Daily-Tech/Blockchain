#include <iostream>
#include <string.h>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

class BlockHeader
{
public:
    string version, timestamp;
    int transno, difflvl, nonce;
    vector<int> intv1;
    size_t prevhash, merkleroot;
};
class Block : public BlockHeader
{
public:
    Block *prev, *next;

    Block() {}
    Block(string version, size_t merkleroot, string timestamp, int difflvl, int nonce, int transno, vector<int> intv1)
    {
        this->version = version;
        this->merkleroot = merkleroot;
        this->timestamp = timestamp;
        this->difflvl = difflvl;
        this->nonce = nonce;
        this->transno = transno;
        this->intv1 = intv1;
        this->prev = NULL;
        this->next = NULL;
    }
};
Block *genesisblock = NULL;
class operation : public Block
{

public:
    operation() {}
    void createBlock(string version, size_t merkleroot, string timestamp, int difflvl, int nonce, int transno, vector<int> intv1)
    {

        while (nonce != difflvl)
        {
            nonce++;
        }
        Block *newblock = new Block(version, merkleroot, timestamp, difflvl, nonce, transno, intv1);
        if (genesisblock == NULL)
        {
            cout << "\nGenesis block is created";
            genesisblock = newblock;
            newblock->prevhash = 0;
        }
        else
        {
            Block *temp = genesisblock;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newblock;
            newblock->prev = temp;
            hash<Block *> bh;
            size_t hashofprev = bh(temp);
            newblock->prevhash = hashofprev;
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
            int ch;
            cout << "\nDo you want to see detailed transaction press 1\nelse press 2\nEnter Your Choice:- ";
            cin >> ch;
            cout << "\n||------Block In Block Chain------||";
            while (temp != NULL)
            {

                if (ch == 1)
                {

                    for (auto k = temp->intv1.begin(); k != temp->intv1.end(); k++)
                    {
                        cout << "\nTotal Amount of Bill:- " << *k;
                    }
                }
                cout << "\n\nVersion: " << temp->version;
                cout << "\nprevhash: " << temp->prevhash;
                cout << "\nmerkleroot: " << temp->merkleroot;
                cout << "\ntimestamp: " << temp->timestamp;
                cout << "difflvl: " << temp->difflvl;
                cout << "\nnonce: " << temp->nonce;
                cout << "\ntransno: " << temp->transno;
                cout << "\n------------------------------------";
                temp = temp->next;
            }
        }
    }
    int doTrans()
    {
        int item1, item2, item3;
        cout << "\nEnter a price of item 1: ";
        cin >> item1;
        cout << "\nEnter a price of item 2: ";
        cin >> item2;
        cout << "\nEnter a price of item 3: ";
        cin >> item3;
        return (item1 + item2 + item3);
    }
    size_t calcMerkleRoot(vector<size_t> size_tv1, vector<size_t> newsize_tv1)
    {
        size_t merkleint;
        if (size_tv1.size() == 0)
        {
            return 0;
        }
        do
        {
            if (size_tv1.size() % 2 != 0)
            {
                size_tv1.push_back(0);
            }
            for (auto i = size_tv1.begin(); i < size_tv1.end(); i = i + 2)
            {
                auto nxt = i + 1;
                // cout << "\nAddition of :- " << *i << "+" << *nxt;
                merkleint = (*i) + *nxt;
                // cout << "\nAddition:- " << merkleint;
                newsize_tv1.push_back(merkleint);
            }
            size_tv1.clear();
            for (auto j = newsize_tv1.begin(); j != newsize_tv1.end(); j++)
            {
                size_tv1.push_back(*j);
            }
            newsize_tv1.clear();
        } while (size_tv1.size() != 1);
        return merkleint;
    }
};
int main()
{
    int ch, ch1, notrans;
    int difflvl, nonce;
    operation o1;
    size_t merkleRoot;
    string version = "1.0.1";
    vector<int> intv1;
    vector<size_t> size_tv1;
    vector<size_t> newsize_tv1;
    stringstream inttostring;
    hash<string> h1;
    string strtot;
    string timestamp;
    int val;
    time_t now;
    do
    {
        cout << "\n1.Transaction";
        cout << "\n2.Display";
        cout << "\n3.Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            do
            {
                cout << "\n1.Make Transaction";
                cout << "\n2.Exit";
                cout << "\nEnter your choice: ";
                cin >> ch1;
                switch (ch1)
                {
                case 1:
                    val = o1.doTrans();
                    intv1.push_back(val);
                    inttostring.clear();
                    inttostring << val;
                    inttostring >> strtot;
                    // cout << "\nStrtot:- " << strtot;
                    size_tv1.push_back(h1(strtot));
                    break;
                case 2:

                    // for (auto i = size_tv1.begin(); i < size_tv1.end(); i++)
                    // {
                    //     cout << endl
                    //          << *i;
                    // }

                    merkleRoot = o1.calcMerkleRoot(size_tv1, newsize_tv1);
                    // cout << "\nFinally MerkleRoot is:- " << merkleRoot;
                    // intv1.clear();
                    // size_tv1.clear();
                    // newsize_tv1.clear();
                    // cout << "\nExit Successfully";
                    break;
                }
            } while (ch1 != 2);

            cout << "\nEnter difficulty target: ";
            cin >> difflvl;
            nonce = 0;
            now = time(0);
            timestamp = ctime(&now);
            o1.createBlock(version, merkleRoot, timestamp, difflvl, nonce, intv1.size(), intv1);
            intv1.clear();
            size_tv1.clear();
            newsize_tv1.clear();
            break;
        case 2:
            o1.displayBlockChain();
            break;
        case 3:
            break;
        }

    } while (ch != 3);
}