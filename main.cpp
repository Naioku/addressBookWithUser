#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Users
{
    int id;
    string nickname;
    string password;
};

struct Person
{
    int id;
    string name;
    string surname;
    string phone_number;
    string email;
    string address;
};

struct Dimensions
{
    int id_width;
    int name_width;
    int surname_width;
    int phone_number_width;
    int email_width;
    int address_width;
};

void show_users_menu(vector<Users> users_vector);
void register_one_user(vector<Users> &users_vector);
char load_char();
void save_users_to_file(string file_name, vector<Users> &users_vector);
string get_word_from_line_splited_by_character(string &text_line, char splitting_character);
vector<Users> load_users_from_file(string file_name, vector<Users> users_vector);
int give_and_check_log_data(vector<Users> users_vector);

char load_char();
void print_text_in_table(string text, int characters_quantity, string ending);

void show_main_menu(vector<Person> friends);
void show_searching_menu(vector<Person> friends);
void add_friend(vector<Person> &friends, int &people_in_whole_database, int &max_friend_id);
void delete_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting);
string change_name(string name);
string change_surname(string surname);
string change_phone_number(string phone_number);
string change_email(string email);
string change_address(string address);
Person edit_record(Person record, Dimensions setting);
void change_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting);

void print_headers(Dimensions setting);
void show_one_friend(Person record, Dimensions setting);
void search_by_name_and_show(vector<Person> &friends, Dimensions setting, int people_in_whole_database, int max_friend_id);
void search_by_surname_and_show(vector<Person> &friends, Dimensions setting, int people_in_whole_database, int max_friend_id);
void show_all(vector<Person> &friends, Dimensions setting);

void save_friends_to_file(string file_name, vector<Person> friends, int user_id_from_vector, int people_in_whole_database);
string get_first_word_from_line_splited_by_character(string text_line, char splitting_character, int which_word_in_turn_you_want_to_get);
vector<Person> load_friends_from_file(string file_name, vector<Person> friends, int user_id, int &people_in_whole_database, int &max_friend_id);

