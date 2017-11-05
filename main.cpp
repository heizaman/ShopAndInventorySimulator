#include <iostream>
#include <string>




enum class GameStates {EXIT, MAIN_MENU, INVENTORY, SHOP, PLAYING};
enum class ShopStates {EXIT, MENU, VIEW_SHOP, BUY_ITEMS};
enum class InventoryStates {EXIT, MENU, VIEW_INVENTORY, USE_ITEMS};


GameStates gameState = GameStates::MAIN_MENU;
ShopStates shopState = ShopStates::EXIT;
InventoryStates invState = InventoryStates::EXIT;




//Declared it here so that any function in the entire program can access it
const int arrSize = 5;
//Made constant as the array needs a constant number as its size

//Stores the shop from which we can buy stuff
const std::string shop[arrSize] = {"Swords", "Pistols", "Grenades", "RPGs", "Flash Bangs"};
//Made it constant too as it is never going to change

//Stores the number of each item of shop we have corresponding to their indexes
int inventory[arrSize] = {1, 0, 0, 0, 0};




void game();
bool quitGame();
GameStates mainMenu();
bool play();
bool inventoryFun();
InventoryStates inventoryMenu();
void viewInventory();
bool useItems();
bool shopFun();
ShopStates shopMenu();
void viewShop();
bool buyItems();




int main()
{
    game();
    return 0;
}




void game() {
    while(true) {
        switch(gameState) {
        case GameStates::EXIT:
            {
                bool quit = quitGame();

                if(quit)
                    return;
                else
                    gameState = GameStates::MAIN_MENU;
                break;
            }
        case GameStates::MAIN_MENU:
            gameState = mainMenu();
            break;
        case GameStates::PLAYING:
            {
                bool stopPlay = play();
                if(stopPlay)
                    gameState = GameStates::MAIN_MENU;
                break;
            }
        case GameStates::INVENTORY:
            {
                invState = InventoryStates::MENU;
                bool stopInventory = inventoryFun();
                if(stopInventory) {
                    gameState = GameStates::MAIN_MENU;
                    invState = InventoryStates::EXIT;
                }

                break;
            }
        case GameStates::SHOP:
            {
                shopState = ShopStates::MENU;
                bool stopShop = shopFun();
                if(stopShop)
                    gameState = GameStates::MAIN_MENU;
                    shopState = ShopStates::EXIT;
                    break;
            }
        default:
            std::cout << "Unexpected Error!";
            return;
        }
    }
}




bool quitGame() {
    std::cout << "Are you sure you want to quit the game? Y or N : ";

    char opt;
    std::cin >> opt;

    if(opt == 'y' || opt == 'Y')
        return true;
    else
        return false;
}




GameStates mainMenu() {
    int choice;
    std::cout << std::endl << "1. Play" << std::endl << "2. Inventory" << std::endl << "3. Shop" << std::endl << "4. Quit" << std::endl;

    while(true) {
        std::cout << "Enter your choice : ";
        std::cin >> choice;
        switch(choice) {
        case 1:
            return GameStates::PLAYING;
        case 2:
            return GameStates::INVENTORY;
        case 3:
            return GameStates::SHOP;
        case 4:
            return GameStates::EXIT;
        default:
            std::cout << std::endl << "Invalid Choice! Please try again!" << std::endl;
        }
    }
}




bool play() {
    char c;
    while(true) {
        std::cout << std::endl << "You are now playing the game..... Enter q to quit : ";

        std::cin >> c;

        if(c == 'q' || c == 'Q')
            return true;
    }
}




bool inventoryFun() {
    while(true) {
        switch(invState) {
        case InventoryStates::MENU:
            invState = inventoryMenu();
            break;
        case InventoryStates::VIEW_INVENTORY:
            viewInventory();
            invState = InventoryStates::MENU;
            break;
        case InventoryStates::USE_ITEMS:
            {
                bool stopUse = useItems();
                if(stopUse)
                    invState = InventoryStates::MENU;
                break;
            }
        case InventoryStates::EXIT:
            return true;
        default:
            std::cout << "Unexpected Error!";
            return true;
        }
    }
}


InventoryStates inventoryMenu() {
    int choice;

    while(true) {
        std::cout << std::endl << "1. Show Inventory" << std::endl << "2. Use Items" << std::endl << "3. Exit" << std::endl;

        std::cout << "Enter your choice : ";
        std::cin >> choice;
        switch(choice) {
        case 1:
            return InventoryStates::VIEW_INVENTORY;
            break;
        case 2:
            return InventoryStates::USE_ITEMS;
            break;
        case 3:
            return InventoryStates::EXIT;
            break;
        default:
            std::cout << std::endl << "Invalid Choice! Please try again!" << std::endl;
        }
    }
}


void viewInventory() {
    for(int i=0; i<arrSize; i++) {
        if(inventory[i]>0)
            std::cout << i+1 << ". " << inventory[i] << " x " << shop[i] << std::endl;
    }
    std::cout << std::endl;
}


bool useItems() {
    int i;
    viewInventory();
    std::cout << "What would you like to use? Enter -1 to exit : ";
    std::cin >> i;

    if(i == -1)
        return true;

    if(i<1 || i>arrSize || inventory[i-1] <= 0) {
        std::cout << std::endl << "Invalid choice!" << std::endl;
        return false;
    }

    inventory[i-1]--;
    std::cout << std::endl << "Item used from your inventory!" << std::endl;
    return false;
}




bool shopFun() {
    while(true) {
        switch(shopState) {
        case ShopStates::MENU:
            shopState = shopMenu();
            break;
        case ShopStates::VIEW_SHOP:
            viewShop();
            shopState = ShopStates::MENU;
            break;
        case ShopStates::BUY_ITEMS:
            {
                bool stopBuy = buyItems();
                if(stopBuy)
                    shopState = ShopStates::MENU;
                break;
            }
        case ShopStates::EXIT:
            return true;
        default:
            std::cout << "Unexpected Error!";
            return true;
        }
    }
}


ShopStates shopMenu() {
    int choice;

    while(true) {
        std::cout << std::endl << "1. Show Shop" << std::endl << "2. Buy Items" << std::endl << "3. Exit" << std::endl;

        std::cout << "Enter your choice : ";
        std::cin >> choice;
        switch(choice) {
        case 1:
            return ShopStates::VIEW_SHOP;
            break;
        case 2:
            return ShopStates::BUY_ITEMS;
            break;
        case 3:
            return ShopStates::EXIT;
            break;
        default:
            std::cout << std::endl << "Invalid Choice! Please try again!" << std::endl;
        }
    }
}


void viewShop() {
    for(int i=0; i<arrSize; i++) {
        std::cout << i+1 << ". " << shop[i] << std::endl;
    }
    std::cout << std::endl;
}


bool buyItems() {
    int i;
    viewShop();
    std::cout << "What would you like to buy? Enter -1 to exit : ";
    std::cin >> i;

    if(i == -1)
        return true;

    if(i<1 || i>arrSize) {
        std::cout << std::endl << "Invalid choice!" << std::endl;
        return false;
    }

    inventory[i-1]++;
    std::cout << std::endl << "Item added to your inventory!" << std::endl;
    return false;
}
