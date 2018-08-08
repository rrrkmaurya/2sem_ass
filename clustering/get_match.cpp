#include<bits/stdc++.h>
using namespace std;

// function for finding minimum edit distance b/w two different words.

int edit(string str1, string str2)
{
	int m=str1.size();
	int n=str2.size();
    int dp[m+1][n+1];
    for (int i=0;i<=m;i++)
        for (int j=0;j<=n;j++)
            if(i==0)
                dp[i][j]=j;
            else if(j==0)
                dp[i][j]=i; 
            else if(str1[i-1]==str2[j-1])
                dp[i][j]=dp[i-1][j-1];
            else
				dp[i][j]= 1+min(dp[i][j-1], min(dp[i-1][j-1],dp[i-1][j]) );     
				
        //finding what are the possible operation to change str1 into str2
    
 /*       for(int i=m,j=n;i>0 and j>0;)
        	if(dp[i][j]==dp[i-1][j-1])
        		i--,j--;
        	else if(dp[i][j]== 1+dp[i-1][j])
        		del++,i--;
        	else if(dp[i][j]== 1+dp[i][j-1])
        		ins++,j--;
        	else
        		sub++,i--,j--;
        
      */  
    return dp[m][n]; //minimum edit distance
}

 // function for similarity ratio b/w two different string
 
int matchinput(multiset<string> input1, multiset<string> input2, int sthr)
{
	sthr=sthr/10;
	sthr=10-sthr;
	int size=max(input1.size(), input2.size());
	int count=0;
	multiset<string> ::iterator it,itt;
	string val;
	for(it=input1.begin();it!=input1.end() and input2.size()>0 ; it++)
	{
		int cur_ed=INT_MAX,pos=0;
		val=*input2.begin();
		for(itt=input2.begin(); itt!=input2.end(); itt++)
		{
			int ed =edit(*it, *itt); // finding no of minimum edit distance b/w two words.
			if(ed < cur_ed)
	 		{
				val=*itt;
				cur_ed=ed;
			}
		}

		if(cur_ed < sthr)  // : no of words that can be ignored from 100% similarity 
		{
			input2.erase(val);
			count++;
	 	}	
	}
	return ((double(count)/double(size))*100);	
}

// function for geting similarity ration b/w two differnt files

float matchfile(multiset< multiset< string > > input1, multiset< multiset< string > > input2, int sthr,int dthr)
{
	int maxsize=max(input1.size(),input2.size());
	multiset< multiset< string > >::iterator first,second,pos;
	first=input1.begin();
	second=input2.begin();
	int count=0;
	
	for(;first!=input1.end() and input2.size()>0;first++)
	{
		pos=input2.begin();
		int maxratio=0;
		for(second=input2.begin();second!=input2.end();second++)
		{
			int ed=matchinput(*first,*second, sthr);
			if(ed==100)
			{	
				maxratio=ed;
				break;
			}
			else if(maxratio<ed)
			{
				pos=second;
				maxratio=ed;
			}
		}
		if(maxratio>=dthr)
		{
			count++;
			input2.erase(pos);
		}
	}

	return(double(count)/double(maxsize) *100);
}


//functin for chenging irregular verbs in first form

string convert_in_first(string str, map< string, vector<string> > irr_verb)
{
	map< string, vector<string> >::iterator it;
	vector<string > temp;
	vector<string >::iterator itt;
	for(it=irr_verb.begin();it!=irr_verb.end();it++)
	{
		temp=it->second;
		for(itt=temp.begin();itt!=temp.end();itt++)
			if(*itt==str)
				str=it->first;
	}
	return str;
 }
 
 //funtion for swap words with their synonyms
 
 string check_syn(string str, map< string, set<string> > syn)
 {
 	map< string, set<string> >::iterator it;
 	set<string> temp;
 	for(it=syn.begin();it!=syn.end();it++)
 	{
 		temp=it->second;
 		if(temp.find(str)!=temp.end())
 		{
 			str=it->first;
 			return str;
 		}
	 }
 	return str;
  } 
