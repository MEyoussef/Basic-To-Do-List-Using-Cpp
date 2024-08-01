#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
/*

    This code snippet is a C++ program that implements a basic to-do list application. It allows the user to perform various operations on a text file, such as adding, updating, and deleting tasks.

    Here's a high-level overview of the code:

    The program starts by creating a file stream object and a vector to store user tasks.
    It prompts the user to choose whether they want to check for existing .txt files.
    If the user chooses to check for files, the program prompts the user to enter a file name.
    If the file exists, the program prompts the user to choose an operation (Add, Update, or Delete).
    Depending on the chosen operation, the program performs the corresponding action (adding a new task, updating an existing task, or deleting a task).
    If the user chooses not to check for files, the program prompts the user to enter the number of tasks and a file name.
    The program then prompts the user to enter each task and saves them to the file.
    After the user has finished adding tasks, the program prompts the user to choose whether they want to update or delete any tasks.
    If the user chooses to update tasks, the program prompts the user to select a task to update and asks for the new task.
    If the user chooses to delete tasks, the program prompts the user to select a task to delete.
    Finally, the program displays the updated or deleted tasks and exits.
    The code snippet includes error handling and input validation to ensure that the program runs smoothly and handles user input correctly.

*/
std::string UPDATE = "Update";
std::string DELETE = "Delete";

