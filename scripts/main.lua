function main()
    createWindow()
    scene.object = scene_title
    while (not windowShouldClose()) do
        typeSceneObject = type(scene.object)
        if (type(scene.object) == "table") then
            typeRender = type(scene.object.render)
            if (typeRender == "function") then
                scene.object.render()
            else
                message("Error: render function type error, current is " .. typeRender .. ".")
                destroyWindow()
                break
            end
        else
            message("Error: scene type error, current is " .. typeSceneObject ..".")
            destroyWindow()
            break
        end
        windowEventsHandler()
    end
end