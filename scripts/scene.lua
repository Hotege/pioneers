scene = {}
scene.title = "Pioneers"
scene.width = 800
scene.height = 600
scene.object = nil

function scene.verify()
    typeSceneObject = type(scene.object)
    if (typeSceneObject == "table") then
        typeRender = type(scene.object.render)
        if (typeRender == "function") then
            return true
        else
            message("Error: render function type error, current is " .. typeRender .. ".")
            return false
        end
    else
        message("Error: scene type error, current is " .. typeSceneObject .. ".")
        return false
    end
end