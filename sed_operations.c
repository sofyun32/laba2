#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "operations.h"

// Функция для чтения содержимого файла и возврата его как строки
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        perror("Ошибка открытия файла."); 
        return NULL; // Возвращаем NULL, если не удалось открыть файл
    }

    fseek(file, 0, SEEK_END); // Перемещаем указатель на конец файла
    long length = ftell(file); // Получаем размер файла
    fseek(file, 0, SEEK_SET); // Возвращаем указатель в начало файла

    char *content = malloc(length + 1); 
    fread(content, 1, length, file); // Читаем содержимое файла
    content[length] = '\0'; 

    fclose(file); 
    return content; 
}

// Функция для записи содержимого в файл
void write_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w"); 
    if (!file) 
    {
        perror("Ошибка открытия файла"); 
        return; // Выходим из функции, если не удалось открыть файл
    }

    fwrite(content, 1, strlen(content), file); // Записываем содержимое в файл
    fclose(file); 
}


void delete_lines_regex(const char *filename, const char *pattern) 
{
    char *content = read_file(filename);
    if (!content)
    {
        return;
    }
    
    // Создаем объект регулярного выражения
    regex_t regex;
    // Компилируем паттерн для регулярного выражения с использованием расширенных синтаксических правил
    regcomp(&regex, pattern, REG_EXTENDED);

    char *res = malloc(strlen(content) + 1);
    res[0] = '\0';

    char *line = strtok(content, "\n");
    // Обрабатываем каждую строку
    while (line) 
    {
        if (regexec(&regex, line, 0, NULL, 0) != 0) {
            strcat(res, line);  // Добавляем строку в результат
            strcat(res, "\n");   // Добавляем разделитель новой строки
        }
        // Получаем следующую строку
        line = strtok(NULL, "\n");
    }

    regfree(&regex);
    // Записываем результирующее содержимое обратно в файл
    write_file(filename, res);
    free(res);
}


// Функция для замены текста в файле по регулярному выражению
void replace_text_regex(const char *filename, const char *pattern, const char *new_text) 
{
    char *content = read_file(filename); 
    if (!content) 
    {
        return; // Выходим, если не удалось прочитать файл
    }

    regex_t regex; // Объявляем переменную для регулярного выражения
    regcomp(&regex, pattern, REG_EXTENDED); // Компилируем регулярное выражение

    char *res = malloc(strlen(content) + 1); 
    res[0] = '\0'; 

    char *line = strtok(content, "\n"); // Разбиваем содержимое на строки
    while (line) 
    {
        regmatch_t match; 
        if (regexec(&regex, line, 1, &match, 0) == 0) 
        {
            char *prefix = strndup(line, match.rm_so); // Получаем префикс до совпадения
            char *suffix = strdup(line + match.rm_eo); // Получаем суффикс после совпадения

            strcat(res, prefix); // Добавляем префикс в результат
            strcat(res, new_text); // Добавляем новый текст
            strcat(res, suffix); // Добавляем суффикс
            strcat(res, "\n"); 

            free(prefix); // Освобождаем память под префикс
            free(suffix); // Освобождаем память под суффикс
        } else 
        {
            strcat(res, line); // Если совпадений нет, просто добавляем строку
            strcat(res, "\n"); 
        }
        line = strtok(NULL, "\n"); // Переходим к следующей строке
    }

    regfree(&regex); 
    write_file(filename, res); // Записываем результат обратно в файл
    free(res); 
}

// Функция для добавления текста в начало каждой строки файла
void text_start(const char *filename, const char *text) 
{
    char *content = read_file(filename); 
    if (!content) 
    {
        return; // Выходим, если не удалось прочитать файл
    }

    char *res = malloc(strlen(content) + strlen(text) * 2 + 1); 
    res[0] = '\0'; 

    char *line = strtok(content, "\n"); // Разбиваем содержимое на строки
    while (line) 
    {
        strcat(res, text); // Добавляем заданный текст в начало строки
        strcat(res, line); // Добавляем саму строку
        strcat(res, "\n"); // Добавляем символ новой строки
        line = strtok(NULL, "\n"); // Переходим к следующей строке
    }

    write_file(filename, res); // Записываем результат обратно в файл
    free(res); 
}

// Функция для добавления текста в конец каждой строки файла
void text_end(const char *filename, const char *text) 
{
    char *content = read_file(filename); 
    if (!content) 
    {
        return; // Выходим, если не удалось прочитать файл
    }

    char *res = malloc(strlen(content) + strlen(text) * 2 + 1); 
    res[0] = '\0';
    char *line = strtok(content, "\n"); // Разбиваем содержимое на строки
    while (line) 
    {
        strcat(res, line); // Добавляем строку к результату
        strcat(res, text); // Добавляем заданный текст в конец строки
        strcat(res, "\n"); // Добавляем символ новой строки
        line = strtok(NULL, "\n"); // Переходим к следующей строке
    }

    write_file(filename, res); // Записываем результат обратно в файл
    free(res); 
}