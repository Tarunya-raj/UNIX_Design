/*
Understanding of UNZX File system
1. Hierachical structure (File path , current directory, parent directory)
2. Consistent treatment of data ( Regular , Directory and Peripheral Devices Files). 
	Unformatted stream of bytes
3. The ability to create and delete files (system calls)
4. Dynamic growth of files.
5. Protection of file data.
6. peripheral devices is also treated as files.

*/


#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
void copy(int ,int);
int main(int argc, char* argv[])
{
	if(argc!= 3)
	{
		write(2, "Invalid number of arguments", sizeof("Invalid number of arguments"));
		return -1;
	}
	int sourceFD=-1, destinationFD=-1;
	sourceFD=open(argv[1], O_RDONLY);
	if(sourceFD<0)
	{
		//write(2,"Source file not opening", sizeof("Source file not opening"));
		perror("Source file opening Failed");
		return -1;
	}
	destinationFD=open(argv[2],O_WRONLY| O_CREAT| O_TRUNC,0666);

	if(destinationFD<0)
	{
		//write(2, "Destination file oepning/creation failed", sizeof("Destination file opening/creation failed"));
		perror("Destination file opening Failed");
		close(sourceFD);
		return -1;
	}
	copy(sourceFD, destinationFD);
	close(sourceFD);
	close(destinationFD);
	return 0;
}
void copy(int sourceFD, int destinationFD)
{

	int MAX_SIZE=1024;
	char buffer[MAX_SIZE];
	int readCharacters=0;
	while((readCharacters=read(sourceFD, buffer, MAX_SIZE))>0)
	{
		write(destinationFD,buffer,readCharacters);
	}
	if(readCharacters<0)
	{
		
	//	write(2, "Copying failed", sizeof("Copying failed"));
		perror("Copy Failed");
	}
}
