#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct node
{
    char itemname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head1 = NULL, *tail1 = NULL;
struct node *head2 = NULL, *tail2 = NULL;
struct node *head3 = NULL, *tail3 = NULL;
struct node *head4 = NULL, *tail4 = NULL;
struct node *head5 = NULL, *tail5 = NULL;

struct node *head_o = NULL;

struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

void changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items to the store\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the store\n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Log Out \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void customermenu()
{
    printf("\n\t\t\t\t\t\t\t1. Select to view items in the store\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Log Out \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void itemgroups()
{
    printf("\n\t\t\t\t\t\t\t1. Cleaning and Household\n");
    printf("\t\t\t\t\t\t\t2. Food Grains\n");
    printf("\t\t\t\t\t\t\t3. Dairy\n");
    printf("\t\t\t\t\t\t\t4. Beverages and Snacks\n");
    printf("\t\t\t\t\t\t\t5. Beauty and Hygiene\n");
    printf("\t\t\t\t\t\t\t6. Back To Main Menu \n\n");
}

struct node *createadmin(struct node *head, int data, char itemname[25], float price)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    strcpy(newnode->itemname, itemname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if (temp == NULL)
        head = newnode;
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
        newnode->prev = temp;
    }

    return head;
}

struct node *createcustomer(struct node *head, struct node *headg, int data, int quantity)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    struct node *temp1 = headg;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {
        newnode->data = data;
        newnode->price = quantity * (temp1->price);
        newnode->quantity = quantity;
        strcpy(newnode->itemname, temp1->itemname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if (temp == NULL)
            headc = tailc = newnode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    if (temp1 == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n", temp1->data, temp1->itemname, temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n", temp1->data, temp1->itemname, temp1->quantity, temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }
}

struct node *totalsales(int data, int quantity)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = headc;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = (temp1->price);
    newnode->quantity = quantity;
    strcpy(newnode->itemname, temp1->itemname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if (temp == NULL)
        head_s = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next = newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while (temp != NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        //head_o = createadmin(head_c,)
        temp = temp->next;
    }
}

struct node *delete (int data, struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node *temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            if (temp->next == NULL)
            {
                (temp->prev)->next = NULL;
                temp->prev = NULL;
                free(temp);
            }
            else
            {
                (temp->prev)->next = temp->next;
                (temp->next)->prev = temp->prev;
                free(temp);
            }
        }
    }
    return head;
}

int deleteadmin()
{
    itemgroups();
    printf("\n\t\t\t\t\t\t\tEnter the section you want to delete the item from: ");
    int n;
    struct node *temp;
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        displayList(head1);
        printf("\n\t\t\t\t\tEnter serial no. of the item which is to be deleted: ");
        int num1;
        scanf("%d", &num1);

        temp = head1;
        while (temp != NULL)
        {
            if (temp->data == num1)
            {
                head1 = delete (num1, head1, tail1);
                return 1;
            }
            temp = temp->next;
        }
        return 0;
        break;

    case 2:
        displayList(head2);
        printf("\n\t\t\t\t\tEnter serial no. of the item which is to be deleted: ");
        int num2;
        scanf("%d", &num2);

        temp = head2;
        while (temp != NULL)
        {
            if (temp->data == num2)
            {
                head2 = delete (num2, head2, tail2);
                return 1;
            }
            temp = temp->next;
        }
        return 0;
        break;

    case 3:
        displayList(head3);
        printf("\n\t\t\t\t\tEnter serial no. of the item which is to be deleted: ");
        int num3;
        scanf("%d", &num3);

        temp = head3;
        while (temp != NULL)
        {
            if (temp->data == num3)
            {
                head3 = delete (num3, head3, tail3);
                return 1;
            }
            temp = temp->next;
        }
        return 0;
        break;

    case 4:
        displayList(head4);
        printf("\n\t\t\t\t\tEnter serial no. of the item which is to be deleted: ");
        int num4;
        scanf("%d", &num4);

        temp = head4;
        while (temp != NULL)
        {
            if (temp->data == num4)
            {
                head4 = delete (num4, head4, tail4);
                return 1;
            }
            temp = temp->next;
        }
        return 0;
        break;

    case 5:
        displayList(head5);
        printf("\n\t\t\t\t\tEnter serial no. of the item which is to be deleted: ");
        int num5;
        scanf("%d", &num5);

        temp = head5;
        while (temp != NULL)
        {
            if (temp->data == num5)
            {
                head5 = delete (num5, head5, tail5);
                return 1;
            }
            temp = temp->next;
        }
        return 0;
        break;
    }
}

