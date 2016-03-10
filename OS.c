#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "PageTable.h"

void PrintPageTable(page_table_entry PageTable[],int NumberOfPages) {

    int Index;

    for (Index =  0;Index < NumberOfPages;Index++) {
        printf("%2d: Valid=%1d Frame=%2d Dirty=%1d Requested=%1d\n",Index,
PageTable[Index].Valid,PageTable[Index].Frame,PageTable[Index].Dirty,
PageTable[Index].Requested);
    }

}

int main() {

	int page; //atoi(argv[1]);
	int frame; //atoi(argv[2]);
	int SegmentID;
	//coba coba
	page_table_pointer PageTable;
	int OSPID = getpid();
	int SharedMemoryKey = OSPID;
	char arguments[255], charPID[10];
	pid_t pidFork;
	const char* command = "./MMU";

	//input page and frame
	printf("> OS ");
	scanf("%d %d", &page, &frame); getchar();

	printf("The shared memory key (PID) is %d\n", OSPID);
	
	//initialing page_table_entry
	SegmentID = shmget(SharedMemoryKey,page*sizeof(page_table_entry), IPC_CREAT | S_IRUSR | S_IWUSR);
	PageTable = (page_table_pointer)shmat(SegmentID,NULL,0);
	//printf("Segment = %d\n", SegmentID);
	printf("Initialized page table\n");
	for (int i=0; i<page; i++) {
	//page_table_entry page_table[page];
		PageTable[i].Valid = 0;
		PageTable[i].Frame = -1;
		PageTable[i].Dirty = 0;
		PageTable[i].Requested = 0;	
	}
	PrintPageTable(PageTable, page);
	

	///get argument
	printf("> MMU ");
  	fgets(arguments, sizeof(arguments), stdin);
  	size_t len = strlen(arguments);
  	if (arguments[len - 1] == '\n') {  // FAILS when len == 0
    	arguments[len -1] = '\0';
  	}

  	strcat(arguments, " ");
  	snprintf(charPID, sizeof(charPID), "%d", OSPID);
  	strcat(arguments, charPID);
  	puts(arguments);

  
  	if (pidFork = fork() < 0) {
  		puts("ERROR");
  		exit(EXIT_FAILURE);
  	} else if (pidFork == 0) {
  		printf("I'm children\n");
  		//execvp(command, arguments);
  		printf("Uh oh! If this prints, execvp() must have failed\n");
		//exit(EXIT_FAILURE);
  	} else {
  		puts ("This is a message from the parent");
	}

	return 0;
}