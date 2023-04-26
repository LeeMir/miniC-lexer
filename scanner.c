#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum tsymbol {
	tnull = -1,
	tnot, tnotequ, tmod, tmodAssign, tident, tnumber,
	tand, tlparen, trparen, tmul, tmulAssign, tplus,
	tinc, taddAssign, tcomma, tminus, tdec, tsubAssign,
	tdiv, tdivAssign, tsemicolon, tless, tlesse, tassign,
	tequal, tgreat, tgreate, tlbracket, trbracket, teof,
	tconst, telse, tif, tint, treturn, tvoid,
	twhile, tlbrace, tor, trbrace
};

#define NO_KEYWORDS 7
#define ID_LENGTH 12

char id[ID_LENGTH];

struct tokenType {
	int number;
	union {
		char id[ID_LENGTH];
		int num;
	} value;
} a;

char* keyword[NO_KEYWORDS] = {
	"const", "else", "if", "int", "return", "void", "while"
};

enum tsymbol tnum[NO_KEYWORDS] = {
	tconst, telse, tif, tint, treturn, tvoid, twhile
};

void lexicalError(int n)
{
	printf(" *** Lexical Error : ");
	switch (n) {
	case 1:
		printf("an identifier length must be less than 12.\n");
		break;
	case 2:
		printf("next character must be &.\n");
		break;
	case 3:
		printf("next character must be |.\n");
		break;
	
	case 4:
		printf("invalid character!!!\n");
		break;
	}
}

int superLetter(char ch)
{ 
	if (isalpha(ch) || ch == '_') return 1;
	else return 0;
}

int superLetterOrDigit(char ch)
{
	if (isalnum(ch) || ch == '_') return 1;
	else return 0;
}

int hexValue(char ch)
{
	switch (ch) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return (ch - '0');
		
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			return (ch - 'A' + 10);

		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			return (ch - 'a' + 10);

		default: return - 1;
	}
}

int getIntNum(char firstCharacter)
{
	int num = 0;
	int value;
	char ch;

	if (firstCharacter != '0') {
		ch = firstCharacter;
		do {
			num = 10*num + (int)(ch - '0');
			ch = getchar();
		} while (isdigit(ch));
	} else {
		ch = getchar();
		if ((ch >= '0') && (ch <= '7'))
			do {
				num = 8*num + (int)(ch - '0');
				ch = getchar();
			} while ((ch >= '0') && (ch <= '7'));
		else if ((ch == 'X') || (ch == 'x')) {
			while ((value=hexValue(ch=getchar())) != -1)
				num = 16*num + value;
		}
		else num = 0;
	}
	ungetc(ch, stdin);
	return num;
}

struct tokenType scanner()
{
	struct tokenType token;
	int i, index;
	char ch, id[ID_LENGTH];
	token.number = tnull;
	
