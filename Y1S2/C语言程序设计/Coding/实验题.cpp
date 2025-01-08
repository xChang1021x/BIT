#include <stdio.h>

#include <stdlib.h>

 

void useLocal(void);

void useStaticLocal(void);

void useGlobal(void);

 

int x = 1; /*【1】*/

int main(void)

{

       int x = 5; /*【2】*/

       printf("local x in outer scope of main is %d\n",x); /*( A )*/

       {/*start a new scope*/

              int x = 7; /*【3】*/

              printf("local x in outer scope of main is %d\n",x); /* ( B )*/

       }/*end new scope*/

 

 

       useLocal();/*(  C  )*/

       useStaticLocal();/*( D )*/

       useGlobal();/*( E )*/

 

       useLocal();/*( F )*/

       useStaticLocal();/*( G )*/

       useGlobal();/*( H )*/

 

       printf("\nlocal x in main is %d\n",x); /*( I )*/

       system("pause");

       return 0;

 

}

 

void useLocal(void)

{

       int x = 25;

       printf("\nlocal x in useLocal is %d after entering useLocal\n",x); /* ( C1,F1 )*/

       x++;

       printf("local x in useLocal is %d before exiting useLocal\n",x); /*( C2,F2 )*/

}

void useStaticLocal(void)

{

       static int x = 50;

 

       printf("\nlocal static x is %d on entering useStaticLocal\n",x); /*( D1,G1 )*/

       x++;

       printf("local static x is %d on exiting useStaticLocal\n",x); /*( D2,G2 )*/

 

}

void useGlobal(void)

{

       printf("\nglobal x is %d on entering useGlobal\n",x); /*( E1,H1 )*/

       x*=10;

       printf("global x is %d on exiting useGlobal\n",x); /*( E2,H2 )*/

}