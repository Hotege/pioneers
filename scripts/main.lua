function main()
    -- load font
    fontInitialize(data.font, data.encrypted)
    -- create window
    icon = loadImage(data.icon, data.encrypted)
    createWindow(icon)
    -- load shaders
    shadersInitialize(shaders)
    -- prepare scene
    scene.object = scene_title:new(nil)
    -- main loop
    while (not windowShouldClose()) do
        if (scene.verify()) then
            scene.object:render()
        else
            print("verification failed")
            destroyWindow()
            break
        end
        windowEventsHandler()
    end
    scene.object:release()
    shadersTerminate()
    fontTerminate()
end