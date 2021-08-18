#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int item_order=-1;
int extra=1;
char give_discount='n';
char has_ordered='n';
struct menu{
    char name[20];
    int price;
    int ordered;
    float rating;
    int id;
}datas[50];
struct list{
char name[20];
    int id;
    int qty;
    int price;
}my_basket[100];

struct detail{
    char name[20];
    char citizen_id[20];
}identy;
void customer();
void orderDishes();
void sort();
void sort1();
void sort2();
void sort3();
void show();
void owner();
void edit();
void add();
void see();
void bill();
//main part
int main()
{
    printf("\t\t* * *  welcome  * * *\n\n");
FILE *fptr;
fptr=fopen("second.txt","r");
int len=0;
while(fread(&datas[len],sizeof(datas[len]),1,fptr)==1)
{
len++;
}
//printf("\n%d",len);
for(int i=0;i<len;i++)
{
    fread(&datas[i],sizeof(datas[i]),1,fptr);}//data of file in datas
    printf("Who is it\n1. Customer\n2. Owner\n");
    int choice;
    scanf("%d",&choice);
    switch(choice){
        case 1:
        customer(len);
        break;
        case 2:
        owner(fptr,len);
        break;
    }
    if(has_ordered=='y')
    {
    add_data_in_file(fptr,len);
    bill();
    }

    }
    void add_data_in_file(FILE *fptr,int len)
    {
    float rate;
    char ans;
    printf("Give the Food Feedback(y/n)?\n");
    scanf(" %c",&ans);

        fclose(fptr);
        FILE * jpt;
        int l;
        jpt=fopen("second.txt","w");
        for(int i=0;i<=item_order;i++)
        {
            l=determine_index(my_basket[i].id,len);
            if(ans=='y')
            {   system("clear");
                printf("Rating for %s:",datas[l].name);
                scanf("%f",&rate);
                datas[l].rating=(rate+datas[l].rating)/2;
            }
            datas[l].ordered+=my_basket[i].qty;
        }
        struct menu temp;
        for(int i=0;i<len;i++)
        {
        for(int j=i+1;j<len;j++)
        {
            if(datas[i].id>datas[j].id)
            {
                temp=datas[i];
                datas[i]=datas[j];
                datas[j]=temp;
            }
        }
        }

        for(int i=0;i<len;i++)
        {
        fwrite(&datas[i],sizeof(datas[i]),1,jpt);

        }
        fclose(jpt);
    }

    void customer(int len)//presenting data
    {
    system("clear");
    int choice;
    order:
show(len);
     printf("1. Order\n2. Sort\n");
     scanf("%d",&choice);
        switch(choice){
        case 1:
        orderDishes(len);
        break;
        case 2:
        sort(len);
        break;
    }
    }
    void orderDishes(int len)//ordering
    {
    int id;
    char q='y';
    char a;
    do
    {
    int i;
    char c;
    item_order++;
    do{
    system("clear");
    show(len);
    printf("Enter the id\n");
    scanf(" %d",&id);
   i=determine_index(id,len);
    system("clear");
    show(len);
        printf("Is it %s (y/n)\n",datas[i].name);
       scanf(" %c",&c);
        }while(c=='n');

        my_basket[item_order].id=datas[i].id;
        strcpy(my_basket[item_order].name,datas[i].name);
            system("clear");
    show(len);
        printf("Enter %s quatity\n",datas[i].name);
        scanf("%d",&my_basket[item_order].qty);
        my_basket[item_order].price=datas[i].price;
        has_ordered='y';
            system("clear");
    show(len);
        printf("Wanna add  more food to the list(y/n)?\n");
        scanf(" %c",&q);
    }while(q=='y');
    int c=getchar();
    system("clear");
    printf("Enter your detail\n");//detail input
    printf("Name :");
    gets(identy.name);
    printf("Citizen id :");
    gets(identy.citizen_id);
    FILE *check;
    check=fopen("customerid.txt","r");
    if(isRegular(check,identy.citizen_id)==1)
   {
   give_discount='y';
   }
   else
   {
   fclose(check);
    give_discount='n';
   check=fopen("customerid.txt","a");
   add_id(check,identy.citizen_id);
   //printf("no is not regular");
   }
    fclose(check);

    }
    void sort(int len)//sorting dishes
    {
    int choice;
    again_sort:
    system("clear");
        printf("1. Respect to price\n2. Respect to Most Ordered\n3. Respect to Favourites\n");
        scanf(" %d",&choice);
        switch(choice)
        {
            case 1:
            sort1(len);
            break;
            case 2:
            sort2(len);
            break;
            case 3:
            sort3(len);
            break;
        }
        system("clear");
        show(len);
        char choice1;
        printf("Want more sorting(y/n)\n");
        scanf(" %c",&choice1);
        if(choice1=='y')
       { goto again_sort;
}
orderDishes(len);

    }
    void sort1(int len)
    {
        struct menu temp;
        for(int i=0;i<len;i++)
        {
            for(int j=i+1;j<len;j++)
            {
            if(datas[i].price<datas[j].price){
                temp=datas[i];
                datas[i]=datas[j];
                datas[j]=temp;

                }
            }
        }

    }
    void sort2(int len)
    {
        struct menu temp2;
        for(int i=0;i<len;i++)
        {
            for(int j=i+1;j<len;j++)
            {
            if(datas[i].ordered<datas[j].ordered){
                temp2=datas[i];
                datas[i]=datas[j];
                datas[j]=temp2;

                }
            }
        }
    }
    void sort3(int len)
    {
        struct menu temp3;
        for(int i=0;i<len;i++)
        {
            for(int j=i+1;j<len;j++)
            {
            if(datas[i].rating<datas[j].rating){
                temp3=datas[i];
                datas[i]=datas[j];
                datas[j]=temp3;

                }
            }
        }
    }
    void show(int len)
    {

    printf("\t\t* * *  welcome  * * *\n\n");
   // printf("%d",len);
     printf("ID\tName\t");
     printf("%21s\n","Price");

    for(int i=0;i<len;i++)
{
    printf("%d\t",datas[i].id);
    printf("%-18s\t",datas[i].name);
    printf("%d\t",datas[i].price);
  /*  printf("%d\t",datas[i].ordered);
    printf("%f\t",datas[i].rating);*/
    printf("\n");


} printf("\n");
    }
    void owner(FILE *fptr,int len)
    {
    char pass[20];
     system("clear");
        printf("Enter the password");
        scanf("%s",pass);
        system("clear");
        if(!strcmp(pass,"qa"))
        {
            printf("1. Edit menu\n2. Add Dishes\n3. See the financial Report\n");
            int choice;
            scanf("%d",&choice);

            switch(choice){
                case 1:
               edit(fptr,len);
                    system("clear");

                show_without_welcome(len);
                break;
                case 2:
                add(fptr,len);
                     system("clear");

                 show_without_welcome(len);
                break;
                case 3:
                report(len);
                break;

                }
        }

    }
    int determine_index(int id,int len)
    {
         for(int i=0;i<len;i++)
    {
        if(id==datas[i].id)
        {
            return i;
        }}
    }
    void edit(FILE *fptr,int len)
    {
    system("clear");

     int delete_id;
    fclose(fptr);
    FILE *edit;
    edit=fopen("second.txt","w");
    int id;
    char name[20];
        printf("1. Edit name\n2. Edit price\n3. Delete a dish\n");
        int choice;
        scanf("%d",&choice);
        if(choice==1)
        {
         char c;
         int i;
        do{
        system("clear");
        show_without_welcome(len);
        printf("Enter the id of the dish to be editted\n");
            scanf("%d",&id);
     i=determine_index(id,len);
  system("clear");
        show_without_welcome(len);
        printf("Is it %s (y/n)\n",datas[i].name);
       scanf(" %c",&c);
               system("clear");
        show_without_welcome(len);
       }while(c=='n');
        char x=getchar();
         printf("Enter the new  name of %s\n",datas[i].name);
        gets(name);
    //  char x=getchar();
        strcpy(datas[i].name,name);
   //     puts(datas[i].name);


    }
    else if(choice==2)
    {
    system("clear");

     char c;
      int i;
       do{
        show_without_welcome(len);
        printf("Enter the id of the dish to be editted\n");
        scanf("%d",&id);
    i=determine_index(id,len);
               system("clear");
        show_without_welcome(len);
        printf("Is it %s (y/n)\n",datas[i].name);
       scanf(" %c",&c);
        }while(c=='n');
        char x=getchar();
                       system("clear");
        show_without_welcome(len);
         printf("Enter the new price of %s\n",datas[i].name);
        scanf("%d",&datas[i].price);
      //  printf("%d",datas[i].price);

    }
      else if(choice==3)
      {
      char qq='y';
      do{

    system("clear");
    show_without_welcome(len);
        printf("Enter the id to be deleted\n");
        scanf("%d",&delete_id);
             printf("Is it %s?\n",datas[delete_id].name);
             scanf(" %c",&qq);
      }while(qq=='n');
      }
    for(int i=0;i<len;i++)
    {
    if(datas[i].id!=delete_id){
        fwrite(&datas[i],sizeof(datas[i]),1,edit);
    }
    }
    fclose(edit);
    }
