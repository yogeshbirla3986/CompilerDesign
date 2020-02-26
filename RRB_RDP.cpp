#include<iostream>
#include<bits/stdc++.h>
#include<string.h>
using namespace std;


#define End 0
#define EOL 10
#define LBrac 2
#define RBrac 3
#define PLUS 4
#define Minus 5
#define MUL 11
#define SEMC 6
#define NUM_OR_ID 7
#define ERR -2

class tokens{
	public: int id;
		string val;	
};

int line_num;
tokens lexerFun(char **curr){

	while(1){
	
        if(**curr == ' '){
            //Eliminating HeadSpaces
            while(**curr==' '){

                (*curr)++;
            }
            //return BLANK;
        }
        else if(**curr == '\0'){
            tokens t;
            t.id=EOL;
            t.val="";
                (*curr)++;
            return t;
        }
        else{
            if (**curr == '\n'){
                cout<<endl;
                while(**curr == '\n'){
                    line_num+=1;
                    (*curr)++;
                }
            }

            tokens t;
            switch(**curr){
					//case '=': return EQ;
				case '+': {t.id = PLUS; t.val="+"; (*curr)++;return t;}
                case '*': {t.id = MUL; t.val="*"; (*curr)++;return t;}
//				case ';': {t.id = SEMC; t.val=";"; (*curr)++;return t;}
				case ')': {t.id = RBrac; t.val=")"; (*curr)++;return t;}
				case '(': {t.id = LBrac; t.val="("; (*curr)++;return t;}
			
				default:
				    if (isdigit(**curr)){
				        char *alstart=*curr;
							
						while(isdigit(**curr))
                            (*curr)++;
						
						string s;
						while(alstart!=*curr){
                            s=s+ *alstart;
                            alstart++;
						}
						tokens t1;
						t1.id = NUM_OR_ID;
						t1.val=s;
						return t1;
						}
				    else if (isalpha(**curr)){
				        char *alstart=*curr;
						
                        while(isalpha(**curr))
                            (*curr)++;
							
						string a;
						while(alstart!=*curr){
                            a=a+ *alstart;
                            alstart++;
				        }
						tokens t2 ;
						t2.id = NUM_OR_ID;
						t2.val=a;
						return t2;
				    }
            }//switch
	   }//elseif
	}//while		
}

//SDT all functions ...........
bool E(char []);
bool F(char []);
bool E1(char []);
bool E2(char []);
bool F(char []);
bool G(char []);
int i,size1;

bool G(char *str){

	if(*(str+i) <= 122 && *(str+i) >= 97){
		i += 1;
		return true;
	}
	if(*(str+i) == '('){
		int temp = i;
		i += 1;
		if(G(str) == true && *(str+i) == ')'){
			i += 1;
			return true;
		}
		else{
			i -= 1;
			return false;
		}

	}
	else{
		i -= 1;
		return false;
	}
}


bool F(char *str){

	if(i >= size1){
		return true;
	}
	else if(*(str+i) == '('){

		int temp = i-1;

/*
		if(G(str)){
			i -= 1;
			Gr(str);
			return true;
		}
		else{
			i -= 1;
		}
*/

		i += 1;
		E(str);

		   if(*(str+i) == ')'){

			i += 1;
			
			if(temp >= 0 && (*(str+temp) == '*' || *(str+temp) == '/')){
				return true;
			}
			else if(i < size1 && (*(str+i) == '*' || *(str+i) == '/')){
				return true;
			}
			else{
				*(str+temp+1) = '\0';
				*(str+i-1) = '\0';
				return true;
			}
		}
		else{
			return false;
		}
		
	}
	else if(*(str+i) >= 97 && *(str+i) <=122){
	//	cout << *(str+i);
		i += 1;
		return true;
	}
	else{
		return false;
	}

}

bool E2(char str[]){

	if(i >= size1){
		return true;
	}
	else if(*(str+i) == '*'){

	//	cout << "*";
		i += 1;
		if(F(str) == false){
			i -= 1;
			return false;
		}
		if(E2(str) == false){
			i -= 1;
			return false;
		}

		return true;
	}
	else if(*(str+i) == '/'){

		//cout << "/";
		i += 1;
		if(F(str) == false){
			i -= 1;
			return false;
		}
		if(E2(str) == false){
			i -= 1;
			return false;
		}
		return true;
	}
	else{
		return true;
	}
}

bool T(char str[]){
	
	if(i >= size1){
		return true;	
	}
	if(F(str) == false){
		return false;
	}
	if(E2(str) == false){
		return false;
	}

	return true;
}

bool E1(char str[]){

	if(i >= size1){
		return true;	
	}
	else if(*(str+i) == '+'){

		i += 1;
	//	cout << "+";
		if(T(str) == false){
			i -= 1;
			return false;
		}
		if(E1(str) == false){
			i -= 1;
			return false;
		}

		return true;
	}
	else if(*(str+i) == '-'){
		
	//	cout << "-";
		i += 1;
		if(T(str) == false){
			i -= 1;
			return false;
		}
		if(E1(str) == false){
			i -= 1;
			return false;
		}

		return true;
	}
	else{
		return true;
	}
}


bool E(char *str){

	if(i >= size1){
		return true;
	}
	if(T(str) == false){
		return false;
	}
	if(E1(str) == false){
		return false;
	}

	return true;
}


//grammer = {'E': ['TE1'], 'E1': ['+TE1', '-TE1', 'e'], 'T': ['FE2'], 'E2': ['*FE2', '/FE2', 'e'], 'F': ['(E)', 'I']}

int main(){

	string temp;
	cout << "Enter a string \n";
	getline(cin, temp);

	char test_inp[temp.length()];

	strcpy(test_inp, temp.c_str());

	i = 0;
	size1 = temp.length();

	if(E(test_inp)){
		cout << "parsing completed without any error \n";
		cout << "output string : ";
		for(int i=0;i<size1;i++){
			cout << test_inp[i];
		}
		cout << endl;
	}
	else{
		cout << "given string is invalid \n";
	}
    cout<<endl;
    

    return 0;
}
	
	
	
