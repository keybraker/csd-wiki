
N=8;
row = [];
col = [];
diag1 = [];
diag2 = [];

function print_board() {
	for (i=0; i < N; ++i)
	{
		for (j=0; j < N; ++j)
		{
			if (col[i] == j)
				print(" Q");
			else
				print(" .");
		}
		print("\n");
	}
	print("\n");

	return 0;
}

function try(c) {
	if (c == N)
		print_board();
	else
	{
		for (r=0; r < N; ++r)
		{
			if ((row[r] == 0) and (diag1[r+c] == 0) and (diag2[r+7-c] == 0))
			{
				row[r]=1;
				diag1[r+c]=1;
				diag2[r+7-c]=1;
				
				col[c]=r;
				try(c+1);
				
				row[r]=0;
				diag1[r+c]=0;
				diag2[r+7-c]=0;
			}
		}
	}
}


for (i=0; i < N; ++i)
{
	row[i]=0;
	col[i]=0;
}

for (i=0; i < 2*N-1; ++i)
{
	diag1[i]=0;
	diag2[i]=0;
}

try(0);

