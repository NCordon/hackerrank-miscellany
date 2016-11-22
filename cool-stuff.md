# C/C++

## if/else or switch assignment

~~~
s = [&](){
    switch(i % 4){
        case 0:
            return "cero";
        case 1:
            return "uno";
        case 2:
            return "dos";
        }
    }();
        
~~~

NOTE: Does this work? Missings `break`s?
