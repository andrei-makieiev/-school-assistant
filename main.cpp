#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

// Определение структуры User
struct User
{
    string firstName;
    string lastName;
    string phoneNumber;
    string address;
};

// Функция для сохранения списка пользователей в файл
void saveUsersToFile(const vector<User>& users, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }

    for (const auto& user : users) {
        file << user.firstName << "\n"
             << user.lastName << "\n"
             << user.phoneNumber << "\n"
             << user.address << "\n";
    }
    file.close();
    cout << "Данные сохранены в файл.\n";
}

void saveUserNameToFile(const string& user_name, const string& userNameFile) {
    ofstream file(userNameFile);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }

    file << user_name << "\n";

    file.close();
    cout << "Имя пользователя сохранено в файл.\n";
}

// Функция для загрузки списка пользователей из файла
void loadUsersFromFile(vector<User>& users, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    User user;
    while (getline(file, user.firstName) &&
           getline(file, user.lastName) &&
           getline(file, user.phoneNumber) &&
           getline(file, user.address)) {
        users.push_back(user);
    }

    file.close();
    cout << "\n";
}
void loadUserNameFromFile(string& user_name, const string& userNameFile) {
    ifstream file(userNameFile);

    // Проверка существования файла и чтение имени
    if (file.is_open()) {
        getline(file, user_name);
        file.close();
    }

    // Если имя пустое или файл не существует
    if (user_name.empty()) {
        cout << "Введите свое имя: ";
        getline(cin, user_name);
        std::cout <<""<< std::endl;
        std::cout << "Привет " << user_name << "! Я твоя программа помогатор, выбери пункт из меню и я с радостью тебе помогу)))" << std::endl;

        // Сохранение введенного имени в файл
        ofstream outFile(userNameFile);
        if (outFile.is_open()) {
            outFile << user_name;
            outFile.close();
        } else {
            cout << "Не удалось создать файл для записи.\n";
        }
    } else {
        std::cout << "Привет " << user_name << "! С возвращением !)))" << std::endl;
    }
}

// Определение функции преобразования в верхний регистр
std::unordered_map<string, string> charMap = {
    {"а", "А"}, {"б", "Б"}, {"в", "В"}, {"г", "Г"}, {"д", "Д"}, {"е", "Е"}, {"ё", "Ё"}, {"ж", "Ж"}, {"з", "З"}, {"и", "И"}, {"й", "Й"}, {"к", "К"}, {"л", "Л"}, {"м", "М"}, {"н", "Н"}, {"о", "О"}, {"п", "П"}, {"р", "Р"}, {"с", "С"}, {"т", "Т"}, {"у", "У"}, {"ф", "Ф"}, {"х", "Х"}, {"ц", "Ц"}, {"ч", "Ч"}, {"ш", "Ш"}, {"щ", "Щ"}, {"ь", "Ь"}, {"ы", "Ы"}, {"э", "Э"}, {"ю", "Ю"}, {"я", "Я"}};

string toUpperCase(const string &input)
{
    string result;
    result.reserve(input.size());

    for (size_t i = 0; i < input.size();)
    {
        string symbol;
        if ((input[i] & 0x80) != 0)
        {
            symbol = input.substr(i, 2);
            i += 2;
        }
        else
        {
            symbol = input.substr(i, 1);
            i += 1;
        }
        if (charMap.find(symbol) != charMap.end())
        {
            result += charMap[symbol];
        }
        else
        {
            result += symbol;
        }
    }

    return result;
}

void inputUserData(User &user)
{
    cout << "Введите имя: ";
    getline(cin, user.firstName);

    cout << "Введите фамилию: ";
    getline(cin, user.lastName);

    cout << "Введите телефон: ";
    getline(cin, user.phoneNumber);

    cout << "Введите адрес: ";
    getline(cin, user.address);
}

void displayUserData(const User &user)
{
    cout << "Имя: " << user.firstName << endl;
    cout << "Фамилия: " << user.lastName << endl;
    cout << "Телефон: " << user.phoneNumber << endl;
    cout << "Адрес: " << user.address << endl;
}

// Функция для работы с меню одноклассников
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

bool team_menu(int &team, vector<User> &users)
{
    switch (team)
    {
    case 1:
    {
        User newUser;
        std::cout << "\nВведите данные для нового одноклассника:\n\n";
        inputUserData(newUser);
        users.push_back(newUser);
        std::cout << "\nОдноклассник добавлен успешно!\n";
        return true;
    }
    case 2:
    {
        if (users.empty())
        {
            std::cout << "\nСписок одноклассников пуст.\n";
        }
        else
        {
            std::cout << "\nСписок одноклассников:\n\n";
            for (const auto &user : users)
            {
                displayUserData(user);
                std::cout << "-----------------------------\n";
            }
        }
        return true;
    }
    case 3:
    {
        std::cout << "Напиши имя или фамилию одноклассника, которого хочешь найти: ";
        std::string searchQuery;
        std::getline(std::cin, searchQuery);

        // Убираем лишние пробелы и преобразуем в верхний регистр
        searchQuery = toUpperCase(trim(searchQuery));

        bool found = false;
        for (const auto &user : users)
        {
            // Преобразуем имя и фамилию для сравнения
            if (toUpperCase(trim(user.firstName)) == searchQuery || toUpperCase(trim(user.lastName)) == searchQuery)
            {
                std::cout << "\nОдноклассник найден:\n";
                displayUserData(user);
                std::cout << "-----------------------------\n";
                found = true;
                break; // Если нужно найти только первого совпавшего
            }
        }

        if (!found)
        {
            std::cout << "Одноклассник с таким именем или фамилией не найден.\n";
        }

        return true;
    }
    default:
        return false;
    }
}

