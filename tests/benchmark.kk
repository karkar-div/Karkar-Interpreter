function add(int x) => int :
	if x == 0:
		return 0;
	return x + add(x-1);

function main () :
	add(5000);