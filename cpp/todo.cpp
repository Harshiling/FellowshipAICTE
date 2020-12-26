#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class Todo
{
private:
    string getDate()
    {
        /*
           Getting the current date in  YYYY - MM - DD  format
        */
        time_t rawtime;
        tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%F", timeinfo);
        string date = string(buffer);
        return date;
    }

    fstream getFileHandler()
    {
        /*
           Opening a file stream  object and returning the same
        */
        fstream file;
        return file;
    }
    vector<string> readContent(fstream &handler, string fileName)
    {
        /*
           Reading the number of todos in a file and returning it
        */
        vector<string> contents;
        handler.open(fileName, ios::in);
        if (handler.is_open())
        {
            string tp;
            while (getline(handler, tp))
            {
                contents.push_back(tp);
            }
        }
        return contents;
    }

    string removeGiven(int number)
    {
        /*
           Removing the specified todo from todo's list with the number of the same
        */
        fstream file = getFileHandler();
        string item;
        vector<string> contents = readContent(file, "todo.txt");
        file.close();

        file.open("todo.txt", ios::out | ios::trunc);
        file.close();
        file.open("todo.txt", ios::out);
        for (size_t i = 0; i < contents.size(); i++)
        {
            if (i != (size_t)number - 1)
            {
                file << contents.at(i) << endl;
            }
            else
            {
                item = contents[i];
            }
        }
        file.close();
        return item;
    }

    int getContentCount(string fileName)
    {
        /*
           Reading the content (number of todos (assigned or completed) and getting the size of them
        */
        fstream handler;
        return readContent(handler, fileName).size();
    }

    inline bool check(int number)
    {
        /*
           An inline function to check if the number specified by the user is a 0 or greater than number of todos
        */
        return number <= 0 || number > getContentCount("todo.txt");
    }

public:
    void delNumber(int number)
    {
        /*
           Deleting a todo from the todo list
        */
        if (check(number))
        {
            cout << "Error: todo #" << number << " does not exist. Nothing deleted." << endl;
        }
        else
        {
            removeGiven(number);
            cout << "Deleted todo #" << number << endl;
        }
    }
    void add(string item)
    {
        /*
           Adding the todos listed by the user to the todo file
        */
        fstream file = getFileHandler();
        file.open("todo.txt", ios::app);
        file << item << '\n';
        cout << "Added todo:"
             << " " << '"' << item << '"'
             << '\n';
        file.close();
    }
    void ls()
    {
        /*
           Listing the remaining todos
        */
        fstream file = getFileHandler();
        vector<string> contents = readContent(file, "todo.txt");
        if (contents.size() == 0)
        {
            cout << "There are no pending todos!" << endl;
        }
        if (file.is_open())
        {
            for (int i = contents.size() - 1; i >= 0; --i)

            {
                if (contents[i] != "")
                    cout << '[' << i + 1 << ']' << " " << contents[i] << '\n';
            }
        }
        file.close();
    }
    void doneNumber(int number)
    {
        /*
           Marking a todo as done after checking whether that todo number is available
       */
        if (check(number))
        {
            cout << "Error: todo #" << number << " does not exist." << endl;
        }
        else
        {
            fstream dfile = getFileHandler();
            string removed = removeGiven(number);
            dfile.open("done.txt", ios::app);
            string content = "x " + getDate() + " " + removed;
            dfile << content << endl;
            dfile.close();
            cout << "Marked todo #" << number << " as done." << endl;
        }
    }
    void help()
    {
        /*
           Showing the usage of the app
        */
        string usage = "Usage :-\n";
        usage += "$ ./todo add \"todo item\"  # Add a new todo\n";
        usage += "$ ./todo ls               # Show remaining todos\n";
        usage += "$ ./todo del NUMBER       # Delete a todo\n";
        usage += "$ ./todo done NUMBER      # Complete a todo\n";
        usage += "$ ./todo help             # Show usage\n";
        usage += "$ ./todo report           # Statistics\n";
        cout << usage;
    }
    void report()
    {
        /*
           Reporting the pending and completed todos
        */
        string date = getDate();
        cout << date << " Pending : " << getContentCount("todo.txt") << " Completed : " << getContentCount("done.txt") << endl;
    }
};

int main(int argc, char *argv[])
{
    /*
      Below runs as per user's choice over the todo app (add , list , done , del , report , or help)
    */
    Todo t;
    if (argv[1] == NULL || argc < 2 || string(argv[1]) == "help") // try argc == 1
    {
        t.help();
    }
    else
    {
        if (string(argv[1]) == "add")
        {
            if (argc == 2)
            {
                cout << "Error: Missing todo string. Nothing added!" << endl;
            }
            else
            {
                t.add(string(argv[2]));
            }
        }

        else if (string(argv[1]) == "ls")
            t.ls();

        else if (string(argv[1]) == "done")
        {
            if (argc == 2)
            {
                cout << "Error: Missing NUMBER for marking todo as done." << endl;
            }
            else
            {
                t.doneNumber(stoi(string(argv[2])));
            }
        }
        else if (string(argv[1]) == "del")
        {
            if (argc == 2)
            {
                cout << "Error: Missing NUMBER for deleting todo." << endl;
            }
            else
            {
                t.delNumber(stoi(string(argv[2])));
            }
        }
        else if (string(argv[1]) == "report")
            t.report();
    }
    return 0;
}
