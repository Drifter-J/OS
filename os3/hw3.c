#include <stdio.h> 
#include <string.h> 
#include <unistd.h>

int showPidInfo1 (char* pid){
   FILE* fp; /* used for file open and read*/
   char buffer[1024]; /* save data in file*/
   size_t bytes_read1; /* for reading status file*/
   size_t bytes_read2; /*for reading statm file*/
   char* name; /* variable for process name*/
   char* token; /* variable for process name*/
   int vir; /* variable for process virtual memory*/
   int phy; /* variable for process physical memory*/
   int shar; /* variable for process shared memory*/
   int index = 0; /* variable for tokenizing data*/
   
   printf("%s\t",pid); 

   /* Read the entire contents of /proc/../status into the buffer. */
   /* in this case .. is 1 which is init process*/
   fp = fopen (("/proc/1/status"), "r"); 
   if(fp==NULL) return 0;
   bytes_read1 = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp);

   /* return nothing if read failed or if buffer isn't big enough.  */ 
   if (bytes_read1 == 0 || bytes_read1 == sizeof (buffer)) return 0;

   /* tokenize the data read from status*/
   /* first token that is read is Name: which is not needed */
   token = strtok(buffer, "\t\n\r "); 
   /* store name of the process into name character pointer*/
   name = strtok(NULL, "\t\n\r ");

   printf ("%s\t", name); 
   buffer[0] = '\0'; //initialzing buffer

   /* Read the entire contents of /proc/../statm into the buffer. */
   fp = fopen (("/proc/1/statm"), "r"); 
   if(fp==NULL) {     
      return 0;
   }

   bytes_read2 = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp);

   /* return nothing if read failed or if buffer isn't big enough.  */ 
   if (bytes_read2 == 0 || bytes_read2 == sizeof (buffer)) return 0;
   
   /* tokenize the data read from statm*/
   /*
   statm is like this:
   size       total program size <- we need this
              (same as VmSize in /proc/[pid]/status)
   resident   resident set size <- and this
              (same as VmRSS in /proc/[pid]/status)
   share      shared pages (from shared mappings) <- and this
   text       text (code) 
   lib        library (unused in Linux 2.6)
   data       data + stack
   dt         dirty pages (unused in Linux 2.6)
   */
   token = strtok(buffer, "\t\n\r ");
   while(token!=NULL){
      if(index==0){
         token = strtok(NULL, "\t\n\r ");
         /*these values are page sizes*/
         /*so they must be multiplied by 4 (1 page=4KB)*/
         /*ex. vir=400->400*4=1600(KB)*/
         vir = atoi(token)*4;
         printf ("%d\t", vir); 
      } else if(index==2){
         token = strtok(NULL, "\t\n\r ");
         phy = atoi(token)*4;
        printf ("%d\t\t", phy); 
      } else if(index==4){
         token = strtok(NULL, "\t\n\r ");  
         shar = atoi(token)*4;
         printf ("%d", shar);        
         break;
   }
      index++;
   }
   /*return the size of physical memory*/
   return phy; 
} 
/*basically repeating the above step*/
/*the only difference is that pid is changed*/
 int showPidInfo2 (char* pid){
   FILE* fp;
   char buffer[1024]; 
   size_t bytes_read1; 
   size_t bytes_read2; 
   char* name;
   char* token;
   int vir;
   int phy;
   int shar;
   int index = 0;
   
   printf("%s\t",pid);

   /* Read the entire contents of /proc/... into the buffer. */
   fp = fopen (("/proc/3289/status"), "r"); 
   if(fp==NULL) return 0;
   bytes_read1 = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp);
   
   token = strtok(buffer, "\t\n\r ");
   name = strtok(NULL, "\t\n\r ");
   
   printf ("%s\t", name); 
   buffer[0] = '\0';

   fp = fopen (("/proc/3289/statm"), "r"); 
   if(fp==NULL) {
      printf("garbage");
      return 0;
   }

   bytes_read2 = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp);

   /* return nothing if read failed or if buffer isn't big enough.  */ 
   if (bytes_read2 == 0 || bytes_read2 == sizeof (buffer)) return 0;
   
   token = strtok(buffer, "\t\n\r ");
   while(token!=NULL){
      if(index==0){
         token = strtok(NULL, "\t\n\r ");
         vir = atoi(token)*4;
         printf ("%d\t", vir); 
      } else if(index==2){
         token = strtok(NULL, "\t\n\r ");
         phy = atoi(token)*4;
        printf ("%d\t\t", phy); 
      } else if(index==4){
         token = strtok(NULL, "\t\n\r ");  
         shar = atoi(token)*4;
         printf ("%d", shar);
   break;        
      }
      index++;
   }
   
   return phy; 
}
int showPidInfo3 (char* pid){
   FILE* fp;
   char buffer[1024]; 
   size_t bytes_read1; 
   size_t bytes_read2; 
   char* name;
   char* token;
   int vir;
   int phy;
   int shar;
   int index = 0;
   
   printf("%s\t",pid);

   /* Read the entire contents of /proc/... into the buffer. */
   fp = fopen (("/proc/3311/status"), "r"); 
   if(fp==NULL) return 0;
   bytes_read1 = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp);
   
   token = strtok(buffer, "\t\n\r ");
   name = strtok(NULL, "\t\n\r ");
   
   printf ("%s\t", name); 
   buffer[0] = '\0';

   fp = fopen (("/proc/3311/statm"), "r"); 
   if(fp==NULL) {
      printf("garbage");
      return 0;
   }

   bytes_read2 = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp);

   /* return nothing if read failed or if buffer isn't big enough.  */ 
   if (bytes_read2 == 0 || bytes_read2 == sizeof (buffer)) return 0;
   
   token = strtok(buffer, "\t\n\r ");
   while(token!=NULL){
   if(index==0){
         token = strtok(NULL, "\t\n\r ");
         vir = atoi(token)*4;
         printf ("%d\t", vir); 
      } else if(index==2){
         token = strtok(NULL, "\t\n\r ");
         phy = atoi(token)*4;
        printf ("%d\t\t", phy); 
      } else if(index==4){
         token = strtok(NULL, "\t\n\r ");  
         shar = atoi(token)*4;
         printf ("%d", shar);        
         break;
   }
      index++;
   }
   return phy; 
}
 int main (){  
   int pid1wss; /*variables for comparing wss size*/
   int pid2wss;
   int pid3wss;
   int curPid1wss;
   int curPid2wss;
   int curPid3wss;
   int flag1; /*variables for printing * two time(0.5sec*2=1sec)*/
   int flag2;
   int flag3;
   int index = 120; /*0.5sec*120=60sec=1min*/

   printf("PID\tName\tVirtual\tPhysical\tShared\tWSS\n");
      while(index>0){
      /*first one doesn't need to be compared*/
      if(index==120){ 
         pid1wss=showPidInfo1("1");
         printf("\n");        
         pid2wss=showPidInfo2("3289");
         printf("\n");        
         pid3wss=showPidInfo3("3311");
         printf("\n");        
      }
      /*index: 199 to 1*/
      else{
         /*store a returned size of a physical memory into curPidwss*/
         curPid1wss=showPidInfo1("1");
         /*if a current wss is not equal to a previous wss 
         then set flag to 2 (flag--; makes it 1 at the end of while{})*/
         if(pid1wss!=curPid1wss){
            flag1 = 2;
         /*since wss has been changed print * and goto next line*/
            printf ("\t*\n");   
         }
         /*flag is 1 print * again, in this way * is printed twice
         (0.5sec*2=1sec)*/
         else if(flag1 == 1){
            printf ("\t*\n"); 
         }else{
            printf("\n");
         }
         /*basically a repeatition*/
         curPid2wss=showPidInfo2("3289");
         if(pid2wss!=curPid2wss){
            flag2 = 2;
            printf ("\t*\n");   
         }else if(flag2 == 1){
            printf ("\t*\n"); 
         }else{
            printf("\n");
         }
         curPid3wss=showPidInfo3("3311");
         if(pid3wss!=curPid3wss){
            flag3 = 2;
            printf ("\t*\n");   
         }else if(flag3 == 1){
            printf ("\t*\n"); 
         }else{
            printf("\n");
         }
         pid1wss=curPid1wss;
         pid2wss=curPid2wss;
         pid3wss=curPid3wss;
      }
      index--;
      flag1--;
      flag2--;
      flag3--;
      /*delay for 500000microsec=0.5sec*/         
      usleep(500000);
   }
   return 0; 
}  