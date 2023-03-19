
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

void GetFileNames(string path, vector<string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            //filenames.push_back(path + "/" + ptr->d_name);
            filenames.push_back(ptr->d_name);
    }
    closedir(pDir);
}


int CPlusMain() {
    vector<string> file_name;
    string data;
    string path = "./folder";
    ofstream outfile;
    outfile.open("sum.txt");
    GetFileNames(path, file_name);
    for(int i = 0; i <file_name.size(); i++)
    {
        ifstream infile;
        infile.open(path+"/"+file_name[i]);
        infile >> data;
        outfile << file_name[i] << "\n" << data << endl;
        infile.close();
        cout<<file_name[i]<<endl;
    }
    outfile.close();
    return 0;
}


