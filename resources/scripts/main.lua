function componentMovable(obj)
	componentDrawable = obj:getComponent("componentDrawable")

	if core:isKeyPressed(KB_A) then 
		componentDrawable:move(-1.0, 0.0)
	elseif core:isKeyPressed(KB_D) then 
		componentDrawable:move(1.0, 0.0)
	end
end

function onEngineSetup()
	core:loadTexture("test", "test1.png")

	base = level:addLayer("base")
	new = level:addLayer("new")

	uid = level:spawnObject(base, "Player")
	playerId = level:getObjectInfoFromUniqueId(uid)["object"]

	level:swapObjectLayer(playerId, base, new)
end

function onObjectCreate(obj)
	if obj:getType() == "Player" then
		obj:addComponent("componentMovable")
		obj:addComponent("componentDrawable")

		componentDrawable = obj:getComponent("componentDrawable")
		componentDrawable:setTexture("test")
		componentDrawable:setTextureRect(0, 0, 32, 32)
	end
end

function onGUI()
end