An interpreter of a custom programming language with built-in fraction type.

Done for the purpose of the compilation techniques classes at university.

### TODO:
* Add project building tools to the repository
* Refactor, including:
  - Storing the operators in the expression classes as enums, not as strings.
  - ArithmeticExpression -> AdditiveExpression, LogicalExpression -> OrExpression,
    add inheritance with new classes ArithmeticExpression and LogicalExpression as the base classes.
  - Split Multiplicable and Comparable to multiple classes storing different kinds of expressions.
  - Move keywords map initializater to the constructor of the Scanner.
  - Consider creating a Scope at the moment of the creation of the FunctionScope and putting function arguments there
    instead of putting them in the FunctionScope object.
  - Consider passing all defined functions to the constructor of the Environment, what would be done during the parsing of the
    declarations block.
  
