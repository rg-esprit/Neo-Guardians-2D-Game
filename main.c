#include <stdio.h>  // Add this line to include the standard I/O library
#include "Menu/menu.h"

int main() {
    int choix = runMenu();
    printf("%d", choix);
    
    return 0;
}
