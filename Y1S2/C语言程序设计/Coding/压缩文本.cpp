#include<stdio.h>  
    #include<string.h>  
    int main(){  
        int word=0,i=0,j=0,k=0,flag=1,m=0;  
        char s[500],words[10000][100],a[500];  
        for(i=0;i<10000;i++)  
           for(j=0;j<100;j++)  
              words[i][j]='\0';  
        while(gets(a) != NULL){
            if('\0'==a[0]){printf("\n");continue;} 
            for(i=0;a[i]!='\0';i++)s[i+1]=a[i];
            s[0]='.';s[i+1]='\0';k=0; i=1; 
            while(s[i]!='\0'){
               if((s[i]>='a' && s[i]<='z')||(s[i]>='A' && s[i]<='Z')){  
                   if(!((s[i-1]>='a' && s[i-1]<='z')||(s[i-1]>='A' && s[i-1]<='Z'))){
					   word++;k=0;words[word][k++]=s[i];}
                   else{words[word][k++]=s[i]; }
				   if(!((s[i+1]>='a' && s[i+1]<='z')||(s[i+1]>='A' && s[i+1]<='Z'))){  
                       words[word][k]='\0';  
                       flag=1;  
                       for(j=1;j<word;j++){  
                           if(!strcmp(words[j],words[word])){  
                               printf("%d",j);  
                               for(m=0;m<100;m++){words[word][m]='\0';} 
                               word--;   
                               flag=0;  
                               break;  
                            }  
                        }  
                        if(flag){printf("%s",words[word]);}}   
               }else{  
                   putchar(s[i]);  
               }i++;  }
            printf("\n"); 
            }    
        return 0;  
    }