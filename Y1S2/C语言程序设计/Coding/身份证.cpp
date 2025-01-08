#include<stdio.h>
#include<string.h>

int main(){
 int n;
 char a[50];
 int w[20]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
 scanf("%d",&n);
 for(int i=0;i<n;++i)
 {
  int sum=0,m=8;
  getchar();
  scanf("%s",&a);
  int k=strlen(a);
  if(k==18)
  {
   
   int l=0;
   for(int i=0;i<k-1;++i)
   {
    sum+=(a[i]-'0')*w[i];
   }
   int y=sum%11;
   if(y==0)
   {
    y=1;
   }
   else if(y==1)
   {
    y=0;
   }
   else{
    for(int i=2;i<=10;++i)
    {
     l=i+m;
     m-=2;
     if(y==i)
     {
      y=l;
      break;
     }
    }
   }
   
   if(a[17]==y)
   {
    printf("Valid\n");
   }
   else if(a[17]=='X' && y==10)
   {
    printf("Valid\n");
   }
   else
   {
    printf("Invalid\n");
   }
  }
  else if(k==15){
   int yy;
   int p=6;
   int l=(a[k-3]-'0')*100+(a[k-2]-'0')*10+(a[k-1]-'0');
   if(l==996 || l==997 || l==998 || l==999)
   {
    yy=8;
   }
   else{
    yy=9;
   }
   for(int i=0;i<2;++i)
   {
    for(int j=p;j<17;++j)
    {
     int swap=a[j+1];
     a[j+1]=a[p];
     a[p]=swap;
    }
    ++p;
   }
   a[6]='1';
   a[7]=yy+'0';
   for(int i=0;i<17;++i)
   {
    sum+=(a[i]-'0')*w[i];
   }
   int y=sum%11;
   if(y==0)
   {
    y=1;
   }
   else if(y==1)
   {
    y=0;
   }
   else{
    for(int i=2;i<=10;++i)
    {
     l=i+m;
     m-=2;
     if(y==i)
     {
      y=l;
      break;
     }
    }
   }
   for(int i=0;i<k+2;++i)
   {
    printf("%c",a[i]);
   }
   if(y==10)
   {
    printf("X\n");
   }
   else
   {
    printf("%d\n",y);
   }
   
  }
 else printf("Invalid\n");
 }
 
 return 0;
}