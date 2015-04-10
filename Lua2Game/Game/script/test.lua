Include("\\script\\test1.lua")

g_TEST_VALUE = 111111;  --重名定义
function main(szName, num1, num2)
	--print("main()", szName, num1, num2);
	--print("main g_TEST_VALUE  =", g_TEST_VALUE)
	--local nRet = SayHello(szName, num1, num2);
	--print("nRet =", nRet);
	--local nRand = math.random(10000);
	--print("nRand =", nRand)
	--test();
	--if nRand > 9999 then
	--	StopGame();
	--end
	--return 1;
	local tTest = {
		gdp = 1234,
		info = "this is test about exchange table data!",
		task = {12, 23, 34, 45},
	};
	local tRet = TestTable(tTest);
	printTable(tRet);
	tRet.key.capi();
end

function fortest(name, num1, num2)
	print("fortest g_TEST_VALUE  =", g_TEST_VALUE)
	print("fortest()", name, num1, num2);
end

function printTable(t, n)
	if "table" ~= type(t) then
		return 0;
	end

	n = n or 0;

	local str_space = "";
	for i = 1, n do
		str_space = str_space.."  ";
	end
	print(str_space.."{");

	for k, v in pairs(t) do
		local str_k_v = str_space.."  ["..tostring(k).."] = ";
		if "table" == type(v) then
			print(str_k_v);
			printTable(v, n + 1);
		else
			str_k_v = str_k_v..tostring(v);
			print(str_k_v);
		end
	end

	print(str_space.."}");
end
