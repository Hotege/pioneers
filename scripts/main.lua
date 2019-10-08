function main()
    -- create window
    createWindow()
    scene_title.initialize()
    scene.object = scene_title
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