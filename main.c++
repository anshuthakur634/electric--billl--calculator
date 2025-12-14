#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

struct customer
{
    char c_name[20];
    int c_id;
    float price;
};

struct bill
{
    int b_id;
    int cid;
    char name[20];
    float price;
    int unit;
};

int customer_id()
{
    int a;
    FILE *fp;
    fp=fopen("cus.txt","r");
    if(fp==NULL)
        a=1;
    else
    {
        fscanf(fp,"%d",&a);
        a++;
        return a;
    }
    fclose(fp);

    fp=fopen("cus.txt","w");
    fprintf(fp,"%d",a);
    fclose(fp);
}

int bill_id()
{
    int y;
    FILE *fp;
    fp=fopen("bi.txt","r");
    if(fp==NULL)
        y=1;
    else
    {
        fscanf(fp,"%d",&y);
        y++;
    }
    fclose(fp);

    fp=fopen("bi.txt","w");
    fprintf(fp,"%d",y);
    fclose(fp);
    return y;
}

void add_customer()
{
    FILE *ptr;
    struct customer c;
    ptr=fopen("cust.txt","a");
    fflush(stdin);
    printf("\nEnter customer details:\nName: ");
    gets(c.c_name);
    fflush(stdin);

    printf("\nPrice of each unit: ");
    scanf("%f",&c.price);
    c.c_id=customer_id();

    printf("\nRecord added successfully.");
    printf("\nYour customer id is %d\n",c.c_id);

    fwrite(&c,sizeof(c),1,ptr);
    fclose(ptr);
}

void generate_bill()
{
    int find,flag=0;
    FILE *ptr,*ptr1;
    struct customer c;
    struct bill b;
    printf("\nEnter your customer id: ");
    scanf("%d",&find);

    ptr=fopen("cust.txt","r");
    while(!feof(ptr))
    {
        fread(&c,sizeof(c),1,ptr);
        if(c.c_id==find)
        { 
            flag=1;
            ptr1=fopen("bill1.txt","a");
            b.b_id=bill_id();
            strcpy(b.name,c.c_name);
            b.price=c.price;
            b.cid=c.c_id;
            printf("\nEnter number of units consumed this month: ");
            scanf("%d",&b.unit);
            fflush(stdin);
            printf("\nBill has been generated successfully.");
            printf("\nYour bill id is %d\n",b.b_id);
            fwrite(&b,sizeof(b),1,ptr1);
            fclose(ptr1);
            break;
        }
    }
    if(flag==0)
        printf("\nError! No such customer with id %d exists.\n",find);
    fclose(ptr);
}

void display_bill()
{
    int flag=0,billid,custid;
    FILE *ptr1;
    struct bill b;
    ptr1=fopen("bill1.txt","r");
    printf("\nEnter your customer id: ");
    scanf("%d",&custid);
    fflush(stdin);
    printf("\nEnter bill id to display: ");
    scanf("%d",&billid);
    while(!feof(ptr1))
    {
        fread(&b,sizeof(b),1,ptr1);
        if((b.b_id==billid)&&(b.cid==custid))
        {
            flag++;
            printf("\nElectricity Bill");
            printf("\nBill id: %d",b.b_id);
            printf("\nName: %s",b.name);
            printf("\nCustomer id: %d",b.cid);
            printf("\nPrice per unit: %.2f",b.price);
            printf("\nUnits consumed: %d",b.unit);
            printf("\nTotal amount: %.2f\n",b.price*b.unit);
            break;
        }
    }
    if(flag==0)
        printf("\nError! No such customer id %d OR bill no %d exists.\n",custid,billid);
    fclose(ptr1);
}

void delete_bill()
{
    int flag=0,billid;
    FILE *ptr,*ptr1;
    struct bill b;

    ptr=fopen("bill1.txt","r");
    ptr1=fopen("temp.txt","w");
    printf("\nEnter bill id to delete: ");
    scanf("%d",&billid);
    while(!feof(ptr))
    {
        fread(&b,sizeof(b),1,ptr);
        if(b.b_id==billid)
        {
            printf("\nBill with id %d DELETED successfully.\n",b.b_id);
            flag=1;
        }
        else
            fwrite(&b,sizeof(b),1,ptr1);
    }

    fclose(ptr);
    fclose(ptr1);
    if(flag==0)
        printf("\nError! No such bill with id %d exists.\n",billid);
    remove("bill1.txt");
    rename("temp.txt","bill1.txt");
}

int main()
{
    char username[20], password[20];
    printf("Please enter username: ");
    scanf("%s",username);
    printf("Please enter password: ");
    scanf("%s",password);
    if(strcmp(username,"admin")==0)
    {
        if(strcmp(password,"12345")==0)
            printf("\nWelcome! Login successful.\n");
        else
        {
            printf("\nInvalid password\n");
            exit(0);
        }
    }
    else
    {
        printf("\nInvalid username\n");
        exit(0);
    }

    int choice=0;
    while(choice!=5)
    {
        printf("\n**************************************");
        printf("\n      Electricity Bill Calculator");
        printf("\n**************************************\n");

        printf("\nMAIN MENU");
        printf("\n1. Add new customer");
        printf("\n2. Bill Generation");
        printf("\n3. Display bill");
        printf("\n4. Delete bill");
        printf("\n5. EXIT");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: add_customer(); break;
            case 2: generate_bill(); break;
            case 3: display_bill(); break;
            case 4: delete_bill(); break;
            case 5: break;
            default:
                printf("\nInvalid Choice...!\nPress any key to continue..");
                getch();
        }
    }
}
