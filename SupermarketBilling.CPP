#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<iostream.h>
#include<iomanip.h>
#include<string.h>
#include<stdlib.h>
#define false (0)
#define true (1)
typedef int bool;
char t[30];
char fname[20];
class product
{
char pno[10];
char name[50];
float qty;
char price[10];
public:
void create_pr()
{
cout<<"\nEnter the product no.";
cin>>pno;
cout<<"\n\nEnter name of the product ";
gets(name);
cout<<"\nEnter price of the product ";
cin>>price;
}
void show_pr()
{
cout<<"\n\nProduct no.: "<<pno;
cout<<"\nProduct name : ";
puts(name);
cout<<"\nPrice of the product : "<<price<<"\n";
}

char* retpno()
{
return pno;
}

char* retprice()
{
return price;
}

char* retname()
{
return name;
}
};

fstream fp,wr;
product pr;
void write_pr()
{
fp.open(fname,ios::out|ios::app);
pr.create_pr();
fp.write((char*)&pr,sizeof(product));
fp<<"\n";
fp.close();
cout<<"\n\nProduct has been added. ";
getchar();
}

void display_all_pr()
{
clrscr();
cout<<"\n\n\n\t\t--All Products--\n\n";
fp.open(fname,ios::in);
while(!fp.eof())
while(fp.read((char*)&pr,sizeof(product)))
{
fp.seekg(fp.tellg()+2,ios::beg);
pr.show_pr();
cout<<"\n\n-------------------------------\n";
getchar();
}
fp.close();
getch();
}

void display_sp(int n)
{
bool found=false;
char s[15];
itoa(n,s,10);
fp.open(fname,ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
fp.seekg(fp.tellg()+2,ios::beg);

if(strcmp(pr.retpno(),s)==0)
{
clrscr();
pr.show_pr();
found=true;
}
}
fp.close();
if(found==false)
cout<<"\n\nproduct not available";
getchar();
}

void modify_pr()
{
char no[15];
clrscr();
bool found=false;
cout<<"\n\n\tPlease enter the product no. to modify";
cin>>no;
fp.open(fname,ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product)) && found==false)
{
fp.seekg(fp.tellg()+2,ios::beg);
if(strcmp(pr.retpno(),no)==0)
{
pr.show_pr();
cout<<"\nEnter new details of the product"<<endl;
pr.create_pr();
int pos=-1*sizeof(pr);
fp.seekp(pos-2,ios::cur);
fp.write((char*)&pr,sizeof(product));
cout<<"\n\n\t Product updated";
found=true;
}
}
fp.close();
if(found==false)
cout<<"\n\n Product not found\n ";
getch();
}

void menu()
{
clrscr();
fp.open(fname,ios::in);
cout<<"\n\n\t\tProduct Menu\n\n";
cout<<"--------------------------------\n";
cout<<"P.NO.\t\tName\t\tPrice\n";
cout<<"------------------------------------\n";
while(fp.read((char*)&pr,sizeof(product)))
{
fp.seekg(fp.tellg()+2,ios::beg);
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fp.close();
}

void pr_order()
{
char order_arr[30][50],quan[30][50];
int c=0;
float amt,damt,total=0;

char ch='Y';
menu();
cout<<"\n-------------------";
cout<<"\n Place your order";
cout<<"\n-------------------\n";
wr.open("buffer11.txt",ios::out|ios::app|ios::binary);
do
{
cout<<"\n\nEnter the product no. : ";
cin>>order_arr[c];
cout<<"\nQuantity : ";
cin>>quan[c];
c++;
cout<<"\nDo u want 2 order another product ? (y/n)";
cin>>ch;
}while(ch=='y'||ch=='Y');
wr<<"-------------------------------------------------------\n";
wr<<"Product no.\tQuantity\tPrice\tNet amount\n";
wr<<"-----------------------------------------------------\n";
cout<<"\n\nThank u for placing order";
getch();
clrscr();
cout<<"\n\n--------------Invoice-------------------\n";
cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount"  ;
for(int x=0;x<=c;x++)
{
fp.open(fname,ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
fp.seekg(fp.tellg()+2,ios::beg);
if(strcmp(pr.retpno(),order_arr[x])==0)
{
wr.write((char*)&order_arr[x],sizeof(char));
wr<<"\t\t";
wr.write((char*)&quan[x],sizeof(char));
wr<<"\t\t";
amt=atof(pr.retprice())*atof(quan[x]);
cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()   ;
cout<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt;
total=total+amt;
wr<<pr.retprice();
wr<<"\t\t"<<amt;
wr<<"\n";
}//if
}//while
fp.close();
}//for
wr<<"\t\t\t\t\ttoatal amount:"<<total<<"\n\n";
wr.close();
cout<<"\n\n\t\t\t\t\tTotal amount = "<<total;
getchar();
}
void a_menu()
{
clrscr();
char ch2;
cout<<"\n\n\n\tADMIN MENU\n";
cout<<"\n\n\t1.Create product";
cout<<"\n\n\t2.Display all products";
cout<<"\n\n\t3.Query ";
cout<<"\n\n\t4.Modify product";
cout<<"\n\n\t5.View product menu";
cout<<"\n\n\t6.Back to main menu\n";
cout<<"\n\n\tEnter ur choice.\n ";
cin>>ch2;
switch(ch2)
{
case '1':clrscr();
write_pr();
break;
case '2':display_all_pr();break;
case '3':int num;
clrscr();
cout<<"\n\n\tPlease enter the product no. ";
cin>>num;
display_sp(num);
break;
case '4':modify_pr();break;
case '5':menu();
getch();
case '6':break;
default:cout<<"\a";a_menu();
}
}

void main()
{
char ch;
clrscr();
cout<<"enter filename";
cin>>fname;
do
{
clrscr();
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t1.Customer";
cout<<"\n\n\t2.Administrator";
cout<<"\n\n\t3.Exit";
cout<<"\n\n\tEnter ur choice ";
cin>>ch;
switch(ch)
{
case '1':clrscr();
pr_order();
getch();
break;
case '2':a_menu();
break;
case '3':exit(0);
default :cout<<"\a";
}
}while(ch!='3');
}