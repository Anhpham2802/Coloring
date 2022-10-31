#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20

// docfile txt dau vao
void docfile(char *filename,int canh[2][MAX],int *sodinh, int *socanh)
{
    FILE *f;
    f = fopen(filename,"r");
    if(f == NULL)
    {
        printf("Khong the mo file\n");
        return;
    }
    fscanf(f,"%d",sodinh);
    fscanf(f,"%d",socanh);
    int i;
    for(i=0;i<*socanh;i++)
    {
        fscanf(f,"%d",&canh[0][i]);
        fscanf(f,"%d",&canh[1][i]);
    }
    fclose(f);
}
void dauvao(int canh[2][MAX],int sodinh,int socanh)
{
    printf("%d\t%d\n",sodinh,socanh);
    int i;
    for(i=0;i<socanh;i++)
    {
        printf("%d\t%d\n",canh[0][i],canh[1][i]);
    }
}
void MaTran(int matran[MAX][MAX],int socanh,int canh[2][MAX])
{
    int i;
    for(i=0;i<socanh;i++)
    {
        matran[canh[0][i]][canh[1][i]] = 1;
        matran[canh[1][i]][canh[0][i]] = 1;
    }
}
void InMaTran(int matran[MAX][MAX],int sodinh)
{
    for(int i=1;i<=sodinh;i++)
    {
        for(int j=1;j<=sodinh;j++)
        {
            printf("%5d",matran[i][j]);
        }
        printf("\n");
    }
}
int DaToMau(int matran[MAX][MAX],int sodinh,int v[],int i,int c)
{
    for(int j=1;j<=sodinh;j++)
    {
        if(matran[i][j] && v[j] == c)
            return 0;
    }
    return 1;
}
int To1Mau(int matran[MAX][MAX],int sodinh,int v[],int color)
{
    int i;
    int cout =0;
    for(i=1;i<=sodinh;i++)
    {
        if(!v[i] && DaToMau(matran,sodinh,v,i,color))
        {
            v[i] = color;
            cout ++;
        }
    }
    return cout;
}
int tomau(int matran[MAX][MAX],int sodinh,int v[])
{
    int i;
    for(i=1;i<= sodinh;i++)
        v[i] = 0;
    int somau =0;
    int cout = 0;
    while(cout < sodinh)
    {
        somau ++;
        cout += To1Mau(matran,sodinh,v,somau);
    }
    return somau;
}
void docfilemau(char *filename,char tenmau[MAX][MAX],int somau)
{
    FILE *f;
    f = fopen(filename,"r");
    if(f == NULL)
    {
        printf("Khong the mo file !!\n");
        return;
    }
    int i;
    for(i=1;i<=somau;i++)
    {
        fscanf(f,"%s",tenmau[i]);
    }
    fclose(f);
}
void ghifile(char *filename,char tenmau[MAX][MAX],int canh[2][MAX],int sodinh,int socanh,int v[])
{
    FILE *f;
    f = fopen(filename,"wb");
    if(f == NULL)
    {
        printf("Khong the tao file !!!");
        return;
    }
    fprintf(f,"graph\n{\n");
    int i;
    for(i=1;i<=sodinh;i++)
    {
        fprintf(f,"%d [fillcolor = %s , style = filled];\n",i,tenmau[v[i]]);
    }
    for(i=0;i<socanh;i++)
    {
        fprintf(f,"%d--%d;\n",canh[0][i],canh[1][i]);
    }
    fprintf(f,"}");
    fclose(f);
}

int main()
{
    int canh[2][MAX];
    int matran[MAX][MAX] = {0};
    int v[MAX];
    char tenmau[MAX][MAX];
    int somau =0;
    int sodinh,socanh;
    docfile("input.txt",canh,&sodinh,&socanh);
    printf("-- input --\n");
    dauvao(canh,sodinh,socanh);
    printf("\n---  Ma tran ke  ---\n");
    MaTran(matran,socanh,canh);
    InMaTran(matran,sodinh);
    somau = tomau(matran,sodinh,v);
    docfilemau("Color.txt",tenmau,somau);
    ghifile("Coloring.dot",tenmau,canh,sodinh,socanh,v);

    return 0;
}