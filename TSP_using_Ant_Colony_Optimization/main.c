#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define Q 1
#define P .8
#define alpha 0.7
#define beta 0.7

int next_edge_selection(int n,double attarctiveness[n][n],double pheromon_distribution[n][n],
                        int city,int visited[n]) {

    double div=0;
    double p=0;
    int ncity,k;
    for(k=0;k<n;k++)
    {
        if(visited[k]==0)
        {
            div+=pow(pheromon_distribution[city][k],alpha)*pow(attarctiveness[city][k],beta);
        }
    }
    for(k=0;k<n;k++)
    {
        if(visited[k]==0&&attarctiveness[city][k]!=0)
        {
            double res=pow(pheromon_distribution[city][k],alpha)*pow(attarctiveness[city][k],beta)/div;
            if(res>p)
            {
                p=res;
                ncity=k;
            }
        }
    }
    return ncity;
}

void pheromon_update(int n,double pheromon_distribution[n][n],double path_length[n],int visited[n][n],double min_path_length)
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            double addition_of_pheromon=0;
            for(k=0;k<n;k++)
            {
                if(((visited[k][j]-visited[k][i])==1||(visited[k][i]-visited[k][j])==n-1)&&path_length[k]==min_path_length)
                {
                    addition_of_pheromon+=Q/path_length[k];
                }
            }
            pheromon_distribution[i][j]=(1-P)*pheromon_distribution[i][j]+addition_of_pheromon;
        }
    }
}

void print_pheromon_distribution(int n,double pheromon_distribution[n][n])
{
    int j,k;
    printf("\n\nPheromon distribution\n\n");
    for(j=0;j<n;j++)
    {
        for(k=0;k<n;k++)
            printf("%lf ",pheromon_distribution[j][k]);
        printf("\n");
    }
    printf("\n");
}

void aco(int n,double attarctiveness[n][n],int rand_city_selection[n],double pheromon_distribution[n][n])
{
    int i,j,k;
    double path_length[n];
    int visited[n][n];
    double min_path_length=9999;
    for(i=0;;i++)
    {
        printf("\n\nIteration %d\n\n",i+1);

        print_pheromon_distribution(n,pheromon_distribution);

        int f=0;

        for(j=0;j<n;j++)
        {
            int start_city=rand_city_selection[j];
            int n_city;

            memset(visited[j],0,n*sizeof(int));

            visited[j][start_city]=1;
            path_length[j]=0;

            for(k=0;k<n-1;k++)
            {
                n_city=next_edge_selection(n,attarctiveness,pheromon_distribution,start_city,visited[j]);
                visited[j][n_city]=visited[j][start_city]+1;
                path_length[j]+=1/attarctiveness[start_city][n_city];
                start_city=n_city;
            }

            path_length[j]+=1/attarctiveness[start_city][rand_city_selection[j]];

            if(path_length[j]<min_path_length)
                min_path_length=path_length[j];

            if(path_length[j]!=min_path_length)
                f=1;

            int path[n];

            for(k=0;k<n;k++)
                path[visited[j][k]-1]=k;

            printf("\nThe path for the Ant %d :\n",j+1);
            for(k=0;k<n;k++)
                printf("%d->",path[k]+1);
            printf("%d",rand_city_selection[j]+1);

            printf("\nPath length for Ant %d = %lf\n",j+1,path_length[j]);
        }
        if(f==0)
            break;
        pheromon_update(n,pheromon_distribution,path_length,visited,min_path_length);
    }
}

int main()
{
    int n,i,j;

    printf("Enter number of cities\n");
    scanf("%d",&n);

    double attarctiveness[n][n];

    printf("Enter the cost matrix\n");

    int rand_city_selection[n];

    double pheromon_distribution[n][n];

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            double d;
            scanf("%lf",&d);
            if(i==j||d==0)
            {
                attarctiveness[i][j]=0;
                pheromon_distribution[i][j]=0;
            }
            else
            {
                attarctiveness[i][j]=1/d;
                pheromon_distribution[i][j]=1;
            }
        }
    }
    for(i=0;i<n;i++)
        rand_city_selection[i]=i;
    aco(n,attarctiveness,rand_city_selection,pheromon_distribution);
    return 0;
}
