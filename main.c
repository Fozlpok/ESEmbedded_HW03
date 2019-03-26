void reset_handler(void)
{
	int a=1;
	a=fun1(a);
		
}

int fun1(int a)
{
	a*=2;
	a=fun2(a);
	return a;
}
int fun2(int a)
{
	a*=2;
	return a;

} 
