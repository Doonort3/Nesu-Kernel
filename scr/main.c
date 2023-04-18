/**
 * @file main.c
 * @author Doonort3
 * @brief 
 * @version 0.1
 * @date 2023-04-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

void kmain(void)
{

    /* Объявление указателей для текста и начала адреса видеопамяти. */
    const char *strptr = "Hello, World!";   // выводимая строка
    char *vidptr = (char*)0xb8000;          // начало видеопамяти
    unsigned int i = 0;
    unsigned int j = 0;

    /* Заливка фона пустым символом. */
    while (j < 80 * 25 * 2)                 // 25 строк; 80 столбов по 2 байта
    {
        vidptr[j] = ' ';                    // пустой символ    
        vidptr[j + 1] = 0x07;               // атрибут байта - серый текст на чёрном фоне
        j = j + 2;                          // +2 байта          
    }

    j = 0;                                  // "В начало консоли"


    /* Запись строки в видеопамять. */
    while (strptr[j] != '\0')               // символ конца строки      
    {
        vidptr[i] = strptr[j];
        vidptr[i + 1] = 0x07;
        ++j;
        i = i + 2;
    }

    return;
}
    
    