	do {
		while (isspace(ch = getchar()));
		if (superLetter(ch)) {
			i = 0;
			do {
				if (i < ID_LENGTH) id[i++] = ch;
				ch = getchar();
			} while (superLetterOrDigit(ch));

			if (i >= ID_LENGTH) lexicalError(1);
			id[i] = '\0';
			ungetc(ch, stdin);

			for (index = 0; index < NO_KEYWORDS; index++)
				if (!strcmp(id, keyword[index])) break;
			if (index < NO_KEYWORDS)
				token.number = tnum[index];
			else {
				token.number = tident;
				strcpy(token.value.id, id);
			}
		}
		else if (isdigit(ch)) {
			token.number = tnumber;
			token.value.num = getIntNum(ch);
		}
		else switch (ch) {
		case '/':
			ch = getchar();
			if (ch == '*')
				do {
					while (ch != '*') ch = getchar();
					ch = getchar();
				} while (ch != '/');
			else if (ch == '/')
				while (getchar() != '\n');
			else if (ch == '=') token.number = tdivAssign;
			else {
				token.number = tdiv;
				ungetc(ch, stdin);
			}
			break;
		case '!':
			ch = getchar();
			if (ch == '=') token.number = tnotequ;
			else {
				token.number = tnot;
				ungetc(ch, stdin);
			}
			break;
		case '%':
			ch = getchar();
			if (ch == '=')
				token.number = tmodAssign;
			else {
				token.number = tmod;
				ungetc(ch, stdin);
			}
			break;
		case '&':
			ch = getchar();
			if (ch == '&')
				token.number = tand;
			else {
				lexicalError(2);
				ungetc(ch, stdin);
			}
			break;
		case '*':
			ch = getchar();
			if (ch == '=')
				token.number = tmulAssign;
			else {
				token.number = tmul;
				ungetc(ch, stdin);
			}
			break;
		case '+':
			ch = getchar();
			if (ch == '+')
				token.number = tinc;
			else if (ch == '=')
				token.number = taddAssign;
			else {
				token.number = tplus;
				ungetc(ch, stdin);
			}
			break;
		case '-':
			ch = getchar();
			if (ch == '-')
				token.number = tdec;
			else if (ch == '=')
				token.number = tsubAssign;
			else {
				token.number = tminus;
				ungetc(ch, stdin);
			}
			break;
		case '<':
			ch = getchar();
			if (ch == '=')
				token.number = tlesse;
			else {
				token.number = tless;
				ungetc(ch, stdin);
			}
			break;
		case '=':
			ch = getchar();
			if (ch == '=')
				token.number = tequal;
			else {
				token.number = tassign;
				ungetc(ch, stdin);
			}
			break;
		case '>':
			ch = getchar();
			if (ch == '=')
				token.number = tgreate;
			else {
				token.number = tgreat;
				ungetc(ch, stdin);
			}
			break;
		case '|':
			ch = getchar();
			if (ch == '|')
				token.number = tor;
			else {
				lexicalError(3);
				ungetc(ch, stdin);
			}
			break;
		case '(': token.number = tlparen; break;
		case ')': token.number = trparen; break;
		case ',': token.number = tcomma; break;
		case ';': token.number = tsemicolon; break;
		case '[': token.number = tlbracket; break;
		case ']': token.number = trbracket; break;
		case '{': token.number = tlbrace; break;
		case '}': token.number = trbrace; break;
		case EOF: token.number = teof; break;
		default: {
			printf("Current character : %c", ch);
			lexicalError(4);
			break;
		}

		}
	} while (token.number == tnull);
	return token;
}

void main()
{
	while (1) {
		a = scanner();
		if (a.number == teof) break;
		switch (a.number) {
			case tnumber: printf("Number: %d\n", a.value.num); break;
			case tident: printf("Identifier: %s\n", a.value.id); break;
			case tplus: printf("Add_op\n"); break;
			case tminus: printf("Sub_op\n"); break;
			case tmul: printf("Mul_op\n"); break;
			case tdiv: printf("Div_op\n"); break;
			case tmod: printf("Mod_op\n"); break;
			case tcomma: printf("Comma\n"); break;
			case tsemicolon: printf("Semicolon\n"); break;
			case tlparen: printf("Begin Parent\n"); break;
			case trparen: printf("End Parent\n"); break;
			case tlbracket: printf("Begin Bracket\n"); break;
			case trbracket: printf("End Bracket\n"); break;
			case tlbrace: printf("Begin Brace\n"); break;
			case trbrace: printf("End Brace\n"); break;
			case tassign: printf("Assign\n"); break;
			case tequal: printf("Equal\n"); break;
			case tnotequ: printf("Not Equal\n"); break;
			case tless: printf("Less\n"); break;
			case tlesse: printf("Less Equal\n"); break;
			case tgreat: printf("Great\n"); break;
			case tgreate: printf("Great Equal\n"); break;
			case tinc: printf("Increase\n"); break;
			case taddAssign: printf("Add Assign\n"); break;
			case tdec: printf("Decrease\n"); break;
			case tsubAssign: printf("Sub Assign\n"); break;
			case tvoid: printf("Void Symbol\n"); break;
			case tconst: printf("Const Symbol\n"); break;
			case tint: printf("Int Symbol\n"); break;
			case twhile: printf("While Symbol\n"); break;
			case tif: printf("If Symbol\n"); break;
		}
	}
}
