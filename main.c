//FOOD DELIVERY ORDER MANAGEMENT SYSTEM 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD 5
#define MAX_ITEMS 10

struct Food {
    int id;
    char name[20];
    float price;
};

struct Food menu[MAX_FOOD] = {
    {1, "Burger", 120},
    {2, "Pizza", 250},
    {3, "Biryani", 180},
    {4, "Momos", 100},
    {5, "Pasta", 150}
};

struct Item {
    int foodId, quantity;
};

struct Order {
    int id;
    char customer[30];
    int itemCount;
    struct Item items[MAX_ITEMS];
    float total;
    struct Order *next;
};

struct Order *front = NULL, *rear = NULL, *top = NULL;
int nextID = 100;


/* Find Food */
struct Food* findFood(int id) {
    for (int i = 0; i < MAX_FOOD; i++)
        if (menu[i].id == id)
            return &menu[i];
    return NULL;
}


/* Show Menu */
void showMenu() {
    printf("\n========== FOOD MENU ==========\n");

    for (int i = 0; i < MAX_FOOD; i++)
        printf("%d. %-10s Rs. %.2f\n",
               menu[i].id, menu[i].name, menu[i].price);
}


/* Calculate Total */
void calculateTotal(struct Order *o) {
    o->total = 0;

    for (int i = 0; i < o->itemCount; i++) {
        struct Food *f = findFood(o->items[i].foodId);
        o->total += f->price * o->items[i].quantity;
    }
}


/* Place Order */
void placeOrder() {
    struct Order *o = malloc(sizeof(struct Order));
    int n, id, qty;

    showMenu();

    printf("\nCustomer Name: ");
    scanf(" %[^\n]", o->customer);

    printf("How many items? ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_ITEMS) {
        printf("Invalid number of items!\n");
        free(o);
        return;
    }

    o->id = nextID++;
    o->itemCount = n;

    for (int i = 0; i < n; i++) {
        printf("\nItem %d\n", i + 1);

        printf("Food ID: ");
        scanf("%d", &id);

        if (findFood(id) == NULL) {
            printf("Invalid Food ID!\n");
            i--;
            continue;
        }

        printf("Quantity: ");
        scanf("%d", &qty);

        if (qty <= 0) {
            printf("Invalid quantity!\n");
            i--;
            continue;
        }

        o->items[i].foodId = id;
        o->items[i].quantity = qty;
    }

    calculateTotal(o);
    o->next = NULL;

    /* Queue */
    if (rear == NULL)
        front = rear = o;
    else {
        rear->next = o;
        rear = o;
    }

    printf("\nOrder placed! ID = %d\n", o->id);
}


/* Pending Orders */
void pendingOrders() {
    struct Order *p = front;

    if (p == NULL) {
        printf("\nNo pending orders.\n");
        return;
    }

    printf("\n========== PENDING ORDERS ==========\n");

    while (p != NULL) {
        printf("ID: %d | Customer: %s | Total: Rs. %.2f\n",
               p->id, p->customer, p->total);
        p = p->next;
    }
}


/* Process Order */
void processOrder() {
    if (front == NULL) {
        printf("\nNo pending orders.\n");
        return;
    }

    struct Order *o = front;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    printf("\nOrder %d delivered to %s\n",
           o->id, o->customer);

    /* Stack */
    o->next = top;
    top = o;
}


/* Order History */
void history() {
    struct Order *o = top;

    if (o == NULL) {
        printf("\nNo order history.\n");
        return;
    }

    printf("\n========== ORDER HISTORY ==========\n");

    while (o != NULL) {
        printf("\n-----------------------------");
        printf("\nOrder ID: %d\nCustomer: %s\n",
               o->id, o->customer);

        for (int i = 0; i < o->itemCount; i++) {
            struct Food *f = findFood(o->items[i].foodId);

            printf("%d. %s | Qty: %d | Rs. %.2f\n",
                   i + 1, f->name,
                   o->items[i].quantity, f->price);
        }

        printf("Total: Rs. %.2f\n", o->total);
        o = o->next;
    }
}


/* Cancel Order */
void cancelOrder() {
    int id;
    struct Order *p = front, *prev = NULL;

    printf("\nEnter Order ID: ");
    scanf("%d", &id);

    while (p != NULL && p->id != id) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Order not found!\n");
        return;
    }

    if (prev == NULL)
        front = p->next;
    else
        prev->next = p->next;

    if (p == rear)
        rear = prev;

    free(p);
    printf("Order cancelled!\n");
}


/* Edit Order */
void editOrder() {
    int id;

    printf("\nEnter Order ID to edit: ");
    scanf("%d", &id);

    struct Order *o = front;

    while (o != NULL && o->id != id)
        o = o->next;

    if (o == NULL) {
        printf("Order not found!\n");
        return;
    }

    showMenu();

    printf("\nHow many items now? ");
    scanf("%d", &o->itemCount);

    if (o->itemCount <= 0 || o->itemCount > MAX_ITEMS) {
        printf("Invalid number!\n");
        return;
    }

    for (int i = 0; i < o->itemCount; i++) {
        printf("\nItem %d\n", i + 1);

        printf("Food ID: ");
        scanf("%d", &o->items[i].foodId);

        printf("Quantity: ");
        scanf("%d", &o->items[i].quantity);
    }

    calculateTotal(o);
    printf("\nOrder updated successfully!\n");
}


/* Main */
int main() {
    int choice;

    while (1) {
        printf("\n\n========== FOOD DELIVERY ==========");
        printf("\n1. View Food Menu");
        printf("\n2. Place Order");
        printf("\n3. View Pending Orders");
        printf("\n4. Process Order");
        printf("\n5. Order History");
        printf("\n6. Cancel Order");
        printf("\n7. Edit Order");
        printf("\n8. Exit");

        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showMenu(); break;
            case 2: placeOrder(); break;
            case 3: pendingOrders(); break;
            case 4: processOrder(); break;
            case 5: history(); break;
            case 6: cancelOrder(); break;
            case 7: editOrder(); break;

            case 8:
                printf("\nThanks For Using management system\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }
}