// Функция для работы с расписанием
bool schedule_choice(std::string &schedule)
{
    std::string uppercase_item = toUpperCase(schedule);

    if (uppercase_item == "ПОНЕДЕЛЬНИК")
    {
        std::cout << "Расписание на понедельник.\n";
        std::cout << "\n";
        std::cout << "1 - Нету\n";
        std::cout << "2 - Английский язык\n";
        std::cout << "3 - Технологии\n";
        std::cout << "4 - Технологии\n";
        std::cout << "5 - Украинский язык\n";
        std::cout << "6 - Математика\n";
        return true;
    }
    else if (uppercase_item == "ВТОРНИК")
    {
        std::cout << "Расписание на вторник.\n";
        std::cout << "\n";
        std::cout << "1 - Нету\n";
        std::cout << "2 - Информатика\n";
        std::cout << "3 - Математика\n";
        std::cout << "4 - Плавание\n";
        std::cout << "5 - Украинский язык\n";
        std::cout << "6 - Английский язык\n";
        return true;
    }
    else if (uppercase_item == "СРЕДА")
    {
        std::cout << "Расписание на среду.\n";
        std::cout << "\n";
        std::cout << "1 - Математика\n";
        std::cout << "2 - Зарубежная литература\n";
        std::cout << "3 - История\n";
        std::cout << "4 - Биология\n";
        std::cout << "5 - Физ-ра\n";
        std::cout << "6 - Обж\n";
        return true;
    }
    else if (uppercase_item == "ЧЕТВЕРГ")
    {
        std::cout << "Расписание на четверг.\n";
        std::cout << "1 - География\n";
        std::cout << "2 - Украинский язык\n";
        std::cout << "3 - Информатика\n";
        std::cout << "4 - Английский язык\n";
        std::cout << "5 - Математика\n";
        std::cout << "6 - Музыка/творчество\n";
        return true;
    }
    else if (uppercase_item == "ПЯТНИЦА")
    {
        std::cout << "Расписание на пятницу:\n";
        std::cout << "\n";
        std::cout << "1 - Украинская литература\n";
        std::cout << "2 - Математика\n";
        std::cout << "3 - История\n";
        std::cout << "4 - Украинский язык\n";
        std::cout << "5 - Физ-ра\n";
        std::cout << "6 - Английский\n";
        std::cout << "7 - Класный час\n";
        return true;
    }
    else
    {
        std::cout << "Введите корректный день недели на русском, пожалуйста:\n";
        return false;
    }
}
// Главная функция
int main()
{
    vector<User> users;
    std::string user_name;
    std::string schedule;
    int team;
    int main_menu_choice;

     const string filename = "users.txt";
     const string userNameFile = "userName.txt";

    // Загрузка данных из файла при старте программы
    loadUsersFromFile(users, filename);

     loadUserNameFromFile(user_name, userNameFile);

    do
    {
        std::cout << "\n";
        std::cout << "__________Главное меню__________\n";
        std::cout << "\n";
        std::cout << "1. Посмотреть расписание\n2. Одноклассники.\n0. Выход" << std::endl;
        std::cout << "Какой пункт ты выбираешь? ";

        while (!(std::cin >> main_menu_choice))
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Пожалуйста, введите число." << std::endl;
            std::cout << "Какой пункт ты выбираешь? ";
        }

        switch (main_menu_choice)
        {

        case 1:
            std::cout << "\n";
            std::cout << "__________Меню расписания__________\n";
            std::cout << "\n";
            std::cout << "Напиши на какой день ты хочешь расписание ? :";
            std::cin.ignore();
            std::getline(std::cin, schedule);
            std::cout << "\n";
            schedule_choice(schedule);
            std::cout << "\n";
            break;

        case 2:
            std::cout << "\n";
            std::cout << "__________Меню одноклассники__________\n";
            std::cout << "\n";
            std::cout << "1. Добавить одноклассника\n2. Посмотреть список одноклассников.\n3. Найти одноклассника\n";
            std::cout << "\n";
            std::cout << "Выбери действие :";
            std::cout << "\n";
            std::cin >> team;
            std::cin.ignore();
            if (!team_menu(team, users))
            {
                cout << "Попробуйте снова." << endl;
            }
            break;

        case 0:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }

    } while (main_menu_choice != 0);

    // Сохранение данных в файл перед завершением программы
    saveUsersToFile(users, filename);
    saveUserNameToFile(user_name,userNameFile);

    return 0;
}