int deletecustomer()
{
    printf("\n\t\t\t\t\tEnter serial no. of the item which is to be deleted: ");
    int num;
    scanf("%d", &num);

    struct node *temp = headc;
    while (temp != NULL)
    {
        if (temp->data == num)
        {
            headc = delete (num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp != NULL)
    {
        total_price += temp->price;
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n", total_price);
}

void displayOrder()
{
    displayList(head_o);
    struct node *temp = head_o;
    float total_price = 0;
    while (temp != NULL)
    {
        total_price += temp->price;
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n", total_price);
}

struct node *deleteList(struct node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin(char cust[], double ph)
{
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while (1)
    {
        adminmenu();

        int opt;
        scanf("%d", &opt);

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            displayList(head_s);
            break;
        case 2:

            printf("\n\t\t\t\t\t\t\tEnter serial no. of the item: ");
            int num, choice, flag = 0;
            char name[50];
            float price;
            scanf("%d", &num);

            struct node *temp;

            itemgroups();
            printf("\n\t\t\t\t\t\t\tEnter the section you want to add the item to: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                temp = head1;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head2;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head3;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head4;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head5;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                printf("\t\t\t\t\t\t\tEnter the item name: ");
                scanf("%s", name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f", &price);
                head1 = createadmin(head1, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew item added to the list!!\n\n");
                break;

            case 2:
                temp = head1;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head2;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head3;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head4;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head5;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                printf("\t\t\t\t\t\t\tEnter the item name: ");
                scanf("%s", name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f", &price);
                head2 = createadmin(head2, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew item added to the list!!\n\n");
                break;

            case 3:
                temp = head1;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head2;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head3;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head4;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head5;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                printf("\t\t\t\t\t\t\tEnter the item name: ");
                scanf("%s", name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f", &price);
                head3 = createadmin(head3, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew item added to the list!!\n\n");
                break;

            case 4:
                temp = head1;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head2;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head3;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head4;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head5;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                printf("\t\t\t\t\t\t\tEnter the item name: ");
                scanf("%s", name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f", &price);
                head4 = createadmin(head4, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew item added to the list!!\n\n");
                break;

            case 5:
                temp = head1;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head2;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head3;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head4;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                temp = head5;

                while (temp != NULL)
                {
                    if (temp->data == num)
                    {
                        printf("\n\t\t\t\t\t\tItem with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                printf("\t\t\t\t\t\t\tEnter the item name: ");
                scanf("%s", name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f", &price);
                head5 = createadmin(head5, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew item added to the list!!\n\n");
                break;
            }
            break;

        case 3:
            if (deleteadmin())
            {
                printf("\n\t\t\t\t\t\t### List Updated ###\n");
            }
            else
                printf("\n\t\t\t\t\t\tItem with the given serial number doesn't exist in this section!\n\n");
            break;

        case 4:
            if (ph == 0000000000)
            {
                printf("\n\t\t\t\t\t\t\tNo Orders!!\n");
            }
            else
            {
                printf("\n\t\t\t\t\t\t   ------------------------------------------------------\n");
                printf("\t\t\t\t\t\t\t\t     ### Order menu ###\n");
                printf("\t\t\t\t\t\t   ------------------------------------------------------\n");
                printf("\t\t\t\t\t\t   %s\n", cust);
                printf("\t\t\t\t\t\t   %0.lf\n", ph);
                printf("\t\t\t\t\t\t   ------------------------------------------------------\n");
                displayList(head_o);
                printf("\t\t\t\t\t\t   ------------------------------------------------------\n");
            }
            printf("\n\t\t\t\t\t\tPress 0 to go back --->");
            int b;
            scanf("%d", &b);
            deleteList(head_o);
            if (b == 0)
                break;

        default:
            printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;
        }
    }
}

void customer(char cust[], double ph)
{
    int flag = 0, j = 1;
    char ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");

    while (1)
    {
        customermenu();

        int opt;
        scanf("%d", &opt);

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            itemgroups();
            printf("\n\t\t\t\t\t\tEnter number corresponding to the section      you want to order from: ");
            int opt1, n, quantity;
            char a;
            printf("\n\t\t\t\t\t\t\t   Enter Your Choice --->");
            scanf("%d", &opt1);

            if (opt1 == 6)
                break;

            switch (opt1)
            {
            case 1:
                while (1)
                {
                    displayList(head1);
                    printf("\n\t\t\t\t\t\tPress 0 to exit or");
                    printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                    scanf("%d", &n);
                    if (n == 0)
                    {
                        break;
                    }
                    printf("\t\t\t\t\t\tEnter quantity: ");
                    scanf("%d", &quantity);
                    head_o = headc = createcustomer(headc, head1, n, quantity);
                    continue;
                }
                break;

            case 2:
                while (1)
                {
                    displayList(head2);
                    printf("\n\t\t\t\t\t\tPress 0 to exit or");
                    printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                    scanf("%d", &n);
                    if (n == 0)
                    {
                        break;
                    }
                    printf("\t\t\t\t\t\tEnter quantity: ");
                    scanf("%d", &quantity);
                    head_o = headc = createcustomer(headc, head2, n, quantity);
                    continue;
                }
                break;

            case 3:
                while (1)
                {
                    displayList(head3);
                    printf("\n\t\t\t\t\t\tPress 0 to exit or");
                    printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                    scanf("%d", &n);
                    if (n == 0)
                    {
                        break;
                    }
                    printf("\t\t\t\t\t\tEnter quantity: ");
                    scanf("%d", &quantity);
                    head_o = headc = createcustomer(headc, head3, n, quantity);
                    continue;
                }
                break;

            case 4:
                while (1)
                {
                    displayList(head4);
                    printf("\n\t\t\t\t\t\tPress 0 to exit or");
                    printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                    scanf("%d", &n);
                    if (n == 0)
                    {
                        break;
                    }
                    printf("\t\t\t\t\t\tEnter quantity: ");
                    scanf("%d", &quantity);
                    head_o = headc = createcustomer(headc, head4, n, quantity);
                    continue;
                }
                break;

            case 5:
                while (1)
                {
                    displayList(head5);
                    printf("\n\t\t\t\t\t\tPress 0 to exit or");
                    printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                    scanf("%d", &n);
                    if (n == 0)
                    {
                        break;
                    }
                    printf("\t\t\t\t\t\tEnter quantity: ");
                    scanf("%d", &quantity);
                    head_o = headc = createcustomer(headc, head5, n, quantity);
                    continue;
                }
                break;
            }

        case 2:
            printf("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");
            displayList(headc);
            break;
        case 3:
            if (deletecustomer())
            {
                printf("\n\t\t\t\t\t\t### Updated list of your ordered items ###\n");
                displayList(headc);
            }
            else
                printf("\n\t\t\t\t\t\tItem with given serial number doesn't exist!!\n");
            break;
        case 4:

            calculatetotsales();
            printf("\n\t\t\t\t\t\t   ------------------------------------------------------\n");
            printf("\t\t\t\t\t\t\t\t       FINAL BILL\n");
            printf("\t\t\t\t\t\t   ------------------------------------------------------\n");
            printf("\t\t\t\t\t\t   %s\n", cust);
            printf("\t\t\t\t\t\t   %0.lf\n", ph);
            printf("\t\t\t\t\t\t   ------------------------------------------------------\n");
            displaybill();
            headc = deleteList(headc);
            printf("\t\t\t\t\t\t   ------------------------------------------------------\n");
            printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;

        default:
            printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;
        }
        if (flag == 1)
            break;
    }
}

void mainnenu()
{
    printf("\n                                 **************************************************************************\n");
    printf("                                                     WELCOME TO DEPARTMENT STORE MANAGEMENT SYSTEM\n");
    printf("                                 **************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");
}

int main()
{
    //Cleaning and household
    head1 = createadmin(head1, 1, "Harpic(500 ml)                 ", 80);
    head1 = createadmin(head1, 2, "Surf Excel Detergent Powder   ", 200);
    head1 = createadmin(head1, 3, "Dettol Liquid Cleaner         ", 180);
    head1 = createadmin(head1, 4, "Pril Dishwash                 ", 130);
    head1 = createadmin(head1, 5, "Colin Glass Cleaner            ", 90);
    head1 = createadmin(head1, 6, "Broom                         ", 150);
    head1 = createadmin(head1, 7, "Floor Mop                     ", 200);

    //Food grains
    head2 = createadmin(head2, 8, "Aashirwad Atta(10 kg)         ", 400);
    head2 = createadmin(head2, 9, "Basmati Rice                  ", 700);
    head2 = createadmin(head2, 10, "Maida(1 kg)                   ", 33);
    head2 = createadmin(head2, 11, "Rice Flour(1 kg)              ", 35);
    head2 = createadmin(head2, 12, "Rava(1 kg)                    ", 40);
    head2 = createadmin(head2, 13, "Ragi(1 kg)                    ", 60);
    head2 = createadmin(head2, 14, "Sona Masoori Rice(25 kg)    ", 1200);
    head2 = createadmin(head2, 15, "Toor Dal(1 kg)               ", 130);
    head2 = createadmin(head2, 16, "Moong Dal                    ", 135);

    //Dairy
    head3 = createadmin(head3, 17, "Paneer(500 g)                ", 200);
    head3 = createadmin(head3, 18, "Butter(500 g)                ", 220);
    head3 = createadmin(head3, 19, "Curd(500 ml)                  ", 27);
    head3 = createadmin(head3, 20, "Bread(500 g)                  ", 40);
    head3 = createadmin(head3, 21, "Toned MIlk(500 ml)            ", 26);
    head3 = createadmin(head3, 22, "Cheese(500 g)                ", 350);

    //Beverages and Snacks
    head4 = createadmin(head4, 23, "Red Label Tea(500 g)         ", 300);
    head4 = createadmin(head4, 24, "Bru Cofee Powder(200 g)      ", 280);
    head4 = createadmin(head4, 25, "Boost(1 kg)                  ", 400);
    head4 = createadmin(head4, 26, "Maggie(500 g)                 ", 80);
    head4 = createadmin(head4, 27, "Bourbon(150 g)                ", 25);
    head4 = createadmin(head4, 28, "Oreo(120 g)                   ", 30);
    head4 = createadmin(head4, 29, "Lays                          ", 10);
    head4 = createadmin(head4, 30, "Noodles(400 g)                ", 65);
    head4 = createadmin(head4, 31, "Corn Flakes(250 g)           ", 100);

    //Beauty and Hygiene
    head5 = createadmin(head5, 32, "Himalaya Face Wash(100 ml)    ", 98);
    head5 = createadmin(head5, 33, "Dettol Handwash(750 ml)       ", 90);
    head5 = createadmin(head5, 34, "Pears Bathing Bar (Pack of 4)", 240);
    head5 = createadmin(head5, 35, "Colgate Toothpaste           ", 125);
    head5 = createadmin(head5, 36, "Toothbrush                    ", 50);
    head5 = createadmin(head5, 37, "Axe Men Deodrant             ", 180);

    char cust[15] = "------";
    double ph = 0000000000;

    while (1)
    {
        changeColor(13);
        mainnenu();
        int choice;
        scanf("%d", &choice);
        int pwd = 301117;
        int code;

        if (choice == 3)
        {
            printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            break;
        }

        switch (choice)
        {
        case 1:
            changeColor(14);
            printf("\n\n\t\t\t\t\t\t\tEnter the 6 digit code : ");
            scanf("%d", &code);
            if (pwd == code)
            {
                admin(cust, ph);
                break;
            }
            else
            {
                printf("\n\n\t\t\t\t\t\t\tCode incorrect!");
                printf("\n\t\t\t\t\t\t\tTry again\n");
                break;
            }
        case 2:
            changeColor(10);
            printf("\n\n\t\t\t\t\t\t\tEnter your name : ");
            scanf("%s", cust);
            printf("\t\t\t\t\t\t\tEnter your phone number : ");
            scanf("%lf", &ph);
            customer(cust, ph);
            break;
        case 3:
            break;

        default:
            changeColor(4);
            printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;
        }
    }
}