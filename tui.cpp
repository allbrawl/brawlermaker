#include <curses.h>

#include "tui.h"

int TUI::menu(std::string tittle, const char *choices[])
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int ch;
    int highlight = 0;
    int choice = 0;

    int numChoices = 0;
    while (choices[numChoices] != nullptr)
    {
        numChoices++;
    }

    mvprintw(0, 0, tittle.c_str());

    while (true)
    {
        for (int i = 0; i < numChoices; i++)
        {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(i + 2, 0, choices[i]);
            attroff(A_REVERSE);
        }
        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 5)
                highlight = 4;
            break;
        default:
            break;
        }
        if (ch == 10)
        {
            choice = highlight;
            break;
        }
    }

    endwin();
    return choice;
}

void TUI::mainMenu()
{
    initscr();
    noecho();
    cbreak();
    const char *choices[] = {"Add Brawler", "Edit Brawler", "Remove Brawler", "Options", "Exit"};
    menu("Brawlermaker v2.0", choices);
}