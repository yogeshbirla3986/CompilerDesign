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
char *cur;
tokens lat;
void E();
void R1();
void R2();
void S();
void T();
void match(string);
void matchOp(string);

void init(char ch[]){
    cur=ch;
    lat=lexerFun(&cur); 
}

void F(){
		if(lat.val != "(" && lat.val != ")"){
		cout << lat.val;
		lat=lexerFun(&cur);
		}

}

void R1(){

    if(lat.val=="+"){
		
		match("+");
		cout << "+";
		if(lat.val == "("){
			while(lat.val == "("){ match("(");}
			
			E();
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/"){
				cout << ")";
				R2();
			}
		}
		else{
			F();
			string tmp = lat.val;
			while(lat.val == "("){ match("(");}
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/"){

				if(tmp == ")"){ cout << ")";}
				R2();
			}
		}

	}
	else if(lat.val=="-"){

		
		match("-");
		cout << "-";
		if(lat.val == "("){
			while(lat.val == "("){ match("(");}
			
			E();
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/"){
				cout << ")";
				R2();
			}
		}
		else{
			F();
			string tmp = lat.val;
			while(lat.val == "("){ match("(");}
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/"){

				if(tmp == ")"){ cout << ")";}
				R2();
			}
		}

	}

}


void R2(){

    if(lat.val=="*"){
		match("*");
		cout << "*";

		if(lat.val == "("){
			cout << "(";
			while(lat.val == "("){ match("(");}
			F();
			R1();
			cout << ")";
			while(lat.val == ")"){ match(")");}
			
			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/")
				R2();
		}
		else{
			F();
			string tmp = lat.val;
			while(lat.val == "("){ match("(");}
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/"){

				if(tmp == ")"){ cout << ")";}
				R2();
			}
			
		}
		
	}
	else if(lat.val=="/"){
		match("/");
		cout << "/";

		if(lat.val == "("){
			cout << "(";
			while(lat.val == "("){ match("(");}
			E();
			cout << ")";	
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/")
				R2();
		}
		else{
			F();
			string tmp = lat.val;
			while(lat.val == "("){ match("(");}
			while(lat.val == ")"){ match(")");}

			if(lat.val == "+" || lat.val == "-")
				R1();
			else if(lat.val == "*" || lat.val == "/"){

				if(tmp == ")"){ cout << ")";}
				R2();
			}
		}

	}

}




void T(){
    F();

	R2();


}

void match(string ch){
    if (lat.val == ch){
        lat=lexerFun(&cur);
    }
    else return;
}

void matchOp(string ch){
    if (lat.val == ch){
        lat=lexerFun(&cur);
    }
    else return;
}

void E(){

	if(lat.val=="\0"){
		return;
	}
	else if(lat.val=="("){
		while(lat.val == "("){
			match("(");
		}
		E();
		while(lat.val == ")"){
			match(")");
		}
	
		if( lat.val == "*" || lat.val == "/"){
			cout << ")";
			R2();
		}	
		else if(lat.val == "+" || lat.val == "-"){
			R1();
		}

	}
	else{

		T();

		R1();

	}

}



int main(){

	string temp;
	cout << "Enter a string \n";
	getline(cin, temp);

	char test_inp[temp.length()+1];

	strcpy(test_inp, temp.c_str());

	init(test_inp);
	E();
    cout<<endl;
    

    return 0;
}
	
	
	
