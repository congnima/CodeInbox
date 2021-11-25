local function b()
	local x = coroutine.yield()
	print('function b after yield', x)
end

co = coroutine.create(function()
	for i=1,10 do
		print('-i: ', i)
		b()
		print('i-: ', i)
	end
end)
coroutine.resume(co)

print('---------------------')
coroutine.resume(co)
print('*********************')
