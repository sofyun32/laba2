#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

// Функция для вывода справки по использованию программы
void print() 
{
    printf("Usage:\n");
    printf("./sed_simplified input.txt -r 'old_regex' 'new_text'\n"); // Замена текста с помощью регулярного выражения
    printf("./sed_simplified input.txt -d 'regex'\n"); // Удаление строк, соответствующих регулярному выражению
    printf("./sed_simplified input.txt -i 'text_to_add_start'\n"); // Добавление текста в начало каждой строки файла
    printf("./sed_simplified input.txt -b 'text_to_add_end'\n"); // Добавление текста в конец каждой строки файла
}

// Главная функция программы
int main(int argc, char *argv[]) 
{
    // Проверяем, достаточно ли аргументов для обработки
    if (argc < 4) 
    {
        print(); // Если аргументов недостаточно, выводим справку
        return 1;
    }

    const char *file_path = argv[1]; // Путь к входному файлу
    const char *option = argv[2]; // Опция для выполнения операции

    // Обработка параметров для замены текста с помощью регулярного выражения
    if (argc == 5 && strcmp(option, "-r") == 0 ) 
    {
        replace_text_regex(file_path, argv[3], argv[4]); // Вызываем функцию замены текста
    } 
    // Обработка параметров для удаления строк
    else if (argc == 4 && strcmp(option, "-d") == 0) 
    {
        delete_lines_regex(file_path, argv[3]); // Вызываем функцию удаления строк
    } 
    // Обработка параметров для добавления текста в начало строк
    else if (argc == 4 && strcmp(option, "-i") == 0) 
    {
        text_start(file_path, argv[3]); // Вызываем функцию добавления текста в начало строк
    } 
    // Обработка параметров для добавления текста в конец строк
    else if (argc == 4 && strcmp(option, "-b") == 0) 
    {
        text_end(file_path, argv[3]); // Вызываем функцию добавления текста в конец строк
    } 
    // Если переданы некорректные аргументы, выводим справку
    else 
    {
        print();
        return 1;
    }

    return 0; // Успешное завершение программы
}
