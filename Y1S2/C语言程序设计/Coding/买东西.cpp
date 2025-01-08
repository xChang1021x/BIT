#include <stdio.h>   
   
typedef struct buy   
{  char  gname;   
   int   sname;   
   int   gprice;   
} BUY;   
   
int main( )   
{  int i, j, n;   
   int min, price[10][3];   
   int findm( int n, int price[][3], BUY scheme[] );   
   
   static BUY scheme[3]={ {'A', 0, 0}, {'B', 0, 0}, {'C', 0, 0} };   
   
   scanf( "%d", &n );   
   for( i = 0; i < n; i++ )   
    for( j = 0; j < 3; j++ )   
       scanf( "%d", &price[i][j] );   
   
   min = findm( n, price, scheme );   
   
   printf("Total Money are : %d\nGoods-Name  Shop-Name  Goods-Price\n", min );   
   for ( i=0; i < 3; i++ )   
       printf("         %c:%10d%13d\n", scheme[i].gname, scheme[i].sname, scheme[i].gprice );   
   return 0;   
}   
 
int findm(int n, int gp[][3], BUY schm[]) 
{ 
int iPriceA=0,iPriceB=0,iPriceC=0; //记录价格 
int iMinA=0,iMinB=0,iMinC=0; //记录商店 
int itotale=0; //记录总价格 
int iMintotal=99999; //记录最小总价格 
 
for (int i=0;i<n;i++) 
{ 
for (int j=0;j<n;j++) 
{ 
if (j==i) 
{ 
continue; 
} 
else 
{ 
for (int k=0 ; k<n;k++) 
{ 
if (k==i || k==j) 
{ 
continue; 
} 
else 
{ 
itotale=gp[i][0]+gp[j][1]+gp[k][2]; 
if (itotale < iMintotal) 
{ 
iMintotal =itotale; 
iMinA=i; 
iMinB=j; 
iMinC=k; 
iPriceA=gp[i][0]; 
iPriceB=gp[j][1]; 
iPriceC=gp[k][2]; 
} 
} 
} 
} 
} 
 
} 
 
schm->gname='A'; 
schm->sname=iMinA+1; 
schm->gprice=iPriceA; 
 
(schm+1)->gname='B'; 
(schm+1)->sname=iMinB+1; 
(schm+1)->gprice=iPriceB; 
 
(schm+2)->gname='C'; 
(schm+2)->sname=iMinC+1; 
(schm+2)->gprice=iPriceC; 
 
return iMintotal; 
 
}  