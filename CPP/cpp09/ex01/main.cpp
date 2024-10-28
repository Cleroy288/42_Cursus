#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc == 2) {
		if (!parsing(argv[1])) {
			return 1;
		}
		if (!executeRPN(argv[1])) {
			PrintErr("I cannot resolve this");
		}
	}
	else {
		printS("Wrong number of arguments");
		return 1;
	}
	return 0;
}
