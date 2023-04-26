%{
#include <stdio.h>
#include <stdlib.h>

enum tnumber {
	TEOF, TNOT, TNOTEQU, TMOD, TMODASSIGN, TIDENT, TNUMBER,
	TAND, TLPAREN, TRPAREN, TMUL, TMULASSIGN, TPLUS,
	TINC, TADDASSIGN, TCOMMA, TMINUS, TDEC, TSUBASSIGN,
	TDIV, TDIVASSIGN, TSEMICOLON, TLESS, TLESSE, TASSIGN,
	TEQUAL, TGREAT, TGREATE, TLBRACKET, TRBRACKET, TCONST,
	TELSE, TIF, TINT, TRETURN, TVOID, TERROR,
	TWHILE, TLBRACE, TOR, TRBRACE,
};

%}
letter	[a-zA-Z_]
digit	[0-9]
%%
"+"	return(TPLUS);
"-"	return(TMINUS);
"*"	return(TMUL);
"/"	return(TDIV);
"%"	return(TMOD);
","	return(TCOMMA);
";"	return(TSEMICOLON);
"("	return(TLPAREN);
")"	return(TRPAREN);
"["	return(TLBRACKET);
"]"	return(TRBRACKET);
"{"	return(TLBRACE);
"}"	return(TRBRACE);
"="	return(TASSIGN);
"=="	return(TEQUAL);
"!="	return(TNOTEQU);
"<"	return(TLESS);
"<="	return(TLESSE);
">"	return(TGREAT);
">="	return(TGREATE);


"++" return(TINC);
"+=" return(TADDASSIGN);
"--" return(TDEC);
"-=" return(TSUBASSIGN);

void return(TVOID);
int	return(TINT);
while	return(TWHILE);
if	return(TIF);

{letter}({letter}|{digit})*	return(TIDENT);
{digit}+	return(TNUMBER);

[ \t\r]	;
.	return(TERROR);
%%
void main()
{
	enum tnumber tn;
	printf("Start of Lex\n");
	while ((tn = yylex()) != TEOF) {
		switch (tn) {
		case TNUMBER: printf("Number: %d\n", atoi(yytext)); break;
		case TIDENT: printf("Identifier: %s\n", yytext); break;
		case TERROR: printf("Error: %c\n", yytext[0]); break;
		case TPLUS: printf("Add_op\n"); break;
		case TMINUS: printf("Sub_op\n"); break;
		case TMUL: printf("Mul_op\n"); break;
		case TDIV: printf("Div_op\n"); break;
		case TMOD: printf("Mod_op\n"); break;
		case TCOMMA: printf("Comma\n"); break;
		case TSEMICOLON: printf("Semicolon\n"); break;
		case TLPAREN: printf("Begin Parent\n"); break;
		case TRPAREN: printf("End Parent\n"); break;
		case TLBRACKET: printf("Begin Bracket\n"); break;
		case TRBRACKET: printf("End Bracket\n"); break;
		case TLBRACE: printf("Begin Brace\n"); break;
		case TRBRACE: printf("End Brace\n"); break;
		case TASSIGN: printf("Assign\n"); break;
		case TEQUAL: printf("Equal\n"); break;
		case TNOTEQU: printf("Not Equal\n"); break;
		case TLESS: printf("Less\n"); break;
		case TLESSE: printf("Less Equal\n"); break;
		case TGREAT: printf("Great\n"); break;
		case TGREATE: printf("Great Equal\n"); break;
		case TINC: printf("Increase\n"); break;
		case TADDASSIGN: printf("Add Assign\n"); break;
		case TDEC: printf("Decrease\n"); break;
		case TSUBASSIGN: printf("Sub Assign\n"); break;
		case TVOID: printf("Void Symbol\n"); break;
		case TINT: printf("Int Symbol\n"); break;
		case TWHILE: printf("While Symbol\n"); break;
		case TIF: printf("If Symbol\n"); break;
		}
	}
}

int yywrap()
{
	printf("End of Lex\n");
	return 1;
}
