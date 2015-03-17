
do
    local vec1 = fso.vector(1, 2, 3)
    local vec2 = fso.vector(3, 2, 1)

    local result = vec1 + vec2

    assert(result.x == 4)
    assert(result.y == 4)
    assert(result.z == 4)
end

do
    local vec1 = fso.vector(1, 2, 3)
    local vec2 = fso.vector(3, 2, 1)

    local result = vec1 - vec2

    assert(result.x == -2)
    assert(result.y == 0)
    assert(result.z == 2)
end

do
    local vec1 = fso.vector(1, 2, 3)
    local vec2 = fso.vector(3, 2, 1)

    local result = vec1 * vec2

    assert(result.x == 3)
    assert(result.y == 4)
    assert(result.z == 3)
end

do
    local vec1 = fso.vector(3, 6, 9)
    local vec2 = fso.vector(3, 3, 3)

    local result = vec1 / vec2

    assert(result.x == 1)
    assert(result.y == 2)
    assert(result.z == 3)
end
