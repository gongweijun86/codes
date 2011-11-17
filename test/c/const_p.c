int fun(const char**p)
{}

int
main()
{
	char **p;
	fun((const char**)p);
}
