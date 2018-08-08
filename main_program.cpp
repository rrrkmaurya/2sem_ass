#include <stdio.h>
#include <dirent.h>
#include<bits/stdc++.h>
#include<string.h>
#include<iostream>
#include"clustering\get_match.cpp"

using namespace std;

// funtion for reading input file from which we are going to find the semilarity ratio among them.

void getinputfile(char filename[], multiset< multiset<string> > &loc, set<string> hverb, set<string> conj, 
set<string> prep, set<string> punt, map<string, vector<string> > irr_verb, map<string, set<string> > syn)
{
	ifstream in;
	multiset<string> temp;
	in.open(filename);
	char c;
	while(!in.eof())
	{
		bool flag=1;
		string str;
		in>>noskipws>>c;       // noskipws is used for do not skip the space from the file
		while(c!= '.' and !in.eof() )
		{
			if(c=='(' or c=='{' or c=='[')
				flag=0;
			else if(c==')' or c=='}' or c==']')
				flag=1;
			if(flag and (c!=')' and c!='}' and c!=']'))
			{
				string t;
				t+=c;
				if(punt.find(string(t)) == punt.end() and c!=32)
					str+=c;
				else if(str.size()>0)
				{
					if(str.find("ing")!=string::npos)
						str.erase(str.size()-3,3);
					
					if(hverb.find(str)!=hverb.end() or conj.find(str)!=conj.end() or prep.find(str)!=prep.end() );
					else
				 	{
						str=convert_in_first(str,irr_verb);
						str=check_syn(str,syn);
						temp.insert(str);
					}			
					str.clear();
				}
			}
			if(!in.eof())
				in>>noskipws>>c;
			
		}
		if(str.size()> 0)
		{
			if(str.find("ing")!=string::npos)
				str.erase(str.size()-3,3);
			str=convert_in_first(str,irr_verb);
			str=check_syn(str,syn);
			if(hverb.find(str)==hverb.end() and conj.find(str)==conj.end() and prep.find(str)==prep.end() )
				temp.insert(str);
		}
		loc.insert(temp);
		temp.clear();	
	}	
}

//function for reading all cunjuctions, prepositions, puntuations etc.

void getinput(char filename[] , set<string> &loc)
{
	ifstream out;
	out.open(filename);
	string str;
	while(!out.eof())
	{
		out>>str;
		loc.insert(str);
	}
}


// function for reading irregular verbs

void get_irr_verb(char filename[] , map<string , vector<string> > &loc)
{
	ifstream out;
	out.open(filename);
	string s1,s2,s3;
	while(!out.eof())
	{
		out>>s1>>s2>>s3;
		loc[s1].push_back(s2);
		loc[s1].push_back(s3);
	}
}

// function for reading list of synonyms

void get_syn(char filename[], map<string, set<string> > &loc)
{
	ifstream out;
	out.open(filename);
	string str, save;
	set<string> temp;
	bool stat=0;
	out>>save;
	while(!out.eof())
	{
		out>>str;
		if(str.size()>0 and str[0]>='A' and str[0]<='Z')
		{
				loc[save]=temp;
				save=str;
				temp.clear();
		}
		else
		{
			str.erase(str.size()-1,1);
			temp.insert(str);
		}

	}
	loc[save]=temp;
}

// function for reading list of file in given directory

void getfilename(string fname,vector<string> &loc)
{
	vector<string>::iterator it;
    struct dirent *de;
    string temp="test\\";
    temp+=fname;
    char folder[50];
    strcpy(folder, temp.c_str());
		 
    DIR *dr = opendir(folder);
    while ((de = readdir(dr)) != NULL)
            loc.push_back(de->d_name);

    closedir(dr);
    loc.erase(loc.begin());
    loc.erase(loc.begin());
}

//main program 

void mmain(string tfname, int tsthr, int tdthr)
{
	
 	set<string> hverb,conj,prep,punt;
 	map<string, vector<string> > irr_verb;
	multiset< multiset<string> > file,compair;
	map<string,float> stats;
	map<string, set<string> > syn;
 	vector<string> filelist;
 	vector<string> folderlist;
 	
	getinput("spacial_input\\helping_verbs.txt" ,hverb);
	getinput("spacial_input\\conjuctions.txt", conj);
 	getinput("spacial_input\\prepositions.txt", prep);
 	getinput("spacial_input\\puntuations.txt", punt);
 	get_irr_verb("spacial_input\\irregular_verbs.txt", irr_verb);
 	get_syn("spacial_input\\synonyms.txt", syn);
 	 	
	string fname,ffname;
	int sthr,dthr;
 	//cout<<endl<<"enter folder name of files  :";
 //	cin>>fname; 
 	fname=tfname;
 	ffname=fname;
 	//cout<<endl<<"enter threshold value for string and document-level :";
 	//cin>>sthr>>dthr;
 	sthr=tsthr;
 	dthr=tdthr;
	getfilename(fname,filelist);
 	
 	vector<string>::iterator it1,it2,tt,ctt;
	string rloc="results\\";
	
	if(sthr<10)
		ffname+=(sthr+'0');
	else
	{
		ffname+=((sthr/10)+'0');
		ffname+=((sthr%10)+'0');
	}
	
	if(dthr<10)
		fname+=(dthr+'0');
	else
	{
		ffname+=((dthr/10)+'0');
		ffname+=((dthr%10)+'0');
	}
	
	cout<<ffname<<endl;
	rloc+=ffname;
	char folder[50];
    strcpy(folder, rloc.c_str());
	
	ofstream in;
	in.open(folder); 
	cout<<endl<<"please wait  :  ";
	
	for(it1=filelist.begin();it1!=filelist.end();)
 	{
		string temp="test\\";
		temp+=fname; 
		temp+="\\";
	 	temp+=*it1;
 		char first[50];
 		strcpy(first, temp.c_str()); 
		
 		getinputfile(first, compair,hverb,conj,prep,punt,irr_verb,syn);
		if(compair.size()>0)
			compair.erase(compair.begin());
		ctt=it1;	
		it1++;
		tt=it1;
		tt++;
		if(it1==filelist.end() or tt==filelist.end())
			break;
		for(it2=it1;it2!=filelist.end();it2++)
		{
			string temp="test\\";
			temp+=fname;
			temp+="\\";
	 		temp+=*it2;
 			char second[50];
 			strcpy(second, temp.c_str());
		
			getinputfile(second,file,hverb,conj,prep,punt,irr_verb,syn);
			if(file.size()>0)
				file.erase(file.begin());
			float res=matchfile(compair,file,sthr,dthr);
			if(int(res) >= dthr)
				stats[*it2]=res;
			file.clear();
		}
 		cout<<"*";
 		if(stats.size()>0)
 		{
			in<<endl<<"input file name------"<<*ctt<<endl;
			map<string,float>::iterator it;
			for(it=stats.begin();it!=stats.end();it++)
				in<<it->first<<"---"<<it->second<<endl;
			stats.clear();
		}
	}
	
	cout<<endl<<endl;//<<"please check your results folder for output "<<endl;
	in.close();	
}

int main()
{
	string fname;
	int sthr[]={50,60,70};
	int dthr[]={50,60,70};
	cout<<"enter folder name of files :";
	cin>>fname;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			mmain(fname,sthr[i],sthr[j]);
	return 0;
}
