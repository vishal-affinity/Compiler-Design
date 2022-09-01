//implementation of Symbol Table using Hash Table

#include <iostream>

using namespace std;

const int MAX = 100;

class Node {

    string identifier, scope, type;
    int lineNo;
    Node* next;

public:
    Node()
    {
        next = NULL;
    }

    Node(string key, string value, string type, int lineNo)
    {
        this->identifier = key;
        this->scope = value;
        this->type = type;
        this->lineNo = lineNo;
        next = NULL;
    }

    void print()
    {
        cout<<"Identifier's Name: "<<identifier<<"\nType: "<<type<<"\nScope: "<<scope<<"\nLine Number: "<<lineNo<<endl;
    }


    friend class SymbolTable;
};

class SymbolTable
{
    Node* head[MAX];

public:
    SymbolTable()
    {
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }

    int hashf(string id) // hash function
    {
        int asciiSum = 0;

        for (int i = 0; i < id.length(); i++)
        {
            asciiSum = asciiSum + id[i];
        }

        return (asciiSum % 100);

    }


    bool insert(string id, string scope,string Type, int lineno)
    {
        int index = hashf(id);
        Node* p = new Node(id, scope, Type, lineno);

        if (head[index] == NULL)
        {
            head[index] = p;
            cout<< "\n"<<id<<" inserted ";
            return true;
        }
        else
        {
            Node* start = head[index];
            while (start->next != NULL)
                start = start->next;
            start->next = p;
            cout<<"\n"<<id<<" inserted ";
            return true;
        }

        return false;

    }

    string find(string id)
    {
        int index = hashf(id);
        Node* start = head[index];

        if (start == NULL)
            return "-1";

        while(start != NULL)
        {

            if (start->identifier == id)
            {
                start->print();
                return start->scope;
            }

            start = start->next;
        }

        return "-1";
    }

    bool deleteRecord(string id)
    {
        int index = hashf(id);
        Node* tmp = head[index];
        Node* par = head[index];

        if (tmp == NULL)                    // no identifier is present at that index
        {
            return false;
        }
        if (tmp->identifier == id && tmp->next == NULL)         //only one identifier is present
        {
            tmp->next = NULL;
            delete tmp;
            return true;
        }

        while (tmp->identifier != id && tmp->next != NULL)
        {
            par = tmp;
            tmp = tmp->next;
        }
        if (tmp->identifier == id && tmp->next != NULL)
        {
            par->next = tmp->next;
            tmp->next = NULL;
            delete tmp;
            return true;
        }
        else                                                    // delete at the end
        {
            par->next = NULL;
            tmp->next = NULL;
            delete tmp;
            return true;
        }
        return false;
    }

    bool modify(string id, string Scope,string Type, int lineno)
    {
        int index = hashf(id);
        Node* start = head[index];

        if (start == NULL)
            return "-1";

        while (start != NULL) {
            if (start->identifier == id)
            {
                start->scope = Scope;
                start->type = Type;
                start->lineNo = lineno;
                return true;
            }
            start = start->next;
        }

        return false;
    }
};

int main ()
{

    SymbolTable st;
    string check;
    cout << "**** SYMBOL_TABLE ****\n";
  
    // insert 'if'
    if (st.insert("if", "local", "keyword", 4))
        cout <<" successfully"<<endl;
    else
        cout <<"Failed to insert.\n";

    //insert 'else'
    if(st.insert("else", "local", "keyword", 7))
        cout<<" successfully"<<endl;
    else
        cout<<"Failed to insert."<<endl;

    // insert 'number'
    if (st.insert("number", "global", "variable", 2))
        cout << " successfully"<<endl;
    else
        cout << "Failed to insert\n";

    // insert 'int'
    if (st.insert("int", "local", "keyword", 5))
        cout << " successfully"<<endl;
    else
        cout << "Failed to insert\n";
    bool ans = true;
    while(ans)
    {
        int choice;
        cout<<endl<<"1.Insert"<<endl<<"2.Find"<<endl<<"3.Modify"<<endl<<"4.Delete"<<endl<<"5.exit"<<endl;
        cout<<"Enter your choice ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                string id1;
                string scope1;
                string type1;
                int line1; 
                cout<<"Enter the ID ";
                cin>>id1;
                cout<<endl<<"Enter the Scope ";
                cin>>scope1;
                cout<<endl<<"Enter the Type ";
                cin>>type1;
                cout<<endl<<"Enter the line No. ";
                cin>>line1;
                cout<<endl;

                if (st.insert(id1,scope1,type1,line1))
                    cout << " successfully\n";
                else
                    cout << "\nFailed to insert\n";
                
                string result;

                cout<<"Do you want to continue (Enter y/n ) ";
                cin>>result;
                if(result == "y")
                    ans = true;
                else
                    ans = false;

                break;
            }

            case 2:
            {
                string id2;
                cout<<"Enter the string to find "<<endl;
                cin>>id2;
                cout<<endl;
                check = st.find(id2);
                if (check != "-1")
                    cout << " Identifier Is present\n";
                else
                    cout << " Identifier Not Present\n";

                string result;

                cout<<"Do you want to continue (Enter y/n ) ";
                cin>>result;
                if(result == "y")
                    ans = true;
                else
                    ans = false;

                break;
            }

            case 3:
            {
                string id3;
                string scope2;
                string type2;
                int line2;
                cout<<"Enter the ID ";
                cin>>id3;
                cout<<endl<<"Enter the Scope ";
                cin>>scope2;
                cout<<endl<<"Enter the Type ";
                cin>>type2;
                cout<<endl<<"Enter the line No. ";
                cin>>line2;
                cout<<endl;

                if (st.modify(id3, scope2, type2, line2))
                    cout <<endl<<id3<<" Identifier updated\n";

                string result;

                cout<<"Do you want to continue (Enter y/n ) ";
                cin>>result;
                if(result == "y")
                    ans = true;
                else
                    ans = false;
                
                break;
            }

            case 4:
            {
                string id4;
                cout<<"Enter the string to delete "<<endl;
                cin>>id4;

                if (st.deleteRecord(id4))
                    cout <<id4<<" Identifier is deleted\n";
                else
                    cout << "\nFailed to delete\n";

                string result;

                cout<<"Do you want to continue (Enter y/n ) ";
                cin>>result;
                if(result == "y")
                    ans = true;
                else
                    ans = false;

                break;
            }

            case 5:
            {
                exit(0);

                string result;

                cout<<"Do you want to continue (Enter y/n ) ";
                cin>>result;
                if(result == "y")
                    ans = true;
                else
                    ans = false;
            }

            default:
            {
                cout<<"Please choose the correct choice"<<endl;
                string result;
                cout<<"Press y to continue or n to exit ";
                cin>>result;
                if(result == "y")
                    ans = true;
                else
                    ans = false;
            }
        }
    }    

    return 0;
}
