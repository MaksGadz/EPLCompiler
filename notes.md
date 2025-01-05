
# Types
- Integer, FloatingPoint
- Character
- Arrays

# Functions


# Expressions (Evaluates to smth.)
- Plus, Minus, Multiplikation, Division, Modulo
- Vergleichsoperationen
- Return

# Statements
- For-Loops, While-Loops
- If-Else
- Variablenzuweisungen


# GRAMMAR
```
    program ::= integer function main () { var_def* stmt* }
  typed_var ::= type ID
    var_def ::= typed_var = literal NEWLINE
   func_def ::= type function ([typed_var [, typed_var]*]{0,1}) [-> type]{0,1}
  func_body ::= {[var_def] stmt+}
       type ::= INTEGER | CHAR | FLOAT | BOOL
    literal ::= None | True | False | INTEGER | IDSTRING | STRING
```

# Context-Free Grammar
```

    program ::= integer function main () { var_def_rep stmt_rep }

var_def_rep ::= var_def var_def_rep | ε
    var_def ::= typed_var = literal NEWLINE
  
  typed_var ::= type ID

```