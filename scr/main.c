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

#define LIN 25
#define COL 85
#define SCREEN LIN * COL

char *vidptr = (char*)0xb8000;                  // начало видеопамяти в защищённом режиме
int cursor_pos_x = 0;                           // положение курсора x
int cursor_pos_y = 0;                           // положение курсора y
int i = 0;
                   
/// @brief Функция, которая очищает экран указанным цветов (0x02 чёрный/зелёный)
/// @param i 
void clearScreen(unsigned int i)
{
    while (i < SCREEN * 2)
    {
        vidptr[i++] = ' ';
        vidptr[i++] = 0x02;
    }
}

/// @brief  Функция, которая печатает символы до символа конца строки
/// @param i 
/// @param string 
void kprint(unsigned int i, const char *string)
{
    while (string[i] != '\0')
    {
        vidptr[cursor_pos_x++] = string[i++];
        vidptr[cursor_pos_x++] = 0x02;
    }
}

/// @brief Главная функция. Вызывает clearScreen и kprint с указанным тектом
/// @param  
void kmain(void)
{
    clearScreen(i);
    kprint(i, "CLEAR SCREEN: Successfully.");
    kprint(i, " OUTPUT STR: Successfully.");

    return;
}