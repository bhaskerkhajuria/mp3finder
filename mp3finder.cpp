//Mp3 finder
//Author: Bhasker Khajuria

#include<iostream>
#include<dirent.h>     
#include<string>
#include<string.h>
#include<vector>    
using namespace std;
class mp3file{
    private:
    string fpath;
    string fname;
    public:
    string showPath(){
    return fpath;
    }
    string showFile(){
    return fname;
    } 
    mp3file(string filename,string path){
    fname=filename;       
    fpath=path;
        
    }   
};
vector<mp3file> list;
class dirfile{
    public:
    DIR *dir;           
    struct dirent *ent;
    dirfile(string str){
    dir=opendir(str.c_str());
    }
    bool isDir(){
    if(ent->d_type==4)
    return true;
    else 
    return false;
    }
    bool isMp3(){
    if(ent->d_type==8){
    string temp;
    for(int i=strlen(ent->d_name)-4;i<strlen(ent->d_name);i++)
    temp.push_back(ent->d_name[i]);
    if(temp==".mp3")
    return true;
    else
    return false;
    }
    else
    return false;                   
    }   
};
void mp3find(string str){
    dirfile d(str);
    if(d.dir!=NULL){
    while((d.ent=readdir(d.dir))!=NULL){
    if(strcmp(d.ent->d_name,".")==0 || strcmp(d.ent->d_name,"..")==0 || d.ent->d_name[0]=='.')            //skips the entities names '.','..' and '.*'
    continue;
    if(d.isDir()){                                                                                        //checks for directory
    string temp(d.ent->d_name);
    temp=str+"/"+temp; 
    mp3find(temp);
            }
    if(d.isMp3()){                                                                                        //checks for mp3 file
    mp3file m((string)d.ent->d_name,str);
                
    list.push_back(m);                                      
            }    
        }
    closedir(d.dir);
    }
    else
    cout<<"Couldn't open the directory "<<str<<endl;
}
int main(){
    string path;
    cout<<"Enter the path: "<<endl;
    cin>>path;
    mp3find(path);
    for(int i=0;i<list.size();i++)
    cout<<list[i].showFile()<<"\t"<<list[i].showPath()<<endl;   
    return 0;
}