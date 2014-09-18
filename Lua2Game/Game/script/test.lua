Include("\\script\\test1.lua")

g_TEST_VALUE = 111111;  --重名定义
function main(szName, num1, num2)
	print("main()", szName, num1, num2);
	print("main g_TEST_VALUE  =", g_TEST_VALUE)
	local nRet = SayHello(szName, num1, num2);
	print("nRet =", nRet);
	local nRand = math.random(10000);
	print("nRand =", nRand)
	test();
	if nRand > 9999 then
		StopGame();
	end
	return 1;
end

function fortest(name, num1, num2)
	print("fortest g_TEST_VALUE  =", g_TEST_VALUE)
	print("fortest()", name, num1, num2);
end