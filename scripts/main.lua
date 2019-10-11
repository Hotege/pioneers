function main()
    -- create window
    icon = loadImage(data.icon, data.encrypted)
    createWindow(icon)
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
end