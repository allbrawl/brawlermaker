#include <curses.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "brawler.h"
#include "brawlermaker.h"
#include "tui.h"

int TUI::menu(std::string title, const char *choices[])
{
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int ch;
    int highlight = 0;
    int choice = 0;
    int start = 0;
    int visible = LINES - 3;

    int numChoices = 0;
    while (choices[numChoices] != nullptr)
    {
        numChoices++;
    }

    mvprintw(0, 0, title.c_str());

    while (true)
    {
        clear();
        mvprintw(0, 0, title.c_str());

        for (int i = start; i < std::min(start + visible, numChoices); i++)
        {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(i - start + 2, 0, choices[i]);
            attroff(A_REVERSE);
        }

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            if (highlight > 0)
                highlight--;
            else if (start > 0)
                start--;
            break;
        case KEY_DOWN:
            if (highlight < numChoices - 1)
                highlight++;
            if (highlight >= start + visible && start + visible < numChoices)
                start++;
            break;
        default:
            break;
        }

        if (ch == 10)
        {
            choice = highlight;
            break;
        }

        if (highlight < start)
            start = highlight;
        if (highlight >= start + visible)
            start = highlight - visible + 1;
    }

    endwin();
    return choice;
}

Brawler TUI::brawlerSelectionMenu()
{
    BrawlerMaker bm;
    std::vector<Brawler> brawlers = bm.getBrawlers(
        assetsFolder + "/csv_logic/characters.csv",
        assetsFolder + "/csv_logic/cards.csv",
        assetsFolder + "/csv_logic/skills.csv",
        assetsFolder + "/localization/texts.csv",
        true);

    if (brawlers.empty())
    {
        throw std::runtime_error("No brawlers found");
    }

    std::vector<const char*> choices;
    for (const auto &brawler : brawlers)
    {
        choices.push_back(brawler.name.c_str());
    }
    choices.push_back(nullptr);

    int choice = menu("Select a brawler", choices.data());

    if (choice >= 0 && choice < static_cast<int>(brawlers.size()))
    {
        return brawlers[choice];
    }

    throw std::runtime_error("Invalid choice");
}


void TUI::mainMenu()
{
    initscr();
    noecho();
    cbreak();
    const char *choices[] = {"Add Brawler", "Edit Brawler", "Remove Brawler", "Options", "Exit"};
    int choice = menu("Brawlermaker v2.0", choices);

    switch (choice)
    {
    case 0:
        //addBrawlerMenu();
        break;
    case 1:
        //editBrawlerMenu();
        break;
    case 2:
        removeBrawlerMenu();
        break;
    case 3:
        //optionsMenu();
        break;
    case 4:
        endwin();
        break;
    }
}

void TUI::removeBrawlerMenu()
{
    Brawler brawler = brawlerSelectionMenu();
    initscr();
    noecho();
    cbreak();
    const char *choices[] = {"Yes", "No"};
    int choice = menu("Are you sure you want to remove " + brawler.name + "?", choices);
    if (choice == 0)
    {
        BrawlerMaker bm;
        bm.removeBrawler(brawler.tid, assetsFolder + "/csv_logic/characters.csv", assetsFolder + "/csv_logic/cards.csv", assetsFolder + "/csv_logic/skills.csv", assetsFolder + "/localization/texts.csv");
    }
}