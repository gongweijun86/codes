//1 //////////
/*unscure*/
#define CUBE(X) ((X) * (X) *(X))
/*CUBE(++i)*/
/*secure*/
inline int cube(int i)
{return i * i * i;}
//2/////////
#define static_assert(e) \
	typedef char JOIN(assertion_failed_at_line_, __LINE__) [(e) ? 1 : -1]
#define JOIN(x, y) x ## y
//----
#define JOIN(x, y) JOIN_AGAIN(x, y)
#define JOIN_AGAIN(x, y) x ## y
//3/////////
// ??= -> #	??) -> ]	??! -> |
// ??( -> [	??' -> ^	??> -> }
// ??/ -> \	??< -> {	??- -> ~
// what is the value of a now??/
a++;
/* a++ will not exetuted ,because ??/ -> \ */
//4/////////
#define swap(x, y) \
	tmp = x; \
	x = y; \
	y = tmp
/*
	if (z == 0)
		swap(x, y);
->
	if (z == 0)
		tmp = x;
	x = y;
	y = tmp;
*/
#define swap(x, y) \
	do { \
		tmp = x; \
		x = y; \
		y = tmp; } \
	while(0)
//5/////////

