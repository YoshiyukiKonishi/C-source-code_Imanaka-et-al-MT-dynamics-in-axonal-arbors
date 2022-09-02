#include<stdio.h>//
#include<stdlib.h>//
#include<time.h>//

int main(){//
    FILE *gp1,*gp2,*fp,*fp2,*data;//
    if((fp=fopen("test.txt","w+"))==NULL)
        printf("file error¥n");//
    if((fp2=fopen("test2.txt","w+"))==NULL)
        printf("file error¥n");
    if((data=fopen("test3.txt","w+"))==NULL)
        printf("file error¥n");
    
    int **mic,**mic2;//
    int *tip,*tip2;//
    int *tot,*tot2;//
    double *ave,*ave2;//
    int *invi,*invi2;//
    int *count,*count2;//
    int i,j,k,l,t;
    int vg=120,vs=250;//
    double kc=0.154,kr=0.05;//kc and kr are opposite
    int branch=20000;//
    int measure=30000;//
    int diff,diff2;
    int q=0,p=0,r;//条件
    int num,num2,lengh,lengh2;
    srand((unsigned)time(NULL));//
    
    printf("length of L\n");
    scanf("%d¥n",&lengh);//
    num=(100*lengh)/10000;//
    printf("Number of MTs%d\n",num);
    printf("length of S\n");
    scanf("%d¥n",&lengh2);//
    num2=(100*lengh2)/10000;//
    printf("Number of MTs%d\n",num2);
    
    
    //
    count=(int *)malloc(sizeof(int)*lengh);
    tot=(int *)malloc(sizeof(int)*lengh);
    ave=(double *)malloc(sizeof(double)*lengh);
    tip=(int *)malloc(sizeof(double)*lengh);
    invi=(int *)malloc(sizeof(int)*num);
    mic=(int **)malloc(sizeof(int *)*num);//age　mic[num][lengh]
    for(i=0;i<num;i++)//
        mic[i]=(int *)malloc(sizeof(int)*lengh);
    
    
    count2=(int *)malloc(sizeof(int)*lengh2);
    tot2=(int *)malloc(sizeof(int)*lengh2);
    ave2=(double *)malloc(sizeof(double)*lengh2);
    tip2=(int *)malloc(sizeof(double)*lengh2);
    invi2=(int *)malloc(sizeof(int)*num2);
    mic2=(int **)malloc(sizeof(int *)*num2);//mic[num][lengh]
    for(i=0;i<num2;i++)
        mic2[i]=(int *)malloc(sizeof(int)*lengh2);
    
    
    
    
    //
    for(i=0;i<lengh;i++){
        count[i]=0;
        tot[i]=0;
        ave[i]=0;
    }
    for(i=0;i<num;i++){
        tip[i]=0;
        invi[i]=0;
    }
    for(i=0;i<lengh;i++){
        for(j=0;j<num;j++)
            mic[j][i]=0;
    }
    for(i=0;i<num;i++){
        tip[i]=(int)rand()*(lengh+1.0)/(1.0+RAND_MAX);//
        k=tip[i];
        invi[i]=tip[i];
        mic[i][k]=1;
    }//
    
    
    for(i=0;i<lengh2;i++){
        count2[i]=0;
        tot2[i]=0;
        ave2[i]=0;
    }
    
    
    for(i=0;i<num2;i++){
        tip2[i]=0;
        invi2[i]=0;
    }
    
    for(i=0;i<lengh2;i++){
        for(j=0;j<num2;j++)
            mic2[j][i]=0;
    }
    
    
    
    for(i=0;i<num2;i++){
        tip2[i]=(int)rand()*(lengh2+1.0)/(1.0+RAND_MAX);//
        k=tip2[i];
        invi2[i]=tip2[i];
        mic2[i][k]=1;
    }
    
    
    
    //
    for(t=0;t<10000;t++){
        for(i=0;i<num;i++){
            if(q==0){//
                tip[i]=tip[i]+vg;
                if(tip[i]>lengh){
                    tip[i]=lengh;
                    q=1;
                }
                else if(tip[i]<lengh){
                    r=(int)(rand()*(1000-1.0)/(1.0+RAND_MAX));
                    if(r<100*kc)
                        q=1;
                }
                
                for(j=invi[i];j<tip[i];j++)
                    mic[i][j]++;
            }
            else if(q==1){//
                tip[i]=tip[i]-vs;
                if(tip[i]<invi[i]){
                    for(j=0;j<invi[i]+1;j++)
                        mic[i][j]=0;
                    tip[i]=invi[i];
                    q=2;//
                }
                else if(tip[i]>invi[i]){
                    r=(int)(rand()*(1000-1.0)/(1.0+RAND_MAX));
                    if(r<100*kr)
                        q=0;
                }
                for(j=invi[i];j<tip[i];j++)
                    mic[i][j]++;
                for(j=tip[i];j<lengh;j++)
                    mic[i][j]=0;
            }
            else if(q==2){
                r=(int)(rand()*(1000-1.0)/(1.0+RAND_MAX));
                if(r<100*kr)
                    q=0;
            }
        }//
        
        
        for(i=0;i<num2;i++){
            if(p==0){//伸長
                tip2[i]=tip2[i]+vg;
                if(tip2[i]>lengh2){
                    tip2[i]=lengh2;
                    p=1;
                }
                else if(tip2[i]<lengh2){
                    r=(int)(rand()*(1000-1.0)/(1.0+RAND_MAX));
                    if(r<100*kc)
                        p=1;
                }
                for(j=invi2[i];j<tip2[i];j++)
                    mic2[i][j]++;
            }
            else if(p==1){//
                tip2[i]=tip2[i]-vs;
                if(tip2[i]<invi2[i]){
                    for(j=0;j<invi2[i]+1;j++)
                        mic[i][j]=0;
                    tip2[i]=invi2[i];
                    p=2;
                }
                else if(tip2[i]>invi2[i]){
                    r=(int)(rand()*(1000-1.0)/(1.0+RAND_MAX));
                    if(r<100*kr)
                        p=0;
                    
                }
                for(j=invi2[i];j<tip2[i];j++)
                    mic2[i][j]++;
                for(j=tip2[i];j<lengh2;j++)
                    mic2[i][j]=0;
            }
            else if(p==2){
                r=(int)(rand()*(1000-1.0)/(1.0+RAND_MAX));
                if(r<100*kr)
                    p=0;
                
                
            }
        }//
    }//
    
    
    //
    for(i=0;i<branch;i++){//
        for(j=0;j<num;j++){
            if(mic[j][i]!=0){
                tot[i]=tot[i]+mic[j][i];//
                count[i]++;//
            }
        }//
        for(j=0;j<num2;j++){
            if(mic2[j][i]!=0){
                tot[i]=tot[i]+mic2[j][i];
                count[i]++;
            }
        }//
        if(tot[i]!=0 && count[i]!=0)
        ave[i]=tot[i]/count[i];//
        ave2[i]=ave[i];
    }//
    for(i=branch;i<lengh;i++){
        for(j=0;j<num;j++){
            if(mic[j][i]!=0){
                tot[i]=tot[i]+mic[j][i];
                count[i]++;
            }
        }
        if(tot[i]!=0 && count[i]!=0)
            ave[i]=tot[i]/count[i];
    }//
    
    for(i=branch;i<lengh2;i++){
        for(j=0;j<num2;j++){
            if(mic2[j][i]!=0){
                tot2[i]=tot2[i]+mic2[j][i];
                count2[i]++;
            }
        }
        if(tot2[i]!=0 && count2[i]!=0)
            ave2[i]=tot2[i]/count2[i];
    }//
    diff=ave[measure]-ave2[measure];//
    printf("%d\n",diff);
    printf("%lf\n",ave2[measure]/ave[measure]);
    
    //
    for(i=0; i<=lengh; i=i+10)
        fprintf(fp,"%d %f\n",i, ave[i]);//
    for(i=0; i<=lengh2; i=i+10)
        fprintf(fp2,"%d %f\n",i, ave2[i]);//
    fprintf(data,"%d %f\n",lengh-70000,869.5128867);//
    fprintf(data,"%d %f\n",lengh-50000,670.4392902);
    fprintf(data,"%d %f\n",lengh-30000,516.9432779);
    fprintf(data,"%d %f\n",lengh-10000,398.5899342);
    
    
    
    fclose(fp);
    fclose(fp2);
    fclose(data);

    /* ---- export to gnuplot--*/
    gp2 = popen("gnuplot -persist","w");//
    fprintf(gp2, "set xrange [0:lengh]\n");//
    fprintf(gp2, "set yrange [0:2000]\n");//
    fprintf(gp2,"plot 'test.txt' with lines\n");//
    fprintf(gp2,"replot 'test2.txt' with lines\n");
    //fprintf(gp2,"replot 'test3.txt' with lines\n");//
    fprintf(gp2,"exit¥n");//
    fflush(gp2);//
    
    pclose(gp2);//
    return 0;
}
