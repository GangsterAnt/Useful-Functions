//string s 는 Enter uid Nickname 이 ' '을 통해 구분되어있으므로 이를 통해 파싱해야한다.
// int& i 는 명령어 "Enter ","Leave " (공백까지 6글자) "Change " ( " 7 글자) 를 넘어가기 위해서.
// i 를 주소로 받음으로써 uid 를 파싱한후 Nickname 앞 index까지 i를 옮겨놓는다.

#include<iostream>
#include<string>
using namespace std;

string token_string(const string& s, int& i)
{
	string tmp = "";
	for (; i < s.size(); ++i)
	{
		if (s[i] == ' ')
		{	// s[i] 가 공백을 가르키므로 i를 하나 띄어놓는다. tmp가 문자열 마지막 단어라면? -> s.end() 와 같아진다.
			i++; return tmp;
		}
		tmp += s[i];	//공백이 아니라면 
	}

	return tmp;
}
