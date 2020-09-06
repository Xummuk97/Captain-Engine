function setup()
	core:loadTexture("test", "test1.png")

	baseLayer = level:addLayer("base")
	playerObject = level:spawnObject(baseLayer, "Player")
	level:getLayer(baseLayer):removeObject(playerObject)
end

function init(obj)
	if obj:getType() == "Player" then
		obj:setTexture("test")
		obj:setTextureRect(0, 0, 32, 32)
	end
end

function update(layer, obj)
	if obj:getType() == "Player" then
		if core:isKeyPressed(KB_A) then 
			obj:move(-1.0, 0.0)
		elseif core:isKeyPressed(KB_D) then 
			obj:move(1.0, 0.0)
		end
	end
end

function draw(layer, obj)
	if obj:getType() == "Player" then
		obj:drawSprite()
	end
end

function gui()
	ImGui.beginWindow("Test Window")
	ImGui.endWindow()
end