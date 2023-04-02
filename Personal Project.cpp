#include<bits/stdc++.h>
using namespace std;

vector<int> myvec, new_line_base_index, line_length, dhara;    //vector<int> myvec keep line found data  //str1 for importing data to file
string str0, str1, str2, searching_for;                 //str0 for exporting data from file
int n=1, choice, choice1, choice2, flag = 0, line_count=1, appearance_count=0, sum_line_length = 0;


class student
{
public:

    string name;
    string id;
    string hsc_batch;


    string prevent_empty(string var)
    {
        bool more = true;
        string something;
        while (more)
        {
            getline(cin, something);

            if (something.empty())
            {
                cout<<"\aNothing Inputed! Again input "<<var<<" here: ";
            }
            else
            {
                more = false;
            }
        }

        return something;
    }


    int singular_result(int initial, int limiter)
    {
        dhara.clear();

        for(int i=1; i<=line_count; i=i+limiter)
        {
            dhara.push_back(i);
        }

        for(int i=0; i<dhara.size(); i++)
        {
            if(initial>=dhara[i] && initial<dhara[i+1])
            {
                initial = dhara[i];
            }
        }
        return initial;
    }
};

student s;


void read_file()
{
    ifstream my_read_file("filename.txt");
    if(my_read_file)    //(took from internet)
    {
        ostringstream ss;
        ss << my_read_file.rdbuf();   // reading data  //Copy data from file to str0 variable
        str0 = ss.str();     //Here, .str() is a function or keyword. not variable
    }
    my_read_file.close();
}


void write_file(string things_to_write)
{
    if(str0=="")    //if else using for solving additional \n problem
    {
        // Create and open a text file
        ofstream my_write_file("filename.txt", ios::app);   //ios::app using for appending
        // Write to the file
        my_write_file<<things_to_write;
        // Close the file
        my_write_file.close();
    }

    else
    {
        ofstream my_write_file("filename.txt", ios::app);
        // Write to the file
        my_write_file<<endl<<things_to_write;
        // Close the file
        my_write_file.close();
    }
}


input_data()
{
    str1.clear();       //emptying string for fresh inputing and appending

    cout<<"Student name: ";
    s.name = s.prevent_empty("name");
    str1.append("Name: ");
    str1.append(s.name);


    cout<<"ID: ";
    s.id = s.prevent_empty("ID");
    str1.append("\nID: ");
    str1.append(s.id);


    cout<<"HSC year: ";
    s.hsc_batch = s.prevent_empty("HSC year");
    str1.append("\nHSC batch: ");
    str1.append(s.hsc_batch);

    write_file(str1);   //write all together, multiple writing can be a failure to create dataset
}


void print_string()
{
    if(str0=="")
        cout<<"<<The file is empty>>\n";
    else
        cout<<"These data are import from the particular file:\n"<<str0;
}


void clear_file()     //without appending cause reset file
{
    ofstream my_write_file("filename.txt");
    my_write_file<<"";
    my_write_file.close();

    str0.clear();

    cout<<"All data erased\n";
}


void search_algo()
{
    myvec.clear();
    new_line_base_index.clear();
    line_length.clear();

    flag=0;
    line_count=1;
    appearance_count=0;     //reset variables

    cout <<"---------------Menu------------------\n\
Press 1 for search by ID number.\n\
Press 2 for search by name.\n\
Enter your choice: ";
    cin>>choice1;
    cin.ignore();   //prevent int string getline \n keyboard buffer


    cout<<"Insert Keyword: ";
    getline(cin, searching_for);

    for(int i=0; i<(str0.size()); i++)
    {
        if(str0[i] == '\n')
        {
            line_count = line_count + 1;
            new_line_base_index.push_back(i);
        }

        if(str0.substr(i, searching_for.size()) == searching_for)
        {

            myvec.push_back(line_count);  //storing data which line search found
            flag = 1;
            appearance_count = appearance_count + 1;
            i = i + (searching_for.size()-1);
        }
    }

}


void search_file()
{
    if(flag == 1)
    {
        cout<<searching_for<<" found at line ";

        for (int i=0; i<myvec.size(); i++)
        {
            cout<<myvec[i]<<", ";

        }
    }

    if(flag == 0)
    {
        cout<<searching_for<<" not found anywhere!"<<endl;
    }

    cout<<"\nTotal line number: "<<line_count<<endl;
    cout<<searching_for<<" total appearance time(s): "<<appearance_count<<endl;


    line_length.push_back(new_line_base_index[0]+1);    //for first line only
    //cout<<str0.substr(0, line_length[0]);
    for (int i=0; i<new_line_base_index.size()-1; i++)    //for rest of the lines except last
    {
        line_length.push_back(new_line_base_index[i+1] - new_line_base_index[i]);
    }

    line_length.push_back(str0.size()-1 - new_line_base_index[new_line_base_index.size()-1]);    //for last line only


    switch(choice1)
    {

    case 1:

        if(flag == 1)
        {
            cout<<"\nIndividual details:\n";

            for (int i=0; i<myvec.size(); i++)
            {

                int initial = myvec[i]-1, limiter = 3;      //myvec[i]-1 cause strat 'from 1'    //range the line to be shown

                for (int i=(initial-2); i<(initial-2)+limiter; i++)    //here i start 'from -1' but initial strat 'from 1' //so difference is 2, that is why '-2'
                {
                    if(i == -1)
                        cout<<i+2<<": "<<str0.substr(0, line_length[i+1]);
                    else
                    {
                        if(i==(initial-2)+limiter-1)
                            cout<<i+2<<": "<<str0.substr(new_line_base_index[i]+1, line_length[i+1]-1);
                        else
                            cout<<i+2<<": "<<str0.substr(new_line_base_index[i]+1, line_length[i+1]);

                    }
                }
            }
        }

        break;

    case 2:

        if(flag == 1)
        {

            for (int j=0; j<myvec.size(); j++)
            {
                cout<<"\nIndividual details: "<<j+1<<endl;
                int initial = myvec[j], limiter = 3;      //myvec[i]-1 cause strat 'from 1'    //range the line to be shown

                for (int i=(initial-2); i<(initial-2)+limiter; i++)    //here i start 'from -1' but initial strat 'from 1' //so difference is 2, that is why '-2'
                {
                    if(i == -1)
                        cout<<i+2<<": "<<str0.substr(0, line_length[i+1]);
                    else
                    {
                        if(i==(initial-2)+limiter-1 && j==myvec.size()-1)
                            cout<<i+2<<": "<<str0.substr(new_line_base_index[i]+1, line_length[i+1]-1);
                        else
                            cout<<i+2<<": "<<str0.substr(new_line_base_index[i]+1, line_length[i+1]);

                    }
                }
            }
        }

        break;

    }

}


