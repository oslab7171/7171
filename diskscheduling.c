#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <stdbool.h>



void fcfs(int n, int head, int arr[]){
    float seektime=0;
    float avfseektime=0;

    int prevhead=head;

    for(int i=0; i<n; i++){
        printf("\ncurrent %d ", arr[i]);

        seektime += abs(prevhead - arr[i]);
        prevhead= arr[i];
    }

    avfseektime=seektime/(float)n;
    printf("\nTottal seektime: %f\n", seektime);
    printf("\navgseektime: %f\n", avfseektime); 
}










void scan(int n, int head, int arr[]){
    float seektime=0;
    float avfseektime=0;


    // sort ...... find starting i.... go right ........ then start from 0 then start going right again
    int copyarr[n];
    for(int i=0 ; i<n ; i++)copyarr[i]=arr[i];

    for(int i=0; i<n ;i++){
        for(int j=i+1; j<n ; j++){
            if(copyarr[i]>copyarr[j]){
                // swap(copyarr[j],copyarr[i]);
                int t=copyarr[j];
                copyarr[j]=copyarr[i];
                copyarr[i]=t;
            }
        }
    }

    int startingpos=0;
    while(head>copyarr[startingpos])startingpos++;
    startingpos--;

    // starting pos....... it will be wither equal or greater than head...... say head is 50 

    // going left............. in sorted array  40 39 21 10...
    int prevhead=head;
    for(int i=startingpos; i>=0; i--){
        printf("\ncurrent %d ", copyarr[i]);
        seektime += abs(prevhead - copyarr[i]);
        prevhead= copyarr[i];
    }

    if(prevhead!=0){
        // hit till end of disc
        printf("\ncurrent %d ", 0);
        seektime += abs(prevhead -0);
        prevhead=0;
    }
    


    


    // goind  up...... 52 60 70 .. 199 ...  
    for(int i=startingpos+1; i<n; i++){
        printf("\ncurrent %d ", copyarr[i]);

        seektime += abs(prevhead - copyarr[i]);
        prevhead= copyarr[i];
    }



    avfseektime=seektime/(float)n;

    printf("Tottal seektime: %f\n", seektime);
    printf("avgseektime: %f\n", avfseektime); 
}








void ss(int n, int head, int arr[]){
    float seektime=0;
    float avfseektime=0;

    int prevhead=head;

    bool visited[n];
    
    for(int i=0 ; i<n ; i++)visited[i]=0;


    for(int i=0; i<n; i++){
        // find next shortest seek position
        int diff= INT_MAX;
        int next= -1;

        for(int j=0; j<n; j++){
            if(abs(prevhead-arr[j]) < diff &&  visited[j]==0){
                diff=abs(prevhead-arr[j]);
                next = j;
                
            }
        }



        visited[next]=1;

        seektime += abs(prevhead - arr[next]);
        printf("\ncurrent %d ", arr[next]);

        prevhead= arr[next];
    }
    avfseektime=seektime/(float)n;

    printf("Tottal seektime: %f\n", seektime);
    printf("avgseektime: %f\n", avfseektime); 
}

















int main(){
    int n;
    printf("Enter numver of requests:");
    scanf("%d",&n);

    int req[n];
    printf("Enter request array: ");
    for(int i=0; i<n; i++){
        scanf("%d", &req[i]);
    }

    printf("Enter initail head pos:");
    int head=0;
    scanf("%d",&head);

    printf("\nfcfs");

    fcfs(n,head,req);

    printf("\nscan elevator:");
    scan(n,head,req);
    printf("\nsstf elevator:");

    ss(n,head,req);


    return 0;
}