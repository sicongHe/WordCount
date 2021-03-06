// WordCount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <io.h>
using namespace std;
int character(string);
int line(string);
int word(string);
int codeLine(string);
int noteLine(string);
int blankLine(string);
vector<string> stop(string);
void getFiles(string, vector<string>&);
int main(int argc,char* argv[])
{
	vector<string> terminalInput;
	string sourceName = "";
	string outputName = "";
	ofstream outfile;
	ifstream infile;
	string infileBuffer;
	vector<string> stopList;
	bool c = false;
	bool w = false;
	bool l = false;
	bool o = false;
	bool s = false;
	bool a = false;
	bool e = false;
	string ret;
	for (int i = 1; i < argc; i++) {
		string tmp = *(argv + i);
		terminalInput.push_back(tmp);
	}
	for (auto v : terminalInput) {
		if (v == "-c") {
			c = true;
		}
		else if (v == "-w") {
			w = true;
		}
		else if (v == "-l") {
			l = true;
		}
		else if (v == "-o") {
			o = true;
		}
		else if (v == "-s") {
			s = true;
		}
		else if (v == "-a") {
			a = true;
		}
		else if (v == "-e") {
			e = true;
		}
		else {
			if(sourceName == "")
				sourceName = v;
			outputName = v;
		}
	}
	if (s) {
		vector<string> files;

		
		getFiles("./", files);

		
		int size = files.size();
		for (int i = 0; i < size; i++)
		{
			int max = files[i].size();
			if (files[i][max - 2] == '.' && files[i][max - 1] == 'c') {
				sourceName = files[i];
				if (o == false) {
					outputName = "result.txt";
				}
				if (c) {
					ret += sourceName + ',' + "字符数：" + to_string(character(sourceName)) + '\n';
				}
				if (w) {
					ret += sourceName + ',' + "单词数：" + to_string(word(sourceName)) + '\n';
				}
				if (l) {
					ret += sourceName + ',' + "行数：" + to_string(line(sourceName)) + '\n';
				}
				if (a) {
					ret += sourceName + ',' + "代码行/空行/注释行：" + to_string(codeLine(sourceName)) + '/' + to_string(blankLine(sourceName)) + '/' + to_string(noteLine(sourceName)) + '\n';
				}
			}
			
		}
		
	}
	else {
		if (o == false) {
			outputName = "result.txt";
		}
		if (c) {
			ret += sourceName + ',' + "字符数：" + to_string(character(sourceName)) + '\n';
		}
		if (w) {
			ret += sourceName + ',' + "单词数：" + to_string(word(sourceName)) + '\n';
		}
		if (l) {
			ret += sourceName + ',' + "行数：" + to_string(line(sourceName)) + '\n';
		}
		if (a) {
			ret += sourceName + ',' + "代码行/空行/注释行：" + to_string(codeLine(sourceName)) + '/' + to_string(blankLine(sourceName)) + '/' + to_string(noteLine(sourceName)) + '\n';
		}
	}

	
	outfile.open(outputName);
	outfile.write(ret.c_str(), ret.length());
	outfile.close();
	
    return 0;
}

int character(string name) {
	ifstream infile;
	infile.open("./" + name);
	int i = 0;
	char buf;
	while (!infile.eof()) {
		infile.get(buf);
		i++;
	}
	

	infile.close();
	
	return i-1;
}

int line(string name) {
	ifstream infile;
	infile.open("./" + name);
	int i = 1;
	char buf;
	while (!infile.eof()) {
		infile.get(buf);
		if(buf == '\n')
			i++;
	}


	infile.close();

	return i;
}

int word(string name) {
	ifstream infile;
	infile.open("./" + name);
	int i = 0;
	bool flag = true;
	char buf;
	while (!infile.eof()) {
		infile.get(buf);
		if (buf != ' ' && buf != ',' && buf != '\n') {
			if (flag == true) {
				i++;
				flag = false;
			}
		}
		else {
			flag = true;
		}
	}
	infile.close();
	return i;
}

int codeLine(string name) {
	ifstream infile;
	infile.open("./" + name);
	int i = 0;
	bool flag = true;
	string buf;
	while (getline(infile,buf)){
		if (flag == false) {
			int max = buf.size();
			if (buf[max - 2] == '*' && buf[max - 1] == '/') {
				flag = true;
			}
			continue;
		}
		if (buf.size() < 2) {
			continue;
		}
		else {
			if (buf[0] == '/' && buf[1] == '/') {
				continue;
			}
			if (buf[0] == '/' && buf[1] == '*') {
				flag = false;
				continue;
			}
			i++;
		}
	}


	infile.close();

	return i;
}
int noteLine(string name) {
	ifstream infile;
	infile.open("./" + name);
	int i = 0;
	bool flag = false;
	string buf;
	while (getline(infile, buf)) {
		if (flag == true && buf.size() != 0) {
			i++;
			int max = buf.size();
			if (buf[max - 2] == '*' && buf[max - 1] == '/') {
				flag = false;
			}
			continue;
		}
		if (flag == false) {
			if (buf[0] == '/' && buf[1] == '*') {
				flag = true;
				i++;
				continue;
			}
		}
		if (buf[0] == '/' && buf[1] == '/') {
			i++;
			continue;
		}

	}
		


	infile.close();

	return i;
}

int blankLine(string name) {
	ifstream infile;
	infile.open("./" + name);
	int i = 0;
	
	string buf;
	while (getline(infile, buf)) {
		if (buf.size() == 1 && buf[0] == '\n') {
			i++;
		}
	}


	infile.close();

	return i;
}

vector<string> stop(string name) {
	ifstream infile;
	infile.open("./" + name);
	vector<string> ret;
	string tmp;
	char buf;
	while (!infile.eof()) {
		infile.get(buf);
		if(buf != ' ' && buf != ',' && buf != '\n')
			tmp += buf;
		else {
			if (!tmp.empty()) {
				ret.push_back(tmp);
				tmp.clear();
			}
		}
		
	}
	infile.close();
	return ret;
}
void getFiles(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}