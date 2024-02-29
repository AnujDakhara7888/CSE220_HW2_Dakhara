#include "hw2.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 

int main(int argc, char **argv) 
{
    int check[6]={0,0,0,0,0,0};
    int inputfile=0;
    int outputfile=0;
    int cposition=0;
    int pposition=0;
    int rposition=0;
    FILE *inpFile;
    FILE *outFile;
    for(int i=1;i<argc;i++)
    {
        if(!strcmp(argv[i],"-i"))
        {
            check[0]++;
            i++;
            if(i==argc)
                return MISSING_ARGUMENT;
            if(!strcmp(argv[i],"-i") || !strcmp(argv[i],"-o") || !strcmp(argv[i],"-p") || !strcmp(argv[i],"-c") || !strcmp(argv[i],"-r"))
            {
                return MISSING_ARGUMENT;
            }
            else
            {
                inputfile=i;
            }
        }
        else if(!strcmp(argv[i],"-o"))
        {
            check[1]++;
            i++;
            if(i==argc)
                return MISSING_ARGUMENT;
            if(!strcmp(argv[i],"-i") || !strcmp(argv[i],"-o") || !strcmp(argv[i],"-p") || !strcmp(argv[i],"-c") || !strcmp(argv[i],"-r"))
            {
                return MISSING_ARGUMENT;
            }
            else
            {
                outputfile=i;
            }
        }
        else if(!strcmp(argv[i],"-c"))
        {
            check[2]++;
            i++;
            if(i==argc)
                return MISSING_ARGUMENT;
            if(!strcmp(argv[i],"-i") || !strcmp(argv[i],"-o") || !strcmp(argv[i],"-p") || !strcmp(argv[i],"-c") || !strcmp(argv[i],"-r"))
            {
                return MISSING_ARGUMENT;
            }
            else
            {
                cposition=i;

            }
        }
        else if(!strcmp(argv[i],"-p"))
        {
            check[3]++;
            i++;
            if(i==argc)
                return MISSING_ARGUMENT;
            if(!strcmp(argv[i],"-i") || !strcmp(argv[i],"-o") || !strcmp(argv[i],"-p") || !strcmp(argv[i],"-c") || !strcmp(argv[i],"-r"))
            {
                return MISSING_ARGUMENT;
            }
            else
            {
                pposition=i;
            }
        
        }
        
        else if(!strcmp(argv[i],"-r"))
        {
            check[4]++;
            i++;
            if(i==argc)
                return MISSING_ARGUMENT;
            if(!strcmp(argv[i],"-i") || !strcmp(argv[i],"-o") || !strcmp(argv[i],"-p") || !strcmp(argv[i],"-c") || !strcmp(argv[i],"-r"))
            {
                return MISSING_ARGUMENT;
            }
            else
            {
                rposition=i;
            }
        }
        else
        {
            check[5]++;
        }
    }
    if((check[0]==0) || (check[1]==0))
    {
        return MISSING_ARGUMENT;
    }
    if(check[5]>0)
    {
        return UNRECOGNIZED_ARGUMENT;
    }
    for(int i=0;i<5;i++)
    {  
        if(check[i]>1)
        {
            return DUPLICATE_ARGUMENT;
        }
    }
    inpFile = fopen(argv[inputfile], "r");
    if (inpFile  == NULL)
    { 
        return INPUT_FILE_MISSING;
    }
    outFile = fopen(argv[outputfile], "w");
    if(outFile == NULL)
    {
        return OUTPUT_FILE_UNWRITABLE;
    }


    if((check[3]>=1) && (check[2]==0)) 
    {
        return C_ARGUMENT_MISSING;
    }
    if(check[2]>0)
    {
        
        char str[strlen(argv[cposition])];
        strcpy(str,argv[cposition]);
        int index = 0;
        char *token = strtok(str, ",");
        while(token!=NULL) 
        {
            index++;
            token = strtok(NULL, ",");
            if(token==NULL)
            {
                break;
            }
        }
        if(index!=4)
        {
            fclose(inpFile);
            fclose(outFile);
            return C_ARGUMENT_INVALID;
        }
    }
    if(check[3]>0)
    {
        char str1[strlen(argv[cposition])];
        strcpy(str1,argv[pposition]);
        int index1 = 0;
        char *token1 = strtok(str1, ",");
        while (token1!=NULL) 
        {
            index1++;
            token1 = strtok(NULL, ",");
            if(token1==NULL)
            {
                break;
            }
        }
        if(index1!=2)
        {
            fclose(inpFile);
            fclose(outFile);
            return P_ARGUMENT_INVALID;
        }
    }
    if(check[4]>0)
    {
        char str2[strlen(argv[cposition])];
        strcpy(str2,argv[rposition]);
        int index3 = 0;
        char *token2 = strtok(str2, ",");
        while (token2!=NULL) 
        {
            if(index3==1)
            {
                FILE *F;
                F = fopen(token2, "r");
                if(F==NULL)
                {
                    return R_ARGUMENT_INVALID;
                }
            }
            index3++;
            token2 = strtok(NULL, ",");
            if(token2==NULL)
            {
                break;
            }
        }
        if(index3!=5)
        {
            fclose(inpFile);
            fclose(outFile);
            return R_ARGUMENT_INVALID;
        }
    }

//After getting all the values and checking if any of those valkue is invalid


    char file;
    fscanf(inpFile,"%s",&file);
    //Check if the file is P3
    if(!strcmp(&file,"P3"))
    {
        //Get height and width of PPM file
        unsigned int height, width;
        fscanf(inpFile, "%u %u", &width, &height);
        
        //getting the max color value from the PPM
        unsigned int max_color;
        fscanf(inpFile, "%u", &max_color);
        //Creating 2d array of height and width*3    
         unsigned int store[height][width*3]; //Width*3 as each pixel has 3 values rgb

        //Read the file and store it in the array
        for(unsigned int i=0;i<height;i++)
        {    
            for(unsigned int j=0;j<width*3;j++)
            {
                unsigned int input;
                fscanf(inpFile, "%u ", &input);
                store[i][j]=input;
            }
        }
        //If we need to Copy Go in this if
        if(check[2]==1)
        {
            //Get the parameters of copy
            char copyPara[strlen(argv[cposition])];
            strcpy(copyPara,argv[cposition]);
            unsigned int index[4] = {0,0,0,0};
            int cursor=0;
            char *token = strtok(copyPara, ",");
            while(true) 
            {
                if(token==NULL)
                    break;

                index[cursor]=atoi(token);
                token = strtok(NULL, ",");
                cursor++;
            }
            unsigned int maxRow = (index[0]+index[3]);
            if(maxRow>=height)
            {
                maxRow=height;
            }
            unsigned int maxCol = (index[1]+index[2]);
            if(maxCol>=width)
            {
                maxCol=width;
            }
            // Array that will have copied elements
            unsigned int makeCopy[maxRow-index[0]][(maxCol-index[1])*3];
            
            int iIndex = 0;
            int jIndex=0;
            // unsigned int correcter=0;
            for(unsigned int i = index[0]; i<(maxRow);i++)
            {
                //If the pixel we try get is outside the image in terms of height
                if(i>height)
                    break;
                
                jIndex = 0;
                for(unsigned int j = (index[1]*3); j<(maxCol*3);j+=3)
                {
                    //If the pixel we try get is outside the image in terms of width
                    if(j>=(width*3))
                        break;
                    
                    makeCopy[iIndex][jIndex++] = store[i][j];
                    makeCopy[iIndex][jIndex++]=store[i][j+1];
                    makeCopy[iIndex][jIndex++]=store[i][j+2];

                }
                iIndex++;
            } 
            // fprintf(outFile,"%s\n%u %u\n%u\n",&file,((jIndex)/3),iIndex,max_color);
            // for(int i=0;i<iIndex;i++)
            // {
            //     for(int j=0;j<jIndex*3;j++)
            //     {
            //         fprintf(outFile,"%u ",makeCopy[i][j]);
            //     }
            // }

            if(check[3])
            {
                // Get the parameters of paste
                char pastePara[strlen(argv[cposition])];
                strcpy(pastePara,argv[pposition]);
                unsigned int index1[2] = {0,0};
                char *token1 = strtok(pastePara, ",");
                unsigned int cur=0;
                while (true) 
                {
                    if(!token1)
                        break;

                    index1[cur]=atoi(token1);
                    token1 = strtok(NULL, ",");
                    cur++;
                }

                //Changing in Store
                iIndex = 0;
                unsigned int maxPasteRow = index1[0]+(maxRow-index[0]);
                unsigned int maxPasteCol = index1[1]+(maxCol-index[1]);
                if(maxPasteRow>=height)
                {
                    maxPasteRow=height;
                }
                if(maxPasteCol>=width)
                {
                    maxPasteCol=width;
                }
                for(unsigned int i = index1[0]; i<(maxPasteRow);i++)
                {
                    if(i>=height)
                        break;

                    jIndex = 0;
                    for(unsigned int j = index1[1]*3; j<(maxPasteCol*3);j+=3)
                    {
                        if(j>=width*3)
                            break;

                        store[i][j] = makeCopy[iIndex][jIndex++];
                        store[i][j+1] = makeCopy[iIndex][jIndex++];
                        store[i][j+2] = makeCopy[iIndex][jIndex++];
                    }
                    iIndex++;
                }
            }
        }
        fprintf(outFile,"%s\n%u %u\n%u\n",&file,width,height,max_color);
        for(unsigned int i=0;i<height;i++)
        {
            for(unsigned int j=0;j<width*3;j+=3)
            {
                fprintf(outFile,"%u %u %u\n",store[i][j],store[i][j+1],store[i][j+2]);
            }
        }
    }
    else
    {
        //Get height and width of SBU file
        unsigned int height, width;
        fscanf(inpFile, "%u %u", &width, &height);
        
        //getting the max color value from the PPM
        unsigned int numOfColors;
        fscanf(inpFile, "%u", &numOfColors);
        //Creating 2d array of height and width*3    
         unsigned int store[numOfColors*3]; //Width*3 as each pixel has 3 values rgb

        //Read the file and store it in the array
        for(unsigned int i=0;i<numOfColors*3;i++)
        {    
            unsigned int input;
            fscanf(inpFile, "%u ", &input);
            store[i]=input;
        }
        printf("store is %d\n",store[(numOfColors*3)-1]);
        //Storing which pixel where in a different array
        unsigned int colorStore[height][width];
        for(unsigned int i=0;i<height;i++)
        {
            for(unsigned int j=0;j<width;j++)
            {
                unsigned char input[10];
                fscanf(inpFile, "%s\n ",input);
                if(*input=='*')
                {
                    unsigned int count = atoi((char*)(input + 1));
                    unsigned int value;
                    fscanf(inpFile,"%u",&value);
                    int x=0;
                    while(count!=0)
                    {
                        if(j<width)
                        {
                           colorStore[i][j]=value;
                        }
                        else
                        {
                            x=1;
                            break;
                        }
                        count--;
                        if(count==0)
                        {
                            break;
                        }
                        else
                        {
                            j++;
                        }
                    }
                    
                    if(x==1)
                    {
                        j=0;
                        while(count!=0)
                        {
                            colorStore[i+1][j]=value;
                            if(count==0)
                            {
                                break;
                            }
                            else
                            {
                                j++;
                            }
                            count--;
                        }
                    }
                }
                else
                {
                    colorStore[i][j]=atoi((char*)input);
                }
            }
        }
        // printing the sbu file
        // fprintf(outFile,"%s\n%u %u\n%u ",&file,width,height,numOfColors);
        printf("%d\n",colorStore[0][0]);
        // for(int i=0;i<numOfColors*3;i++)
        // {
        //     fprintf("%u ",store[i]);
        // }
        // for(int i=0;i<height;i++)
        // {
        //     for(int j=0;j<width;j++)
        //     {
        //         f
        //     }
        // }

    }
fclose(inpFile);
fclose(outFile);
return 0;
}

    