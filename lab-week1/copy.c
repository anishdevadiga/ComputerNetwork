//Name: Shashank
//Regno: 230970004
//date: 25-07-2024

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
	char buffer[100],source[20],dest[20];
	ssize_t bytesRead;
	
	printf("Enter the file name to copy: ");
	scanf("%s",source);
	const char *pathname=source;
	int fd= open(pathname,O_RDONLY);	

	bytesRead= read(fd,buffer,sizeof(buffer)-1);
	
	if(bytesRead == -1)
	{
		perror("Error reading from file!");
		return 1;
	}

	printf("\nEnter destination file name: ");
	scanf("%s",dest);

	int fd2=creat(dest,0666);
	if(fd==-1){
		perror("Error creating file");
		return 1;
	}
	
	int bytes_written=write(fd2,buffer,sizeof(buffer));
	if(bytes_written==-1){
		perror("Error writing to file");
		return 1;
	}
	printf("File copied successfully!\n");
	
	return 0;
}