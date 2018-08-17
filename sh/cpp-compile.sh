if [[ $# < 1 ]]; then
	echo "Not enough arguments";
	echo "Exiting program";
	exit 1;
fi

filename=$1

g++ -c "${filename}.cpp";
echo "Compile step 1"
g++ "${filename}.o" -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system;
echo "Compiled to program!!"
