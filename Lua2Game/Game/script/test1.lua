Include("\\script\\test.lua")

g_TEST_VALUE = 222222;--重名定义
function test()
	print("Include(test1.lua) func test");
	print("test g_TEST_VALUE  =", g_TEST_VALUE)
	fortest("tester", 12, 1)
	--ReloadAllScript();
	return 1;
end