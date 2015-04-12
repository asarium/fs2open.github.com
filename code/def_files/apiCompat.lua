
-- This controls how specific functions will be redirected
local redirects = {
    ba = {
        GameEvents = {
            __index = "get",
            __len = "count"
        },
        GameStates = {
            __index = "get",
            __len = "count"
        }
    }
}

-- "Forward definitions"
local getRedirector = nil
local fillMetatable = nil

fillMetatable = function(metatable, redirDef, original)
    metatable.__index = function(_, key)
        if (redirDef.__index) then
            -- Use the supplied index operator
            return original[redirDef.__index](key)
        end

        local redir = redirDef[key]
        if (redir == nil) then
            return original[key]
        end

        if (type(redir) == "string") then
            -- Simple redirection from one index to another
            return original[redir]
        else
            return getRedirector(redir, original[key])
        end
    end

    metatable.__newindex = function(_, key, value)
        original[key] = value
    end

    metatable.__len = function(_)
        local orig = redirDef.__len
        if (orig == nil) then
            error("No # operator available here!")
        else
            return original[redirDef.__len]()
        end
    end
end

getRedirector = function(redirDef, original)
    local redirector
    if (redirDef.__len) then
        -- HACK: newproxy circumvents the Lua 5.1 limitation that
        -- tables can't have __len in their metatable
        local proxy = newproxy(true)
        local metatable = getmetatable(proxy)
        fillMetatable(metatable, redirDef, original)

        redirector = proxy
    else
        local mt = {}
        fillMetatable(mt, redirDef, original)

        redirector = setmetatable({}, mt)
    end

    return redirector
end

-- Just another redirector
local environment = getRedirector(redirects, _G)

return function(f)
    setfenv(f, environment)
end
