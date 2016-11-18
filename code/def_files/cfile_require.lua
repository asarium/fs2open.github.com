local exts = {
    "",
    ".lua",
    ".lc"
}

local function cfileLoader(name)
    local file = nil

    for i,v in ipairs(exts) do
        file = cf.openFile(name .. v, "r", "data/scripts")

        if (file:isValid()) then
            name = name .. v
            break;
        end
    end

    if (file == nil or not file:isValid()) then
        return "Module '" .. name .. "' is not known by the CFile system"
    end

    local content = file:read("*a")
    file:close()

    local func, err = loadstring(content, name)

    if err then
        return err
    end

    return func
end

table.insert(package.loaders, 2, cfileLoader)
