#define IMPLEMENT_CRUD_USER
#define IMPLEMENT_PELANGGAN
#define IMPLEMENT_CRUD_MENU
#define IMPLEMENT_MENU_DB
#define IMPLEMENT_USER_MENU
#define IMPLEMENT_PESANAN_DB
#define IMPLEMENT_USER_DB


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#include "lib/struct.h"
#include "lib/auth.h"
#include "lib/admin/crudUser.h"
#include "lib/admin/crudMenu.h"
#include "lib/database/menuDb.h"

int main(void) {
    
    menuAutentikasi();
    return 0;
}