void edit_file()
{
    if(flag == 1)
    {
        int initial, limiter = 1;
        cout<<"\nInput the line number which you want to edit: ";
        cin>>initial;
        cin.ignore();
        cout<<"\nEdit: ";
        getline(cin, str2);

        for (int i=(initial-2); i<(initial-2)+limiter; i++)    //here i start 'from -1' but initial strat 'from 1' //so difference is 2, that is why '-2'
        {
            if(i == -1)
                str0.replace(0, line_length[i+1]-1, str2);      //line_length[]-1 because wanted to reserve '\n' in the end
            else
                str0.replace(new_line_base_index[i]+1, line_length[i+1]-1, str2);
        }

        // Create and open a text file
        ofstream my_write_file("filename.txt");
        // Write to the file
        my_write_file<<str0;        //rewrite file
        // Close the file
        my_write_file.close();

    }

}


void delete_specific()
{
    if(flag == 1)
    {
        int initial, limiter = 3;
        cout<<"\nInput any line number to delete: ";
        cin>>initial;
        cin.ignore();

        initial = s.singular_result(initial, limiter);

        for(int i=initial-1; i<initial-1+limiter; i++)
        {
            sum_line_length = sum_line_length + line_length[i];
        }


        if(initial==1)      // first line
            str0.erase(0, sum_line_length);

        else if(initial==line_count-(limiter-1))     // last line  15-2=13
            str0.erase(new_line_base_index[initial-2], sum_line_length+1);

        else
            str0.erase(new_line_base_index[initial-2]+1, sum_line_length);


        // Create and open a text file
        ofstream my_write_file("filename.txt");
        // Write to the file
        my_write_file<<str0;        //rewrite file
        // Close the file
        my_write_file.close();
    }
}


int main()
{

    while(1)
    {
        system("cls");
        cout <<"---------------Menu------------------\n\
Press 1 for input student data to store in the file.\n\
Press 2 for view all data from the file.\n\
Press 3 for delete all data from the file.\n\
Press 4 for search and delete or edit specific data from the file.\n\
Press 0 for exit\n\nEnter your choice: ";
        cin>>choice;
        cin.ignore();   //prevent int string getline \n keyboard buffer
        switch(choice)
        {

        case 1:
            system("cls");
            cout<<"You have chosen option input student data.\n\n";
            read_file();
            input_data();
            cout<<"\nPress enter key to continue...";
            cin.ignore();
            break;

        case 2:
            system("cls");
            cout<<"You have chosen view all data from the file.\n\n";
            read_file();
            print_string();
            cout<<"\nPress enter key to continue...";
            cin.ignore();
            break;

        case 3:
            system("cls");
            cout<<"You have chosen delete all data.\n\n";
            clear_file();
            cout<<"\nPress enter key to continue...";
            cin.ignore();   //pause from infinite loop
            break;

        case 4:
            system("cls");
            //cout<<"You have chosen option search or edit specific data from the file.\n\n";
            read_file();
            search_algo();
            search_file();

            while(n)
            {
                if(flag == 1)
                {
                    cout <<"\n\n\
Press 1 for edit.\n\
Press 2 for specific delete.\n\
Press 0 for exit.\n\
Enter your choice: ";
                    cin>>choice2;
                    cin.ignore();

                    switch(choice2)
                    {
                    case 1:
                        edit_file();
                        cout<<"\nPress enter key to continue...";
                        cin.ignore();
                        continue;
                        break;

                    case 2:
                        delete_specific();
                        cout<<"\nPress enter key to continue...";
                        cin.ignore();
                        continue;
                        break;

                    case 0:
                        n=0;        //exit from infinite loop
                        continue;   //back to main menu
                        break;

                    default:
                        cout<<"INVALID INPUT!";
                        cin.ignore();
                        continue;
                        break;
                    }
                }
            }
            cout<<"\nPress enter key to continue...";
            cin.ignore();
            break;

        case 0:
            cout<<"You have chosen EXIT.";
            cout<<"\n\n\nThis program is made by:\nMd. Fahim Faisal Sami\n\
Dhaka International University\nCSE (1st shift), Batch: 62, Roll: 59";

            exit(0);

        default:
            cout<<"INVALID INPUT!";
            cin.ignore();
            break;
        }
    }

    return 0;
}
