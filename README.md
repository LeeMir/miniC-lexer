# 어휘 분석기 (Lexer)

C 언어와 Lex 두 가지 방법을 이용해 어휘 분석기를 구현

## 실행 방법

### C (scanner.c)

```bash
gcc -o scanner scanner.c
./scanner < input.mc
```

### Lex (lex.l)

```bash
lex lex.l
cc lex.yy.c -o lex -ll
./lex < input.mc
```

## 예시

### 입력

```c
const int max = 500;

void main()
{
  int i = 1;
}
```

### 결과

```txt
Start of Lex
Identifier: const
Int Symbol
Identifier: max
Assign
Number: 500
Semicolon


Void Symbol
Identifier: main
Begin Parent
End Parent

Begin Brace

Int Symbol
Identifier: i
Assign
Number: 1
Semicolon

End Brace

End of Lex
```