int main()
{
    vector<Users> users_vector;
    vector<Person> friends_vector;

    string friends_file = "Address_Book_new_format.txt";
    string users_file = "Users.txt";
    users_vector = load_users_from_file(users_file, users_vector);

    Dimensions setting1;
    setting1.id_width = 4;
    setting1.name_width = 20;
    setting1.surname_width = 20;
    setting1.phone_number_width = 12;
    setting1.email_width = 30;
    setting1.address_width = 50;

    // Starting program
    while(true)
    {
        char choice = '0';
        show_users_menu(users_vector);
        choice = load_char();
        cout << endl;
        if (choice == '1') // Logging
        {
            int user_id = give_and_check_log_data(users_vector);
            if (user_id != 0)
            {
                cout << endl << "You're correctly logged in :)" << endl;
                //cout << "Welcome " << users_vector[] << "." << endl;
                int max_friend_id = 0;
                int people_in_whole_database = 0;
                friends_vector.clear();
                friends_vector = load_friends_from_file(friends_file, friends_vector, user_id, people_in_whole_database, max_friend_id);
                system("pause");

                char choice;
                int id;

                while (true)
                {
                    choice = '0';
                    show_main_menu(friends_vector);
                    choice = load_char();
                    cout << endl;
                    if (choice == '1') // Adding new friends
                    {
                        add_friend(friends_vector, people_in_whole_database, max_friend_id);
                        save_friends_to_file(friends_file, friends_vector, user_id, people_in_whole_database);
                        system("pause");
                    }
                    else if (choice == '2') // Searching friends
                    {
                        while (true)
                        {
                            show_searching_menu(friends_vector);
                            choice = load_char();
                            cout << endl;
                            if (choice == '1') // By name
                            {
                                search_by_name_and_show(friends_vector, setting1, people_in_whole_database, max_friend_id);
                                cout << endl;
                                system("pause");
                            }
                            else if (choice == '2') // By surname
                            {
                                search_by_surname_and_show(friends_vector, setting1, people_in_whole_database, max_friend_id);
                                cout << endl;
                                system("pause");
                            }
                            else if (choice == '3') // Show all
                            {
                                show_all(friends_vector, setting1);
                                cout << endl;
                                system("pause");
                            }
                            else if (choice == '9')
                            {
                                break;
                            }
                        }
                    }
                    else if (choice == '3') // Changing record's data
                    {
                        cout << "Enter the id here: ";
                        cin >> id;
                        cout << endl << endl;
                        change_record_with_searching_by_id(friends_vector, id, setting1);
                        cout << endl;
                        save_friends_to_file(friends_file, friends_vector, user_id, people_in_whole_database);
                        system("pause");
                    }
                    else if (choice == '4') // Deleting record's data
                    {
                        cout << "Enter the id here: ";
                        cin >> id;
                        cout << endl << endl;
                        delete_record_with_searching_by_id(friends_vector, id, setting1);
                        cout << endl;
                        save_friends_to_file(friends_file, friends_vector, user_id, people_in_whole_database);
                        system("pause");
                    }
                    else if (choice == '9') // Returning to USERS MENU
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Logging failed. Returning to USERS MENU" << endl << endl;
                system("pause");
            }
        }

        if (choice == '2') // Registration
        {
            register_one_user(users_vector);
            cout << "User has been added." << endl << endl;
            save_users_to_file(users_file, users_vector);
            cout << endl;
            system("pause");
        }

        if (choice == '9')
        {
            exit(0);
            system("pause");
        }
    }

    return 0;
}

//######################################### CRASH SECURITY #########################################

char load_char()
{
    string input_str = "";
    char character  = {0};

    while (true)
    {
        cin.clear();
        cin.sync();
        getline(cin, input_str);

        if (input_str.length() == 1)
        {
            character = input_str[0];
            break;
        }
        cout << "This isn't single character. Please, try again: ";
    }
    return character;
}

void show_users_menu(vector<Users> users_vector)
{
    system("cls");
    cout << "Welcome to address book!"<< endl;
    cout << "Users in database: " << users_vector.size() << endl;
    cout << endl;
    cout << "USERS MENU"<< endl;
    cout << endl;
    cout << "What do you want to do?" << endl;
    cout << "1. Log in" << endl;
    cout << "2. Register" << endl;
    cout << "9. Exit" << endl;
    cout << endl;
    cout << "Your choice: ";
}

//====================================================== USERS MENU ================================================
void register_one_user(vector<Users> &users_vector)
{
    int number_of_users = users_vector.size();
    Users user;
    if (number_of_users != 0)
    {
        vector<Users>::iterator itr = users_vector.end();
        --itr;
        user.id = (*itr).id + 1;
    }
    else user.id = 1;

    while(true)
    {
        cout << "Nickname: ";
        cin.clear();
        cin.sync();
        getline(cin, user.nickname);
        for (int i = 0; i < number_of_users; i++)
        {
            if (user.nickname == users_vector[i].nickname)
            {
                cout << "Nickname already exist. Please, choose another one." << endl;
                user.nickname = "";
                break;
            }
        }
        if (user.nickname != "") break;
    }

    cout << "Password: ";
    cin.clear();
    cin.sync();
    getline(cin, user.password);

    users_vector.push_back(user);
}

int give_and_check_log_data(vector<Users> users_vector)
{
    string nickname, password;
    int number_of_users = users_vector.size();
    int number_of_trials = 0;
    int max_number_of_trials = 3;

    while (number_of_trials < max_number_of_trials)
    {
        bool is_nickname_in_database = false;
        system("cls");
        cout << "LOGING MENU" << endl << endl;
        cout << "Left trials: " << max_number_of_trials - number_of_trials << endl;
        cout << "Nickname: ";
        cin.clear();
        cin.sync();
        getline(cin, nickname);

        cout << "Password: ";
        cin.clear();
        cin.sync();
        getline(cin, password);

        for (int i = 0; i < number_of_users; i++)
        {
            if (nickname == users_vector[i].nickname)
            {
                if (password == users_vector[i].password)
                {
                    return users_vector[i].id;
                }
                else
                {
                    cout << endl << "Password is incorrect." << endl;
                    number_of_trials++;
                    system("pause");
                }
                is_nickname_in_database = true;
            }
        }
        if (is_nickname_in_database == false)
        {
            char answer;
            cout << endl << "Nickname doesn't exist in our database. Want to leave LOGING MENU? (y = yes)" << endl;
            cout << "Your answer: ";
            answer = load_char();
            if (answer == 'y') break;
        }
    }

    return 0;
}

void save_users_to_file(string file_name, vector<Users> &users_vector)
{
    cout << "Saving data to file..." << endl;
    int users_in_database = users_vector.size();
    fstream file;
    file.open(file_name, ios::out);

    for (int index = 0; index < users_in_database; index++)
    {
        file << users_vector[index].id << "|";
        file << users_vector[index].nickname << "|";
        file << users_vector[index].password << "|" << endl;
    }
    file.close();
    cout << "...completed." << endl;
}

vector<Users> load_users_from_file(string file_name, vector<Users> users_vector)
{
    cout << "Loading data from file..." << endl;
    Users user;
    char splitting_character = '|';
    string word;
    fstream file;
    string line;
    int quantity_of_data_in_one_record = 3;
    file.open(file_name, ios::in);
    if (file.good())
    {
        int which_word = 1;
        while(getline(file, line))
        {
            while(line.length() != 0)
            {
                word = get_first_word_from_line_splited_by_character(line, splitting_character, 1);
                line.erase(0, word.length()+1);
                switch(which_word % quantity_of_data_in_one_record)
                {
                    case 1: user.id = atoi(word.c_str()); break;
                    case 2: user.nickname = word; break;
                    case 0: user.password = word; break;
                }
                if (which_word % quantity_of_data_in_one_record == 0)
                {
                    users_vector.push_back(user);
                }

                which_word++;
            }
        }
    }
    file.close();

    cout << "...completed." << endl;

    return users_vector;
}

//====================================================== PEOPLE MENU ================================================

void show_main_menu(vector<Person> friends)
{
    system("cls");
    cout << "Welcome to address book!"<< endl;
    cout << "People in your database: " << friends.size() << endl;
    cout << endl;
    cout << "MAIN MENU"<< endl;
    cout << endl;
    cout << "What do you want to do?" << endl;
    cout << "1. Add friend" << endl;
    cout << "2. Search friend(s)..." << endl;
    cout << "3. Change record's data" << endl;
    cout << "4. Delete record's data" << endl;
    cout << "9. LOG OUT and back to USERS MENU" << endl;
    cout << endl;
    cout << "Your choice: ";
}
void show_searching_menu(vector<Person> friends)
{
    system("cls");
    cout << "SEARCHING MENU" << endl;
    cout << endl;
    cout << "1. ...by name" << endl;
    cout << "2. ...by surname" << endl;
    cout << "3. Show all!" << endl;
    cout << "9. Back to MAIN MENU" << endl;
    cout << endl;
    cout << "Your choice: ";
}


//######################################### ADDING PEOPLE #########################################

void add_friend(vector<Person> &friends, int &people_in_whole_database, int &max_friend_id)
{
    Person record;
    cout << "Please, write data in." << endl;

    cout << "Name: ";
    cin.clear();
    cin.sync();
    getline(cin, record.name);

    cout << "Surname: ";
    cin.clear();
    cin.sync();
    getline(cin, record.surname);

    cout << "Phone number: ";
    cin.clear();
    cin.sync();
    getline(cin, record.phone_number);

    cout << "E-mail address: ";
    cin.clear();
    cin.sync();
    getline(cin, record.email);

    cout << "Address for correspondence: ";
    cin.clear();
    cin.sync();
    getline(cin, record.address);

    record.id = ++max_friend_id;

    friends.push_back(record);
    people_in_whole_database++;
}

//######################################### DELETING PEOPLE #########################################

void delete_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting)
{
    string answer;
    string deleting_answer = "n";
    string existence = "NO";
    Person record;

    print_headers(setting);
    for (vector<Person>::iterator itr = friends.begin(), stop = friends.end(); itr != stop; ++itr)
    {
        if (id == (*itr).id)
        {
            record = (*itr);
            show_one_friend(record, setting);
            cout << endl << "Is this record, which you are looking for?" << endl;
            cout << "Answer (y/n): ";
            cin >> answer;
            cout << endl;

            if (answer == "y")
            {
                existence = "YES";
                cout << "Are you sure you want to DELETE this record?(y/n)";
                cin >> deleting_answer;
                if (deleting_answer == "y")
                {
                    friends.erase(itr);
                    cout << "Deleting completed successfully!" << endl;
                }
            }
        }
    }

    if (existence == "NO") cout << "That's all you have in the book." << endl;
}


