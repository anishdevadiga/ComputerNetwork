
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>

int main(){
	char msg[25],rmsg[25];
	int fp[2],pid;
	pipe(fp);
	pid=fork();
	
	if(pid>0){
		printf("Enter the string:\n");
		fgets(msg,sizeof(msg),stdin);
		close(fp[0]);
		write(fp[1],msg,25);
		wait(NULL);
	}else{
		close(fp[1]);
		read(fp[0],rmsg,25);
		
		int chcount=0,dcount=0;
		for(int i=0;rmsg[i]!='\0';i++)
		{
			if(isdigit(rmsg[i]))
				dcount++;
			else if(isalpha(rmsg[i]))
				chcount++;
		}
		printf("No. of chars: %d\n",chcount);
		printf("No. of digits: %d\n",dcount);
					
	}
	return 0;
}
