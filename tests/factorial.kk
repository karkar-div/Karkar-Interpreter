
function factorial (int x) => int:
	if x == 0 or x == 1:
		return 1;
	return x * factorial(x-1);

function main():
	factorial(5);