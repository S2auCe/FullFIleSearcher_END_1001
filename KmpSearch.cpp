#ifndef KMPSEARCH_H
#define KMPSEARCH_H

#endif // KMPSEARCH_H

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<QDir>
#include<QFile>
#include<QDebug>
#include<QString>
#include<fstream>

#include "KmpSearch.h"

std::string txt,str,line,brief;
int Next[505],tmp;

void initial(std::string pat)
{
    int j=0;
    Next[0]=0;
    for(int i=1;i<pat.size();i++){
        while(j&&pat[i]!=pat[j])j=Next[j-1];
        if(pat[i]==pat[j])j++;
        Next[i]=j;
    }
}

int kmpSearch3(std::string txt,std::string target)
{
    if(target == "")return -1;
    initial(target);
    int maxsize = txt.size()-1;
    int j=0;
    for(int i=0;i<txt.size();i++){
        while(j&&txt[i]!=target[j])j=Next[j-1];
        if(txt[i]==target[j])j++;
        if(j==target.size()){
            tmp = i - j + 1;
            return tmp;
        }
    }
    return -1;
}