//######################################### CHANGING RECORDS #########################################

string change_name(string name)
{
    cout << "New name: ";
    cin >> name;
    return name;
}

string change_surname(string surname)
{
    cout << "New surname: ";
    cin >> surname;
    return surname;
}

string change_phone_number(string phone_number)
{
    cout << "New phone_number: ";
    cin >> phone_number;
    return phone_number;
}

string change_email(string email)
{
    cout << "New email: ";
    cin >> email;
    return email;
}

string change_address(string address)
{
    cout << "New address: ";
    cin >> address;
    return address;
}

Person edit_record(Person record, Dimensions setting)
{
    while (true)
    {
        char answer;
        system("cls");
        print_headers(setting);
        show_one_friend(record, setting);
        cout << endl;
        cout << "What do you want to change?" << endl;
        cout << "1. Name" << endl;
        cout << "2. Surname" << endl;
        cout << "3. Phone number"<< endl;
        cout << "4. Email" << endl;
        cout << "5. Address for correspondence" << endl;
        cout << "9. Back to main menu" << endl;
        cout << "Answer: ";
        answer = load_char();

        if (answer == '1')
        {
            record.name = change_name(record.name);
            return record;
        }
        else if (answer == '2')
        {
            record.surname = change_surname(record.surname);
            return record;
        }
        else if (answer == '3')
        {
            record.phone_number = change_phone_number(record.phone_number);
            return record;
        }
        else if (answer == '4')
        {
            record.email = change_email(record.email);
            return record;
        }
        else if (answer == '5')
        {
            record.address = change_address(record.address);
            return record;
        }
        else if (answer == '9') return record;

    }
}

