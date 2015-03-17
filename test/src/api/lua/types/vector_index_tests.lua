
local vec = fso.vector(1, 2, 3)

assert(vec.x == 1)
assert(vec.y == 2)
assert(vec.z == 3)

assert(vec[1] == 1)
assert(vec[2] == 2)
assert(vec[3] == 3)

vec = fso.vector(1, 2, 3)

vec.x = 10
vec.y = 20
vec.z = 30
assert(vec.x == 10)
assert(vec.y == 20)
assert(vec.z == 30)

vec = fso.vector(1, 2, 3)

vec[1] = 100
vec[2] = 200
vec[3] = 300
assert(vec[1] == 100)
assert(vec[2] == 200)
assert(vec[3] == 300)
