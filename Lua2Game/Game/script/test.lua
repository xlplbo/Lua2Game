Include("\\script\\test1.lua")

function main(szName, num1, num2)
	print("main()", szName, num1, num2);
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