scene_title = {}
scene_title.background = nil

function scene_title.initialize()
    scene_title.background = loadImage(data.title.image, data.encrypted)
    return scene_title
end

function scene_title.render()
    clearScene(0.0, 0.5, 0.5, 1.0)
end