void change_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting)
{
    int people_in_database = friends.size();
    string answer;
    string existence = "NO";
    Person record;

    print_headers(setting);
    for (int index = 0; index < people_in_database; index++)
    {
        if (id == friends[index].id)
        {
            record = friends[index];
            show_one_friend(record, setting);
            cout << endl << "Is this record, which you are looking for?" << endl;
            cout << "Answer (y/n): ";
            cin >> answer;
            cout << endl;

            if (answer == "y")
            {
                existence = "YES";
                record = edit_record(record, setting);
                friends[index] = record;
                cout << "Changing completed successfully!" << endl;
            }
        }

    }

    if (existence == "NO") cout << "That's all you have in the book." << endl << endl;
}

//######################################### SHOWING PEOPLE IN TABLE #########################################

void print_text_in_table(string text, int characters_quantity, string ending = "|")
{
    int text_length = text.length();
    string result;
    if (text_length < characters_quantity)
    {
        int space_char_quantity = characters_quantity - text_length;
        string space = "";
        for (int i = 0; i < space_char_quantity; i++)
        {
            space += " ";
        }

        result = text + space + ending;
    }
    else
    {
        result = text + ending;
    }
    cout << result;

}

void print_headers(Dimensions setting)
{
    print_text_in_table("id", setting.id_width);
    print_text_in_table("Name", setting.name_width);
    print_text_in_table("Surname", setting.surname_width);
    print_text_in_table("Phone number", setting.phone_number_width);
    print_text_in_table("Email address", setting.email_width);
    print_text_in_table("Address for correspondence", setting.address_width, "\n");
    string underscore = "";
    int widths_plus_functions_quantity = 132 + 5;
    for (int i = 0; i < widths_plus_functions_quantity; i++)
    {
        underscore += "=";
    }
    cout << underscore << endl;
}

void show_one_friend(Person record, Dimensions setting)
{
    print_text_in_table(to_string(record.id), setting.id_width);
    print_text_in_table(record.name, setting.name_width);
    print_text_in_table(record.surname, setting.surname_width);
    print_text_in_table(record.phone_number, setting.phone_number_width);
    print_text_in_table(record.email, setting.email_width);
    print_text_in_table(record.address, setting.address_width, "\n");
}

//######################################### SEARCHING PEOPLE #########################################

void search_by_name_and_show(vector<Person> &friends, Dimensions setting, int people_in_whole_database, int max_friend_id)
{
    int people_in_user_database = friends.size();
    string name;
    string existence = "NO";
    string answer;
    Person record;

    cout << "Name: ";
    cin >> name;
    cout << endl << endl;

    print_headers(setting);
    for (int index = 0; index < people_in_user_database; index++)
    {
        if (name == friends[index].name)
        {
            record = friends[index];
            show_one_friend(record, setting);
            existence = "YES";
        }

    }
    if (existence == "NO")
    {
        cout << endl << "There is no one with that name. Want to add? (y/n)" << endl;
        cin >> answer;

        if (answer == "y")
        {
            add_friend(friends, people_in_whole_database, max_friend_id);
        }
    }
}

void search_by_surname_and_show(vector<Person> &friends, Dimensions setting, int people_in_whole_database, int max_friend_id)
{
    int people_in_user_database = friends.size();
    string surname;
    string existence = "NO";
    string answer;
    Person record;

    cout << "Surname: ";
    cin >> surname;
    cout << endl << endl;

    print_headers(setting);
    for (int index = 0; index < people_in_user_database; index++)
    {
        if (surname == friends[index].surname)
        {
            record = friends[index];
            show_one_friend(record, setting);
            existence = "YES";
        }

    }
    if (existence == "NO")
    {
        cout << endl << "There is no one with that name. Want to add? (y/n)" << endl;
        cin >> answer;
        if (answer == "y")
        {
            add_friend(friends, people_in_whole_database, max_friend_id);
        }
    }
}