void add(FILE* fptr,int len)
{
char c='y';
    fclose(fptr);
    FILE *add;
    add=fopen("second.txt","a");
do{
    c=getchar();
    system("clear");

    printf("Enter the name of dish :\n");
    gets(datas[len+extra].name);
    printf("Enter the Price of %s :\n",datas[len+extra].name);
    scanf("%d",&datas[len+extra].price);
    datas[len+extra].ordered=0;
    datas[len+extra].rating=0;
    datas[len+extra].id=100+len+extra;
    fwrite(&datas[len+extra],sizeof(datas[len+extra]),1,add);
    extra++;
    printf("Wanna add more?\n");
   scanf(" %c",&c);
    }while(c=='y');
        fclose(add);
}
int isRegular(FILE *check,char id[])
{
    char temp[20];
    while(fgets(temp,15,check)!=NULL)
    {
        if(!(strcmp(temp,id)))
        {
            return 1;
        }

    }
    return 0;
}
void add_id(FILE *check,char id[])
{
    fputs(id,check);
}
void bill()
{
    system("clear");
    printf("\t\t* * *  Thank you  * * *\n\n");
    printf("Name : %s\t",identy.name);
    printf("ID : %s\t",identy.citizen_id);
int total=0;
        printf("\nDish\%22s\tPrice","Quantity");
     for(int i=0;i<=item_order;i++)
    {
        printf("\n%-18s\t",my_basket[i].name);
        printf("%d\t",my_basket[i].qty);
        printf("%d",my_basket[i].price);
        total+=my_basket[i].qty*my_basket[i].price;
    }
    printf("\n");
    if(give_discount=='y')
    printf("\nTotal %d ",total-5*total/100);
    else
    printf("\nTotal %d ",total);


}
void report(int len)
{
system("clear");
          printf("Name\t\t%22s\tRating\n","Ordered");
    for(int i=0;i<len;i++)
{
   // printf("%d\t",datas[i].id);
    printf("%-18s\t\t",datas[i].name);
  //  printf("%d\t",datas[i].price);
   printf("%d\t",datas[i].ordered);
    printf("%.2f\t",datas[i].rating);
    printf("\n");

}

}
    void show_without_welcome(int len)
    {


   // printf("%d",len);
     printf("ID\tName\t");
     printf("%21s\n","Price");

    for(int i=0;i<len;i++)
{
    printf("%d\t",datas[i].id);
    printf("%-18s\t",datas[i].name);
    printf("%d\t",datas[i].price);
  /*  printf("%d\t",datas[i].ordered);
    printf("%f\t",datas[i].rating);*/
    printf("\n");


} printf("\n");
    }


