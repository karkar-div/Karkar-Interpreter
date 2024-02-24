
# Karkar-Interpreter 
an interpreter made for the Karkar programming language. a programming language with a near syntax to python for Arabic and English

## the interpreter
1. download the .linux executable in the bin folder named as interpreter
2. you type your text file name, insure you use UTF-16 or URF8-BOM as an incoding
3. you can add the `debug` and `verbode-debug` to check the last function return value and how you program was parced via the AST
   
## The syntax
### Function declaration 
you declare a function by using the key word `function`
then you specify the name with no numbers
and you add you round brakets. in this brakets, you put your parameters, "how i can write parameters?" you do that by writing a type and then a name. "What about return types ?" you will use a thick arrow `=>` then the returned type. you finish with coloms<br/>
example:<br/> `function main () :` another example : <br/> `function add (int x,int y) => int: ` another ? <br/> `function factorial(int x) => int :`

### Blocks and Nesting
there is no crurlt brakets you can use. instead, you are provided with an indentation base nesting. Example:
```
function main () :
    while 1:
        if 4 == 2:
            ;
```
#### note: only use tabs for nesting

### Statements
there is three types,
#### conntrol flow 
like return statements `return expr;` or while statements `while expr:` or if statements `if expr:`
#### logic/math operation
like expression based statements `expr;`, the operation you can do are `=`,`+`,`-`,`/`,`*`,`%` for math; bitwize ones like `|`for OR,`&` for AND,and`^`for XOR; and logical ones using keyword like `or`and`and`
#### empty ones
Examples `;`
=======
#### 1. conntrol flow 
like return statements `return expr;` or while statements `while expr:` or if statements `if expr:`
#### 2. logic/math operation
like expression based statements `expr;`, the operation you can do are `=`,`+`,`-`,`/`,`*`,`%` for math; bitwize ones like `|`for OR,`&` for AND,and`^`for XOR; and logical ones using keyword like `or`and`and`
#### 3. empty ones
Examples `;`
#### variable declation
you need to use the `var` keyword followe by a time, there is only `int` for this time, followed by an indetifier. <br/> Example: `var int x`, you can also decare it with a value like
 `var int x = 0`


## next goals:
1. adding vectors
2. adding *.so support
3. adding bytecode formats
4. optimization
5. stabalty

this project now is not a serios one, i will be glad for feadback
