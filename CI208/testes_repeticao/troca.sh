#/bin/bash

function swap() {
    echo "Moving $clean to $1..."
    mv $clean $1
    echo "Done."
}

clean=clean_$1
if [ -a $clean ]; then
        echo "File $string exists..."
        swap $1
else
    echo "Clean file does not exist, running Java cortaAspas..."
    java cortaAspas $1
    if [ -a $clean ]; then
        echo "File $string exists..."
        swap $1
    else
        echo "An error ocurred."
    fi
fi
echo "Compilando $1 para a.out..."
g++ $1
