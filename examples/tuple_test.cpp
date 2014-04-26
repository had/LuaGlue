#include <LuaGlue/LuaGlue.h>

class TupleTester {
	public:
		int abc;
		TupleTester() { printf("%p ctor!\n", this); }
		~TupleTester() { printf("dtor!\n"); }
		std::tuple<int, double, std::string> tuplify(int a, double b, std::string c)
		{
			printf("a: %d, b: %f, c: %s\n", a, b, c.c_str());
            return std::make_tuple(a,b,c);
		}
};

int main(int, char **)
{
	LuaGlue state;
	
	auto &Class = state.Class<TupleTester>("TupleTester").
		ctor("new").
		method("tuplify", &TupleTester::tuplify);
		
	state.open().glue();
	
	printf("running lua script!\n");
	if(!state.doFile("tuple_test.lua"))
	{
		printf("failed to dofile: tuple_test.lua\n");
		printf("err: %s\n", state.lastError().c_str());
	}
	
	
	return 0;
}
