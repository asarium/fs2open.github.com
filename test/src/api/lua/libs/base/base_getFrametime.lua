
local a = ba.getFrametime()
assert(a == 2.0)

local b = ba.getFrametime(true)
assert(b == 1.0)
