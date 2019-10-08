global = {}

global.name = "Pioneers Game Engine"
global.description =
[=[
Copyright (c) 2019 DL.
This is a real-time tactics game engine, created by DL.
You can contact me via myownroc@163.com.]=]
global.version = "0.0.0"

function global.getInfo()
    return global.name .. "\n" .. global.description .. "\n" .. "Current version: " .. global.version
end

function global.showInfo()
    message(global.getInfo())
end