void show_all(vector<Person> &friends, Dimensions setting)
{
    int people_in_user_database = friends.size();
    Person record;
    print_headers(setting);

    for (int index = 0; index < people_in_user_database; index++)
    {
        record = friends[index];
        show_one_friend(record, setting);
    }
}

//######################################### SAVING AND LOADING #########################################

string get_first_word_from_line_splited_by_character(string text_line, char splitting_character, int which_word_in_turn_you_want_to_get)
{
    string word = "";

    int character_position = 0;
    char character = text_line[character_position];

    while (character != splitting_character)
    {
        word += character;
        character_position++;
        character = text_line[character_position];
    }
    text_line.erase(0, character_position + 1);

    if(which_word_in_turn_you_want_to_get == 1) return word;
    else if(1 < which_word_in_turn_you_want_to_get) return get_first_word_from_line_splited_by_character(text_line, splitting_character, which_word_in_turn_you_want_to_get - 1);
}

void save_friends_to_file(string file_name, vector<Person> friends, int user_id_from_vector, int people_in_whole_database)
{
    cout << "Saving data to file..." << endl;
    int people_in_user_database = friends.size();
    char splitting_character = '|';
    string temp_file_name = get_first_word_from_line_splited_by_character(file_name, '.', 1) + "_temporary.txt";
    bool is_getline_true = true;
    string main_file_line;
    fstream main_file, temp_file;
    main_file.open(file_name, ios::in);
    temp_file.open(temp_file_name, ios::out);

    cout << "people_in_whole_database 1: " << people_in_whole_database << endl;

    int vector_index = 0;
    for(int i = 0; i < people_in_whole_database; i++)
    {
        cin.clear();
        cin.sync();
        if (getline(main_file, main_file_line))
        {
            is_getline_true = true;
        }
        else
        {
            is_getline_true = false;
        }

        int user_id_from_main_file = atoi(get_first_word_from_line_splited_by_character(main_file_line, splitting_character, 2).c_str());
        if (((user_id_from_vector == user_id_from_main_file) || (is_getline_true == false)) && (vector_index < people_in_user_database))
        {
            temp_file << friends[vector_index].id << splitting_character;
            temp_file << user_id_from_vector << splitting_character;
            temp_file << friends[vector_index].name << splitting_character;
            temp_file << friends[vector_index].surname << splitting_character;
            temp_file << friends[vector_index].phone_number << splitting_character;
            temp_file << friends[vector_index].email << splitting_character;
            temp_file << friends[vector_index].address << splitting_character << endl;

            vector_index++;
        }
        else
        {
            temp_file << main_file_line << endl;
        }
    }

    cout << "people_in_whole_database 2: " << people_in_whole_database << endl;

    temp_file.close();
    main_file.close();

    temp_file.open(temp_file_name, ios::in);
    main_file.open(file_name, ios::out);

    string text_line = "";
    while (getline(temp_file, text_line))
    {
        main_file << text_line << endl;
    }

    temp_file.close();
    main_file.close();
    remove(temp_file_name.c_str());

    cout << "...completed." << endl;

}

vector<Person> load_friends_from_file(string file_name, vector<Person> friends, int user_id, int &people_in_whole_database, int &max_friend_id)
{
    cout << "Loading data from file..." << endl;
    Person record;
    int user_id_from_file;
    char splitting_character = '|';
    string word;
    fstream file;
    string line;
    int quantity_of_data_in_one_record = 7;
    file.open(file_name, ios::in);
    if (file.good())
    {
        int which_word = 1;
        while(getline(file, line))
        {
            while(line.length() != 0)
            {
                word = get_first_word_from_line_splited_by_character(line, splitting_character, 1);
                line.erase(0, word.length()+1);
                switch(which_word % quantity_of_data_in_one_record)
                {
                    case 1: record.id = atoi(word.c_str());           break;
                    case 2: user_id_from_file = atoi(word.c_str());   break;
                    case 3: record.name = word;                       break;
                    case 4: record.surname = word;                    break;
                    case 5: record.phone_number = word;               break;
                    case 6: record.email = word;                      break;
                    case 0: record.address = word;                    break;
                }
                if (which_word % quantity_of_data_in_one_record == 0)
                {
                    if (user_id_from_file == user_id)
                    {
                        friends.push_back(record);
                    }
                    if (max_friend_id < record.id)
                        {
                            max_friend_id = record.id;
                        }
                    people_in_whole_database++;
                }
                which_word++;
            }
        }
    }
    file.close();


    cout << "...completed." << endl << endl;

    return friends;
}
