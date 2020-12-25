a = b = c = d = e = f = 1;

x = a < b or c > d and e < f;

y = not x and x or a;

x = x and (function (){ return false;})(2) or (function(){return true;});

if (a or b or (y = x)) {
	for (local i = 0; i < 5 and a; ++i) {
		print(i);
		continue;	
		++i;
	}
	print(y);
}
else
	while (not y) {
		print(not y);
		break;
	}
