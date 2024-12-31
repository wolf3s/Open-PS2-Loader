#ifndef __MENUSYS_H
#define __MENUSYS_H

#include "include/dia.h"

typedef struct menu_hint_item
{
    int icon_id;
    int text_id;

    struct menu_hint_item *next;
} menu_hint_item_t;

/// a single menu item. Linked list impl (for the ease of rendering)
typedef struct menu_item
{
    /// Icon used for rendering of this item
    int icon_id;

    /// item description
    char *text;

    /// item description in localised form (used if value is not negative)
    int text_id;

    // Indicates if the menu item should be drawn or not.
    int visible;

    void *userdata;

    /// submenu, selection and page start (only used in static mode)
    struct submenu_list *submenu, *current, *pagestart;

    short remindLast;

    void (*refresh)(struct menu_item *curMenu);

    void (*execCross)(struct menu_item *curMenu);

    void (*execTriangle)(struct menu_item *curMenu);

    void (*execCircle)(struct menu_item *curMenu);

    void (*execSquare)(struct menu_item *curMenu);

    /// hint list
    struct menu_hint_item *hints;
} menu_item_t;

typedef struct menu_list
{
    struct menu_item *item;

    struct menu_list *prev, *next;
} menu_list_t;

void menuInit();
void menuEnd();
void menuReinitMainMenu(void);
void menuInitGameMenu(void);
void menuInitAppMenu(void);

void menuAppendItem(menu_item_t *item);

char *menuItemGetText(menu_item_t *it);
config_set_t *menuLoadConfig();
config_set_t *gameMenuLoadConfig(struct UIItem *ui);
void menuSaveConfig();

void menuRenderMain();
void menuRenderMenu();
void menuRenderInfo();
void menuRenderGameMenu();
void menuRenderAppMenu();
void menuHandleInputMain();
void menuHandleInputMenu();
void menuHandleInputInfo();
void menuHandleInputGameMenu();
void menuHandleInputAppMenu();

// Sets the selected item if it is found in the menu list
void menuSetSelectedItem(menu_item_t *item);

void menuAddHint(menu_item_t *menu, int text_id, int icon_id);
void menuRemoveHints(menu_item_t *menu);

int menuSetParentalLockCheckState(int enabled);
int menuCheckParentalLock(void);

#endif
