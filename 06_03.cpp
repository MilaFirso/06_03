#include <iostream>

using namespace std;

int find_substring_light_rabin_karp(string& source, string& substring)
{
    int hashCurrent = 0; 
    int hashSearch = 0; 
    bool value = false; // Переменная для определения, нашлось ли совпадение

    // Вычисляем хэш строки, которую нужно найти
    for (int i = 0; i < substring.length(); ++i)
    {
        hashSearch += static_cast<int>(substring[i]);
    }

    // Пробегаем циклом по индексам, которые будем проверять на начало потенциального совпадения с substring
    for (int i = 0; i < source.length() - substring.length(); ++i)
    {
        if (i == 0) // Если это первая итерация, то считаем хэш от первых substring.length() символов
        {
            for (int j = 0; j < substring.length(); ++j)
            {
                hashCurrent += static_cast<int>(source[j]);
            }
        }
        else // Иначе быстро сгенерируем хэш для следующих searchString.length() символов, используя предыдущее значение такого хэша
        {
            hashCurrent -= source[i - 1];
            hashCurrent += source[i + substring.length() - 1];
        }

        if (hashCurrent == hashSearch) // Если хэши совпали, то совпадение следующих substring.length() символов возможно. Проверяем
        {
            for (int j = 0; j < substring.length(); ++j)
            {
                if (source[i + j] == substring[j])
                {
                    value = true;
                }
                else
                {
                    value = false;
                    break;
                }
            }

            if (value)
            {
                return i;
            }
        }
    }

    return -1;
}

int main() {

    setlocale(LC_ALL, "rus");
    system("chcp 1251");

    string source = ""; 
    string substring = ""; 

    cout << "Введите строку, в которой будет осуществляться поиск: ";
    cin >> source;

    while (substring != "exit")
    {
        cout << "Введите подстроку, которую нужно найти: ";
        cin >> substring;

        int index = find_substring_light_rabin_karp(source, substring); // Индекс искомой подстроки
        if (index == -1) 
        {
            cout << "Подстрока " << substring << " не найдена" << endl;
        }
        else 
        {
            cout << "Подстрока " << substring << " найдена по индексу " << index << endl;
        }
    }

    return 0;
}