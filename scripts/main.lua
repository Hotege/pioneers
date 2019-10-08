function main()
    -- create window
    icon = loadImage(data.icon, data.encrypted)
    createWindow(icon)
    scene.object = scene_title.initialize()
    -- main loop
    while (not windowShouldClose()) do
        if (scene.verify()) then
            scene.object.render()
        else
            destroyWindow()
            break
        end
        windowEventsHandler()
    end
end