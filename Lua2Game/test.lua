function main(szName, num1, num2)
	print("main()", szName, num1, num2);
	local nRet = SayHello(szName, num1, num2);
	print("nRet =", nRet);
	local nRand = math.random(100);
	print("nRand =", nRand)
	if nRand > 80 then
		StopGame();
	end
	return 1;
end