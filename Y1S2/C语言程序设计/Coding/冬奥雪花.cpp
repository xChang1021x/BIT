#include <stdio.h>

#define N 729

void draw(char a[][N], int n, int row, int col)

{

       if(n==0){

              a[row][col] = '*';

              return;

       }

       int w = 1;

       int i;

       for(i=1; i<=n-1; i++) w *= 3;

       draw(a,n-1, row+w, col);

       draw(a,n-1, row, col+w);

       draw(a,n-1, row+w,col+w);

       draw(a,n-1, row+2*w, col+w);

       draw(a,n-1, row+w,col+2*w);

        }

int main()

{

       char a[N][N];

       int n,w,i,j;

       for(i=0;i<N;i++)

         for(j=0;j<N;j++)

              a[i][j] = ' ';

       scanf("%d",&n);
		n=n-1;
       w=1;

       for(i=1; i<=n; i++) w *= 3;

       draw(a,n,0,0);

       for(i=0; i<w; i++)

       {

              for(j=0; j<w; j++)
					if(j==0)
					{
						printf("%c",a[i][j]);
					}
					else
					{
						printf(" %c",a[i][j]);
					}
                    

              printf("\n");

       }

       return 0;

}