int main()
{
    // Create a file stream object
    std::ofstream file;
    std::vector<std::string> User_Tasks_Vector;
    std::cout << "== WELCOME TO MY BASIC TO-DO LIST ==" << "\n";
    std::cout << "- - - - - - - - - - - -" << "\n";
    std::string User_Answer = "";
    int RESULT_ERROR_REASON = -1;
    std::cout << "Do You Want to Check For .txt Files (Yes | No) : ";
    std::cin >> User_Answer;
    std::cin.ignore();

    std::cout << "User Answer: " << User_Answer << std::endl;

    if (User_Answer == "Yes")
    {
        std::string File_Name = "";
        std::cout << "Enter File Name (File_Name.txt) : ";
        std::getline(std::cin, File_Name);

        std::cout << "File Name: " << File_Name << std::endl;

        if (std::filesystem::exists(File_Name))
        {
            std::cout << "File Exist!" << "\n";
            std::fstream MyFileContent(File_Name);
            std::cout << "What Do You Want to Do (Add | Update | Delete) : ";
            std::string Operation = "";
            std::cin >> Operation;
            std::cin.ignore();

            std::cout << "Operation: " << Operation << std::endl;

            std::vector<std::string> new_vector; // look at Update Section
            if (Operation == "Add")
            {
                int Number_of_Tasks;
                std::cout << "How Many Tasks ? : ";
                std::cin >> Number_of_Tasks;
                std::cin.ignore();

                std::cout << "Number of Tasks: " << Number_of_Tasks << std::endl;

                if (Number_of_Tasks < 0)
                {
                    std::cout << "Restart Program And Enter a Valid Value (>= 0)" << "\n";
                    return RESULT_ERROR_REASON;
                }
                if (Number_of_Tasks == 0)
                {
                    std::cout << "GoodBye!" << "\n";
                    return 0;
                }
                for (int i = 0; i < Number_of_Tasks; i++)
                {
                    std::string New_Tasks = "";
                    std::cout << "Add New Tasks : ";
                    std::getline(std::cin, New_Tasks);

                    std::cout << "New Task: " << New_Tasks << std::endl;

                    std::ofstream outfile;
                    outfile.open(File_Name, std::ios_base::app); // append
                    outfile << New_Tasks << "\n";
                    outfile.close();
                }
                MyFileContent.close();
            }

            if (Operation == UPDATE)
            {
                std::string str = "";
                std::ifstream ReadFile(File_Name);
                while (std::getline(ReadFile, str))
                {
                    new_vector.push_back(str);
                }
                std::cout << "Enter Task Index to Update (Start From Index 0) : ";
                int Task_Index;
                std::cin >> Task_Index;
                std::cin.ignore();

                std::cout << "Task Index: " << Task_Index << std::endl;

                while (Task_Index < 0 || Task_Index >= new_vector.size())
                {
                    std::cout << "Enter Valid Task Index (Start From Index 0) : ";
                    std::cin >> Task_Index;
                    std::cin.ignore();
                }
                std::cout << "Enter New Task : ";
                std::string new_Task = "";
                std::getline(std::cin, new_Task);

                std::cout << "New Task: " << new_Task << std::endl;

                new_vector[Task_Index] = new_Task;
                file.open(File_Name);
                if (!file.is_open())
                {
                    std::cerr << "Failed to open file: " << File_Name << "\n";
                    return RESULT_ERROR_REASON;
                }
                for (int i = 0; i < new_vector.size(); i++)
                {
                    file << new_vector[i] << "\n";
                }
                file.close();
            }

            if (Operation == DELETE)
            {
                std::cout << "Enter Task Index to Delete (Start From Index 0) : ";
                int Task_index;
                std::cin >> Task_index;
                std::string str = "";
                std::ifstream ReadFile(File_Name);
                while (std::getline(ReadFile, str))
                {
                    new_vector.push_back(str);
                }

                std::cout << "Task Index: " << Task_index << std::endl;

                while (Task_index < 0 || Task_index >= new_vector.size())
                {
                    std::cout << "Enter Valid Index (Start From Index 0) : ";
                    std::cin >> Task_index;
                }
                file.open(File_Name);
                if (!file.is_open())
                {
                    std::cerr << "Failed to open file: " << File_Name << "\n";
                    return RESULT_ERROR_REASON;
                }
                for (int i = 0; i < new_vector.size(); i++)
                {
                    if (i == Task_index)
                    {
                        continue;
                    }
                    file << new_vector[i] << "\n";
                }
                file.close();
            }
        }
        else if (!std::filesystem::exists(File_Name))
        {
            std::cout << "File Doesn't Exist." << "\n";
            return RESULT_ERROR_REASON;
        }
    }
    else if (User_Answer == "No")
    {
        int Number_of_Tasks = 0, i = 1;
        std::cout << "New File Will Be Created - How Many Tasks do You Have : ";
        std::cin >> Number_of_Tasks;

        std::cin.ignore();
        while (Number_of_Tasks < 0 || Number_of_Tasks == 0)
        {
            std::cout << "Enter Valid Number of Tasks >= 1 : ";
            std::cin >> Number_of_Tasks;
            std::cin.ignore();
        }

        std::cout << "Enter a Name to Create a Text File Containing Your Tasks (For Example : MyTasks.txt | NO WHITE SPACES) : ";
        std::string Tasks_File_Name = "";
        std::cin >> Tasks_File_Name;
        std::cin.ignore();

        std::cout << "Tasks File Name: " << Tasks_File_Name << std::endl;

        file.open(Tasks_File_Name, std::ios::out);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << Tasks_File_Name << "\n";
            return RESULT_ERROR_REASON;
        }

        std::cout << "You Have " << Number_of_Tasks << " Tasks to Enter" << "\n";

        while (i <= Number_of_Tasks)
        {
            std::string User_Tasks_Input = "";
            std::cout << "Enter Task Number " << i << " : ";
            std::getline(std::cin, User_Tasks_Input);
            User_Tasks_Vector.push_back(User_Tasks_Input);
            file << User_Tasks_Input << "\n";
            i++;
        }
        file.close();

        std::cout << "\n===========\n\n";
        std::cout << "Do You Want to Update or Delete Any Tasks From Your Task File ? (Update | Delete | No) : ";
        std::string UpdateTasks_AddTasks_DeleteTasks = "";
        std::getline(std::cin, UpdateTasks_AddTasks_DeleteTasks);
        if (UpdateTasks_AddTasks_DeleteTasks == UPDATE)
        {
            std::string chooseOpreation = "";
            std::string ADD = "Add";
            std::cout << "Choose Opreation (Add | Update) : ";
            std::cin >> chooseOpreation;
            if (chooseOpreation != ADD && chooseOpreation != UPDATE)
            {
                while (chooseOpreation != "Add" && chooseOpreation != "Update")
                {
                    std::cout << "Enter Valid Opreation (Add | Update) : ";
                    std::cin >> chooseOpreation;
                    std::cin.ignore();
                }
            }
            if (chooseOpreation == ADD)
            {
                int How_Many_More_tasks = 0;
                std::cout << "How Many Tasks You Need to Add ? : ";
                std::cin >> How_Many_More_tasks;
                std::cin.ignore();
                if (How_Many_More_tasks <= 0)
                {
                    while (How_Many_More_tasks <= 0)
                    {
                        std::cout << "Enter Valid Number of Tasks (1 - 9) : ";
                        std::cin >> How_Many_More_tasks;
                        std::cin.ignore();
                    }
                }
                for (int i = 0; i < How_Many_More_tasks; i++)
                {
                    std::string New_Task = "";
                    std::cout << "Enter New Task : ";
                    std::getline(std::cin, New_Task);
                    User_Tasks_Vector.push_back(New_Task);
                    New_Task = "";
                }
                file.open(Tasks_File_Name, std::ios::out);
                if (!file.is_open())
                {
                    std::cerr << "Failed to open file: " << Tasks_File_Name << "\n";
                    return RESULT_ERROR_REASON;
                }
                for (int i = 0; i < User_Tasks_Vector.size(); i++)
                {
                    file << User_Tasks_Vector[i] << "\n";
                }
                file.close();
                std::cout << "\n====================";
                std::cout << "\n== Your Tasks ==\n";
                std::cout << "====================\n";
                for (std::string &task : User_Tasks_Vector)
                {
                    std::cout << task << "\n";
                }
            }
            if (chooseOpreation == UPDATE)
            {
                int Index_of_Task;
                std::cout << "Enter The Task You Want to Update (Start From Index 0) : ";
                std::cin >> Index_of_Task;
                std::cin.ignore();
                while (Index_of_Task < 0 || Index_of_Task > User_Tasks_Vector.size())
                {
                    std::cout << "Enter Valid Value (Start From Index 0) : ";
                    std::cin >> Index_of_Task;
                    std::cin.ignore();
                }

                std::string Updated_Task = "";
                std::cout << "Enter Your Task to Replace it With Task Number " << Index_of_Task << " : ";
                std::getline(std::cin, Updated_Task);
                User_Tasks_Vector[Index_of_Task] = Updated_Task;
                file.open(Tasks_File_Name, std::ios::out);
                if (!file.is_open())
                {
                    std::cerr << "Failed to open file: " << Tasks_File_Name << "\n";
                    return RESULT_ERROR_REASON;
                }
                std::cout << "\n=============\n";
                std::cout << "Task Number ( " << Index_of_Task << " ) Has Been Updated." << "\n";
                for (int i = 0; i < User_Tasks_Vector.size(); i++)
                {
                    file << User_Tasks_Vector[i] << "\n";
                }
                file.close();
                std::cout << "Your Tasks Are Up-to Date" << "\n";
                for (std::string &task : User_Tasks_Vector)
                {
                    std::cout << task << "\n";
                }
            }
        }
        if (UpdateTasks_AddTasks_DeleteTasks == DELETE)
        {
            int Number_of_Task;
            std::cout << "Choose Task to Delete By it's Index (Start From Index 0) : ";
            std::cin >> Number_of_Task;
            std::cin.ignore();
            while (Number_of_Task > User_Tasks_Vector.size() || Number_of_Task < 0)
            {
                std::cout << "Enter Valid Value (Start From Index 0) : ";
                std::cin >> Number_of_Task;
                std::cin.ignore();
            }
            User_Tasks_Vector.erase(std::next(User_Tasks_Vector.begin() + Number_of_Task - 1));
            file.open(Tasks_File_Name, std::ios::out);
            if (!file.is_open())
            {
                std::cerr << "Failed to open file: " << Tasks_File_Name << "\n";
                return RESULT_ERROR_REASON;
            }
            for (int i = 0; i < User_Tasks_Vector.size(); i++)
            {
                file << User_Tasks_Vector[i] << "\n";
            }
            file.close();
            std::cout << "\n===============\n";
            std::cout << "== Tasks After Deletion ==";
            std::cout << "\n===============\n";
            for (int i = 0; i < User_Tasks_Vector.size(); i++)
            {
                std::cout << "\n"
                          << User_Tasks_Vector[i] << "\n";
            }
        }
        if (UpdateTasks_AddTasks_DeleteTasks == "No")
        {
            std::cout << "Goodbye!" << "\n";
        }
    }
    return 0;
}
