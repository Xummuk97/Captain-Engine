function setup()
	core:loadTexture("test", "test1.png")

	level:addLayer("base")
	level:spawnObject(level:getMapIdFromName("base"), "Player")
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
end