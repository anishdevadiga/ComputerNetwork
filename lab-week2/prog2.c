
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
        char *result;
        int pp[2],pc[2],pid,n;
        pipe(pp);
        pipe(pc);
        pid=fork();

        if(pid==0){
                close(pc[0]);
                read(pp[0],&n,sizeof(n));
                close(pp[1]);

                int sum=0,rem,temp=n;
                while(temp!=0){
                        rem=temp%10;
                        temp=temp/10;
                        sum+=rem*rem*rem;
                }
                if(sum==n)
                        write(pc[1],"Yes",4);
                else
                        write(pc[1],"No",3);

        }else{
                printf("Enter the number:\n");
                scanf("%d",&n);

                close(pp[0]);
                write(pp[1],&n,sizeof(n));
                close(pc[1]);

                wait(NULL);

                read(pc[0],result,sizeof(result));

                if(result[0]=='Y'){
                        printf("The no. is Armstrong number.\n");
                }else{
                        printf("Not an Armstrong number.\n");
                }
        }
        return 0;
}