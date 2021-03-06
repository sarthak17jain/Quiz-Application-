#include<conio.h>
#include<math.h>
#include<fstream.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include <iostream.h>


int quiz();
void playermode();
void adminmode();
void deleteques();
void insertques();

void main()
{ clrscr();
  cout<<"Welcome to the quiz!!!"<<endl;
  int choice;
do
{
  cout<<"\nChoose option"<<endl;
  cout<<"1.Admin"<<endl;
  cout<<"2.Player"<<endl;
  cout<<"3.Exit"<<endl;
  cout<<"Enter your choice: ";
  cin>>choice;
  switch (choice)
  { case 1: adminmode();
	    break;
    case 2: playermode();
	    break;
    case 3: cout<<"THANKS!!!";
	    break;
    default:
       cout<<"\Wrong Choice....Try again";
       break;
  }
}while (choice!=3);
getch();
}

int quiz()
{ clrscr();
  int x,i=0,store[20],k=0,j;
  randomize();
  while(i<20)
   {  x=random(20)+1;
	  //cout<<x<<" ";
	  for (j=0;j<i;j++)
	{ if (store[j]==x)
		k=1;
	}
	  if (k==0)
	   {store[i]=x;
	i++;}
	  k=0;
   }
  cout<<endl;
  //for(j=0;j<20;j++)
  // {cout<<store[j]<<" ";}
  cout<<endl;
  fstream f;
  f.open("qtest.txt", ios::in,ios::beg);
  // first 2 lines of text file should be blank
  //question in 1 line whole then 4 options in 4 consecutive line
  //followed by line and then ans option
  //followed by a space
  char l[100];
  char check[100];
  int score=0;
  for(i=0;i<5;i++)
   { for(j=0;j<2+(store[i]-1)*8;j++)
	  {f.getline(l,100);}
	 for(j=0;j<6;j++)
	  {f.getline(l,100);
	   puts(l);}
	 f.getline(l,100);
	 cout<<"Enter option: ";
	 gets(check);
	 if (strcmpi(check,l)==0)
	   { score++;
	     cout<<"Correct Answer!!!"<<endl;}
	 else {cout<<"Wrong Answer!!!"<<endl;}
	 cout<<"Your score is "<<score<<endl;
	 f.seekg(0,ios::beg);
	 getch();
   }

  f.close();
  return score;
}

void playermode()
{int noofplayer,result[3],i,l,hscorer;
 cout<<"Enter number of players(max 3): ";
	    cin>>noofplayer;
	    for (i=0;i<noofplayer;i++)
	      {result[i]=quiz();}
	    for (i=0;i<noofplayer;i++)
	      {cout<<"\nPlayer "<<i+1<<" scored "<<result[i];}
	    l=result[0];
	    for (i=0;i<3;i++)
	      {if (l<=result[i])
		 {l=result[i];
		  hscorer=i;}
	      }
	    cout<<"\nPlayer "<<hscorer+1<<" is the winner with a score of "<<l;
}


void adminmode()
{ int choice;
do
{
  cout<<"\nChoose option"<<endl;
  cout<<"1.Insert a question in database"<<endl;
  cout<<"2.Delete a question in database"<<endl;
  cout<<"3.Exit"<<endl;
  cout<<"Enter your choice: ";
  cin>>choice;
  switch (choice)
  { case 1:insertques();
	   break;
    case 2:deleteques();
	   break;
    case 3:break;
    default:
       cout<<"\Wrong Choice....Try again";
       break;
  }
}while (choice!=3);

}


void deleteques()
{int q,j,c;
 char l[100];
 cout<<"Enter the question you want to delete: ";
 cin>>q;
 fstream fd;
 fd.open("qtest.txt", ios::in);

 for(j=0;j<2+(q-1)*8;j++)
    {fd.getline(l,100);}
 cout<<"Are you sure you want to delete the following question"<<endl;
 for(j=0;j<6;j++)
    {fd.getline(l,100);
     puts(l);}
 fd.getline(l,100);
 cout<<"Choose option"<<endl;
 cout<<"1.YES"<<endl;
 cout<<"2.NO"<<endl;
 cout<<"Enter your choice: ";
 cin>>c;
 if (c==1)
   { ofstream ftemp;
     ftemp.open("temp.txt",ios::out);
     fd.seekg(0,ios::beg);
     for(j=0;j<2+(q-1)*8;j++)
      {fd.getline(l,100);
       ftemp<<l<<endl;
      }
     for(j=0;j<8;j++)
      {fd.getline(l,100);}
     while(!fd.eof())
     {fd.getline(l,100);
      ftemp<<l<<endl;}
     ftemp.close();
     fd.close();
     remove("qtest.txt");
     rename("temp.txt","qtest.txt");
     cout<<"Question successfully deleted!!!";
   }
  else if(c==2)
    {fd.close();}
}


void insertques()
{  ofstream fin;
   fin.open("qtest.txt",ios::ate,ios::end);
   char l[100];
   fin<<endl;
   fin<<endl;
   cout<<"Write the queston statement you want to insert"<<endl;
   gets(l);
   fin<<l<<endl;
   cout<<"Write option A: ";
   gets(l);
   fin<<l<<endl;
   cout<<"Write option B: ";
   gets(l);
   fin<<l<<endl;
   cout<<"Write option C: ";
   gets(l);
   fin<<l<<endl;
   cout<<"Write option D: ";
   gets(l);
   fin<<l<<endl;
   fin<<endl;
   cout<<"Write correct option: ";
   gets(l);
   fin<<l;
   fin.close();
   cout<<"Question successfully inserted!!!";
}

