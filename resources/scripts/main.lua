function componentMovable(obj)
	if core:isKeyPressed(KB_A) then 
		obj:getComponentDrawable():move(-1.0, 0.0)
	elseif core:isKeyPressed(KB_D) then 
		obj:getComponentDrawable():move(1.0, 0.0)
	end
end

function onEngineSetup()
	core:loadTexture("test", "test1.png")

	level:addLayer("base")
	base = level:getMapIdFromName("base")
	level:spawnObjectTag(base, "Player", "Player")
end

function onObjectCreate(obj)
	if obj:getType() == "Player" then
		obj:addComponent("componentMovable")
		obj:addComponent("componentDrawable")

		componentDrawable = obj:getComponentDrawable()
		componentDrawable:setTexture("test")
		componentDrawable:setTextureRect(0, 0, 32, 32)
	end
end

function onGUI()
end