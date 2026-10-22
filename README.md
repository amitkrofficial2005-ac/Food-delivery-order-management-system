# Food Delivery Order Management System

A simple console-based food delivery system written in **C**.

## Features

- View food menu
- Place an order
- View pending orders
- Process (deliver) an order
- View order history
- Cancel an order
- Edit an existing order

## Data Structures Used

- **Queue** — manages pending orders (FIFO)
- **Stack** — stores delivered order history (LIFO)
- **Linked List** — used internally for both

## Menu Items

| ID | Item    | Price     |
|----|---------|-----------|
| 1  | Burger  | Rs. 120   |
| 2  | Pizza   | Rs. 250   |
| 3  | Biryani | Rs. 180   |
| 4  | Momos   | Rs. 100   |
| 5  | Pasta   | Rs. 150   |

## How to Run

### Compile
```
gcc main.c -o main
```

### Run
```
./main
```

## Project Structure

```
Food_Delivery_order_Management_system/
+-- main.c      # Source code
+-- README.md
```
