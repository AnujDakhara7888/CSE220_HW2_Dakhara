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
        char str[100] = {"\0"};
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
        char str1[100] = {'\0'};
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
        char str2[100] = {'\0'};
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
    char *lastChar = argv[outputfile];
    char file[10];
    fscanf(inpFile,"%s",file);
    //Check if the file is P3
    if(!strcmp(file,"P3"))
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
        if(check[2]==1 &&!strcmp(&lastChar[strlen(argv[outputfile])-1],"m"))
        {
            // Get the parameters of copy
            char copyPara[100] = {'\0'};
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

            if(check[3]==1)
            {
                char pastePara[100] = {'\0'};
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
            fprintf(outFile,"%s\n%u %u\n%u\n",file,width,height,max_color);
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width*3;j++)
                {
                    fprintf(outFile,"%u ",store[i][j]);
                }
                fprintf(outFile,"\n");
            }
            fprintf(outFile,"\n");
        }
        else if(check[2]==0 &&!strcmp(&lastChar[strlen(argv[outputfile])-1],"m"))
        {
            fprintf(outFile,"%s\n%u %u\n%u\n",file,width,height,max_color);
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width*3;j++)
                {
                    fprintf(outFile,"%u ",store[i][j]);
                }
                fprintf(outFile,"\n");
            }
            fprintf(outFile,"\n");
        }
        else if(check[2]==0 &&!strcmp(&lastChar[strlen(argv[outputfile])-1],"u"))
        {
            unsigned int colorTable[height*width][3];
            unsigned int whereToStore[height*width];
            //
            unsigned int colorTablesize=0;
            unsigned int tempIndex=0;
            unsigned int storeIndex=0;
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width*3;j+=3)
                {
                    if(i==0 && j==0)
                    {
                        colorTable[tempIndex][0]=store[i][j];
                        colorTable[tempIndex][1]=store[i][j+1];
                        colorTable[tempIndex++][2]=store[i][j+2];
                        whereToStore[storeIndex++]=colorTablesize;
                        colorTablesize++;
                    }
                    else
                    {
                        int maker=0;
                        for(unsigned int k=0;k<(colorTablesize);k++)
                        {
                            if((colorTable[k][0]==store[i][j]) && (colorTable[k][1]==store[i][j+1]) && (colorTable[k][2]==store[i][j+2]) && storeIndex<(height*width))
                            {
                                whereToStore[storeIndex++]=k;
                                maker=1;
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        if(maker==0 && storeIndex<(height*width))
                        {
                                colorTable[tempIndex][0]=store[i][j];
                                colorTable[tempIndex][1]=store[i][j+1];
                                colorTable[tempIndex++][2]=store[i][j+2];
                                whereToStore[storeIndex++]=colorTablesize;
                                colorTablesize++;
                        }
                    }
                }  
            }
            fprintf(outFile,"%s\n%u %u\n%u ","SBU",width,height,colorTablesize);
            for(unsigned int i=0;i<(colorTablesize);i++)
            {
                fprintf(outFile,"%u %u %u ",colorTable[i][0],colorTable[i][1],colorTable[i][2]);
            }
            fprintf(outFile,"\n");
            unsigned int i=0;
            while(i<storeIndex)
            {
                unsigned int runLength=1;
                while(i + runLength < storeIndex && whereToStore[i] == whereToStore[i + runLength]) 
                {
                    runLength++;
                }
                if(runLength>1)
                {
                    fprintf(outFile,"*%u %u ", runLength, whereToStore[i]);
                    i += runLength;
                }
                else 
                {
                    fprintf(outFile,"%u ", whereToStore[i]);
                    i++;
                }
            }
        }
        else if(check[2]==1 &&!strcmp(&lastChar[strlen(argv[outputfile])-1],"u"))
        {
            // Get the parameters of copy
            char copyPara[100] = {'\0'};
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

            if(check[3]==1)
            {
                char pastePara[100] = {'\0'};
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
            unsigned int colorTable[height*width][3];
            unsigned int whereToStore[height*width];
            //
            unsigned int colorTablesize=0;
            unsigned int tempIndex=0;
            unsigned int storeIndex=0;
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width*3;j+=3)
                {
                    if(i==0 && j==0)
                    {
                        colorTable[tempIndex][0]=store[i][j];
                        colorTable[tempIndex][1]=store[i][j+1];
                        colorTable[tempIndex++][2]=store[i][j+2];
                        whereToStore[storeIndex++]=colorTablesize;
                        colorTablesize++;
                    }
                    else
                    {
                        int maker=0;
                        for(unsigned int k=0;k<(colorTablesize);k++)
                        {
                            if((colorTable[k][0]==store[i][j]) && (colorTable[k][1]==store[i][j+1]) && (colorTable[k][2]==store[i][j+2]) && storeIndex<(height*width))
                            {
                                whereToStore[storeIndex++]=k;
                                maker=1;
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        if(maker==0 && storeIndex<(height*width))
                        {
                                colorTable[tempIndex][0]=store[i][j];
                                colorTable[tempIndex][1]=store[i][j+1];
                                colorTable[tempIndex++][2]=store[i][j+2];
                                whereToStore[storeIndex++]=colorTablesize;
                                colorTablesize++;
                        }
                    }
                }  
            }
            fprintf(outFile,"%s\n%u %u\n%u ","SBU",width,height,colorTablesize);
            for(unsigned int i=0;i<(colorTablesize);i++)
            {
                fprintf(outFile,"%u %u %u ",colorTable[i][0],colorTable[i][1],colorTable[i][2]);
            }
            fprintf(outFile,"\n");
            unsigned int i=0;
            while(i<storeIndex)
            {
                unsigned int runLength=1;
                while(i + runLength < storeIndex && whereToStore[i] == whereToStore[i + runLength]) 
                {
                    runLength++;
                }
                if(runLength>1)
                {
                    fprintf(outFile,"*%u %u ", runLength, whereToStore[i]);
                    i += runLength;
                }
                else 
                {
                    fprintf(outFile,"%u ", whereToStore[i]);
                    i++;
                }
            }
        }
    }
    //SBU FILE
    else
    {
        //Get height and width of SBU file
        unsigned int height, width;
        fscanf(inpFile, "%u %u", &width, &height);
        
        //getting the max color value from the PPM
        unsigned int numOfColors;
        fscanf(inpFile, "%u", &numOfColors);
        //Creating 2d array of height and width*3    
         unsigned int colorStore[numOfColors*3]; //Width*3 as each pixel has 3 values rgb

        //Read the file and store it in the array
        for(unsigned int i=0;i<numOfColors*3;i++)
        {    
            unsigned int input;
            fscanf(inpFile, "%u ", &input);
            colorStore[i]=input;
        }
        //Storing which pixel where in a different array
        unsigned int pixels[height*width];
        unsigned int pixelCount=0;

        while(pixelCount<height*width)
        {
            unsigned char input[10];
            fscanf(inpFile, "%s",input);
            if(*input=='*')
            {
                unsigned int count = atoi((char*)(input + 1));
                unsigned int value;
                fscanf(inpFile,"%u",&value);
                for(unsigned int i=0;i<count;i++)
                {
                    pixels[pixelCount++]=value;
                }
            }
            else
            {
                pixels[pixelCount++]=atoi((char*)(input));
            }
        }
        // checking for c if there
        if(check[2]==1 &&!strcmp(&lastChar[strlen(argv[outputfile])-1],"u"))
        {
            //making a new file ppm
            FILE *tempFile;
            tempFile = fopen("result1.ppm","w");
            fprintf(tempFile,"%s\n%u %u\n%u\n","P3",width,height,255);
            
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width;j++)
                {
                    unsigned int x = pixels[(i*width)+j];
                    fprintf(tempFile,"%u %u %u ",colorStore[3*x],colorStore[(3*x)+1],colorStore[(3*x)+2]);
                }
                fprintf(tempFile,"\n");
            }
            fclose(tempFile);
            FILE *tempFile1;
            tempFile1 = fopen("result1.ppm","r");
            char first[10];
            fscanf(tempFile1,"%s",first);
            //ppm file encoded into an array
            unsigned int tempHeight, tempWidth;
            fscanf(tempFile1, "%u %u", &tempWidth, &tempHeight);
            
            //getting the max color value from the PPM
            unsigned int tempMax_color;
            fscanf(tempFile1, "%u", &tempMax_color);
            //Creating 2d array of height and width*3    
            unsigned int tempStore[tempHeight][tempWidth*3]; //Width*3 as each pixel has 3 values rgb

            //Read the file and store it in the array
            for(unsigned int i=0;i<tempHeight;i++)
            {    
                for(unsigned int j=0;j<tempWidth*3;j++)
                {
                    unsigned int tempInput;
                    fscanf(tempFile1, "%u ", &tempInput);
                    tempStore[i][j]=tempInput;
                }
            }
            //reading copy commands and pasting as well
            char tempCopyPara[100] = {'\0'};
            strcpy(tempCopyPara,argv[cposition]);
            unsigned int index[4] = {0,0,0,0};
            int tempCursor=0;
            char *tempToken = strtok(tempCopyPara, ",");
            while(true) 
            {
                if(tempToken==NULL)
                    break;

                index[tempCursor]=atoi(tempToken);
                tempToken = strtok(NULL, ",");
                tempCursor++;
            }
            unsigned int maxRow = (index[0]+index[3]);
            if(maxRow>=tempHeight)
            {
                maxRow=tempHeight;
            }
            unsigned int maxCol = (index[1]+index[2]);
            if(maxCol>=tempWidth)
            {
                maxCol=tempWidth;
            }
            // Array that will have copied elements
            unsigned int tempMakeCopy[maxRow-index[0]][(maxCol-index[1])*3];
            
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
                    
                    tempMakeCopy[iIndex][jIndex++] = tempStore[i][j];
                    tempMakeCopy[iIndex][jIndex++]=tempStore[i][j+1];
                    tempMakeCopy[iIndex][jIndex++]=tempStore[i][j+2];

                }
                iIndex++;
            } 
            //read copy command and stores in tempstore array in ppm
            if(check[3]==1)
            {
                char tempPastePara[100] = {'\0'};
                strcpy(tempPastePara,argv[pposition]);
                unsigned int index1[2] = {0,0};
                char *tempToken1 = strtok(tempPastePara, ",");
                unsigned int cur=0;
                while (true) 
                {
                    if(!tempToken1)
                        break;

                    index1[cur]=atoi(tempToken1);
                    tempToken1 = strtok(NULL, ",");
                    cur++;
                }

                //Changing in Store
                iIndex = 0;
                unsigned int maxPasteRow = index1[0]+(maxRow-index[0]);
                unsigned int maxPasteCol = index1[1]+(maxCol-index[1]);
                if(maxPasteRow>=tempHeight)
                {
                    maxPasteRow=tempHeight;
                }
                if(maxPasteCol>=tempWidth)
                {
                    maxPasteCol=tempWidth;
                }
                for(unsigned int i = index1[0]; i<(maxPasteRow);i++)
                {
                    if(i>=tempHeight)
                        break;

                    jIndex = 0;
                    for(unsigned int j = index1[1]*3; j<(maxPasteCol*3);j+=3)
                    {
                        if(j>=tempWidth*3)
                            break;

                        tempStore[i][j] = tempMakeCopy[iIndex][jIndex++];
                        tempStore[i][j+1] = tempMakeCopy[iIndex][jIndex++];
                        tempStore[i][j+2] = tempMakeCopy[iIndex][jIndex++];
                    }
                    iIndex++;
                }
            }
            // now convert ppm to sbu

            unsigned int tempColorTable[tempHeight*tempWidth][3];
            unsigned int tempWhereToStore[tempHeight*tempWidth];
            //
            unsigned int tempColorTablesize=0;
            unsigned int TtempIndex=0;
            unsigned int TstoreIndex=0;
            for(unsigned int i=0;i<tempHeight;i++)
            {
                for(unsigned int j=0;j<tempWidth*3;j+=3)
                {
                    if(i==0 && j==0)
                    {
                        tempColorTable[TtempIndex][0]=tempStore[i][j];
                        tempColorTable[TtempIndex][1]=tempStore[i][j+1];
                        tempColorTable[TtempIndex++][2]=tempStore[i][j+2];
                        tempWhereToStore[TstoreIndex++]=tempColorTablesize;
                        tempColorTablesize++;
                    }
                    else
                    {
                        int maker=0;
                        for(unsigned int k=0;k<(tempColorTablesize);k++)
                        {
                            if((tempColorTable[k][0]==tempStore[i][j]) && (tempColorTable[k][1]==tempStore[i][j+1]) && (tempColorTable[k][2]==tempStore[i][j+2]) && TstoreIndex<(tempHeight*tempWidth))
                            {
                                tempWhereToStore[TstoreIndex++]=k;
                                maker=1;
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        if(maker==0 && TstoreIndex<(tempHeight*tempWidth))
                        {
                                tempColorTable[TtempIndex][0]=tempStore[i][j];
                                tempColorTable[TtempIndex][1]=tempStore[i][j+1];
                                tempColorTable[TtempIndex++][2]=tempStore[i][j+2];
                                tempWhereToStore[TstoreIndex++]=tempColorTablesize;
                                tempColorTablesize++;
                        }
                    }
                }  
            }
            fprintf(outFile,"%s\n%u %u\n%u ","SBU",width,height,tempColorTablesize);
            for(unsigned int i=0;i<(tempColorTablesize);i++)
            {
                fprintf(outFile,"%u %u %u ",tempColorTable[i][0],tempColorTable[i][1],tempColorTable[i][2]);
            }
            fprintf(outFile,"\n");
            unsigned int i=0;
            while(i<TstoreIndex)
            {
                unsigned int runLength=1;
                while(i + runLength < TstoreIndex && tempWhereToStore[i] == tempWhereToStore[i + runLength]) 
                {
                    runLength++;
                }
                if(runLength>1)
                {
                    fprintf(outFile,"*%u %u ", runLength, tempWhereToStore[i]);
                    i += runLength;
                }
                else 
                {
                    fprintf(outFile,"%u ", tempWhereToStore[i]);
                    i++;
                }
            }
            fclose(tempFile1);
        }
        else if(check[2]==1 && !strcmp(&lastChar[strlen(argv[outputfile])-1],"m"))
        {
            //making a new file ppm
            FILE *tempFile;
            tempFile = fopen("result1.ppm","w");
            fprintf(tempFile,"%s\n%u %u\n%u\n","P3",width,height,255);
            
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width;j++)
                {
                    unsigned int x = pixels[(i*width)+j];
                    fprintf(tempFile,"%u %u %u ",colorStore[3*x],colorStore[(3*x)+1],colorStore[(3*x)+2]);
                }
                fprintf(tempFile,"\n");
            }
            fclose(tempFile);
            FILE *tempFile1;
            tempFile1 = fopen("result1.ppm","r");
            char first[10];
            fscanf(tempFile1,"%s",first);
            //ppm file encoded into an array
            unsigned int tempHeight, tempWidth;
            fscanf(tempFile1, "%u %u", &tempWidth, &tempHeight);
            
            //getting the max color value from the PPM
            unsigned int tempMax_color;
            fscanf(tempFile1, "%u", &tempMax_color);
            //Creating 2d array of height and width*3    
            unsigned int tempStore[tempHeight][tempWidth*3]; //Width*3 as each pixel has 3 values rgb

            //Read the file and store it in the array
            for(unsigned int i=0;i<tempHeight;i++)
            {    
                for(unsigned int j=0;j<tempWidth*3;j++)
                {
                    unsigned int tempInput;
                    fscanf(tempFile1, "%u ", &tempInput);
                    tempStore[i][j]=tempInput;
                }
            }
            //reading copy commands and pasting as well
            char tempCopyPara[100] = {'\0'};
            strcpy(tempCopyPara,argv[cposition]);
            unsigned int index[4] = {0,0,0,0};
            int tempCursor=0;
            char *tempToken = strtok(tempCopyPara, ",");
            while(true) 
            {
                if(tempToken==NULL)
                    break;

                index[tempCursor]=atoi(tempToken);
                tempToken = strtok(NULL, ",");
                tempCursor++;
            }
            unsigned int maxRow = (index[0]+index[3]);
            if(maxRow>=tempHeight)
            {
                maxRow=tempHeight;
            }
            unsigned int maxCol = (index[1]+index[2]);
            if(maxCol>=tempWidth)
            {
                maxCol=tempWidth;
            }
            // Array that will have copied elements
            unsigned int tempMakeCopy[maxRow-index[0]][(maxCol-index[1])*3];
            
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
                    
                    tempMakeCopy[iIndex][jIndex++] = tempStore[i][j];
                    tempMakeCopy[iIndex][jIndex++]=tempStore[i][j+1];
                    tempMakeCopy[iIndex][jIndex++]=tempStore[i][j+2];

                }
                iIndex++;
            } 
            //read copy command and stores in tempstore array in ppm
            if(check[3]==1)
            {
                char tempPastePara[100] = {'\0'};
                strcpy(tempPastePara,argv[pposition]);
                unsigned int index1[2] = {0,0};
                char *tempToken1 = strtok(tempPastePara, ",");
                unsigned int cur=0;
                while (true) 
                {
                    if(!tempToken1)
                        break;

                    index1[cur]=atoi(tempToken1);
                    tempToken1 = strtok(NULL, ",");
                    cur++;
                }

                //Changing in Store
                iIndex = 0;
                unsigned int maxPasteRow = index1[0]+(maxRow-index[0]);
                unsigned int maxPasteCol = index1[1]+(maxCol-index[1]);
                if(maxPasteRow>=tempHeight)
                {
                    maxPasteRow=tempHeight;
                }
                if(maxPasteCol>=tempWidth)
                {
                    maxPasteCol=tempWidth;
                }
                for(unsigned int i = index1[0]; i<(maxPasteRow);i++)
                {
                    if(i>=tempHeight)
                        break;

                    jIndex = 0;
                    for(unsigned int j = index1[1]*3; j<(maxPasteCol*3);j+=3)
                    {
                        if(j>=tempWidth*3)
                            break;

                        tempStore[i][j] = tempMakeCopy[iIndex][jIndex++];
                        tempStore[i][j+1] = tempMakeCopy[iIndex][jIndex++];
                        tempStore[i][j+2] = tempMakeCopy[iIndex][jIndex++];
                    }
                    iIndex++;
                }
            }
            fprintf(outFile,"%s\n%u %u\n%u\n","P3",tempWidth,tempHeight,255);
            for(unsigned int i=0;i<tempHeight;i++)
            {
                for(unsigned int j=0;j<tempWidth*3;j++)
                {
                    fprintf(outFile,"%u ",tempStore[i][j]);
                }
                fprintf(outFile,"\n");
            }
            fprintf(outFile,"\n");

        }
        else if(check[2]==0 && !strcmp(&lastChar[strlen(argv[outputfile])-1],"m"))
        {
            fprintf(outFile,"%s\n%u %u\n%u\n","P3",width,height,255);
            
            for(unsigned int i=0;i<height;i++)
            {
                for(unsigned int j=0;j<width;j++)
                {
                    unsigned int x = pixels[(i*width)+j];
                    fprintf(outFile,"%u %u %u ",colorStore[3*x],colorStore[(3*x)+1],colorStore[(3*x)+2]);
                }
                fprintf(outFile,"\n");
            }
        }
        // //printing sbu file
        else
        {
            fprintf(outFile,"%s\n%u %u\n%u",file,width,height,numOfColors);
            fprintf(outFile,"\n");
            for(unsigned int i=0;i<numOfColors*3;i+=3)
            {
                fprintf(outFile,"%u %u %u ",colorStore[i],colorStore[i+1],colorStore[i+2]);
            }
            fprintf(outFile,"\n");
            unsigned int i=0;
            while(i<pixelCount)
            {
                unsigned int runLength=1;
                while(i + runLength < pixelCount && pixels[i] == pixels[i + runLength]) 
                {
                    runLength++;
                }
                if(runLength>1)
                {
                    fprintf(outFile,"*%u %u ", runLength, pixels[i]);
                    i += runLength;
                }
                else 
                {
                    fprintf(outFile,"%u ", pixels[i]);
                    i++;
                }
            }
        }
    }
fclose(inpFile);
fclose(outFile);
return 0;
}