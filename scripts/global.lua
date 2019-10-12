global = {

    name = "Pioneers Game Engine",
    description =
[=[
Copyright (c) 2019 DL.
This is a real-time tactics game engine, created by DL.
You can contact me via myownroc@163.com.]=],
    version = "0.0.0",

    getInfo = function()
        return global.name .. "\n" .. global.description .. "\n" .. "Current version: " .. global.version
    end,

    showInfo = function()
        message(global.getInfo())
    end,
}